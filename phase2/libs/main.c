#include "symtable.h"
#define TESTSIZE 16 

void multiply(const char*, void*, void*);

int main(){
    SymTable_T testTable;
    int i, ints[TESTSIZE], *tmp, mapAdd = 16;
    char *strs[TESTSIZE];

    testTable = SymTable_new();

    for(i = 0; i < TESTSIZE; i++){
        ints[i] = i;
        strs[i] = (char *) malloc(10 * sizeof(char));
        sprintf(strs[i], "%d", i);
        assert(SymTable_put(testTable, strs[i], (ints + i)) == 1);
    }

    for(i = 0; i < TESTSIZE; i++){
        tmp = SymTable_get(testTable, strs[i]);
        printf("Bindind%d contains %d\n", i, *tmp);
    }
    
    printf("--------------------\n");
    
    tmp = &mapAdd;
    SymTable_map(testTable, multiply,tmp);

    for(i = 0; i < TESTSIZE; i++){
        tmp = SymTable_get(testTable, strs[i]);
        printf("Bindind%d contains %d\n", i, *tmp);
    }

    assert(SymTable_getLength(testTable) == TESTSIZE);

    
    assert(SymTable_remove(testTable, strs[1]) == 1);
    assert(SymTable_remove(testTable, strs[2]) == 1); 

    assert(SymTable_getLength(testTable) == TESTSIZE - 2);
    
    assert(SymTable_contains(testTable, strs[0]) == 1);
    assert(SymTable_contains(testTable, strs[1]) == 0);
    
    tmp = (int *) SymTable_get(testTable, strs[5]);
    assert(*tmp == 26);
    assert(SymTable_get(testTable, strs[1]) == NULL);

    printf("--------------------\n");

    for(i = 0; i < TESTSIZE; i++){
        tmp = SymTable_get(testTable, strs[i]);
        if(tmp)
            printf("Bindind%d contains %d\n", i, *tmp);
    }

    /* clear table to see that it happens correctly */
    for(i = 0; i < TESTSIZE; i++){
        SymTable_remove(testTable, strs[i]);
    }

    printf("--------------------\n");

    for(i = 0; i < TESTSIZE; i++){
        tmp = SymTable_get(testTable, strs[i]);
        if(tmp)
            printf("Bindind%d contains %d\n", i, *tmp);
    }

    SymTable_free(testTable);
    for(i = 0; i < TESTSIZE; i++)
        free(strs[i]);
    return 0;
}

void multiply(const char* key, void *number, void *addition){
    int *num = (int *) number, *add = (int *) addition;
    (*num) = (*num)*2 + *add;
}

