#include <file_scanner.h>
#include <stdio.h>
#include <stdlib.h>
#include "index.h"
#include <string.h>

int word_is_valid(char* the_string);

/**
   2. Takes a buffer containing filenames as input, and goes
   through it, adding all words to index
   along with the line number it appears on

   This is a 'consumer' of the bounded buffer.

   There can be more than one indexer running at one time.
*/
int file_indexer() {

  //init_index();
  FILE * file;
  int i;
  for(i = 0; i < bnd_buf->buf_size; i++){
    //printf("buff %s\n", bnd_buf->buffer[i]);
    file = fopen(bnd_buf->buffer[i], "r");
    if(file != NULL){
    //if((file = fopen(bnd_buf->buffer[i], "r"))){
      while (!feof(file)) {
        int line_number = 0;
        char * word;
        char * saveptr;
        char buffer[MAXPATH];
        fgets(buffer, sizeof(buffer),file);
        word = strtok_r(buffer, " \n\t-_!@#$%^&*;()_+=,./<>?", &saveptr);
        while (word != NULL){
         if(word_is_valid(word)){
          printf("Word is: %s\n", word);
          //insert_into_index(word, file_name, line_number);
         }
         word = strtok_r(NULL, " \n\t-_!@#$%^&*;()_+=,./<>?",&saveptr);
        }
        line_number = line_number+1;
       } //end not eof
       fclose(file);
     } //end if not null
    
   } //end for
 
  return 0;
} //end function

/** 
	helper function for file indexer
	over 3 chars, alphanumeric values only
	return 0 if false, nonzero if true
*/
int word_is_valid(char* the_string) {
  if(strlen(the_string) <= 3) return 0;
  int i;
  for(i=0; i < strlen(the_string); i++){
    int c = (int)the_string[i]; //char at index
    //if char at index is outside of the ranges of ascii alphanumeric
    //characters, the word is invalid
    if(c < 48 || (c > 57 && c < 65) || (c > 90 && c < 97) || c > 122) return 0;
  }
  return 1;
}

/**
   3. Reads a string from standard input
   and outputs the indices it appears in

   Prog should exit when user enters ctrl+D

   Also runs on a seperate thread

   Basic search: search for a single word across all files

   Advanced search: search for a word in one file
*/
