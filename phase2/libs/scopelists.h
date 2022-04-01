#ifndef SCOPELIST_HEADER
#define SCOPELIST_HEADER
#include "zarkList.h"
#include "symtable.h"
typedef zarkList scopelist;

typedef struct scopeArray {
    scopelist* scopes;
    int size;
} scopeArray;

/*hides the elements of the given scope */
void soft_hide(scopeArray* array, int scope);

/*hides the elements of the given scope and removes the list from the scope list*/
void hard_hide(scopeArray* array, int scope);

/*unhides every element of the given scope*/
void unhide(scopeArray* array, int scope);

/*initializes the scope array to hold 5 scopelists*/
scopeArray scope_initialize();

/*expands the scope array to hold 5 more scopelists*/
scopeArray* expand_scopeArr(scopeArray* array);

/*frees the given scopeArray*/
void free_scopeArr(scopeArray* array);

/*puts in the scopeArray at the end of the scope list the entry*/
void insert_to_scopeArr(int scope, SymTableEntry * entry);


#endif



