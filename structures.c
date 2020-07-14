#include <stdlib.h>
#include <stdio.h>

//representação generica das estruturas de dados
typedef struct elem{
    int id;
    struct elem* next;
}ELEM;

typedef struct{
    ELEM *first,*last;
    int counter;
}QUEUE;

ELEM *create_elem(int new)
{
    ELEM *elem = calloc(1, sizeof(ELEM));
    //Modificar aqui para alocação dinamica
    elem->id = new; 
    return elem;
}
//Funçoes da fila
QUEUE *new_queue()
{
    return calloc(1, sizeof(QUEUE));
}
int queue_is_empty(QUEUE *queue)
{
    return queue->counter == 0;
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
ELEM *dequeue(QUEUE *queue)
{
    if (queue_is_empty(queue))
        return NULL;

    ELEM *elem = queue->first;
    queue->first = elem->next;
    queue->counter--;
    if (queue_is_empty(queue))
        queue->last = NULL;
    return elem;
}

void free_queue(QUEUE *queue)
{
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
void print_queue(QUEUE*q){
    ELEM*p = q->first;
    while(p){
        printf("%d ",p->id);
        p = p->next;
    }
    printf("\n");
}
// int main(void){
//     //teste da fila
//     ELEM *elem1, *elem2, *elem3, *searched;
//     elem1 = create_elem(1);
//     elem2 = create_elem(2);
//     elem3 = create_elem(3);
//     QUEUE *queue = new_queue();
//     //fila tem que imprimir na ordem de entrada
//     enqueue(queue, elem1);
//     enqueue(queue, elem2);
//     enqueue(queue, elem3);
//     print_queue(queue);
//     dequeue(queue);
//     print_queue(queue);

//     free_queue(queue);
//     return 0;
// }