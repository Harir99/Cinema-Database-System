#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "hashfn.h"
char *removeExt (char* myStr);
int main(int argc, char const *argv[]){
   if(argc != 2){
        fprintf( stderr, "Usage: %s 'actor name'\n",argv[0]);
        return -1;
    }
    // open files 
    FILE* kv = fopen("title.principals.kv","r");
    FILE* moviename = fopen("title.basics.kv","r");
    FILE* actorsname = fopen("name.basics.kv","r");
    char key[STRLEN+1];
    char val[STRLEN+1];

    // get capacity 
    int capacity = get_capacity(kv);
    int index = 0;
    int index2 = 0;

    char movieK[STRLEN+1];
    char moviekey[STRLEN+1];
    char finalmovie[STRLEN+1];
    char actorskey[STRLEN+1];
    char kevinkey[STRLEN+1];

    // go back to beginning of file 
    rewind(kv);

    for(index = 0; index < capacity;index++){
        
        read_keyval(actorsname,key,val);
        hashfn(val,capacity);
        read_val(actorsname,index,val);
        
        // get movie name using key 
        if(strcmp(val,argv[1]) == 0){
            read_key(actorsname,index,key);
            strcpy(actorskey,key);
        }
        // get movie name using key 
        if(strcmp(val,"Kevin Bacon") == 0){
            read_key(actorsname,index,key);
            strcpy(kevinkey,key);
        }
    }
    for(index = 0; index < capacity;index++){

        // get other actor movies 
        read_val(kv,index,val);

        if(strcmp(val,actorskey) == 0){
            read_key(kv,index,key);
            strcpy(moviekey,key);
        } 
        // get kevin movies 
        if(strcmp(val,kevinkey) == 0){
            read_key(kv,index,key);
            strcpy(movieK,key);            
        } 
        // find common movies between  kevin movies and the other actor
        if( movieK[0] != 0 && moviekey[0] != 0 && strcmp(moviekey,movieK) == 0){
            for(index2 = 0; index2 < capacity;index2++){
                read_key(moviename,index2,key);
                if(strcmp(key,moviekey)==0){
                    read_val(moviename,index2,val);
                    strcpy(finalmovie,val);
                    printf("%s\n",finalmovie);
                }
                
            } 
            // clear values 
            movieK[0]= '\0';
            moviekey[0] = '\0';
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
