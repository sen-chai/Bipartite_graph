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
    graph->elem[current_pos].name = (char*) malloc((strlen(name)+1)*sizeof(char));
    strcpy(graph->elem[current_pos].name,name); 
    graph->elem[current_pos].role = role;
    graph->elem[current_pos].adjacents = NULL;
    graph->elem[current_pos].n_adjacents = 0;
}
// pesquisa se existe, se nao, adiciona. Retorna posicao
int ins_get_vertex(GRAPH*graph,char*name,int role){
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
        printf("%s ",graph->elem[i].name);
        printf("|%d| ",graph->elem[i].n_adjacents);
        for(int j = 0; j<graph->elem[i].n_adjacents ; j++){
            printf(" / %d /",graph->elem[i].adjacents[j]);
        }
    }
}
void print_name(GRAPH*graph,int pos){
    if(graph->elem[pos].role==MOVIE){
        printf("MOVIE ");
    }
    else{
        printf("ACTOR ");
    }
    printf("|%d| ",graph->elem[pos].n_adjacents);
    printf("%s ",graph->elem[pos].name);  
    for(int i = 0; i<graph->elem[pos].n_adjacents; i++){
        printf(" %d,",graph->elem[pos].adjacents[i]);
    }
    printf("\n");
}
int first_adj(GRAPH*graph,int vertice){
    if(graph->elem[vertice].n_adjacents){
        return graph->elem[vertice].adjacents[0];
    }
    return NO_ADJACENTS;
}
int next_adj(GRAPH*graph,int vertice,int*current){
    (*current)++;
    if(graph->elem[vertice].n_adjacents > *current){
        return graph->elem[vertice].adjacents[*current];
    }
    return NO_ADJACENTS;
}
// o push e pop nao estao otimizados complexidade O(n)
void push(int*queue,int*n_elem,int val){
    queue[*n_elem] = val;
    (*n_elem)++;
}
// retorna front, o primeiro item da fila
int pop(int*queue,int*n_elem){
    int front = queue[0];
    memcpy(queue,&queue[1],*n_elem*sizeof(int));
    (*n_elem)--;
    return front;
}
int* visit_breadth(GRAPH*graph,int origin){
    int p, has_waiting = 0,adj_counter;
    int *color = (int*) calloc(graph->n_elem,sizeof(int));
    int *queue = (int*) calloc(graph->n_elem,sizeof(int));
    int *antecedents = (int*) calloc(graph->n_elem,sizeof(int));
    for(int i = 0; i<graph->n_elem; i++){
        antecedents[i] = -1;
    }

    color[origin] = 1;
    push(queue,&has_waiting,origin);
    printf("push %d ",queue[0]);
    print_name(graph,queue[0]);
    for(int i = 0; i<has_waiting; i++)
        printf("_%d_",queue[i]);
    printf("\n");

    while(has_waiting > 0){
        origin = pop(queue,&has_waiting);

        printf("pop %d ",origin);
        for(int i = 0; i<has_waiting; i++)
            printf("_%d_",queue[i]);
        printf("\n");

        p = first_adj(graph,origin);
        printf("first_adj %d\n",p);
        adj_counter = 0;

        while(p >= 0){
            if(color[p]==0){
                color[p]=1;
                push(queue,&has_waiting,p);
                antecedents[p] = origin;

                printf("push %d ",p);
                for(int i = 0; i<has_waiting; i++)
                    printf("_%d_",queue[i]);
                printf("\n");

            }
            p = next_adj(graph,origin,&adj_counter);
        }
        color[origin] = 2;
    }
    free(color);
    free(queue);
    return antecedents;
}