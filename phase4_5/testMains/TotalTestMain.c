#include<stdio.h>
#include<string.h>
#include"../libs/symtable/symtable.h"
#include"../libs/scopelist/scopelists.h"
#include"../libs/SymTableEntry/SymTableEntry.h"
#include"../libs/zarkList/zarkList.h"

scopeArray* globalScopeArr;

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


int main(){
    SymTable_T testTable = SymTable_new();
    SymTableEntry* tmp;
    scopeArray *array = scope_initialize();
    globalScopeArr = scope_initialize();
    int scope = 0;

    /* Putting all the library functions in the SymTable */
    for (int i = 0; i < 12; i++){
        //char *key = strdup(libraryFunctions[i]);
        tmp = makeSymTableEntry(libraryFunctions[i], NULL, scope, 0, LIBFUNC);
        SymTable_put(testTable, libraryFunctions[i], (void*)tmp);
        insert_to_scopeArr(&array,0,tmp);
    }

    if(lookup_active_with_scope(&array, scope, "x") == NULL){
        SymTableEntry *x = makeSymTableEntry("x", NULL,  scope, 1, VAR_GLOBAL);
        SymTable_put(testTable,"x",x);
        insert_to_scopeArr(&array,scope,x);   
    }else{
        printf("x already exists\n");
    }

    /*if(lookup_with_scope(&array, scope, "input") == NULL){
        printf("failure couldn't find input in this scope");
    }*/


    if(lookup_active_with_scope(&array, scope, "g") == NULL){
        SymTableEntry *g = makeSymTableEntry("g", NULL,  scope, 2, VAR_GLOBAL);
        SymTable_put(testTable,"g",g);
        insert_to_scopeArr(&array,scope,g);
    }else{
        printf("g already exists\n");
    }


    scope ++;
    
    idList* f_arguments = zarklist_initialize(0);

    SymTableEntry *f_x = makeSymTableEntry("x", NULL,  scope, 4, VAR_FORMAL);
    SymTable_put(testTable,"x",f_x);
    insert_to_scopeArr(&array,scope,f_x);
    zarklist_insert(f_arguments,"x");


    SymTableEntry *f_y = makeSymTableEntry("y", NULL,  scope, 4, VAR_FORMAL);
    SymTable_put(testTable,"y",f_y);
    insert_to_scopeArr(&array,scope,f_y);
    zarklist_insert(f_arguments,"y");
    
    //to look up gia print(x + y)
    if (lookup_active_with_scope(&array,scope,"y")==NULL ||lookup_active_with_scope(&array,scope,"x")==NULL)
    {
      printf("failure couldnt find x or y in this scope \n");
      return -1;
    }

    //to look up gia p = y
    if (lookup_active_with_scope(&array,scope,"y")==NULL)
    {
      printf("failure couldnt find y in this scope \n");
      return -1;
    }

    //to look up gia to p
    if (lookup_active_with_scope(&array,scope,"p")!=NULL)
    {
      printf("failure p already exists in this scope \n");
      return -1;
    }

    SymTableEntry *p = makeSymTableEntry("p", NULL,  scope, 6, VAR_LOCAL);
    SymTable_put(testTable,"p",p);
    insert_to_scopeArr(&array,scope,p);

    //to look up gia to p
    if (lookup_active_with_scope(&array,scope,"p")==NULL)
    {
      printf("failure couldnt find p in this scope \n");
      return -1;
    }

    //to look up gia ::print
    if (lookup_active_with_scope(&array,0,"print")==NULL)
    {
      printf("failure couldnt find local in global scope \n");
      return -1;
    }
    //gia na mpume stin h
    soft_hide(&array ,scope);
    scope++;
	
	idList *h_idlist = zarklist_initialize(0);

	SymTableEntry *a = makeSymTableEntry("a", NULL,  scope, 8, VAR_FORMAL);
    SymTable_put(testTable,"a",a);
    insert_to_scopeArr(&array,scope,a);
	zarklist_insert(h_idlist,"a");
	//to look up gia a
    if (lookup_active_with_scope(&array,scope,"a")==NULL)
    {
		printf("failure couldnt find local a in this scope \n");
		return -1;
    }

	if (lookup_active_with_scope(&array,scope,"x")==NULL)
    {
		printf("AUTO EINAI SWSTO => failure couldnt find local x in this scope \n");
    }

	if (lookup_active_with_scope(&array,scope,"y")==NULL)
    {
		printf("AUTO EINAI SWSTO => failure couldnt find local y in this scope \n");
    }

	hard_hide(&array,scope);
	scope--;
	unhide(&array,scope);
	//bazw to h function

	SymTableEntry *h_func = makeSymTableEntry("h", h_idlist,  scope, 8, USERFUNC);
    SymTable_put(testTable,"h",h_func);
    insert_to_scopeArr(&array,scope,h_func);


	//11 y = h(::x);
	//12 }

	if (lookup_active_with_scope(&array,scope,"h")==NULL)
    {
		printf("failure couldnt find h function in this scope \n");
		return -1;
    }
	if (lookup_active_with_scope(&array,0,"x")==NULL)
    {
		printf("failure couldnt find x in global scope \n");
		return -1;
    }

	hard_hide(&array,scope);
	scope--;
	unhide(&array,scope);

	SymTableEntry *foo = makeSymTableEntry("foo", f_arguments,  scope, 4, USERFUNC);
    SymTable_put(testTable,"foo",foo);
    insert_to_scopeArr(&array,scope,foo);

	scope++;
	scope++;

	//SymTable_lookup(SymTable_T oSymTable, const char *pcKey, int (*condition)(void *));
	if (SymTable_lookup(testTable,"x",isActive)==NULL)
	{
		printf("failure couldnt find x \n");
	}
	printf("%d line of found x is \n",((SymTableEntry *)SymTable_lookup(testTable,"x",isActive))->value.varVal->line);

  SymTable_quickApply(testTable, printSymTableEntry);
  return 0;
}