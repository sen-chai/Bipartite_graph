
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "data_structures.h"

//Funçoes da lista encadeada
LLIST *new_llist()
{
    LLIST *list = malloc(sizeof(LLIST));
    list->counter = 0;
    list->first = NULL;
    return list;
}
void add_llist(LLIST *llist, ELEM *elem)
{
    if (llist->counter)
        elem->next = llist->first;
    else
        elem->next = NULL;
    llist->first = elem;
    llist->counter++;
}
void free_llist(LLIST *llist)
{
    int i;
    ELEM *elem;
    for (i = 0; i < llist->counter; i++)
    {
        elem = llist->first;
        llist->first = elem->next;
        free(elem);
    }
    free(llist);
}

//Funçoes da fila
QUEUE *new_queue()
{
    QUEUE* queue = malloc(sizeof(QUEUE));
    queue->counter = 0;
    queue->first = NULL;
    queue->last = NULL;
    return queue;
}
void enqueue(QUEUE *queue, ELEM *elem)
{
    elem->next = NULL;
    if (!queue_is_empty(queue))
        queue->last->next = elem;
    else
        queue->first = elem;
    queue->last = elem;
    queue->counter++;
}
ELEM *dequeue(QUEUE *queue){
    if(queue_is_empty(queue))
        return NULL;

    ELEM *elem = queue->first;
    queue->first = elem->next;
    queue->counter--;
    if(queue_is_empty(queue))
        queue->last = NULL;
        return elem;
}

int queue_is_empty(QUEUE *queue){
    return queue->counter == 0;
}
void free_queue(QUEUE *queue){
    int i;
    ELEM *elem;
    for (i = 0; i < queue->counter; i++)
    {
        elem = queue->first;
        queue->first = elem->next;
        free(elem);
    }
    free(queue);
}
//testando
int main(){
ELEM *elem1, *elem2, *elem3;
elem1 = malloc(sizeof(ELEM));
elem2 = malloc(sizeof(ELEM));
elem3 = malloc(sizeof(ELEM));
strcpy(elem1->name ,"list1");
strcpy(elem2->name ,"list2");
strcpy(elem3->name ,"list3");

//teste da lista
LLIST *llist = new_llist();
add_llist(llist,elem1);
add_llist(llist,elem2);
add_llist(llist,elem3);
//lista insere sempre na frente, imprimir na ordem contraria de entrada
printf(" %s ", llist->first->name);
printf(" %s ", llist->first->next->name);
printf(" %s ", llist->first->next->next->name);
free_llist(llist);

//teste da fila
elem1 = malloc(sizeof(ELEM));
elem2 = malloc(sizeof(ELEM));
elem3 = malloc(sizeof(ELEM));
strcpy(elem1->name ,"queue1");
strcpy(elem2->name ,"queue2");
strcpy(elem3->name ,"queue3");
QUEUE *queue = new_queue();
//fila tem que imprimir na ordem de entrada
enqueue(queue,elem1);
enqueue(queue,elem2);
enqueue(queue,elem3);
printf(" %s ",dequeue(queue)->name);
printf( "%s ",dequeue(queue)->name);
printf(" %s ",dequeue(queue)->name);
free_queue(queue);
}