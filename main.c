#include <stdlib.h>
#include <stdio.h>
#include <graph.c>
#include <graph.h>
#include <document_reader.c>
// #include <data_structures.h>

int main(void){
    GRAPH* graph = init_graph();

    // Input de dados
    FILE *file = fopen("test.txt", "r");
    // FILE *file = fopen("input-top-grossing.txt", "r");
    assert(file);
    // role pode ser MOVIE, ACTOR ou EOF
    int role = MOVIE, movie, actor;
    char*name = (char*) malloc(999*sizeof(char));

    while (role!=EOF){
        if(role==MOVIE){
            role = read_name(file,&name);
            if(role==EOF) {break;}
            // printf("\nMOVIE %s\n",name);

            // retornar filme do momento e adiciona-lo
            movie = ins_vertex(graph,name,MOVIE);
        }
        if(role==ACTOR){
            role = read_name(file,&name);

            // printf("\nACTOR %s\n",name);

            // retornar posicao do ator e inserir-lo
            actor = ins_vertex(graph,name,ACTOR);
            // ligar ator ao filme que participou
            ins_edge(graph,movie,actor);
        }
    }
    // fclose(file);
    free(name);

    printf("fred and closed\n");
    print_graph(graph);
    return 0;
}