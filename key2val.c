#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "hashfn.h"

char *removeExt(char* myStr);
int main(int argc, char const *argv[])
{
    if(argc > 3 || argc < 3){
        fprintf( stderr, "Usage: filename.kv 'search term'\n");
        return 0;
    }
    // get filename.kv
    char * filename = (char*) argv[1];
    char *fn = malloc(strlen(filename)+5);
    FILE* kv = fopen(filename,"r");

    // remove .kv and get filename.khs
    char * filename2 = removeExt(filename); 
    sprintf(fn, "%s.khs", filename2); 
    FILE* khs = fopen(fn,"w");

    char* searchTerm = (char*) argv[2];
    char key[STRLEN+1];
    char val[STRLEN+1];
    int hashkey = 0;

    // get capacity 
    int capacity = get_capacity(kv);
    int index = 0;
    int j = 0;
    
    // get hash value
    hashkey = hashfn(searchTerm,capacity);
    
    for (index = 0; index< capacity;index++){
        j = index;
        // get indexes of the file 
        read_index(kv,hashkey,&j);
        read_keyval(kv,key,val);
        // read the keys 
        int kinx = read_key(kv,index,key);

        // check case scenario  
        if(kinx == j){
            printf("read key returns %d and read index reads %d\nd",kinx,j);
        }

        // search for the term if found get the value
        if(strcmp(key,searchTerm)==0){
            read_val(kv,index,val);
            printf("%s\n",val);
            return 0;
        } 
       
    }
        
    printf("NOT FOUND\n");
    fclose(kv);
    fclose(khs);
    
    return 0;
}
char *removeExt (char* myStr) {
    char *retStr;
    char *lastExt;
    if (myStr == NULL) return NULL;
    if ((retStr = malloc (strlen (myStr) + 1)) == NULL) return NULL;
    strcpy (retStr, myStr);
    lastExt = strrchr (retStr, '.');
    if (lastExt != NULL)
        *lastExt = '\0';
    return retStr;
}