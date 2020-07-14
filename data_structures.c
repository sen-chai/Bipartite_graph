
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "data_structures.h"

ELEM *create_elem(int new)
{
    ELEM *elem = calloc(1, sizeof(ELEM));
    //Modificar aqui para alocação dinamica
    elem->id = new; 
    return elem;
}
//Funçoes da lista encadeada
LLIST *new_llist()
{
    return calloc(1, sizeof(LLIST));
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

ELEM *search_string_list(LLIST *llist, char *string)
{
    ELEM *elem;
    int i;
    elem = llist->first;
    while (elem && strcmp(string, elem->name) && (elem = elem->next))
        i++;
    if(elem)
        return elem;
    else 
        return NULL;
}
//Funçoes da fila
QUEUE *new_queue()
{
    return calloc(1, sizeof(QUEUE));
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

int queue_is_empty(QUEUE *queue)
{
    return queue->counter == 0;
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
//testando
/*int main()
{
    ELEM *elem1, *elem2, *elem3, *searched;
    elem1 = create_elem("list1", NULL, 1);
    elem2 = create_elem("list2", NULL, 1);
    elem3 = create_elem("list3", NULL, 1);

    //teste da lista
    LLIST *llist = new_llist();
    add_llist(llist, elem1);
    add_llist(llist, elem2);
    add_llist(llist, elem3);
    //teste da busca por string
    searched = search_string_list(llist, "list1");
    if(searched)
    printf("ACHOU");   
    //lista insere sempre na frente, imprimir na ordem contraria de entrada
    printf(" %s ", llist->first->name);
    printf(" %s ", llist->first->next->name);
    printf(" %s ", llist->first->next->next->name);
    free_llist(llist);

    //teste da fila
    elem1 = create_elem("queue1", NULL, 1);
    elem2 = create_elem("queue2", NULL, 1);
    elem3 = create_elem("queue3", NULL, 1);
    QUEUE *queue = new_queue();
    //fila tem que imprimir na ordem de entrada
    enqueue(queue, elem1);
    enqueue(queue, elem2);
    enqueue(queue, elem3);
    printf(" %s ", dequeue(queue)->name);
    printf("%s ", dequeue(queue)->name);
    printf(" %s ", dequeue(queue)->name);
    dequeue(queue);
    free_queue(queue);
}*/