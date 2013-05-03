#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "index.h"
#include "bounded_buffer.h"

char * word;
char * saveptr;
FILE * file = NULL;
int line_number;

//printf("buffSize %d\n", bnd_buf->buf_size);
char temp_buffer[MAXPATH];
//fill buffer with list of file names

int file_scanner(char* filename) {


  if(file == NULL) {
	// if we haven't yet opened file, do so
	line_number = 0;
	file = fopen(filename, "r");
	while (!feof(file)) {
	  fgets(temp_buffer, MAXPATH,file);
	  line_number = line_number+1;
	  //printf("Line: %d\n", line_number);
	}

	// reset file pointer for second pass
	rewind(file);
	//initialize struct to hold file list

	buff_init(line_number);
  }

  if(fgets(temp_buffer, MAXPATH, file) == NULL) {
	fclose(file);
	return 1; 
  }

  temp_buffer[strlen(temp_buffer)-1] = '\0';
  add_filename(temp_buffer);

  // if we are at the of file, close
  return 0;
}
