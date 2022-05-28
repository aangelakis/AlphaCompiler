#include"SymTableEntry.h"

char symTypes[5][20]= {
    "global variable",
    "local variable",
    "formal argument",
    "user function",
    "library function"    
};

SymTableEntry* makeSymTableEntry(const char* name, idList* args, unsigned scope, unsigned line, SymbolType type, scopespace_t scopespace, int offset)
{
    SymTableEntry* new_entry = malloc(sizeof(SymTableEntry));

    new_entry->isActive = 1;
    new_entry->type = type;
    if(IS_FUNCTION(new_entry)) {
        new_entry->value.funcVal = malloc(sizeof(Function));
        new_entry->value.funcVal->name  = strdup(name);
        new_entry->value.funcVal->args  = args;
        new_entry->value.funcVal->scope = scope;
        new_entry->value.funcVal->line  = line;
    }
    else{
        new_entry->value.varVal = malloc(sizeof(Variable)); 
        new_entry->value.varVal->name  = strdup(name);
        new_entry->value.varVal->scope = scope;
        new_entry->value.varVal->line  = line;
        new_entry->value.varVal->offset = offset;
        new_entry->value.varVal->scopespace = scopespace;
        printf("name : %s , scopespace : %d , offset : %d\n",name,scopespace,offset);
        
    }

    return new_entry;
}

void printSymTableEntry(void* entry)
{
    SymTableEntry* symtab = (SymTableEntry*) entry;
    int type = symtab->type;
    
    if(IS_FUNCTION(symtab)){
        
        printf("\"%s\" [%s]", symtab->value.funcVal->name,symTypes[type]);
        
        printf(" (line %u) (scope %u)",  symtab->value.funcVal->line, symtab->value.funcVal->scope);

        if(type == USERFUNC){
            printf(" (funcstart at %d)  (local vars %d)", symtab->value.funcVal->quadfuncStartIndex, symtab->value.funcVal->numOfLocalVars);
        }
        printf("\n");
        
    }
    else{
        printf("\"%s\" [%s] (line %u) (scope %u)\n"\
        , symtab->value.varVal->name, symTypes[type] , symtab->value.varVal->line, symtab->value.varVal->scope );
    }
}

void freeSymTableEntry(SymTableEntry* entry)
{
    if(IS_FUNCTION(entry)){
        free((char*)entry->value.funcVal->name);
        zarklist_free(entry->value.funcVal->args);
        free(entry->value.funcVal);
    }
    else{
        free((char*)entry->value.varVal->name);
        free(entry->value.varVal);
    }
    free(entry);
}

int isActive(void* entry) { return ((SymTableEntry*) entry)->isActive; }

char *idListContent_to_string(void* content){ return ((char*) content); }