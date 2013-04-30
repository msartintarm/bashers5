/**
   1. Takes the filename containing
   a list of files to scan, then for each
   file found, writes the name to a bounded buffer.

   With respect to the buffer, it is a 'producer'.
*/
int file_scanner(char* filename) {

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
