#include"zarkList.h"

zarkList* zarklist_initialize(int isContentFreeable)
{
    zarkList* list = malloc(sizeof(zarkList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->isContentFreeable = isContentFreeable;

    return list;
}
/* Inserts a token in the struct token list. */
void zarklist_insert(zarkList* list, void* content)
{
    zarkNode* new_entry = malloc(sizeof(zarkNode));
    new_entry->content = content;
    new_entry->next = NULL;

    if (list->head == NULL)
        list->head = new_entry;
    else if (list->tail == NULL)
    {
        list->tail = new_entry;
        list->head->next = new_entry;
    }
    else
    {
        list->tail->next = new_entry;
        list->tail = new_entry;
    }
    list->size++;
}

/* Prints the content of each node of the list using function print */
void zarklist_apply(void *list, void (*apply)(void*))
{
    zarkNode *iter = list->head;
    while (iter)
    {   
        apply(iter->content);
        iter = iter->next;
    }
}

/* Frees the struct token list. */
void zarklist_free_all(zarkList* list)
{
    zarkNode *iter = list->head, *tmp;
    int isFreeable = list->isContentFreeable;
    while (iter)
    {
        tmp = iter;
        iter = iter->next;
        if(isFreeable)
            free(tmp->content);
        free(tmp);
    }
}