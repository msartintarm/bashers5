#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "index.h"
#include "file_indexer.h"

int search_interface() {
  char* in;//line of user input
  char* word;//word to search for
  char* file;//file to search for word
  int sameFile;//1 if file in result matches file variable, 0 otherwise
  
  while(1){
    in = (char*)malloc(130);
        
    printf("word:");
    fgets(in, 130, stdin);
        
    if(feof(stdin)){ 
      free(in);
      printf("END\n");
      return 0;
    }

    //no word inputed
    if(strcmp(in, "\n") == 0) continue;

    
    file = strtok(in, " \n");
    word = strtok(NULL, " \n");
    
    //if file isn't specified, the first arg should be the word
    if(word == NULL){
      word = file;
      file = NULL;
    }
    
    //don't bother searching for invalid words
    if(!word_is_valid(word)){
      printf("Word not found.\n");
      continue;
    }
    
    //find file in index if indexed already
    index_search_results_t* file_results;
    if(file){
      //wait for file to be indexed or for indexing to be done
      do {
        file_results = find_in_index(file);
      }
      while(!file_results && !is_done());
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
    	      //only print if file_name of result matches specified
    	      sameFile = strcmp(file, result.file_name);
    	      if(sameFile == 0){
  	        	printf("FOUND: %s %d\n", result.file_name, result.line_number + 1);
  	        }  
	        }
	      }
  	  }
    } else {
  	  printf("Word not found.\n");
    }
    if(!file_results && file != NULL) printf("ERROR: File %s not found\n", file);
    free(in);
  }
  return 0;
}
