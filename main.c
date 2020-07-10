#include <stdlib.h>
#include <stdio.h>
#include <graph.c>

int main(void){
    //  dados do caso de compra e venda de computadores 
    int vertices = 6;
    GRAPH*graph = init_graph();
    ins_vertex(graph,vertices);
    for(int i = 0; i<9 ; i++){
        ins_edge(graph,data[i].row,data[i].col,data[i].weight);
    }
    print(graph);
    breadth_search(graph);


    free_graph(graph);
    return 0;
}