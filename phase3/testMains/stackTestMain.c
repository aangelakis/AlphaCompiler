#include "../libs/stack/stack.h"
#include <stdio.h>
#include <string.h>

void print_string(void *s){
    puts((char*)s);
}


int main(){
    stack_t* alexoukos = stack_t_init();
    
    char *dodos=strdup("dodos");
    char *alex=strdup("aliekmonas");
    char *czark=strdup("zarkoulis");

    stack_push(alexoukos, (void*) dodos);
    stack_push(alexoukos, (void*) alex);
    stack_push(alexoukos, (void*) czark);

    printf("Size=%u\n", stack_get_size(alexoukos));
    printf("Top=%s\n", (char*)stack_top(alexoukos));
    
    stack_apply(alexoukos, print_string);

    void* lol = stack_pop(alexoukos);
    printf("stack_pop returned:%s\n", (char*)lol);

    printf("Is empty:%d\n", stack_is_empty(alexoukos));

    printf("Size=%u\n", stack_get_size(alexoukos));
    printf("Top=%s\n", (char*)stack_top(alexoukos));

    stack_clear(alexoukos);
    printf("Size=%u\n", stack_get_size(alexoukos));

    stack_free(alexoukos);

    return 0;
}