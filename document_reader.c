#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <graph.h>


// ler nome e dizer se o proximo eh filme ou ator
int read_name(FILE*file,char**name ){
    int read_counter = 0,flag;
    char c = '0';
    while( 1 ){
        fscanf(file,"%c",&c);
        if(feof(file)){
            flag = EOF;
            break;
        }
        if(c =='\n'){
            name[read_counter] = '\0';
            flag = MOVIE;
            break;
        }
        if(c == '/'){
            flag = ACTOR;
            break;
        }
        (*name)[read_counter++] = c;
    }
    (*name)[read_counter] = '\0';
    return flag;
}