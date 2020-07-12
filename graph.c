#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <graph.h>

typedef struct {
    char* name;
    int role; // ACTOR ou MOVIE
    int* adjacents;
    int n_adjacents;
} ITEM;
typedef struct {
    ITEM* elem;
    int n_elem;
} GRAPH;

GRAPH* init_graph(){
    GRAPH* graph = (GRAPH*) calloc(1,sizeof(GRAPH));
    return graph;
}
int name_compare(ITEM elem,char*name){
    if(strcmp(elem.name,name)==0){
        return 1;
    }
    return 0;
}
void add_elem(GRAPH*graph,char*name,int role){
    int current_pos = graph->n_elem++;
    graph->elem = (ITEM*) realloc(graph->elem,graph->n_elem*sizeof(ITEM));
    graph->elem[current_pos].name = (char*) malloc(strlen(name)*sizeof(char));
    strcpy(graph->elem[current_pos].name,name); 
    graph->elem[current_pos].role = role;
    graph->elem[current_pos].adjacents = NULL;
    graph->elem[current_pos].n_adjacents = 0;
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
    graph->elem[movie].adjacents = (int*) realloc(graph->elem[movie].adjacents,graph->elem[movie].n_adjacents*sizeof(int));
    graph->elem[movie].adjacents[n_adj] = actor;

    n_adj = graph->elem[actor].n_adjacents++;
    graph->elem[actor].adjacents = (int*) realloc(graph->elem[actor].adjacents,graph->elem[actor].n_adjacents*sizeof(int));
    graph->elem[actor].adjacents[n_adj] = movie;
}
void print_graph(GRAPH*graph){
    printf("N ITEMS %d",graph->n_elem);
    for(int i = 0; i<graph->n_elem ; i++){
        if(graph->elem[i].role==MOVIE){
            printf("\nMOVIE ");
        }
        else{
            printf("\nACTOR ");
        }
        printf("%s",graph->elem[i].name);
        for(int j = 0; j<graph->elem[i].n_adjacents ; j++){
            printf(" / %d /",graph->elem[i].adjacents[j]);
        }
    }
}
int first_adj(GRAPH*graph,int vertice){
    if(graph->elem[vertice].n_adjacents){
        return graph->elem[vertice].adjacents[0];
    }
    return NO_ADJACENTS;
}
int next_adj(GRAPH*graph,int vertice,int current){
    if(graph->elem[vertice].n_adjacents<current){
        return graph->elem[vertice].adjacents[current+1];
    }
    return NO_ADJACENTS;
}
// o push e pop nao estao otimizados complexidade O(n)
void push(int*queue,int n_elem,int val){
    for(int i = 0; i<n_elem ; i++){
        if(queue[i]==0){
            queue[i] = val;
            return;
        }
    }
}
// retorna front, o primeiro item da fila
int pop(int*queue,int n_elem){
    int front = queue[0];
    memcpy(&queue[0],&queue[1],n_elem-1);
    // deleta o antigo ultimo elemento
    for(int i = 0; i<n_elem ; i++){
        if(queue[i]==0){
            queue[i-1] = 0;
            break;
        }
    }
    return front;
}
// se existem elementos aguardando na fila
int has_waiting(int*queue){
    return queue[0];
}