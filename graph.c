#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    char* name;
    int role; // ACTOR ou MOVIE
    int* adjacents;
    int n_adjacents;
} ELEM;
typedef struct {
    ELEM* elem;
    int n_elem;
} GRAPH;

GRAPH* init_graph(){
    GRAPH* graph = (GRAPH*) calloc(1,sizeof(GRAPH));
    return graph;
}
int name_compare(ELEM elem,char*name){
    return strcmp(elem.name,name);
}
void add_elem(GRAPH*graph,char*name,int role){
    int current_size = graph->n_elem++;
    graph->elem = (ELEM*) realloc(graph->elem,current_size*sizeof(ELEM));
    graph->elem[current_size].name = (char*) malloc(strlen(name)*sizeof(char));
    strcpy(graph->elem[current_size].name,name); 
    graph->elem[current_size].role = role;
    graph->elem[current_size].adjacents = NULL;
    graph->elem[current_size].n_adjacents = 0;
}
// pesquisa se existe, se nao, adiciona. Retorna posicao
int ins_vertex(GRAPH*graph,char*name,int role){
    // retornar elem se ja criado
    for(int i = 0; i<graph->n_elem; i++){
        if(name_compare(graph->elem[i],name)){
            return i;
        }
    }
    // criar novo elem
    add_elem(graph,name,role);
    return graph->n_elem-1;
}
// cria aresta biderecional entre movie e actor dado o indice de ambos
void ins_edge(GRAPH*graph,int movie,int actor){
    int n_adj = graph->elem[movie].n_adjacents++;
    graph->elem[movie].adjacents = (int*) realloc(graph->elem[movie].adjacents,n_adj*sizeof(int));
    graph->elem[movie].adjacents[n_adj-1] = actor;

    n_adj = graph->elem[actor].n_adjacents++;
    graph->elem[actor].adjacents = (int*) realloc(graph->elem[actor].adjacents,n_adj*sizeof(int));
    graph->elem[actor].adjacents[n_adj-1] = movie;
}