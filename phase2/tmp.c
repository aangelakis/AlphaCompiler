#include"yacc_utilities.h"
#include "libs/scopelist/scopelists.h"
#include "libs/SymTableEntry/SymTableEntry.h"
#include "libs/symtable/symtable.h"
#include "libs/zarkList/zarkList.h"


void Manage_lvalue_id(SymTableEntry** new_entry, char* id, int scope, int line){
    printf("lvalue -> id\n");

    int tmpscope = scope;
    SymTableEntry* entry = lookup_with_scope(&scpArr, scope, id);
    while(entry == NULL && tmpscope > 0){
        entry = lookup_with_scope(&scpArr, tmpscope, id);
        tmpscope--;
    }

    if(entry == NULL) {
        if(scope == 0)
            entry = makeSymTableEntry(id, NULL,  scope, line, VAR_GLOBAL);
        else
            entry = makeSymTableEntry(id, NULL,  scope, line, VAR_LOCAL);

        SymTable_put(symTable,id, entry);
        insert_to_scopeArr(&scpArr, scope, entry);
    }
    else if(entry->type == LIBFUNC) {
        fprintf(stderr, "ERROR: Cannot shadow a library function \'%s\'\n", id);
        return;
    }
    else
        *new_entry = entry;

}

void Manage_lvalue_localID(SymTableEntry** new_entry, char* id, int scope, int line){
    printf("lvalue -> local id\n");

    SymTableEntry* entry = lookup_with_scope(&scpArr, scope, id);
    if(entry == NULL){
        entry = SymTable_lookup(symTable, id, isActive);

        if(entry == NULL) {
            if(scope == 0)
                entry = makeSymTableEntry(id, NULL,  scope, line, VAR_GLOBAL);
            else
                entry = makeSymTableEntry(id, NULL,  scope, line, VAR_LOCAL);

            SymTable_put(symTable,id, entry);
            insert_to_scopeArr(&scpArr, scope, entry);
        }
        else if(entry->type == LIBFUNC) {
            fprintf(stderr, "ERROR: Cannot shadow a library function \'%s\'\n", id);
            return;
        }
    }
    else
        *new_entry = entry;
}

void Manage_lvalue_globalID(SymTableEntry** new_entry, char* id){
    printf("lvalue -> ::id\n");
    
    SymTableEntry* entry = lookup_with_scope(&scpArr, 0, id);
    if(entry == NULL){
        fprintf(stderr, "ERROR 404: Global variable named \'%s\' not found\n", id);
        *new_entry = NULL;
        return;
    }
    else
        *new_entry = entry;
}

void Manage_lvalue_member(){
    printf("lvalue -> member\n");
}