/*
Lucas Martins NUSP 11275126
Sen Chai NUSP 10727830
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define NO_ADJACENTS -2
#define ACTOR 0
#define MOVIE 1

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
// print de todo o grafo
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
    printf("\n");
}
// dado o indice, printa ator e em qual filme pariticipou
void print_name(GRAPH*graph,int pos){
    if(graph->elem[pos].role==MOVIE){
    printf(" atuou em \"%s\" com ",graph->elem[pos].name);  
    }
    else{
    printf("\"%s\"",graph->elem[pos].name);  
    }
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
    memcpy(queue,&queue[1],(*n_elem)*sizeof(int));
    (*n_elem)--;
    return front;
}
// busca o caminho do ator ate destiny, no caso caminho ate KB
void search_actor(GRAPH*graph,int origin,int destiny){
    int p, has_waiting = 0, adj_counter;

    int *color= (int*) calloc(graph->n_elem,sizeof(int));
    int *queue= (int*) calloc(graph->n_elem,sizeof(int));
    int *antecedents = (int*) calloc(graph->n_elem,sizeof(int));
    for(int i = 0; i<graph->n_elem; i++){
        color[i] = 0;
        queue[i] =-1;
        antecedents[i] = -1;
    }

    color[origin] = 1;
    push(queue,&has_waiting,origin);

    while(has_waiting > 0){
        origin = pop(queue,&has_waiting);

        p = first_adj(graph,origin);
        adj_counter = 0;

        while(p >= 0){
            if(color[p]==0){
                color[p]=1;
                push(queue,&has_waiting,p);
                antecedents[p] = origin;

            }
            p = next_adj(graph,origin,&adj_counter);
        }
        color[origin] = 2;
    }
    if(antecedents[destiny] == -1){
        printf("esse ator não se liga a Kevin bacon");
        return;
    }
    int count =0;
    int search = destiny;
    int back[100];
    back[count] = search;
    while(search != origin && search != -1){
        count++;
        search = antecedents[search];
        back[count] = search;
    }
    print_name(graph,destiny);
     printf(" tem KB %d\n", (count/2));
     int scount = 0;
     for(int i = 0;i < count;i++){
         print_name(graph,back[i]);
         if(scount == 2 && i != count-1){
             printf("\n");
         print_name(graph,back[i]);
         scount = 0;
         }
         scount++;
     }

    free(color);
    free(queue);
    free(antecedents);

}
// Mundo de Kevin Bacon com media e desvio padrao
void kevin_world(GRAPH *graph,int origin){
    int p, has_waiting = 0, adj_counter;

    int *color= (int*) calloc(graph->n_elem,sizeof(int));
    int *queue= (int*) calloc(graph->n_elem,sizeof(int));
    int *antecedents = (int*) calloc(graph->n_elem,sizeof(int));
    for(int i = 0; i<graph->n_elem; i++){
        color[i] = 0;
        queue[i] =-1;
        antecedents[i] = -1;
    }

    color[origin] = 1;
    push(queue,&has_waiting,origin);

    while(has_waiting > 0){
        origin = pop(queue,&has_waiting);

        p = first_adj(graph,origin);
        adj_counter = 0;

        while(p >= 0){
            if(color[p]==0){
                color[p]=1;
                push(queue,&has_waiting,p);
                antecedents[p] = origin;

            }
            p = next_adj(graph,origin,&adj_counter);
        }
        color[origin] = 2;
    }
    int* distance = malloc(sizeof(int) * graph->n_elem);
    int i,search,count, sum = 0,mean_correction = 0;
    float mean,std_deviation = 0;;
    for(i=0;i < graph->n_elem;i++){
        search = antecedents[i];
        count = 0;
        if(search == -1) mean_correction++;
        while(search != origin && search != -1){
        count++;
        search = antecedents[search];
    }
    sum += count/2;
    distance[i] = count/2;
    }
    //os atores que não estão ligados a kb são computados como 0 na soma, e o mean_correction os tira da divisão 
    mean = 1.0*sum/(graph->n_elem-mean_correction);

    for(i=0;i < graph->n_elem;i++){
    if(distance[i] != -1){
    std_deviation += pow(distance[i] - mean,2);
    }}
    std_deviation = sqrt((std_deviation/(graph->n_elem-mean_correction)));
    printf("\nMedia dos números de Kevin Bacon: %f", mean);
    printf("\nDesvio Padrão números de Kevin Bacon: %f", std_deviation);
    free(color);
    free(queue);
    free(distance);
    free(antecedents);

}
// liberar grafo
void free_graph(GRAPH *graph){
    for(int i = 0; i<graph->n_elem ; i++){
        free(graph->elem[i].name);
        free(graph->elem[i].adjacents);
    }
    free(graph->elem);
    free(graph);
}