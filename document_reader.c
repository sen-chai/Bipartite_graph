#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define ACTOR 0
#define MOVIE 1

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
void load_file(FILE*file){
    // role pode ser MOVIE, ACTOR ou EOF
    int role = MOVIE;
    char*name = (char*) malloc(999*sizeof(char));
    while (role!=EOF){
        role = read_name(file,&name);
        if(role==MOVIE){
            printf("\nMOVIE %d %s\n",role,name);

            // insere name como vertice filme
            // definir filme do momento
        }
        if(role==ACTOR){
            printf("\nACTOR %d %s\n",role,name);

            // insere name como ator
            // ligar ator ao filme que participou
        }
    }
    free(name);
}
int main(void){
    printf("\n\n");
    FILE *file = fopen("test.txt", "r");
    // FILE *file = fopen("input-top-grossing.txt", "r");
    assert(file);
    load_file(file);
    fclose(file);
}