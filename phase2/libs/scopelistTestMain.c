#include"SymTableEntry.h"
#include"scopelists.h"
#include<stdio.h>

/*
local z;
func f(x,y){
    return x;
}
local x;

*/
int main(){
    
    scopeArray *array = scope_initialize();
    
    
    SymTableEntry *z = makeSymTableEntry("z", NULL,  0, 1, GLOBAL);
    insert_to_scopeArr(&array,0,z);

    idList* args = zarklist_initialize(0);
    zarklist_insert(args, "x");
    SymTableEntry *formal_x = makeSymTableEntry("x", NULL,  1, 2, FORMAL);
    insert_to_scopeArr(&array,1,formal_x);

    zarklist_insert(args, "y");
    SymTableEntry *formal_y = makeSymTableEntry("y", NULL,  1, 2, FORMAL);
    insert_to_scopeArr(&array,1,formal_y);
    
    printf("%s with type=%d\n",lookup_with_scope(&array,1,"x")->value.varVal->name,lookup_with_scope(&array,1,"x")->type);
    printf("%s with type=%d\n",lookup_with_scope(&array,1,"y")->value.varVal->name,lookup_with_scope(&array,1,"y")->type);

    
    hard_hide(&array,1);
    
    if (lookup_with_scope(&array,1,"x")==NULL)
    {
        printf("hide is successfull \n");
    }
    
    SymTableEntry *f = makeSymTableEntry("f", args,  0, 2, USERFUNC);
    insert_to_scopeArr(&array,0,f);

    SymTableEntry *global_x = makeSymTableEntry("x", NULL,  0, 4, GLOBAL);
    insert_to_scopeArr(&array,0,global_x);

    printf("%s with type=%d\n",lookup_with_scope(&array,0,"x")->value.varVal->name,lookup_with_scope(&array,0,"x")->type);
    printf("%s with type=%d\n",lookup_with_scope(&array,0,"f")->value.funcVal->name,lookup_with_scope(&array,0,"f")->type);
    printf("%s with type=%d\n",lookup_with_scope(&array,0,"z")->value.varVal->name,lookup_with_scope(&array,0,"z")->type);

    SymTableEntry *nikos = makeSymTableEntry("nikos", NULL,  6, 0, GLOBAL);
    printf("before %d size of array \n\n",array->size);
    insert_to_scopeArr(&array,6,nikos);
    printf("after %d size of array \n\n",array->size);
    printf("%s with type=%d\n",lookup_with_scope(&array,6,"nikos")->value.varVal->name,lookup_with_scope(&array,6,"nikos")->type);
    
    
    
    free_scopeArr(array);
    
    return 0;
}