#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define ACTOR 0
#define MOVIE 1

// ler nome e dizer se o proximo eh filme ou ator
int read_name(FILE*file,char**name){
    int read_counter = 0;
    while((*name)[read_counter] !='/' ){
        // fscanf(file,"%c",(*name)[read_counter++]);
        (*name)[read_counter++] = getc(file);
        if((*name)[read_counter] =='\n'){
            (*name)[read_counter] = '\0';
            return MOVIE;
        }
    }
    (*name)[read_counter] = '\0';
    return ACTOR;
}
void load_file()
{
    printf("start file");
    FILE *file;
    // role pode ser MOVIE ou ACTOR
    int role = MOVIE;
    char*tmp = (char*) malloc(999*sizeof(char));

    file = fopen("input-top-grossing.txt", "r");
    assert(file);

    while (!feof(file)){
        if(role==MOVIE){
            role = read_name(file,tmp);
            
            printf("- %s",&tmp);
            // insere tmp como vertice filme
            // definir filme do momento
        }
        if(role==ACTOR){
            role = read_name(file,tmp);
            printf("- %s",&tmp);
            // insere tmp como ator
            // ligar ator ao filme que participou
        }
    }
    fclose(file);
}
int main(){
    printf("start main");
    load_file();
}