#include <stdio.h>
#include <malloc.h>
#include "index.h"
 
/**
 * bounded buffer using circular implementation
 **/
typedef struct {
  int count;
  char** filenames;
  int size;   // maximum number of filenames
  int start;  // index of first element
  //int end;    // index at which to write new element
} Bounded_buffer;
/**
 * Initializes an empty buffer
 **/
void buff_init(Bounded_buffer *buffer, int size) {
  buffer->count = 0;
  buffer->filenames = malloc(size*sizeof(char*)*MAXPATH); //MAXPATH = 511
  buffer->size  = size;
  buffer->start = 0;
}
//bookeeping function
void buff_free(Bounded_buffer *buffer) {
  free(buffer->filenames); // can be null 
}
//return true if buffer is full
int is_full(Bounded_buffer *buffer) {
  return buffer->count == buffer->size; 
}
//return true if buffer is empty
int is_empty(Bounded_buffer *buffer) {
  return buffer->count == 0;
}
/**
 * Adds filename from buffer.
 * FIFO
 * If full return error code 1
 **/
int add_filename(Bounded_buffer *buffer, char* fname) {
  int rc = 0;
  int end = (buffer->start + buffer->count) % buffer->size;
  buffer->filenames[end] = fname;
  if (buffer->count == buffer->size) {
    fprintf(stderr, "Error: can't add to a full buffer\n");
    rc = 1;
  }
  else {
    ++buffer->count; //increment count
  }
  return rc;  
}
/**
 * Removes the filename from the buffer.
 * FIFO
 * @return filename
 **/
char* remove_filename(Bounded_buffer *buffer, char* fname) {
  fname = buffer->filenames[buffer->start];
  buffer->start = (buffer->start + 1) % buffer->size;
  --buffer->count; //decrement count
  return fname;
}

