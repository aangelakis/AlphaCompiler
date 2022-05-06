#include "libs/scopelist/scopelists.h"
#include "libs/SymTableEntry/SymTableEntry.h"
#include "libs/symtable/symtable.h"
#include "libs/zarkList/zarkList.h"
#include "expression.h"
#include "parser.h"
#include "libs/Vektor/Vektor.h"
#include "expression.h" 
#include "quads.h"
#include "scanner.h"

SymTable_T symTable;
scopeArray* scpArr;
Vektor* quads;

scopeArray* globalScopeArr;

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

int main(int argc, char *argv[]){
    // initialize necessary global structures
	symTable = SymTable_new();
	scpArr = scope_initialize();
	globalScopeArr = scope_initialize();
    quads = vektor_initialize();

    SymTableEntry* tmp;
    
    if (argc > 1)
    {
        if (!(yyin = fopen(argv[1], "r")))
        {
            fprintf(stderr, "Cannot read file: %s\n", argv[1]);
            return 1;
        }
    }
    else
    {
        yyin = stdin;
    }

    /* Putting all the library functions in the SymTable */
    for (int i = 0; i < 12; i++){
        //char *key = strdup(libraryFunctions[i]);
        tmp = makeSymTableEntry(libraryFunctions[i], NULL, 0, 0, LIBFUNC);
        SymTable_put(symTable, libraryFunctions[i], (void*)tmp);
        insert_to_scopeArr(&scpArr,0,tmp);
    }

    yyparse();
    puts("----------------Symbol Table Entries-------------------------");
    //SymTable_quickApply(symTable, printSymTableEntry);
    int len = globalScopeArr->size;
    for(int i = 0; i < len; i++) {
        if(globalScopeArr->scopes[i]->size != 0) {
            char scopeStr[1024];
            sprintf(scopeStr, "\n-----------\tScope #%d\t-----------", i);
            puts(scopeStr);
            zarklist_apply(globalScopeArr->scopes[i], printSymTableEntry);
        }
    }
    puts("quad#\t\topcode\t\t\t\t\t  result\t\targ1\t\targ2\t\tlabel");
    vektor_apply(quads, print_quad);

    SymTable_free(symTable);
    free_scopeArr(scpArr);
    free_scopeArr(globalScopeArr);
    return 24;
}