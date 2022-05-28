#ifndef ZARKLIST_HEADER
#define ZARKLIST_HEADER
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>

typedef struct zarkNode {
        void *content;
        struct zarkNode* next;
} zarkNode;

typedef struct zarkList {
    zarkNode* head;
    zarkNode* tail;
    unsigned size;
    int isContentFreeable;
} zarkList;

unsigned zarklist_getsize(zarkList* list);

/* Initializes the zarkList */
zarkList* zarklist_initialize(int);

/* Inserts a zarkNode in the zarkList. */
void zarklist_insert(zarkList*, void*);

/* Deletes zarkNode 'node' from the zarkList 'list' */
void zarklist_delete(zarkList *list, void* content, int (*compare)(void*, void*));

/* Applys function 'apply(void*)' to the content of each zarkNode of the zarkList */
void zarklist_apply(zarkList *list, void (*apply)(void*));

/* Frees the zarkList and all its zarkNodes. */
void zarklist_delete_all_nodes(zarkList* list);

void zarklist_free(zarkList* list);

void zarklist_print(zarkList *list, char* (*content_to_string)(void*));


#endif