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

void zarklist_delete(zarkList *list, zarkNode* node)
{
    zarkNode *iter = list->head, *prev = NULL;

    // Find the node to be deleted
    while(iter != NULL && iter != node) {
        prev = iter;
        iter = iter->next;
    }

    // node must exist based on our structures
    assert(iter != NULL);

    // delete the node you found 'iter' points to it
    if(prev == NULL){
        list->head = iter->next;
        iter->next = NULL;
        if(list->isContentFreeable)
            free(iter->content);
        free(iter);
    }
    else if(iter == list->tail){
        list->tail = prev;
        prev->next = NULL;
        if(list->isContentFreeable)
            free(iter->content);
        free(iter);
    }
    else {
        prev->next = iter->next;
        iter->next = NULL;
        if(list->isContentFreeable)
            free(iter->content);
        free(iter);
    }
}

void zarklist_apply(void *list, void (*apply)(void*))
{
    zarkNode *iter = list->head;
    while (iter)
    {   
        apply(iter->content);
        iter = iter->next;
    }
}

void zarklist_free_all_nodes(zarkList* list)
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

void zarklist_free(zarkList* list) {
    zarklist_free_all_nodes(list);
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->isContentFreeable = 0;
    free(list);
}