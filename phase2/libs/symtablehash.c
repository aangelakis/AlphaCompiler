#include "symtable.h"
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


typedef struct SymTableEntry{
    char *key;
    void *value;
    struct SymTableEntry *next;
} SymTableEntry;

struct SymTable_T{
    struct SymTableEntry **hashtable;
    int currentSizeIn;
    unsigned int length;
};

SymTable_T SymTable_new(void){
    int i;

    SymTable_T newTable = (SymTable_T) malloc(sizeof(struct SymTable_T));
    newTable -> hashtable = (SymTableEntry **) malloc(509*sizeof(SymTableEntry*));
    newTable -> currentSizeIn = 0;

    for(i = 0; i < 509; i++)
        newTable -> hashtable[i] = NULL;

    newTable -> length = 0;

    return newTable;
}

void SymTable_free(SymTable_T oSymTable){
    int i, size = diffSizes[oSymTable -> currentSizeIn];
    SymTableEntry *iter = NULL, *tmp;
    if(oSymTable == NULL)
        return;

    /* Iterate through the hashtable of 'oSymTable', free memory allocated for
     * the (string) key the current SymTableEntry and then the SymTableEntry itself */
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
    SymTableEntry *iter = NULL, *forExpand = NULL, **newTable;
    unsigned int index;
    int i, oldSize = diffSizes[oSymTable -> currentSizeIn], newSize, sizeIndex;
    sizeIndex = ++(oSymTable -> currentSizeIn);
    newSize = diffSizes[sizeIndex];
    /* The new hashtable with greater size */
    newTable = (SymTableEntry **) malloc(newSize * sizeof(SymTableEntry*));

    for(i = 0; i < newSize; i++)
        newTable[i] = NULL;

    /* Iterate through the old hashtable and hash every SymTableEntry it contains 
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
    SymTableEntry *iter = oSymTable -> hashtable[index], *newSymTableEntry;
    assert(oSymTable);
    assert(pcKey);

    while(iter){
        /* Just return 0(FALSE) if SymTableEntry with 'pcKey' already exists in 'oSymTable' */
        if(strcmp(iter -> key, pcKey) == 0)
            return 0;
        iter = iter -> next;
    }

    /* if you got out from the last loop, it means that there is no SymTableEntrys 
     * with 'pcKey', so you can just make the new SymTableEntry, insert it at the
     * start of the list at the index of the hash table, and return 1(TRUE) */

    newSymTableEntry = (SymTableEntry *) malloc(sizeof(SymTableEntry));
    newSymTableEntry -> key = (char *) malloc((strlen(pcKey) + 1) * sizeof(char));
    strcpy(newSymTableEntry -> key, pcKey);
    newSymTableEntry -> value = (void *) pcValue;

    newSymTableEntry -> next = oSymTable -> hashtable[index];
    oSymTable -> hashtable[index] = newSymTableEntry;
    oSymTable -> length++;

    /* If insertion of new SymTableEntry makes length exceed some number,
     * expand the hashtable */
    if(oSymTable -> length > diffSizes[oSymTable -> currentSizeIn]
       && oSymTable -> currentSizeIn != 7)
        expandTable(oSymTable);

    return 1;
}

int SymTable_remove(SymTable_T oSymTable, const char *pcKey){
    unsigned int index = SymTable_hash(pcKey, oSymTable -> currentSizeIn); 
    SymTableEntry *iter = oSymTable -> hashtable[index], *prev = NULL;
    assert(oSymTable);
    assert(pcKey);

    while(iter){
        /* Find SymTableEntry to remove */
        if(strcmp(iter -> key, pcKey) == 0)
            break;
        prev = iter;
        iter = iter -> next;
    }

    /* if iter is NULL, it means that you did not find the SymTableEntry
     * with key == 'pcKey', so just return 0(FALSE). */
    if(iter == NULL)
        return 0;
    /* else remove the SymTableEntry you found */
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
    /* Reduce length by one since you have removed one SymTableEntry*/
    oSymTable -> length--;
    /* SymTableEntry successfully removed so return 1(TRUE). */
    return 1;
}

int SymTable_contains(SymTable_T oSymTable, const char *pcKey){
    unsigned int index = SymTable_hash(pcKey, oSymTable -> currentSizeIn); 
    SymTableEntry *iter = oSymTable -> hashtable[index];
    assert(oSymTable);
    assert(pcKey);

    while(iter){
        /* If you find the SymTableEntry you are searching, just return 1(TRUE) */
        if(strcmp(iter -> key, pcKey) == 0)
            return 1;
        iter = iter -> next;
    }

    /* If you got here it means that the SymTableEntry with key == 'pcKey'
     * was not found and thus 'oSymTable' does not contain it.
     * So just return 0(FALSE). */
    return 0;
}

void *SymTable_get(SymTable_T oSymTable, const char *pcKey){
    unsigned int index = SymTable_hash(pcKey, oSymTable -> currentSizeIn); 
    SymTableEntry *iter = oSymTable -> hashtable[index];
    assert(oSymTable);
    assert(pcKey);

    while(iter){
        /* If you find the SymTableEntry you are searching, return its value */
        if(strcmp(iter -> key, pcKey) == 0)
            return iter -> value;
        iter = iter -> next;
    }

    /* If you got here it means that the SymTableEntry with key == 'pcKey'
     * was not found and thus 'oSymTable' does not contain it.
     * So just return NULL. */
    return NULL;
}

void SymTable_map(SymTable_T oSymTable, 
void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),
const void *pvExtra){
    
    int i, size = diffSizes[oSymTable -> currentSizeIn];
    SymTableEntry *iter = NULL;
    assert(oSymTable);
    assert(pfApply);

    /* Iterate oSymTable's hashtable and call 'pfApply' for every SymTableEntry */
    for(i = 0; i < size; i++){
        iter = oSymTable -> hashtable[i];
        while(iter){
            (*pfApply)(iter -> key, iter -> value, (void *) pvExtra);
            iter = iter -> next;
        }
    }
} 
