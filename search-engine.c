#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // access
#include <pthread.h>
//#include "bounded_buffer.h"
#include "index.h"
#include "file_indexer.h"
#include "file_scanner.h"
#include "search_interface.h"

//pthread_mutex_lock(&mymutex);
//pthread_mutex_unlock(&mymutex);
pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER;

/**
 * If one of the multithreaded methods has failed,
 * 'gracefully' terminate everything else and exit.
 */
void error_out(int errnum) {
  switch(errnum) {
  case 0:
    fprintf(stderr, "Usage: ./search-enginer [num-indexer-threads] [list-of-files.txt]\n");
    exit(1);
  case 1:
    fprintf(stderr, "File scanner failed.\n");
    exit(1);
  case 2:
    fprintf(stderr, "File indexer failed.\n");
    exit(1);
  case 3: default:
    fprintf(stderr, "Search interface failed.\n");
    exit(1);
  }
}


/**
 * POSIX thread functions to call
 *
 * We will modify these to use atomic variables and / or use the bounded buffer
 */
void* scanning_function() {  
  pthread_exit(0);// (void*) file_scanner("the_file"));
}
void* indexing_function() {
  pthread_exit(0);// (void*) file_indexer());
}
void* searching_function() {
  pthread_exit(0);// (void*) search_interface());
}
/**
   Main function that creates threads
   (and may do synchronization between them).
   
   Once all threads are complete, program will terminate.
*/
int main(int argc, char* argv[]) {

  // Check for possible errors, which could include:
  // - wrong number of args
  if(argc != 3) { error_out(0); }
  int num_threads = atoi(argv[1]);
  // - not a valid thread count
  if(num_threads < 1) { error_out(0); }
  // - file to read from doesn't exist
  if(access(argv[2], F_OK) == -1) { error_out(0); }

  //  index_search_results_t* results;
  init_index();

  // Create the threads we will use..
  pthread_t scanning_thread;
  pthread_t indexing_thread[num_threads];
  pthread_t searching_thread;

  int i;

  pthread_create(&scanning_thread, NULL, scanning_function, NULL);
  for(i = 0; i < num_threads; ++i) {
    pthread_create(&indexing_thread[i], NULL, indexing_function, NULL);
  }
  pthread_create(&searching_thread, NULL, searching_function, NULL);

  pthread_join(scanning_thread, NULL);
  for(i = 0; i < num_threads; ++i) {
    pthread_join(indexing_thread[i], NULL);
  }
  pthread_join(searching_thread, NULL);

  exit(0);
}
