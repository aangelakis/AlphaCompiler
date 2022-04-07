#include<stdio.h>
#include<string.h>
#include"../libs/zarkList/zarkList.h"

void print_string(void *s){
    puts((char*)s);
}

int string_compare(void* s1, void* s2){
    return strcmp((char*)s1, (char*)s2);
}

int main(){
    zarkList* zarkoulhs = zarklist_initialize(1);
    char *dodos=strdup("gro8os1");
    char *alex=strdup("peospeosp\teospeospeospeo\tspeospeospeos\npeospeospeospeospeo\tspeospeospeos:\n");
    char *czark=strdup("gro8os2");
    
    zarklist_insert(zarkoulhs, (void*) dodos);
    zarklist_insert(zarkoulhs, (void*) alex);
    zarklist_insert(zarkoulhs, (void*) czark);
    printf("Size=%d\n", zarklist_getsize(zarkoulhs));

    zarklist_apply(zarkoulhs, print_string);

    zarklist_delete(zarkoulhs, alex, string_compare);

    puts("************");
    printf("Size=%d\n", zarklist_getsize(zarkoulhs));
    zarklist_apply(zarkoulhs, print_string);

    zarklist_delete_all_nodes(zarkoulhs);

    puts("************");
    printf("Size=%d\n", zarklist_getsize(zarkoulhs));
    zarklist_apply(zarkoulhs, print_string);
    
    dodos=strdup("gro8os1");
    zarklist_insert(zarkoulhs, (void*) dodos);
    puts("************");
    printf("Size=%d\n", zarklist_getsize(zarkoulhs));
    zarklist_apply(zarkoulhs, print_string);

    zarklist_free(zarkoulhs);
    return 0;
}