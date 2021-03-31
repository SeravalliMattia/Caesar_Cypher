#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCAR (20) //Max number of letter per word
#define KEY (3) //Number of position a letter have to be moved
#define KEY2 (26 - KEY) 

typedef char word[MAXCAR + 1];


word *readFile(FILE *f, int *n){
	//This function can read words in a file
	int i = 0;
	int dim = 4; 
	int nElem = 0;
	char buf[60];
	word *list, *listRedim;
	
	list = malloc(dim * sizeof(*list));
	
	if(list == NULL){
		(*n) = 0;
		return NULL;
	}
	
	while (fgets(buf, sizeof(buf), f) != NULL){
		nElem = sscanf(buf, "%s", list[i]);
		
		if (nElem != 1){
			continue;
		}
		
		i += 1;
		
		if(i >= dim) {
			dim *= 2;
			listRedim = realloc(list, dim * sizeof(*list));
			
			if(listRedim == NULL){
				return NULL;
			}
			list = listRedim;
		}
	}
	
	(*n) = i;
	list = realloc(list, i * sizeof(*list));
	return list;
}



char *translateWord (char *word){
	//Function that translate the word in input
	
	char *filteredWord = malloc (MAXCAR * sizeof(char));
	
	int i, len;
	
	len = strlen(word);
	
	for(i = 0; i < len; i++){
		//Divide every word in letters and translate them one at one
		
		if((word[i] > 'c' && word[i] <= 'z') || (word[i] > 'C' && word[i] <= 'Z')){
			filteredWord[i] = word[i] - KEY;
		}else{
			filteredWord[i] = word[i] + KEY2;
		}
	}
	
	filteredWord[len] = '\0';
	return filteredWord;
}


void stampAllTranslated(word *list, int n){
	//Function that translate and print all the word in "list" 
	int i;
	
	for(i = 0; i < n; i++){
		printf("%s\n", translateWord(list[i]));
	}
}





int main(int argc, char *argv[]){

	FILE *f;
	word *list;
	int n = 0;
	
	if(!(f = fopen(argv[1], "r"))){
		perror("ERROR: File can't be loaded\n");
	}
	
	//I'll read the file
	list = readFile(f, &n);
	
	fclose (f);
	
	//Print and translate all the word in "list";
	stampAllTranslated(list, n);
	
	free(list);
	

}
