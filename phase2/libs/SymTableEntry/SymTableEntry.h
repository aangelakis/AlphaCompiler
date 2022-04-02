#ifndef SYMTABLEENTRY_HEADER
#define SYMTABLEENTRY_HEADER
#include "../zarkList/zarkList.h"
#include <string.h>
typedef struct zarkList idList;

#define IS_FUNCTION(entry) (entry->type == USERFUNC || entry->type == LIBFUNC)

int isActive(void* entry);

char *idListContent_to_string(void* content);

extern char symTypes[5][20];

/* Symbol Table Entries */

typedef struct Variable {
    const char *name;
    unsigned int scope;
    unsigned int line;
} Variable;

typedef struct Function {
    const char *name;
    idList* args;   //List of arguments
    unsigned int scope;
    unsigned int line;
} Function;

typedef enum SymbolType {
    VAR_GLOBAL, VAR_LOCAL, VAR_FORMAL, USERFUNC, LIBFUNC
} SymbolType;

typedef struct SymTableEntry {
    int isActive; //Boolean
    union {
        Variable *varVal;
        Function *funcVal;
    } value;
    enum SymbolType type;
} SymTableEntry;

SymTableEntry* makeSymTableEntry(const char* name, idList* args, unsigned scope, unsigned line, SymbolType type);

void printSymTableEntry(void*);

void freeSymTableEntry(SymTableEntry* entry);

#endif