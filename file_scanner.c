#include <stdio.h>
#include <stdlib.h>
#include "index.h"
#include <string.h>

/**
 * A simple bounded buffer struct
 * to store the filenames for 
 * word indexing.
 **/
struct bounded_buffer {
  char** buffer;
  int buf_size;
};
//global variable to be shared
struct bounded_buffer* bnd_buf;

int file_scanner(char* filename) {
  
  char buffer[MAXPATH];
  FILE * file;
  //count line numbers in file list
  file = fopen(filename, "r");
  int line_number = 0;
  while (!feof(file)) {
    fgets(buffer, MAXPATH,file);
    line_number = line_number+1;
    //printf("Line: %d\n", line_number);
  }
  fclose(file);
  //initialize struct to hold file list
  bnd_buf = (struct bounded_buffer *)malloc(sizeof(struct bounded_buffer));
  bnd_buf->buffer = malloc(line_number*sizeof(char*)*MAXPATH);
  bnd_buf->buf_size = line_number;
  char temp_buffer[MAXPATH][line_number];
  //fill buffer with list of file names
  file = fopen(filename, "r");
  int i = 0;
  while (!feof(file)) {
    fgets(temp_buffer[i], MAXPATH, file);
    bnd_buf->buffer[i] = temp_buffer[i];
    //printf("Word: %s\n", bnd_buf->buffer[i]);
    i++;
  }
  fclose(file);
  
  return 0;
}



