#ifndef FILE_SCANNER_H
#define FILE_SCANNER_H
/**
 * A simple bounded buffer struct
 * to store the filenames for 
 * word indexing.
 **/
struct bounded_buffer {
  char** buffer;
  int buf_size;
};

/**
 * Input: a list containing files to scan
 */
int file_scanner(char* filename);

int get_numfiles(char* filename);

//global variable to be shared
struct bounded_buffer* bnd_buf;

#endif // FILE_SCANNER_H
