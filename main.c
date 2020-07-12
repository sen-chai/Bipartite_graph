#include <stdlib.h>
#include <stdio.h>
#include <graph.c>
#include <document_reader.c>
#include <data_structures.h>

int main(void){
    QUEUE* graph = init_graph();

    // Input de dados
    FILE *file = fopen("test.txt", "r");
    // FILE *file = fopen("input-top-grossing.txt", "r");
    assert(file);

    // role pode ser MOVIE, ACTOR ou EOF
    int role = MOVIE, movie, actor;
    char*name = (char*) malloc(999*sizeof(char));

    while (role!=EOF){
        role = read_name(file,&name);
        if(role==MOVIE){
            // printf("\nMOVIE %d %s\n",role,name);

            // retornar filme do momento e adiciona-lo
            movie = ins_vertex(graph,name,role);
        }
        if(role==ACTOR){
            // printf("\nACTOR %d %s\n",role,name);

            // retornar posicao do ator e inserir-lo
            actor = ins_vertex(graph,name,role);
            // ligar ator ao filme que participou
            ins_edge(graph,movie,actor);
        }
    }
    fclose(file);
    free(name);

    breadth_search(graph);

    free_graph(graph);
    return 0;
}