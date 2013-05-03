#ifndef FILE_INDEXER_H
#define FILE_INDEXER_H
#include "file_scanner.h"

int word_is_valid(char* the_string);

/**
   2. Takes a buffer containing filenames as input, and goes
   through it, adding all words to index
   along with the line number it appears on

   This is a 'consumer' of the bounded buffer.

   There can be more than one indexer running at one time.
*/
int file_indexer();
#endif // FILE_INDEXER_H
