#ifndef data_structures
#define data_Structures

#include <stdlib.h>
#include <stdio.h>

//representação generica das estruturas de dados
struct{
void* first;
int counter;
}generic_header;
typedef struct generic_header LLIST;
typedef struct generic_header QUEUE;
typedef struct generic_header STACK;


//representação generica dos elementos
typedef struct elem{
char* name;
int is_actor;
struct elem* next;
void* content;
}ELEM;

//Funçoes da lista encadeada
LLIST* new_llist();
void add_llist(LLIST* llist, void* elem);
void free_llist(LLIST* llist);

//Funçoes da fila
QUEUE* new_queue();
void enqueue(QUEUE* queue, void* elem);
ELEM* dequeue(QUEUE* queue);
int queue_is_empty(QUEUE* queue);
void free_queue(QUEUE* queue);

//Funçoes da pilha
STACK* new_stack();
void push_stack(STACK* stack,void* elem);
ELEM* pop_stack(STACK* stack);
int stack_is_empty(STACK* stack);
void free_stack(STACK* stack);
#endif