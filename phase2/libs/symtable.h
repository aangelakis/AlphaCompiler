#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct SymTable_T* SymTable_T;

/* Symbol Table Entries */

typedef struct Variable {
    const char *name;
    unsigned int scope;
    unsigned int line;
} Variable;

typedef struct Function {
    const char *name;
    //List of arguments
    unsigned int scope;
    unsigned int line;
} Function;

enum SymbolType {
    GLOBAL, LOCAL, FORMAL, USERFUNC, LIBFUNC
};

typedef struct SymbolTableEntry {
    int isActive; //Boolean
    union {
        Variable *varVal;
        Function *funcVal;
    } value;
    enum SymbolType type;
} SymbolTableEntry;


/* SymTable_T interface */

/* Returns a new empty SymTable(no bindings) */
SymTable_T SymTable_new(void);

/* Frees all memory allocated by 'oSymTable'
 * Does nothing if 'oSymTable' is NULL. */
void SymTable_free(SymTable_T oSymTable);

/* Returns number of binding in 'oSymTable' 
 * It is a checked runtime error for 'oSymTable' to be NULL. */
unsigned int SymTable_getLength(SymTable_T oSymTable);

/* Inserts new binding with key 'pcKey' to 'oSymTable' if it doesn't
 * already exists in 'oSymTable' and returns 1(TRUE).
 * Does nothing and returns 0(FALSE) in any other situation.
 * It is a checked runtime error for 'oSymTable' or 'pcKey' to be NULL. */
int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pcValue);

/* Removes binding with 'pcKey' if it exists in the 'oSymTable'
 * and returns 1(TRUE).
 * Does nothing and returns 0(FALSE) in any other situation.
 * It is a checked runtime error for 'oSymTable' or 'pcKey' to be NULL. */
int SymTable_remove(SymTable_T oSymTable, const char *pcKey);

/* Returns 1(TRUE) if binding with 'pcKey' exists in 'oSymTable',
 * else returns 0(FALSE).
 * It is a checked runtime error for 'oSymTable' or 'pcKey' to be NULL. */
int SymTable_contains(SymTable_T oSymTable, const char *pcKey);

/* Returns corresponding value to 'pcKey' if 'pcKey' exists in 'oSymTable',
 * else returns NULL.
 * It is a checked runtime error for 'oSymTable' or 'pcKey' to be NULL. */
void *SymTable_get(SymTable_T oSymTable, const char *pcKey);

/* Applys function 'pfApply' to every binding in 'oSymTable'
 * and "passes" 'pvExtra' as extra argument to this function.
 * It is a checked runtime error for 'oSymTable' or 'pcApply' to be NULL. */
void SymTable_map(SymTable_T oSymTable, 
void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),
const void *pvExtra); 
