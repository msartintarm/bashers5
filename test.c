#include <stdio.h>
#include <stdlib.h>
#include "index.h"

int main(int argc, char * argv[])
{
  index_search_results_t * results;
  init_index();


  // adds an entry to index for [word], 
  // in [filename], at [line_number]

  insert_into_index("hello", "test.c", 10);
  insert_into_index("hello", "test.c", 20);
  insert_into_index("hello", "foo.c", 30);
  insert_into_index("goodbye", "test.c", 10);

  results = find_in_index("hello");
  if (results) {
    int i;
    for (i = 0; i < results->num_results; i++) {
      printf("%s: %d\n",
	     results->results[i].file_name,
	     results->results[i].line_number);
    }
    free(results);
  }
  find_in_index("goodbye");
  return(0);
}

/**
   1. Takes the filename containing
   a list of files to scan, then for each
   file found, writes the name to a bounded buffer.

   With respect to the buffer, it is a 'producer'.
*/
int file_scanner(char* filename) {

  FILE* the_file = open(filename, "r");
  unsigned int line_num = 0;
  while(getc(the_file) != NULL) {
	while(strtok(the_string,"\n \t")) {

	  if(word_is_valid(the_string)) {
		insert_into_index(string, filename, line_num);
	  }
	  line_num++;
	}
  }
}

/**
   2. Takes a buffer containing filenames as input, and goes
   through it, adding all words to index
   along with the line number it appears on

   This is a 'consumer' of the bounded buffer.

   There can be more than one indexer running at one time.
*/
int file_indexer(bounded_buffer* filenames) {

  lock();
  char* filename = filenames->next_file;

  FILE* the_file = open(filename, "r");
  unsigned int line_num = 0;
  while(getc(the_file) != NULL) {
	while(strtok(the_string,"\n \t")) {

	  if(word_is_valid(the_string)) {
		insert_into_index(string, filename, line_num);
	  }
	  line_num++;
	}
  }
}

/** 
	helper function for file indexer
	over 3 chars, alphanumeric values only
	return 0 if false, nonzero if true
*/
int word_is_valid(char* the_string) {}

/**
   3. Reads a string from standard input
   and outputs the indices it appears in

   Prog should exit when user enters ctrl+D

   Also runs on a seperate thread

   Basic search: search for a single word across all files

   Advanced search: search for a word in one file
*/
int search_interface() {
  if(found ==true) {
	printf("FOUND: %s %d\n", file_name, line_num);
  } else {
	printf("Word not found.\n");
}
