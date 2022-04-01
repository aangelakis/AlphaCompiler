#ifndef SYMTABLEENTRY_HEADER
#define SYMTABLEENTRY_HEADER
#include "zarkList.h"

typedef struct zarkList idList;

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
    GLOBAL, LOCAL, FORMAL, USERFUNC, LIBFUNC
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
#endif