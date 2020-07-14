#ifndef data_structures
#define data_structures

#include <stdlib.h>
#include <stdio.h>

//representação generica das estruturas de dados
typedef struct elem{
    int id;
    struct elem* next;
}ELEM;

typedef struct{
    ELEM* first;
    int counter;
}LLIST;

typedef struct{
    ELEM *first,*last;
    int counter;
}QUEUE;

/*
    # Eu acho que so precisaremos da QUEUE. 
*/

ELEM* crate_elem(char* name, void* content, int is_actor);
//Funçoes da lista encadeada
LLIST* new_llist();
void add_llist(LLIST* llist,ELEM* elem);
ELEM* search_string_list(LLIST* llist, char* string); //Retorna void se não achar o elemento
void free_llist(LLIST* llist);

//Funçoes da fila
QUEUE* new_queue();
void enqueue(QUEUE* queue, ELEM* elem);
ELEM* dequeue(QUEUE* queue);
int queue_is_empty(QUEUE* queue);
void free_queue(QUEUE* queue);

#endif