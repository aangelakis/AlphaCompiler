#ifndef YACC_UTILITIES_HEADER
#define YACC_UTILITIES_HEADER
#include "libs/scopelist/scopelists.h"
#include "libs/SymTableEntry/SymTableEntry.h"
#include "libs/symtable/symtable.h"
#include "libs/zarkList/zarkList.h"
extern int yylineno;
extern char* yytext;
extern int scope;
extern int flag_scope;
extern scopeArray* scpArr;
extern SymTable_T symTable; 
unsigned int invalid_funcname_number  = 0;

int yyerror(char* yaccProvideMessage)
{
    fprintf(stderr , "\033[0;31mERROR\033[0m\n");
    fprintf(stderr, "\033[0;33m%s\033[0m -> at line %d, before token: \033[0;36m\'%s\'\033[0m\n",  yaccProvideMessage, yylineno, yytext);
    fprintf(stderr , "\033[0;31mINPUT NOT VALID\033[0m\n");
}

int print_custom_error(char* yaccProvideMessage,const char* yaccProvideName,const int scope)
{
    fprintf(stderr , "\033[1;31mERROR\033[0m at line\033[0;35m %d\033[0m, with scope \033[0;35m%d \033[0m: ", yylineno,scope);
    fprintf(stderr, "\033[0;33m%s\033[0m -> at token: \033[0;36m\'%s\'\033[0m\n",  yaccProvideMessage, yaccProvideName);
    //fprintf(stderr , "\033[0;31mINPUT NOT VALID\033[0m\n");
}

//if the the last who called this function is a block(0) and you are a block(0) => scope++
//else if you are a function(1) => scope++
//else if the last was a function and you are a block you change the flag
void ScopeUp(int callee){
    if (callee == 0 && flag_scope == 0)
    {
        //we dont soft hide inside the block
        scope ++;
        printf("Scope up to %d\n",scope);
    }else if (callee == 1){
        //inside one function we soft hide every other scope except the latest scope
        scope ++;
        for (int i = 1; i < scope; i++)
        {
            soft_hide(&scpArr,i);
        }
        flag_scope = 1 ;
        printf("Scope up to %d\n",scope);
    }else {
        //this is again inside a block so we dont soft hide the previous
        flag_scope = 0;
    }
    
    
}
void ScopeDown(int callee){
    //printf("%d\n",scope);
    hard_hide(&scpArr,scope); //hide the current scope
    printf("Scope down to %d\n",--scope);   //print tha we go a scope down
    unhide(&scpArr,scope);  //unhide the scope
    
}

/* Generates a invalid name for a function */
char* invalid_funcname_generator(){
    char* invalid_name = malloc(1024*(sizeof(char)));
    sprintf(invalid_name, "_$f%u", invalid_funcname_number++);
    
    return invalid_name;
}

void Manage_returnstmt_returnexpr(){
    printf("returnstmt -> return expr;\n");
} 

void Manage_returnstmt_return(){
    printf("returnstmt -> return;\n");
}

void Manage_forstmt(){
    printf("forstmt -> for(elist;expr;elist) stmt\n");
}

void Manage_whilestmt(){
    printf("whilestmt -> while(expr) stmt\n");
}

void Manage_ifstmt_ifelse(){
    printf("ifstmt -> if (expr) stmt else\n");
}

void Manage_ifstmt_if(){
    printf("ifstmt -> if (expr)\n"); 
}

void Manage_idlist_empty(idList ** dest){
    //making an empty idlist
    *dest = zarklist_initialize(0);
    printf("idlist -> ε\n"); 
}

void Manage_idlist_idlistId(idList ** dest , idList * old_list , char * new_element){
    //if it already exists in the global scope as an lib func
    SymTableEntry* search = lookup_active_with_scope(&scpArr,0,new_element);
    if (search!=NULL && search->type==LIBFUNC)
    {
        print_custom_error("Formal argument shadows library function",new_element,scope);
        return;
    }
    //if it already exists in the same scope
    search = lookup_active_with_scope(&scpArr,scope,new_element);
    if (search!=NULL)
    {
        print_custom_error("Formal argument already exists in given scope",new_element,scope);        
        return ;
    }
    
    //insertion in the symtable and in the scopelist
    SymTableEntry* entry = makeSymTableEntry(new_element,NULL,scope,yylineno,VAR_FORMAL);
    SymTable_put(symTable,new_element,entry);
    insert_to_scopeArr(&scpArr,scope,entry);

    //insertion in the idlist and saving the idlist
    zarklist_insert(old_list,new_element);
    dest = &old_list;
    printf("idlist -> id,id*\n");
}

