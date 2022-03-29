#include "symtable.h"

typedef struct binding{
    char *key;
    void *value;
    struct binding *next;
} binding;

struct SymTable_T{
    struct binding *head;
    unsigned int length;
};

SymTable_T SymTable_new(void){
    SymTable_T newTable = (SymTable_T) malloc(sizeof(struct SymTable_T));

    newTable -> head = NULL;
    newTable -> length = 0;

    return newTable;
}

void SymTable_free(SymTable_T oSymTable){
    binding *iter = oSymTable -> head, *tmp;
    if(oSymTable == NULL)
        return;

    while(iter){
        tmp = iter;
        iter = iter -> next;
        free(tmp -> key);
        free(tmp);
    }

    free(oSymTable);
}

unsigned int SymTable_getLength(SymTable_T oSymTable){
    assert(oSymTable);
    return oSymTable -> length;
}

int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pcValue){
    binding *iter = oSymTable -> head, *newBinding;
    assert(oSymTable);
    assert(pcKey);

    while(iter){
        /* Just return 0(FALSE) if binding with 'pcKey' already exists in 'oSymTable' */
        if(strcmp(iter -> key, pcKey) == 0)
            return 0;
        iter = iter -> next;
    }

    /* if you got out from the last loop, it means that there is no bindings 
     * with 'pcKey', so you can just make the new binding, insert it at the
     * start of the list, and return 1(TRUE) */

    newBinding = (binding *) malloc(sizeof(binding));
    newBinding -> key = (char *) malloc((strlen(pcKey) + 1) * sizeof(char));
    strcpy(newBinding -> key, pcKey);
    newBinding -> value = (void *) pcValue;

    newBinding -> next = oSymTable -> head;
    oSymTable -> head = newBinding;
    oSymTable -> length++;

    return 1;
}

int SymTable_remove(SymTable_T oSymTable, const char *pcKey){
    binding *iter = oSymTable -> head, *prev = NULL;
    assert(oSymTable);
    assert(pcKey);

    while(iter){
        /* Find binding to remove */
        if(strcmp(iter -> key, pcKey) == 0)
            break;
        prev = iter;
        iter = iter -> next;
    }

    /* if iter is NULL, it means that you did not find the binding
     * with key == 'pcKey', so just return 0(FALSE). */
    if(iter == NULL)
        return 0;
    /* else remove the binding you found */
    /* Case you are removing the head of the list. */
    if(prev == NULL){
        oSymTable -> head = iter -> next;
        iter -> next = NULL;
        free(iter -> key);
        free(iter);
    }
    /* Every other removal*/
    else{
        prev -> next = iter -> next;
        iter -> next = NULL;
        free(iter -> key);
        free(iter);
    }
    /* Reduce length by one since you have removed one binding*/
    oSymTable -> length--;
    /* Binding successfully removed so return 1(TRUE). */
    return 1;
}

int SymTable_contains(SymTable_T oSymTable, const char *pcKey){
    binding *iter = oSymTable -> head;
    assert(oSymTable);
    assert(pcKey);

    while(iter){
        /* If you find the binding you are searching, just return 1(TRUE) */
        if(strcmp(iter -> key, pcKey) == 0)
            return 1;
        iter = iter -> next;
    }

    /* If you got here it means that the binding with key == 'pcKey'
     * was not found and thus 'oSymTable' does not contain it.
     * So just return 0(FALSE). */
    return 0;
}

void *SymTable_get(SymTable_T oSymTable, const char *pcKey){
    binding *iter = oSymTable -> head;
    assert(oSymTable);
    assert(pcKey);

    while(iter){
        /* If you find the binding you are searching, return its value */
        if(strcmp(iter -> key, pcKey) == 0)
            return iter -> value;
        iter = iter -> next;
    }

    /* If you got here it means that the binding with key == 'pcKey'
     * was not found and thus 'oSymTable' does not contain it.
     * So just return NULL. */
    return NULL;
}

void SymTable_map(SymTable_T oSymTable, 
void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),
const void *pvExtra){
    
    binding *iter = oSymTable -> head;
    assert(oSymTable);
    assert(pfApply);

    while(iter){
        (*pfApply)(iter -> key, iter -> value, (void *) pvExtra);
        iter = iter -> next;
    }
} 
