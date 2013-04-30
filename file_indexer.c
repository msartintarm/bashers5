/**
   2. Takes a buffer containing filenames as input, and goes
   through it, adding all words to index
   along with the line number it appears on

   This is a 'consumer' of the bounded buffer.

   There can be more than one indexer running at one time.
*/
int file_indexer(bounded_buffer* filenames) {

  lock();
  char* filename = filenames->next_file;

  FILE* the_file = open(filename, "r");
  unsigned int line_num = 0;
  while(getc(the_file) != NULL) {
	while(strtok(the_string,"\n \t")) {

	  if(word_is_valid(the_string)) {
		insert_into_index(string, filename, line_num);
	  }
	  line_num++;
	}
  }
}

/** 
	helper function for file indexer
	over 3 chars, alphanumeric values only
	return 0 if false, nonzero if true
*/
int word_is_valid(char* the_string) {}

/**
   3. Reads a string from standard input
   and outputs the indices it appears in

   Prog should exit when user enters ctrl+D

   Also runs on a seperate thread

   Basic search: search for a single word across all files

   Advanced search: search for a word in one file
*/