void Manage_idlist_id(idList ** dest , char * new_element){
    //if it already exists in the global scope as an lib func
    SymTableEntry* search = lookup_active_with_scope(&scpArr,0,new_element);
    if (search!=NULL && search->type==LIBFUNC)
    {
        print_custom_error("Formal argument shadows library function",new_element,scope);
        return;
    }
    //if it already exists in the same scope
    search = lookup_active_with_scope(&scpArr,scope,new_element);
    if (search!=NULL)
    {
        print_custom_error("Formal argument already exists in given scope",new_element,scope);        
        return ;
    }
    
    //insertion in the symtable and in the scopelist
    SymTableEntry* entry = makeSymTableEntry(new_element,NULL,scope,yylineno,VAR_FORMAL);
    SymTable_put(symTable,new_element,entry);
    insert_to_scopeArr(&scpArr,scope,entry);

    //insertion in the idlist and saving the idlist
    
    *dest = zarklist_initialize(0);
    zarklist_insert(*dest,new_element);
    printf("idlist -> id,id*\n");
}

void Manage_const_number(){
    printf("const -> number\n");
}

void Manage_const_string(){
    printf("const -> string\n");
}

void Manage_const_nil(){
    printf("const -> nil\n");
}

void Manage_const_true(){
    printf("const -> true\n");
}

void Manage_const_false(){
    printf("const -> false\n");
}

void Manage_funcdef_functionId(char *name,idList *args){
    //if it already exists in the global scope as an lib func
    SymTableEntry* search = lookup_active_with_scope(&scpArr,0,name);
    if (search!=NULL && search->type==LIBFUNC)
    {
        print_custom_error("User function shadows library function",name,scope);
        return;
    }
    //if it already exists in the same scope print error
    if ((search = lookup_active_with_scope(&scpArr,scope,name)) != NULL)
    {
        if(IS_FUNCTION(search))
            print_custom_error("Function redefinition",name,scope);
        else
            print_custom_error("Funtion declared with same name as variable",name,scope);
        return ;
    }
    
    //insertion in the symtable and in the scopelist
    SymTableEntry* entry = makeSymTableEntry(name,args,scope,yylineno,USERFUNC);
    SymTable_put(symTable,name,entry);
    insert_to_scopeArr(&scpArr,scope,entry);

    printf("function id (idlist) block\n");
}

void Manage_funcdef_function(idList *args){
    char * name = invalid_funcname_generator();
    //insertion in the symtable and in the scopelist
    SymTableEntry* entry = makeSymTableEntry(name,args,scope,yylineno,USERFUNC);
    SymTable_put(symTable,name,entry);
    insert_to_scopeArr(&scpArr,scope,entry);

    printf("function (idlist) block\n");
}

void Manage_block_liststmt(){
    printf("block -> stmt*\n");
}

void Manage_block_emptyblock(){
    printf("block -> {}\n");
}

void Manage_indexedelem(){
    printf("indexedelem -> {expr:expr}\n");
}

void Manage_indexed_indexedIndexedelem(){
    printf("indexed -> indexed,indexedelem\n");
}

void Manage_indexed_indexedelem(){
    printf("indexed -> indexedelem\n");
}

void Manage_objectdef_elist(){
    printf("objectdef -> [elist]\n");
}

void Manage_objectdef_indexed(){
    printf("objectdef -> [indexed]\n");
}

void Manage_elist_empty(){
    printf("elist -> ε\n");
}

void Manage_elist_elistExpr(){
    printf("elist -> elist,expr\n");
}

void Manage_elist_expr(){
    printf("elist -> epxr\n");
}

void Manage_methodcall(){
    printf("methodcall -> ..id(elist)\n");
}

void Manage_normcall(){
    printf("normcall -> (elist)\n");
}

void Manage_callsuffix_normcall(){
    printf("callsuffix -> normcall\n");
}

void Manage_callsuffix_methodcall(){
    printf("callsuffix -> methodcall\n");
}

void Manage_call_callElist(){
    printf("call -> call(elist)\n");
}

void Manage_call_lvalueCallsuffix(SymTableEntry * entry){
    if(entry == NULL)
        {print_custom_error("Function not declared", "", scope);}
    else if(entry->type != USERFUNC && entry->type != LIBFUNC){
        print_custom_error("Cant make call from a variable",entry->value.varVal->name,scope);
    }
    printf("call -> lvalue callsuffix\n");
}

void Manage_call_funcdefElist(){
    printf("call -> (funcdef)(elist)\n");
}

void Manage_member_lvalueID(){
    printf("member -> lvalue.id\n");
}

void Manage_member_lvalueExpr(){
    printf("member -> lvalue[expr]\n");
}

void Manage_member_callID(){
    printf("member -> call.id\n");
}

