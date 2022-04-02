#include"SymTableEntry.h"

char symTypes[5][20]= {
    "global variable",
    "local variable",
    "formal argument",
    "user function",
    "library function"    
};

SymTableEntry* makeSymTableEntry(const char* name, idList* args, unsigned scope, unsigned line, SymbolType type)
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
    }

    return new_entry;
}

void printSymTableEntry(void* entry)
{
    SymTableEntry* symtab = (SymTableEntry*) entry;
    int type = symtab->type;
    
    if(IS_FUNCTION(symtab)){
        printf("SymTableEntry: <name>=%s, <args>=(", symtab->value.funcVal->name);
        zarklist_print(symtab->value.funcVal->args, idListContent_to_string);
        printf("), <scope>=%u, <line>=%u, <type>=%s\n", symtab->value.funcVal->scope, symtab->value.funcVal->line, symTypes[type]);
    }
    else{
        printf("SymTableEntry: <name>=%s, <scope>=%u, <line>=%u, <type>=%s\n"\
        , symtab->value.varVal->name, symtab->value.varVal->scope, symtab->value.varVal->line, symTypes[type]);
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