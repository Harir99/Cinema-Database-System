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
    sprintf(fn, "%s.vhs", filename2); 
    FILE* vhs = fopen(fn,"w");

    // declare variables 
    char* searchTerm = (char*) argv[2];
    char key[STRLEN+1], val[STRLEN+1];
    int j = 0, index = 0, hashval = 0, capacity = 0;

    // get capacity 
    capacity = get_capacity(kv);

    for(index = 0; index < capacity;index++){
        j = index;
        // find the hash value 
        hashval = hashfn(searchTerm,capacity);
        read_index(kv,hashval,&j);
        // get the values 
        int vinx = read_val(kv,index,val);
        if(vinx == j){
           printf("read val returns %d and read index reads %d\nd",vinx,j);
       }
       // compare term with values if found get key at that index
        if(strcmp(val,searchTerm)==0){
            read_key(kv,index,key);
            printf("%s\n",key);

            return 0;
        } 
    }
    printf("NOT FOUND\n");
    fclose(kv);
    fclose(vhs);
    
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