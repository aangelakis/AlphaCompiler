#include "symtable.h"
#include <stdio.h>
#define HASH_MULTIPLIER 65599

static int diffSizes[8] = {509, 1021, 2053, 4093, 8191, 16381, 32771, 65521}; 

/* Return a hash code for 'pcKey'. */
static unsigned int SymTable_hash(const char *pcKey, int currentSizeIn){
    size_t ui;
    unsigned int uiHash = 0U, size = diffSizes[currentSizeIn];
    for(ui = 0U; pcKey[ui] != '\0'; ui++)
        uiHash = uiHash * HASH_MULTIPLIER + pcKey[ui];
    return uiHash % size;
}


typedef struct binding{
    char *key;
    void *value;
    struct binding *next;
} binding;

struct SymTable_T{
    struct binding **hashtable;
    int currentSizeIn;
    unsigned int length;
};

SymTable_T SymTable_new(void){
    int i;

    SymTable_T newTable = (SymTable_T) malloc(sizeof(struct SymTable_T));
    newTable -> hashtable = (binding **) malloc(509*sizeof(binding*));
    newTable -> currentSizeIn = 0;

    for(i = 0; i < 509; i++)
        newTable -> hashtable[i] = NULL;

    newTable -> length = 0;

    return newTable;
}

void SymTable_free(SymTable_T oSymTable){
    int i, size = diffSizes[oSymTable -> currentSizeIn];
    binding *iter = NULL, *tmp;
    if(oSymTable == NULL)
        return;

    /* Iterate through the hashtable of 'oSymTable', free memory allocated for
     * the (string) key the current binding and then the binding itself */
    for(i = 0; i < size; i++){
        iter = oSymTable -> hashtable[i];
        while(iter){
            tmp = iter;
            iter = iter -> next;
            free(tmp -> key);
            free(tmp);
        }
    }

    free(oSymTable -> hashtable);
    free(oSymTable);
}

unsigned int SymTable_getLength(SymTable_T oSymTable){
    assert(oSymTable);
    return oSymTable -> length;
}

static void expandTable(SymTable_T oSymTable){
    binding *iter = NULL, *forExpand = NULL, **newTable;
    unsigned int index;
    int i, oldSize = diffSizes[oSymTable -> currentSizeIn], newSize, sizeIndex;
    sizeIndex = ++(oSymTable -> currentSizeIn);
    newSize = diffSizes[sizeIndex];
    /* The new hashtable with greater size */
    newTable = (binding **) malloc(newSize * sizeof(binding*));

    for(i = 0; i < newSize; i++)
        newTable[i] = NULL;

    /* Iterate through the old hashtable and hash every binding it contains 
     * into the new hashtable */
    for(i = 0; i < oldSize; i++){
        iter = oSymTable -> hashtable[i];
        while(iter){
            forExpand = iter;
            iter = iter -> next;

            index = SymTable_hash(forExpand -> key, sizeIndex);

            forExpand -> next = newTable[index];
            newTable[index] = forExpand;
        }
    }

    /* The memory where the old hashtable was needs to be freed and the pointer
     * inside 'oSymTable' must now point to the new hashtable */
    free(oSymTable -> hashtable);
    oSymTable -> hashtable = newTable;
}

int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pcValue){
    unsigned int index = SymTable_hash(pcKey, oSymTable -> currentSizeIn); 
    binding *iter = oSymTable -> hashtable[index], *newBinding;
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
     * start of the list at the index of the hash table, and return 1(TRUE) */

    newBinding = (binding *) malloc(sizeof(binding));
    newBinding -> key = (char *) malloc((strlen(pcKey) + 1) * sizeof(char));
    strcpy(newBinding -> key, pcKey);
    newBinding -> value = (void *) pcValue;

    newBinding -> next = oSymTable -> hashtable[index];
    oSymTable -> hashtable[index] = newBinding;
    oSymTable -> length++;

    /* If insertion of new binding makes length exceed some number,
     * expand the hashtable */
    if(oSymTable -> length > diffSizes[oSymTable -> currentSizeIn]
       && oSymTable -> currentSizeIn != 7)
        expandTable(oSymTable);

    return 1;
}

int SymTable_remove(SymTable_T oSymTable, const char *pcKey){
    unsigned int index = SymTable_hash(pcKey, oSymTable -> currentSizeIn); 
    binding *iter = oSymTable -> hashtable[index], *prev = NULL;
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
        oSymTable -> hashtable[index] = iter -> next;
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
    unsigned int index = SymTable_hash(pcKey, oSymTable -> currentSizeIn); 
    binding *iter = oSymTable -> hashtable[index];
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
    unsigned int index = SymTable_hash(pcKey, oSymTable -> currentSizeIn); 
    binding *iter = oSymTable -> hashtable[index];
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
    
    int i, size = diffSizes[oSymTable -> currentSizeIn];
    binding *iter = NULL;
    assert(oSymTable);
    assert(pfApply);

    /* Iterate oSymTable's hashtable and call 'pfApply' for every binding */
    for(i = 0; i < size; i++){
        iter = oSymTable -> hashtable[i];
        while(iter){
            (*pfApply)(iter -> key, iter -> value, (void *) pvExtra);
            iter = iter -> next;
        }
    }
} 

void SymTable_quickApply(SymTable_T oSymTable, void (*pfApply)(void *))
{
    int i, size = diffSizes[oSymTable -> currentSizeIn];
    binding *iter = NULL;
    assert(oSymTable);
    assert(pfApply);

    /* Iterate oSymTable's hashtable and call 'pfApply' for every binding */
    for(i = 0; i < size; i++){
        iter = oSymTable -> hashtable[i];
        while(iter){
            (*pfApply)(iter -> value);
            iter = iter -> next;
        }
    }
} 