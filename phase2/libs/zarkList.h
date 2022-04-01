#ifndef ZARKLIST_HEADER
#define ZARKLIST_HEADER

typedef struct zarkNode {
        void *content;
        struct zarkNode* next;
} zarkNode;

typedef struct zarkList {
    zarkNode* head;
    zarkNode* tail;
    int size;
    int isContentFreeable;
} zarkList;

/* Initializes the zarkList */
zarkList* zarklist_initialize(int);

/* Inserts a zarkNode in the zarkList. */
void zarklist_insert(zarkList*, void*);

/* Deletes zarkNode 'node' from the zarkList 'list' */
void zarklist_delete(zarkList *list, zarkNode* node);

/* Applys function 'apply(void*)' to the content of each zarkNode of the zarkList */
void zarklist_apply(void*, void (*apply)(void*));

/* Frees the zarkList and all its zarkNodes. */
void zarklist_free_all_nodes(zarkList*);

#endif