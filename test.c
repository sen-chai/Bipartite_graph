#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int pop(int*queue,int*count){
    printf("size %d\n",*count*sizeof(int));
    memcpy(queue,&queue[1],*count*sizeof(int));
    (*count)--;
}
int main(void){
    int v[] = {1,2,3,4};
    int has_waiting = 4;
    pop(v,&has_waiting);
    printf("\n");
    for(int i = 0; i<has_waiting; i++)
        printf("%d ",v[i]);
    printf("\n");
    printf("waiting %d\n",has_waiting );
    return 0;
}

