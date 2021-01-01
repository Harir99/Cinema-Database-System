#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "hashfn.h"

char *removeExt(char* myStr);
int main(int argc, char const *argv[]){ 
    if(argc != 3){
        fprintf( stderr, "Usage: %s filename.kv capacity\n",argv[0]);
        return -1;
    }
    
    // get filename.kv
    char * filename = (char*) argv[1];
    char *fn = malloc(strlen(filename)+5);
    FILE* kv = fopen(filename,"rb");

    // remove .kv and get filename.khs
    char* filename2 = removeExt(filename);

    // remove .khs and make it filename.vhs
    sprintf(fn, "%s.vhs", filename2); 
    FILE* vhs = fopen(fn,"wb+");

    sprintf(fn, "%s.khs", filename2); 
    FILE* khs = fopen(fn,"wb+");

    // declare variables 
    long long capacity = atoi(argv[2]);
    char key[STRLEN+1];
    char val[STRLEN+1];
    int hashkey = 0, hashval = 0;
    int Kindex = 0, Vindex = 0, position = 0;
   

    write_empty(khs,capacity);
    write_empty(vhs,capacity);

    while(read_keyval(kv,key,val)==2){
        hashkey = hashfn(key,capacity);
        int Kbucket = capacity + hashkey;
        while(hashkey <  Kbucket){
            // read index, and store it 
            read_index(khs,hashkey,&Kindex);
            if(Kindex == -1){
                write_index(khs,position,hashkey);
                break;
            }
            // otherwise get next index and keep going till you find requied value
            if(feof(kv)){
                rewind(kv);
            } 
            hashkey++;
        }
            
        hashval = hashfn(val,capacity);
        int Vbucket = capacity + hashval;
        while(hashval <  Vbucket){
            // read index, and store it 
            read_index(vhs,hashval,&Vindex);
            if( Vindex == -1){
                write_index(vhs,position,hashval);
                break;
            }
            // otherwise get next index and keep going till you find requied value
            if(feof(kv)){
                rewind(kv);
            } 
            hashval++;
        }
        position++; 
    }
        
    // close all files at the end of the program
    fclose(kv);
    fclose(khs);
    fclose(vhs);
    free(fn);
    return 0;
}
// remove extension from end of file
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

