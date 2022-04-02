#include "symtable/symtable.h"
#include "SymTableEntry.h"
#include "scopelists.h"
#define TESTSIZE 16 

char libraryFunctions[12][24]={
    "print",
    "input",
    "objectmemberkeys",
    "objecttotalmembers",
    "objectcopy",
    "totalarguments",
    "argument",
    "typeof",
    "strtonum",
    "sqrt",
    "cos",
    "sin"
};

void do_nothing(void * a){
    puts("I AM NOBODY");
}

int main(){
    SymTable_T testTable = SymTable_new();
    SymTableEntry* tmp;
    scopeArray *array = scope_initialize();


    for (int i = 0; i < 12; i++)
    {
        char *key = strdup(libraryFunctions[i]);
        tmp = makeSymTableEntry(key, NULL, 0, 0, LIBFUNC);
        SymTable_put(testTable, key, (void*)tmp);
        insert_to_scopeArr(&array,0,tmp);
    }
    printf("lookup %s \n",lookup_with_scope(&array,0,"sin")->value.funcVal->name);
    
    soft_hide(&array,0);
    if (lookup_with_scope(&array,0,"sin")==NULL)
    {
        printf("successfull hide\n");
    }
    printf("\n\n calling print before unhide \n\n");
    SymTable_quickApply(testTable, printSymTableEntry);
    printf("\n");


    unhide(&array,0);
    if (lookup_with_scope(&array,0,"sin")!=NULL)
    {
        printf("successfull unhide\n");
    }
    free_scopeArr(array);
    
    SymTable_quickApply(testTable, printSymTableEntry);

    SymTable_free(testTable);
    return 0;
}

