#include <stdlib.h>
#include <stdio.h>


int main(void){
    int size = 1879;
    // int*color = (int*) calloc(size,sizeof(int));
    int color[size];
    for(int i = 0; i<size+10; i++){
        printf("%d ",color[i]);
    }
    printf("\n\n");
    printf("array size %d\n",(int)sizeof(color));

    return 0;
}