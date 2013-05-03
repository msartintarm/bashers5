
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
void buff_init(int size);

//bookeeping function
void buff_free();

//return true if buffer is full
int is_full();

//return true if buffer is empty
int is_empty();

/**
 * Adds filename from buffer.
 * FIFO
 * If full return error code 1
 **/
int add_filename(char* fname);

/**
 * Removes the filename from the buffer.
 * FIFO
 * @return filename
 **/
char* remove_filename(char* fname);


