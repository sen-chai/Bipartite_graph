#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void){
    int a[] = {1,2,3,4,5,6,7,8,9};
    int b[4];
    memcpy(a,&a[1],-1*sizeof(int));
    for(int i = 0; i<9 ; i++){
        printf("%d ",a[i]);
    }

    return 0;
}