#include "../libs/stack/stack.h"
#include <stdio.h>
#include <string.h>

void print_int(void *s){
    printf("%d\n", *(int*)s);
}


int main(){
    alpha_stack* alexoukos = alpha_stack_init();
    
    int dodos= 69;
    int alex= 420;
    int czark= 69420;

    stack_push(alexoukos, (void*) &dodos);
    stack_push(alexoukos, (void*) &alex);
    stack_push(alexoukos, (void*) &czark);

    printf("Size=%u\n", stack_get_size(alexoukos));
    printf("Top=%d\n", *((int*)stack_top(alexoukos)));
    
    stack_apply(alexoukos, print_int);

    void* lol = stack_pop(alexoukos);
    printf("stack_pop returned:%d\n", *((int*)lol));

    printf("Is empty:%d\n", stack_is_empty(alexoukos));

    printf("Size=%u\n", stack_get_size(alexoukos));
    printf("Top=%d\n", *((int*)stack_top(alexoukos)));

    stack_clear(alexoukos);
    printf("Size=%u\n", stack_get_size(alexoukos));

    stack_free(alexoukos);

    return 0;
}