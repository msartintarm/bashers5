#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "index.h"
#include "file_scanner.h"
#include "bounded_buffer.h"
#include "line_sizer.h"
int done = 0;

int is_done(){
 return done;
}

void set_done(){
 done = 1;
}

int word_is_valid(char* the_string);

/**
   2. Takes a buffer containing filenames as input, and goes
   through it, adding all words to index
   along with the line number it appears on

   This is a 'consumer' of the bounded buffer.

   There can be more than one indexer running at one time.
*/

int file_indexer() {

  FILE * file;
  char* filename = malloc(sizeof(char)*MAXPATH);
  int line_number = 0;
  if(is_empty()){
    //printf("f e %d %d\n", is_empty(), is_full());
    return 1;
  }
  //get filename from buffer
  filename = remove_filename(filename);
  int max = line_sizer(filename);
  file = fopen(filename, "r");
  if(file == NULL){ return(1); }
  char buffer[max + 1];

  while (!feof(file)) {

	  char * word;
	  char * saveptr;
	  fgets(buffer, sizeof(buffer),file);
	  word = strtok_r(buffer, " \n\t", &saveptr);
	  while (word != NULL){
	    if(word_is_valid(word)){
//		  printf("buff %s eof %d word %s saveptr%s\n", buffer, feof(file), word, saveptr);
		  if(feof(file)){
		    break;
		  }
		  insert_into_index(word, filename, line_number);
	    }
	    word = strtok_r(NULL, " \n\t",&saveptr);
	  }
	  //move down a line and increment
	  line_number = line_number+1;
  } //end not eof
  line_number = 0; //reset line counter; new file
  insert_into_index(filename, "filename", -1); //hash filenames for search/indexer concurrency
  fclose(file);
return 0;
} //end function

/** 
	helper function for file indexer
	over 3 chars, alphanumeric values only
	return 0 if false, nonzero if true
*/
int word_is_valid(char* the_string) {
  if(strlen(the_string) < 3) return 0;
  int i;
  for(i=0; i < strlen(the_string); i++){
    int c = (int)the_string[i]; //char at index
    //if char at index is outside of the ranges of ascii alphanumeric
    //characters, the word is invalid
    if(c < 48 || (c > 57 && c < 65) || (c > 90 && c < 97) || c > 122) return 0;
  }
  return 1;
}
