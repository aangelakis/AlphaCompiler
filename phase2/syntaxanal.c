#include "libs/scopelist/scopelists.h"
#include "libs/SymTableEntry/SymTableEntry.h"
#include "libs/symtable/symtable.h"
#include "libs/zarkList/zarkList.h"
#include "parser.h"
#include "scanner.h"

SymTable_T symTable;
scopeArray* scpArr;

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
    puts("\n\n\n"); 
    puts("----------------Symbol Table Entries-------------------------\n");
    SymTable_quickApply(symTable, printSymTableEntry);
    return 24;
}