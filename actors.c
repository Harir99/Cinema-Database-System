#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "hashfn.h"

char *removeExt (char* myStr);
int main(int argc, char const *argv[]){
   if(argc != 2){
        fprintf( stderr, "Usage: %s 'moviename'\n",argv[0]);
        return -1;
    }
    // open files 
    FILE* kv = fopen("title.principals.kv","r");
    FILE* moviename = fopen("title.basics.kv","r");
    FILE* actorsname = fopen("name.basics.kv","r");
    
    char key[STRLEN+1];
    char val[STRLEN+1];

    // get required capacity 
    int capacity = get_capacity(kv);

    // declare variables 
    int index = 0;
    int index2 = 0;
    char moviekey[STRLEN+1];
    char fullkey[STRLEN+1];
    char actorsval[STRLEN+1];
    // return to beginning of file 
    rewind(kv);

    for(index = 0; index < capacity;index++){
        read_keyval(moviename,key,val);
        hashfn(val,capacity);
        read_val(moviename,index,val);
        
        // get movie name using key 
        if(strcmp(val,argv[1]) == 0){
            read_key(moviename,index,key);
            strcpy(moviekey,key);
        }
    }
    for(index = 0; index < capacity;index++){
        // get actors values 
        read_keyval(kv,key,val);
        read_key(kv,index,key);

        if(strcmp(key,moviekey) == 0){
            
            read_val(kv,index,val);
            strcpy(actorsval,val);

            // get the names of the found actors 
            for(index2 = 0; index2 < capacity;index2++){
                read_key(actorsname,index2,fullkey);
                if(strcmp(fullkey,actorsval) == 0){
                    read_val(actorsname,index2,val);
                    printf("%s\n",val);
                }
            }
        } 
    }

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