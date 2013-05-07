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

pthread_mutex_t buff_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;

/**
 * POSIX thread functions to call
 *
 * Synchronization variable logic obtained from here:
 * http://www.stanford.edu/class/cs140/cgi-bin/lecture.php?topic=locks
 */
void* scanning_function(void* the_file) {  

  int scanning_done = 0;
  while(!scanning_done) {
    
    // Apparently this combination of locks and vars is called a _monitor_.
    pthread_mutex_lock(&buff_lock);
    while(is_full()) pthread_cond_wait(&not_full, &buff_lock);

    if(file_scanner((char*)the_file) == 1) scanning_done = 1;

    pthread_cond_signal(&not_empty);
    pthread_mutex_unlock(&buff_lock);
  }

  pthread_exit(0);// (void*) file_scanner("the_file"));
}

void* indexing_function() {

  while(!is_empty()) {
    pthread_mutex_lock(&buff_lock);
    while(is_empty()) pthread_cond_wait(&not_empty, &buff_lock);
    file_indexer();
    pthread_cond_signal(&not_full);
    pthread_mutex_unlock(&buff_lock);
  }

  pthread_exit(0);// (void*) file_indexer());
}

void* searching_function() {
  //  search_interface();
  pthread_exit(0);// (void*) search_interface());
}
/**
   Main function that creates threads
   (and may do synchronization between them).
   
   Once all threads are complete, program will terminate.
*/
int main(int argc, char* argv[]) {

  // Check for possible errors, which could include:
  // 1. wrong number of args
  if(argc != 3) { error_out(0); }
  int num_threads = atoi(argv[1]);
  // 2. not a valid thread count
  if(num_threads < 1) { error_out(0); }
  // 3. file to read from doesn't exist
  if(access(argv[2], R_OK) == -1) { error_out(1); }

  init_index();
  buff_init(20);

  // Create the threads we will use..
  pthread_t scanning_thread;
  pthread_t indexing_thread[num_threads];
  pthread_t searching_thread;

  int i;

  pthread_create(&scanning_thread, NULL, 
		 scanning_function, (void*)argv[2]);
  atexit(exit_main);
  for(i = 0; i < num_threads; ++i) {
    pthread_create(&indexing_thread[i], NULL, 
		   indexing_function, NULL);
  }

  pthread_join(scanning_thread, NULL);
  for(i = 0; i < num_threads; ++i) {
    pthread_join(indexing_thread[i], NULL);  
  }



  pthread_create(&searching_thread, NULL,
		 searching_function, NULL);
  pthread_join(searching_thread, NULL);

  exit(0);
}
