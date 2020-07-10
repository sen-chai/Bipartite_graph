#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct{
    int **adj_matrix; // contem row de adjacentes
    int n_vertices;
    int n_edges;
} GRAPH;
typedef struct{
    int row;
    int col;
    int weight;
} EDGE;

GRAPH* init_graph(){
    GRAPH* graph = (GRAPH*) calloc(1,sizeof(GRAPH));
    graph->adj_matrix = (int**) malloc(sizeof(int*));
    return graph;
}

void ins_vertex(GRAPH*graph,int n_new){
    graph->n_vertices+=n_new;
    graph->adj_matrix = (int**) realloc(graph->adj_matrix,graph->n_vertices*sizeof(int*));
    // novas rows
    for(int i = 0; i<n_new; i++){
        graph->adj_matrix[graph->n_vertices-i-1] = (int*) calloc(graph->n_vertices,sizeof(int));
    }
    // novas colunas
    for(int i = 0; i<graph->n_vertices-n_new; i++){
        graph->adj_matrix[i] = (int*) realloc(graph->adj_matrix[i],graph->n_vertices*sizeof(int));
        for(int j = graph->n_vertices-n_new-1; j<n_new ; j++){
            graph->adj_matrix[i][j] = 0;
        }
        graph->adj_matrix[i][graph->n_vertices-1] = 0;
    }
}
void ins_edge(GRAPH*graph,int row,int col,int weight){
    if(row<graph->n_vertices && col<graph->n_vertices){
        graph->adj_matrix[row][col] = weight;
        graph->n_edges++;
    }
}
void del_edge(GRAPH*graph,int row,int col){
    if(row<graph->n_vertices && col<graph->n_vertices){
        graph->adj_matrix[row][col] = 0;
        graph->n_edges--;
    }
}
void print(GRAPH*graph){
    printf("\n");
    for(int i = 0; i<graph->n_vertices ; i++){
        for(int j = 0; j<graph->n_vertices ; j++){
            printf(" %6d", graph->adj_matrix[i][j]);
        }
        printf("\n");
    }
}
int get_weight(GRAPH*graph,int row,int col){
    return graph->adj_matrix[row][col];
}
int free_graph(GRAPH*graph){
    for(int i = 0; i<graph->n_vertices ; i++){
        free(graph->adj_matrix[i]);
    }
    free(graph->adj_matrix);
    free(graph);
}
int first_adj(GRAPH*graph,int row){
    for(int i = 1; i<graph->n_vertices; i++){
        if(graph->adj_matrix[row][i]!=0){
            printf("first %d\n",graph->adj_matrix[row][i]);
            return i;
        }
    }
    printf("first NULL\n");
    return 0;
}
int next_adj(GRAPH*graph,int row,int current){
    for(int i = current+1; i<graph->n_vertices; i++){
        if(graph->adj_matrix[row][i]!=0){
            printf("next %d\n",graph->adj_matrix[row][i]);
            return i;
        }
    }
    printf("next NULL\n");
    return 0;
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
void visit_breadth(GRAPH*graph,int*color,int row){
    int p;
    int *queue = (int*) calloc(graph->n_vertices,sizeof(int));
    color[row] = 1;
    push(queue,graph->n_vertices,row);

    printf("push ");
    for(int i = 0; i<graph->n_vertices; i++)
        printf("_%d_ ",queue[i]);
    printf("\n");

    while(has_waiting(queue)){
        row = pop(queue,graph->n_vertices);

        printf("pop  ");
        for(int i = 0; i<graph->n_vertices; i++)
            printf("_%d_ ",queue[i]);
        printf("\n");
        p = first_adj(graph,row);
        while(p!=0){
            if(color[p]==0){
                color[p]=1;
                push(queue,graph->n_vertices,p);

                printf("push ");
                for(int i = 0; i<graph->n_vertices; i++)
                    printf("_%d_ ",queue[i]);
                printf("\n");
            }
            p = next_adj(graph,row,p);
        }
        color[row] = 2;
    }
}
void breadth_search(GRAPH*graph){
    int *color = (int*) malloc((graph->n_vertices)*sizeof(int));
    for(int i = 0; i<graph->n_vertices; i++){
       color[i]=0;
    }
    for(int i = 1; i<graph->n_vertices; i++){
        if(color[i]==0){
            printf("### depth\n");
            visit_breadth(graph,color,i);
        }
    }
    // show colors
    for(int i = 0; i<graph->n_vertices; i++){
        printf("%d ",color[i]);
    }
    printf("\n");

    free(color);
}
