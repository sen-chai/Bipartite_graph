#include <stdlib.h>
#include <stdio.h>
#include <graph.c>
#include <graph.h>
#include <document_reader.c>

typedef struct{
    int a;
    int b;
} DATA;

int main(void){
    GRAPH* graph = init_graph();
    int size = 9;
    DATA data[] = {
        {1,2},
        {2,5},
        {1,6},
        {6,3},
        {6,7},
        {3,7},
        {3,4},
        {4,7},
        {4,8},
        {7,8},
    };

    char name[9];
    int ind;
    for(int i = 0; i<size ; i++){
        sprintf(name,"name%02d",i);
        ins_get_vertex(graph,name,ACTOR);
    }
    for(int i = 0; i<10 ; i++){
        ins_edge(graph,data[i].a,data[i].b);
    }
    print_graph(graph);

    int*antecedents = visit_breadth(graph,1);
    for(int i = 0; i<9 ; i++){
        printf("%3d ",antecedents[i]);
    }
    printf("\n");

    return 0;
}

