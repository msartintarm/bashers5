#include "line_sizer.h"

int line_sizer(char* filename) {

  FILE* file = fopen(filename, "r");

  // The distance between pointer 1 and pointer 2 is the size of the line.                    
  int curr_size = 0;
  int max_size = 0;
  char c;
  for(c = fgetc(file); c != EOF; c = fgetc(file)) {

    curr_size ++;
    if(c == '\n') {
      if(max_size < curr_size) max_size = curr_size;
      curr_size = 0;
    }
  }
  fclose(file);
  return max_size;

} //end function                                                                              
