
/**
 * A simple bounded buffer struct
 * to store the filenames for 
 * word indexing.
 **/
struct bounded_buffer {
  char** buffer;
  int buf_size;
};

int file_scanner(char* filename);

//global variable to be shared
struct bounded_buffer* bnd_buf;

