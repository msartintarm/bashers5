
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
void buff_init(Bounded_buffer *buffer, int size);

//bookeeping function
void buff_free(Bounded_buffer *buffer);

//return true if buffer is full
int is_full(Bounded_buffer *buffer);

//return true if buffer is empty
int is_empty(Bounded_buffer *buffer);

/**
 * Adds filename from buffer.
 * FIFO
 * If full return error code 1
 **/
int add_filename(Bounded_buffer *buffer, char* fname);

/**
 * Removes the filename from the buffer.
 * FIFO
 * @return filename
 **/
char* remove_filename(Bounded_buffer *buffer, char* fname);


