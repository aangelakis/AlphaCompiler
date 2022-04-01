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

/* Inserts a token in the struct token list. */
void zarklist_insert(zarkList*, void*);

/* Prints the content of each node of the list using function print */
void zarklist_apply(void*, void (*apply)(void*));

/* Frees the struct token list. */
void zarklist_free_all(zarkList*);





#endif