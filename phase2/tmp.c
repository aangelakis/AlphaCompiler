#include"yacc_utilities.h"
#include "libs/scopelist/scopelists.h"
#include "libs/SymTableEntry/SymTableEntry.h"
#include "libs/symtable/symtable.h"
#include "libs/zarkList/zarkList.h"

/*
function g(){
    local x;
    function f(){
        x = 5;  // error because of local x in function g and there is function in between
    }
}

function g(){
    local x;
    {
        x = 5;  // not error because it's just a block
    }
}

local x = 24
function g(){
    local x;
    function f(){
        x = 5;      // error because of local x in function g and there is function in between, it does not matter there is a global x also
        ::x = 5;    // not error because we only search for globals
        print(x);       
        ::print;     
    }
}

*/

// otan kaleitai auto kai parembaletai synarthsh exei ginei SOFTHIDE
/* genika exoume duo periptwseis gia ta conflicts onomatwn:
        1) na paremballetai synarthsh kai na allazei auth to scope
        2) na uparxei apla ena block pou allazei to scope
    emeis theloume na kanoume lookup kai logw tou SOFTHIDE ama broume kati me th mia
    na to therwroume swsto giati gia na mporoume na to doume, den exei ginei softhide kai ara den paremballetai synarthsh.
    
    epeita ama den broume tpt theloume na psaksoume ta scopelist bottom-up kai ama broume kati pou den einai global na petaksoume error
    ama broume kati global tote einai swsto kai to epistrefoume.
*/
void Manage_lvalue_id(SymTableEntry** new_entry, char* id, int scope, int line){
    printf("lvalue -> id\n");

    // search bottom-up for active matching symbols in all scopes except global
    int tmpscope = scope;
    SymTableEntry* entry = lookup_active_with_scope(&scpArr, tmpscope, id);
    while(entry == NULL && tmpscope > 0){
        entry = lookup_active_with_scope(&scpArr, tmpscope, id);
        tmpscope--;
    }

    // if you didn't find anything active
    // search bottom-up for any matching symbols in all scopes except global
    if(entry == NULL) {
        int tmpscope = scope;
        entry = lookup_any_with_scope(&scpArr, tmpscope, id);
        while(entry == NULL && tmpscope > 0){
            entry = lookup_any_with_scope(&scpArr, tmpscope, id);
            tmpscope--;
        }

        if(entry == NULL){   
            // lookup for a global matching symbol
            entry = lookup_active_with_scope(&scpArr, 0, id);
            // if you didn't find anything then create new symbol
            if(entry == NULL){
                SymbolType type = (scope == 0) ? VAR_GLOBAL : VAR_LOCAL;
                entry = makeSymTableEntry(id, NULL,  scope, line, type);
                SymTable_put(symTable,id, entry);
                insert_to_scopeArr(&scpArr, scope, entry);
            }
            // else you found something active it means that the varible refers to it, so returned it as is
            else{
                *new_entry = entry;     // return but we use call by reference
                return;
            }
        }
        // if you found a matching non-active symbol then there is an error
        else{
            fprintf(stderr, "ERROR: Cannot access local variable \'%s\' in line %u with scope %u\n"
                                    , id, entry->value.varVal->line, entry->value.varVal->scope);
            return;
        }
    }
    // else you found something active it means that the varible refers to it, so returned it as is
    else {
        *new_entry = entry;     // return but we use call by reference
        return;
    }
}

void Manage_lvalue_localID(SymTableEntry** new_entry, char* id, int scope, int line){
    printf("lvalue -> local id\n");

    SymTableEntry* entry = lookup_active_with_scope(&scpArr, scope, id);
    if(entry == NULL){
        entry = SymTable_lookup(symTable, id, isActive);

        if(entry != NULL && entry->type == LIBFUNC) {
            fprintf(stderr, "ERROR: Cannot shadow a library function \'%s\'\n", id);
            return;
        }
        else {
            if(scope == 0)
                entry = makeSymTableEntry(id, NULL,  scope, line, VAR_GLOBAL);
            else
                entry = makeSymTableEntry(id, NULL,  scope, line, VAR_LOCAL);

            SymTable_put(symTable,id, entry);
            insert_to_scopeArr(&scpArr, scope, entry);
        }
    }
    else
        *new_entry = entry;
}

void Manage_lvalue_globalID(SymTableEntry** new_entry, char* id){
    printf("lvalue -> ::id\n");
    
    SymTableEntry* entry = lookup_active_with_scope(&scpArr, 0, id);
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