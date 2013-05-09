#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "index.h"
#include "file_indexer.h"

int search_interface() {
  char* in;
  char* word;
  char* file;
  int sameFile;
  int fileNotFound;
    
  while(1){
    in = (char*)malloc(130);
    fileNotFound = 1;//This doesn't really work yet.
        
    printf("word:");
    fgets(in, 130, stdin);
        
    if(feof(stdin)){ 
      free(in);
      printf("END\n");
      return 1;
    }

    file = strtok(in, " \n");
    word = strtok(NULL, " \n");
    if(word == NULL){
      word = file;
      file = NULL;
      fileNotFound = 0;
    }
        
    if(!word_is_valid(word)){
      printf("Word not found.\n");
      continue;
    }
    
    index_search_results_t* results = find_in_index(word);

    if(results != NULL) {
      int i;
      for(i = 0; i < results->num_results; i++){
        index_search_elem_t result = results->results[i];
  	    
  	    if(result.line_number >= 0){//don't print file entries
    	    if(file == NULL){
    	      printf("FOUND: %s %d\n", result.file_name, result.line_number + 1);
    	    }else{
    	      sameFile = strcmp(file, result.file_name);
    	      if(sameFile == 0){
    	        fileNotFound = 0;
    	        printf("FOUND: %s %d\n", result.file_name, result.line_number + 1);
  	        }  
	        }
	      }
  	  }
    } else {
  	  printf("Word not found.\n");
    }
    if(fileNotFound) printf("ERROR: File %s not found\n", file);
    free(in);
  }
  return 0;
}