void Manage_member_callExpr(){
    printf("member -> call[expr]\n");
}

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
                *new_entry = entry;
                return;
            }
            // else you found something active it means that the varible refers to it, so returned it as is
            else{
                *new_entry = entry;     // return but we use call by reference
                return;
            }
        }
        // if you found a matching non-active symbol then there is an error
        else{
            char errmsg[1024];
            if (entry->type == USERFUNC || entry->type == LIBFUNC)
            {
                sprintf(errmsg, "Cannot access local function declared in line %d with scope %d", entry->value.funcVal->line, entry->value.funcVal->scope);
            }else{
                sprintf(errmsg, "Cannot access local variable declared in line %d with scope %d", entry->value.varVal->line, entry->value.varVal->scope);
            }
            print_custom_error(errmsg , id, scope);
            *new_entry = NULL;
            return;
        }
    }
    //
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

        if(entry != NULL && entry->type == LIBFUNC && scope != 0) {
            print_custom_error("Cannot shadow a library function", id, scope);
            *new_entry = NULL;
            return;
        }
        else {
            if(scope == 0)
                entry = makeSymTableEntry(id, NULL,  scope, line, VAR_GLOBAL);
            else
                entry = makeSymTableEntry(id, NULL,  scope, line, VAR_LOCAL);

            SymTable_put(symTable,id, entry);
            insert_to_scopeArr(&scpArr, scope, entry);
            *new_entry = entry;
            return;
        }
    }
    else {
        *new_entry = entry;
        return;
    }
}

void Manage_lvalue_globalID(SymTableEntry** new_entry, char* id){
    printf("lvalue -> ::id\n");
    
    SymTableEntry* entry = lookup_active_with_scope(&scpArr, 0, id);
    if(entry == NULL){
        print_custom_error("Global variable not found", id, scope);
        *new_entry = NULL;
        return;
    }
    else
        *new_entry = entry;
}

void Manage_lvalue_member(){
    printf("lvalue -> member\n");
}

void Manage_primary_lvalue(){
    printf("primary -> lvalue\n");
}

void Manage_primary_call(){
    printf("primary -> call\n");
}

void Manage_primary_objectdef(){
    printf("primary -> objectdef\n");
}

void Manage_primary_funcdef(){
    printf("primary -> (funcdec)\n"); 
}

void Manage_primary_const(){
    printf("primary -> const\n");
}

void Manage_assignexpr(SymTableEntry* entry){
    if(entry == NULL){return;}
    if(entry->type==USERFUNC || entry->type==LIBFUNC){
        print_custom_error("Cant make assignment to function",entry->value.funcVal->name,scope);
    }
    
}

void Manage_term_expr(){
    printf("term -> (expr)\n");
}

void Manage_term_uminusExpr(){
    printf("term -> -expr\n");
}

void Manage_term_notExpr(){
    printf("term -> not expr\n");
}

void Manage_term_pluspluslvalue(SymTableEntry *entry){
    if(entry == NULL){return;}
    if(entry->type==USERFUNC || entry->type==LIBFUNC){
        print_custom_error("Cant use a function as an lvalue",entry->value.funcVal->name,scope);
    }
    printf("term -> ++lvalue\n");
}

void Manage_term_lvalueplusplus(SymTableEntry *entry){
    if(entry == NULL){return;}
    if(entry->type==USERFUNC || entry->type==LIBFUNC){
        print_custom_error("Cant use a function as an lvalue",entry->value.funcVal->name,scope);
    }
    printf("term -> lvalue++\n");
}

void Manage_term_minusminuslvalue(SymTableEntry *entry){
    if(entry == NULL){return;}
    if(entry->type==USERFUNC || entry->type==LIBFUNC){
        print_custom_error("Cant use a function as an lvalue",entry->value.funcVal->name,scope);
    }
    printf("term -> --lvalue\n");
}

void Manage_term_lvalueminusminus(SymTableEntry *entry){
    if(entry == NULL){return;}
    if(entry->type==USERFUNC || entry->type==LIBFUNC){
        print_custom_error("Cant use a function as an lvalue",entry->value.funcVal->name,scope);
    }
    printf("term -> lvalue--\n");
}

void Manage_term_primary(){
    printf("term -> primary\n");
}

void Manage_expr_exprOPexpr(char* op){
    printf("expr -> expr %s expr\n", op);
}

void Manage_expr_term(){
    printf("expr -> term\n");
}

void Manage_expr_assignexpr(){
    printf("expr -> assignexpr\n");
}

void Manage_stmt_expr(){
    printf("stmt -> expr;\n");
}

void Manage_stmt_ifstmt(){
    printf("stmt -> ifstmt\n");
}

void Manage_stmt_whilestmt(){
    printf("stmt -> whilestmt\n");
}

void Manage_stmt_forstmt(){
    printf("stmt -> forstmt\n");
}

void Manage_stmt_returnstmt(){
    printf("stmt -> returnstmt\n");
}

void Manage_stmt_break(){
    printf("stmt -> break;\n");
}

void Manage_stmt_continue(){
    printf("stmt -> continue;\n");
}

void Manage_stmt_block(){
    printf("stmt -> block\n"); 
}

void Manage_stmt_funcdef(){
    printf("stmt -> funcdef\n");
}

void Manage_stmt_semicolon(){
    printf("stmt -> ;\n");
}

void Manage_liststmt_liststmtStmt(){
    printf("liststmt -> liststmt stmt\n");
}

void Manage_liststmt_stmt(){
    printf("liststmt -> stmt\n");
}

void Manage_program_liststmt(){
    printf("program -> stmt+\n");
}

void Manage_program_empty(){
    printf("empty program\n");  
}

#endif