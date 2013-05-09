#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // access
#include <pthread.h>
#include "bounded_buffer.h"
#include "index.h"
#include "file_indexer.h"
#include "file_scanner.h"
#include "search_interface.h"

//pthread_mutex_lock(&mymutex);
//pthread_mutex_unlock(&mymutex);
/**
 * If one of the multithreaded methods has failed,
 * 'gracefully' terminate everything else and exit.
 */
void error_out(int errnum) {
  switch(errnum) {
  case 0:
    fprintf(stderr, "Usage: ./search-engine [num-indexer-threads] [list-of-files.txt]\n");
    exit(1);
  case 1:
    fprintf(stderr, "File does not exist.\n");
    exit(1);
  case 2:
    fprintf(stderr, "File scanner failed.\n");
    exit(1);
  case 3:
    fprintf(stderr, "File indexer failed.\n");
    exit(1);
  case 4: default:
    fprintf(stderr, "Search interface failed.\n");
    exit(1);
  }
}

void exit_main() { buff_free(); }

int list_scanned = 0;
int buf_head = 0;
int buf_tail = 0;
const int SIZE = 10;
pthread_mutex_t fill_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t full_cv;
pthread_cond_t empty_cv;

int fill() { buf_head++; buf_head %= SIZE; return buf_head; }
int empty() { buf_tail++; buf_tail %= SIZE; return buf_tail; }
int num_elements() { return (buf_head > buf_tail)?
	buf_head - buf_tail: SIZE + buf_head - buf_tail; }

/**
 * POSIX thread functions to call
 *
 * We will modify these to use atomic variables and / or use the bounded buffer
 */
void* scanning_function(void* the_file) {  
   
  //int scanning_done = 0;
  while(!list_scanned) {
    pthread_mutex_lock(&fill_mutex);
	  while(is_full()){
	    pthread_cond_wait(&full_cv, &fill_mutex);
	  }
	  //scan a file
	  if(file_scanner((char*)the_file) == 1) list_scanned = 1;
	  if(get_count() == 1){
	    pthread_cond_signal(&empty_cv);
	  }
	  pthread_mutex_unlock(&fill_mutex);
  }
  pthread_exit(0);// (void*) file_scanner("the_file"));
}

void* indexing_function() {

  while(!list_scanned){
    pthread_mutex_lock(&fill_mutex);
    while(is_empty()) {
      pthread_cond_wait(&empty_cv, &fill_mutex);
    }
	  file_indexer();
	  //after consuming one filename there will always be an opening
	  pthread_cond_signal(&full_cv);
	  pthread_mutex_unlock(&fill_mutex);
  }
  pthread_exit(0);// (void*) file_indexer());
}

void* searching_function() {
  search_interface();
  pthread_exit(0);// (void*) search_interface());
}
/**
   Main function that creates threads
   (and may do synchronization between them).
   
   Once all threads are complete, program will terminate.
*/
int main(int argc, char* argv[]) {
  buff_init(74); //TODO change this
  // Check for possible errors, which could include:
  // - wrong number of args
  if(argc != 3) { error_out(0); }
  int num_threads = atoi(argv[1]);
  // - not a valid thread count
  if(num_threads < 1) { error_out(0); }
  // - file to read from doesn't exist
  if(access(argv[2], R_OK) == -1) { error_out(1); }

  //  index_search_results_t* results;
  init_index();

  // Create the threads we will use..
  pthread_t scanning_thread;
  pthread_t indexing_thread[num_threads];
  pthread_t searching_thread;

  int i;
  //run scan thread and index threads concurrently
  pthread_create(&scanning_thread, NULL, 
				 scanning_function, (void*)argv[2]);
  atexit(exit_main);
  //start the index threads
  for(i = 0; i < num_threads; ++i) {
    pthread_create(&indexing_thread[i], NULL, 
				   indexing_function, NULL);
  }
  pthread_join(scanning_thread, NULL);
  /*for(i = 0; i < num_threads; ++i) {
  	pthread_join(indexing_thread[i], NULL);
  }*/

  pthread_create(&searching_thread, NULL,
				 searching_function, NULL);
  pthread_join(searching_thread, NULL);
  
  return 0;
}
