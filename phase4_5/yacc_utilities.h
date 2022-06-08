#ifndef YACC_UTILITIES_HEADER
#define YACC_UTILITIES_HEADER
#include "libs/scopelist/scopelists.h"
#include "libs/SymTableEntry/SymTableEntry.h"
#include "libs/symtable/symtable.h"
#include "libs/zarkList/zarkList.h"
#include "libs/Vektor/Vektor.h"
#include "libs/stack/stack.h"
#include "expression.h" 
#include "quads.h"

extern int yylineno;
extern char* yytext;
extern int scope;
extern int flag_scope;
extern scopeArray* scpArr;
extern SymTable_T symTable;
extern FILE* yacc_out; 
unsigned int invalid_funcname_number  = 0;
unsigned int temp_counter = 0;
// phase3 staff
extern Vektor* quads;
unsigned total;
unsigned int currQuad = 1;
extern alpha_stack* anon_func_names_stack;
extern alpha_stack* invalid_funcname_number_stack;
extern alpha_stack* loopcounter_stack;
extern alpha_stack* func_init_jump_stack;

//gia offset
extern alpha_stack* function_local_offset_stack;
scopespace_t currscopespace = programvar;
int programvar_offset = 0;
int functionlocal_offset = 0;
int formalarg_offset = 0;



void push_function_local_offset(){
    int *tmp = malloc(sizeof(int));
    *tmp = functionlocal_offset;
    stack_push(function_local_offset_stack,(void *) tmp);
    functionlocal_offset = 0;
}

void pop_function_local_offset(){
    int *tmp =(int*) stack_pop(function_local_offset_stack);
    functionlocal_offset = *tmp;
    free(tmp);
}

/*returns offset of currscopespace and proceeds to add 1 to it */
int get_offset(){
    switch (currscopespace) {
        case programvar:
            return programvar_offset++;
        case functionlocal:
            return functionlocal_offset++;
        case formalarg:
            return formalarg_offset++;
        default:
            printf("PANIC ERROR IN get_offset()\n");
            return 0;
    }
}

int loopcounter = 0;

unsigned nextquad(void) { return currQuad; }

stmt_t* make_stmt(void) {
    stmt_t* s = malloc(sizeof(stmt_t));
    s->breaklist = 0;
    s->continuelist = 0;
    s->returnlist = 0;
    return s;
}

int newlist(int i) {
    ((quad*)quads->data[i])->label = 0;
    return i;
}

int mergelist(int l1, int l2) {
    if(!l1)
        return l2;
    else if(!l2)
        return l1;
    else {
        int i = l1;
        while(((quad*)quads->data[i])->label)
            i = ((quad*)quads->data[i])->label;
        ((quad*)quads->data[i])->label = l2;
        return l1;
    }
}

void patchlist(int list, int label) {
    while(list) {
        int next = ((quad*)quads->data[list])->label;
        ((quad*)quads->data[list])->label = label;
        list = next;
    }
}

void patchlabel(unsigned quadNo, unsigned label) {
    assert(quadNo < currQuad );
    assert(!((quad*)quads->data[quadNo])->label);
    ((quad*)quads->data[quadNo])->label = label;
}

void emit(
        iopcode     op,
        expr*       result,
        expr*       arg1,
        expr*       arg2,
        unsigned    label,
        unsigned    line
        )
{

    quad* p     = malloc(sizeof(quad));
    assert(p);
    p->result   = result;
    p->arg1     = arg1;
    p->arg2     = arg2;
    p->label    = label;
    p->line     = line;
    p->op       = op;
    p->source_code_line = yylineno;
    vektor_set_element(quads, currQuad, (void*) p);
    currQuad++;
}

SymTableEntry* new_temp(); // <---- dont remove this

expr* emit_iftableitem(expr* e){
    if(e->type != tableitem_e){
        return e;
    }else{
        expr* result = newexpr(var_e);
        result->sym = new_temp();
        emit(tablegetelem,result,e,e->index,-1,currQuad);
        return result;
    }
}

int true_test(expr* arg){
    //puts("I AM TRUE TESTING");
    if(arg == NULL){
        //puts("I AM HERE");
        return 0;
    }
    else if(arg->type == boolexpr_e ) {
        //puts("I AM HERE");
        return 0;
    }
    
    // DEN KSERW TI SPAEI TO UNCOMMENT TWN 2 KATW GRAMMWN ALLA STAMATISAN TA ASSERTION KAI TA QUAD EINAI SWSTA
    //arg->type = boolexpr_e;
    if(arg->type < 8 || arg->type > 11){ // <----------- ama einai const , paramenei const
        arg->is_also_const = 0;
        
    } 
    else {
        arg->is_also_const = 1;
    }
    arg->type = boolexpr_e;
    emit(if_eq, NULL, arg, newexpr_constbool(1), 0, currQuad);
    emit(jump, NULL, NULL, NULL, 0, currQuad);
    // printf("%d\n", nextquad()-2);
    // printf("%d\n", nextquad()-1);
    arg->truelist = newlist(nextquad()-2);
    arg->falselist = newlist(nextquad()-1);
    return 1;
}

expr* emit_ifbool(expr* e){
    // printf("inside emit if bool\n");
    if(e->type == boolexpr_e || e->type == constbool_e){
        patchlist(e->truelist, nextquad());
        patchlist(e->falselist, nextquad()+2);

        expr* tmp = newexpr(boolexpr_e);
        tmp->sym = new_temp();
        tmp->is_also_const = e->is_also_const;
        emit(assign, tmp, newexpr_constbool(1), NULL, -1, currQuad);
        emit(jump, NULL, NULL, NULL, nextquad() + 2 , currQuad);
        emit(assign, tmp, newexpr_constbool(0), NULL, -1, currQuad);
        
        return tmp;
    }
    return e;
}

expr* member_item(expr* lv, char* name){
    lv = emit_iftableitem(lv);
    expr* ti = newexpr(tableitem_e);
    ti->sym = lv->sym;
    ti->index = newexpr_conststring(name);
    return ti;
}

expr* member_item_expr(expr* lv, expr* inBrackets){
    lv = emit_iftableitem(lv);
    expr* ti = newexpr(tableitem_e);
    ti->sym = lv->sym;
    ti->index = inBrackets;
    return ti;
}

void check_arith(expr* e){
    if( e->type == constbool_e   ||
        e->type == conststring_e ||
        e->type == nil_e         ||
        e->type == newtable_e    ||
        e->type == programfunc_e ||
        e->type == libraryfunc_e ||
        e->type == boolexpr_e )
    {
        printf("Invalid use of arithmetic operator!\n");
        exit(-1);
    }

}

int yyerror(char* yaccProvideMessage)
{
    fprintf(stderr , "\033[0;31mERROR\033[0m\n");
    fprintf(stderr, "\033[0;33m%s\033[0m -> at line %d, before token: \033[0;36m\'%s\'\033[0m\n",  yaccProvideMessage, yylineno, yytext);
    fprintf(stderr , "\033[0;31mINPUT NOT VALID\033[0m\n");

    return 0;
}

int print_custom_error(char* yaccProvideMessage,const char* yaccProvideName,const int scope)
{
    fprintf(stderr , "\033[1;31mERROR\033[0m at line\033[0;35m %d\033[0m, with scope \033[0;35m%d \033[0m: ", yylineno,scope);
    fprintf(stderr, "\033[0;33m%s\033[0m -> at token: \033[0;36m\'%s\'\033[0m\n",  yaccProvideMessage, yaccProvideName);
    //fprintf(stderr , "\033[0;31mINPUT NOT VALID\033[0m\n");

    return 0;
}
int last_soft_hide[1024] = {0};
int last_soft_hide_index = 0;
//if the the last who called this function is a block(0) and you are a block(0) => scope++
//else if you are a function(1) => scope++
//else if the last was a function and you are a block you change the flag
void ScopeUp(int callee){
    if (callee == 0 && flag_scope == 0)
    {
        unsigned int *tmp = (unsigned int *)malloc(sizeof(unsigned int)); //malloc space to have the name in the stack
        *tmp = invalid_funcname_number; //copy the name
        stack_push(invalid_funcname_number_stack, (void*)tmp); //put it in the stack
        invalid_funcname_number = 0; //reset the counter

        //we dont soft hide inside the block
        scope ++;
        fprintf(yacc_out,"Scope up to %d\n",scope);
    } else if (callee == 1){
        unsigned int *tmp = (unsigned int *)malloc(sizeof(unsigned int)); //malloc space to have the name in the stack
        *tmp = invalid_funcname_number; //copy the name
        stack_push(invalid_funcname_number_stack, (void*)tmp); //put it in the stack
        invalid_funcname_number = 0; //reset the counter

        //when we soft hide we push in the stack the last scope
        last_soft_hide[last_soft_hide_index] = scope;
        last_soft_hide_index++;
        //inside one function we soft hide every other scope except the latest scope
        scope ++;
        for (int i = 1; i < scope; i++)
        {
            soft_hide(&scpArr,i);
        }
        flag_scope = 1 ;
        fprintf(yacc_out,"Scope up to %d\n",scope);
    } else {
        //this is again inside a block so we dont soft hide the previous
        flag_scope = 0;
    }
}

void ScopeDown(int callee){
    
    hard_hide(&scpArr,scope); //hide the current scope
    scope--;
    unsigned int *tmp = (unsigned int *)stack_pop(invalid_funcname_number_stack); //get the name from the stack
    invalid_funcname_number = *tmp;  //copy the value to the global variable
    free(tmp); //free the variable used from the stack
    
    unhide(&scpArr,scope); //unhide the current scope
    
}

void ScopeDownFunc(void){
    // apo to scope pu eimaste ews tote pu egine to teleutaio soft hide kane unhide
    for(int i = scope ; i > last_soft_hide[last_soft_hide_index] ; i--){
        unhide(&scpArr,i);  //unhide the scope
    }
    last_soft_hide[last_soft_hide_index] = 0;
    assert(&last_soft_hide[last_soft_hide_index] != &programvar_offset);
    last_soft_hide_index--;
}

/* Generates a invalid name for a function */
char* invalid_funcname_generator(){
    char* invalid_name = malloc(1024*(sizeof(char)));
    sprintf(invalid_name, "_$f%u", invalid_funcname_number++);
    
    return invalid_name;
}

/* Generates a new temporary name for a temporary variable for the quads */
char* new_temp_name(){
    char* temp_name = malloc(1024*sizeof(char));
    sprintf(temp_name, "_t%u", temp_counter++);

    return temp_name;
}

void reset_temp_counter(){
    temp_counter = 0;
}

SymTableEntry* new_temp(){
    char* name = new_temp_name();
    SymTableEntry* sym = lookup_active_with_scope(&scpArr, scope, name);

    // mporei mia temporary metabliti na einai typou VAR_FORMAL?
    if(sym == NULL){
            SymbolType type = (scope == 0) ? VAR_GLOBAL : VAR_LOCAL;
            SymTableEntry* entry = makeSymTableEntry(name,NULL,scope,yylineno,type,currscopespace,get_offset()); //create new entry
            SymTable_put(symTable, name, entry); //put it inside the global symtable
            insert_to_scopeArr(&scpArr,scope,entry); //and inside the scope array
            return entry;
    }
    
    return sym; //return the entry
}

stmt_t* Manage_returnstmt_returnexpr(expr* rvalue){
    stmt_t* stmt_tmp = make_stmt();
    emit(ret,rvalue,NULL,NULL,-1,nextquad());
    emit(jump, NULL, NULL, NULL, 0, currQuad);
    stmt_tmp->returnlist = newlist(nextquad()-1);
    fprintf(yacc_out,"returnstmt -> return expr;\n");

    return stmt_tmp;
} 

stmt_t* Manage_returnstmt_return(){
    stmt_t* stmt_tmp = make_stmt();
    emit(ret,NULL,NULL,NULL,-1,nextquad());
    emit(jump, NULL, NULL, NULL, 0, currQuad);
    stmt_tmp->returnlist = newlist(nextquad() - 1);
    fprintf(yacc_out,"returnstmt -> return;\n");

    return stmt_tmp;
}

void Manage_forstmt(){
    fprintf(yacc_out,"forstmt -> for(elist;expr;elist) stmt\n");
}

void Manage_whilestmt(){
    fprintf(yacc_out,"whilestmt -> while(expr) stmt\n");
}

void Manage_ifstmt_ifelse(){
    fprintf(yacc_out,"ifstmt -> if (expr) stmt else\n");
}

void Manage_ifstmt_if(){
    fprintf(yacc_out,"ifstmt -> if (expr)\n"); 
}

void Manage_idlist_empty(idList ** dest){
    //making an empty idlist
    *dest = zarklist_initialize(0);
    fprintf(yacc_out,"idlist -> ε\n"); 
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
    SymTableEntry* entry = makeSymTableEntry(new_element,NULL,scope,yylineno,VAR_FORMAL,currscopespace,get_offset());
    SymTable_put(symTable,new_element,entry);
    insert_to_scopeArr(&scpArr,scope,entry);

    //insertion in the idlist and saving the idlist
    zarklist_insert(old_list,new_element);
    dest = &old_list;
    fprintf(yacc_out,"idlist -> id,id*\n");
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
    SymTableEntry* entry = makeSymTableEntry(new_element,NULL,scope,yylineno,VAR_FORMAL,currscopespace,get_offset());
    SymTable_put(symTable,new_element,entry);
    insert_to_scopeArr(&scpArr,scope,entry);

    //insertion in the idlist and saving the idlist
    
    *dest = zarklist_initialize(0);
    zarklist_insert(*dest,new_element);
    fprintf(yacc_out,"idlist -> id,id*\n");
}

expr* Manage_const_int(int n){
    fprintf(yacc_out,"const -> number\n");
    //printf("%d\n", n);
    return newexpr_constint(n);
}

expr* Manage_const_double(double n){
    fprintf(yacc_out,"const -> number\n");
    //printf("%f\n", n);
    return newexpr_constdouble(n);
}

expr* Manage_const_string(char* s){
    fprintf(yacc_out,"const -> string\n");
    //printf("%s\n", s);
    return newexpr_conststring(s);
}

expr* Manage_const_nil(){
    fprintf(yacc_out,"const -> nil\n");
    //puts("NULL");
    return newexpr_constnil();
}

expr* Manage_const_bool(unsigned char c){
    if(c) {
        fprintf(yacc_out,"const -> true\n");
        //puts("TRUE");
    }
    else {
        fprintf(yacc_out,"const -> false\n");
        //puts("FALSE");
    }
    return newexpr_constbool(c);
}

SymTableEntry* Manage_funcdef_functionId(char *name,idList *args){
    fprintf(yacc_out,"scope is =%d\n",scope);
    //if it already exists in the global scope as an lib func
    SymTableEntry* search = lookup_active_with_scope(&scpArr,0,name); // TODO: edw einai to lathos me to object_creation_expression test

    push_function_local_offset();
    currscopespace = functionlocal;
    

    if (search!=NULL)
    {
        if(search->type==LIBFUNC){
            print_custom_error("User function shadows library function",name,scope);
            return NULL;
        }else if(scope-1 == 0){
            print_custom_error("Already found a symbol with same name",name,0);
            return NULL;
        }
        
        
    }
    //if scope 2 , 3 etc 
    if (scope>1)
    {
        //search in previus scope because u are one scope inside 
        //and u need to check the name if given like this 
        //function f(x){
        //     function x(){}
        //}
        search = lookup_any_with_scope(&scpArr,scope-1,name);
        if (search !=NULL)
        {
            print_custom_error("Variable already exists",name,scope);
            return NULL;
        }
        
    }
    
    //if it already exists in the same scope print error, the same scope is -1 for the name coz this is called before scope down
    if ((search = lookup_active_with_scope(&scpArr,scope-1,name)) != NULL)
    {
        if(IS_FUNCTION(search))
            print_custom_error("Function redefinition",name,scope);
        else
            print_custom_error("Funtion declared with same name as variable",name,scope); // edw skasei error function four(four){four=4;}
        return NULL;
    }
    
    //insertion in the symtable and in the scopelist
    SymTableEntry* entry = makeSymTableEntry(name,args,scope-1,yylineno,USERFUNC,currscopespace,0);
    SymTable_put(symTable,name,entry);
    insert_to_scopeArr(&scpArr,scope-1,entry);
    return entry;
    //printf("function id (idlist) block\n");
}

SymTableEntry* Manage_funcdef_function(idList *args){
    
    int *tmp_loopcounter = (int *) stack_pop(loopcounter_stack);
    loopcounter = *tmp_loopcounter;
    free(tmp_loopcounter);

    char * name = (char*)stack_pop(anon_func_names_stack);
    //insertion in the symtable and in the scopelist
    SymTableEntry* entry = makeSymTableEntry(name,args,scope,yylineno,USERFUNC,currscopespace,0);
    SymTable_put(symTable,name,entry);
    insert_to_scopeArr(&scpArr,scope,entry);
    emit(funcend,newexpr_conststring(name),NULL,NULL,-1,currQuad);

    //patch the jump
    int *tmp_currQuad = (int *) stack_pop(func_init_jump_stack);
    patchlabel(*tmp_currQuad, nextquad());
    free(tmp_currQuad);

    fprintf(yacc_out,"function (idlist) block\n");
    return entry;
}

void Manage_block_liststmt(){
    fprintf(yacc_out,"block -> stmt*\n");
}

void Manage_block_emptyblock(){
    fprintf(yacc_out,"block -> {}\n");
}

void Manage_indexedelem(){
    fprintf(yacc_out,"indexedelem -> {expr:expr}\n");
}

void Manage_indexed_indexedIndexedelem(){
    fprintf(yacc_out,"indexed -> indexed,indexedelem\n");
}

void Manage_indexed_indexedelem(){
    fprintf(yacc_out,"indexed -> indexedelem\n");
}

void Manage_objectdef_elist(){
    fprintf(yacc_out,"objectdef -> [elist]\n");
}

void Manage_objectdef_indexed(){
    fprintf(yacc_out,"objectdef -> [indexed]\n");
}

void Manage_elist_empty(){
    fprintf(yacc_out,"elist -> ε\n");
}

void Manage_elist_elistExpr(){
    fprintf(yacc_out,"elist -> elist,expr\n");
}

void Manage_elist_expr(){
    fprintf(yacc_out,"elist -> epxr\n");
}

void Manage_methodcall(){
    fprintf(yacc_out,"methodcall -> ..id(elist)\n");
}

void Manage_normcall(){
    fprintf(yacc_out,"normcall -> (elist)\n");
}

void Manage_callsuffix_normcall(){
    fprintf(yacc_out,"callsuffix -> normcall\n");
}

void Manage_callsuffix_methodcall(){
    fprintf(yacc_out,"callsuffix -> methodcall\n");
}

void Manage_call_callElist(){
    fprintf(yacc_out,"call -> call(elist)\n");
}

void Manage_call_lvalueCallsuffix(expr * entry){
    if(entry == NULL)
        {print_custom_error("Function not declared", "", scope);}
    //else if(entry->type != USERFUNC && entry->type != LIBFUNC){
    //    print_custom_error("Cant make call from a variable",entry->value.varVal->name,scope);
    //}
    fprintf(yacc_out,"call -> lvalue callsuffix\n");
}

void Manage_call_funcdefElist(){
    fprintf(yacc_out,"call -> (funcdef)(elist)\n");
}

expr* Manage_member_lvalueID(expr * entry, char* index){
    expr* tableitem;

    if(entry == NULL)
        {print_custom_error("lvalue not declared", "", scope);}
    else if(entry->type==programfunc_e || entry->type==libraryfunc_e){
        print_custom_error("Cant use function name as an lvalue.id",entry->sym->value.funcVal->name,scope);
    }

    tableitem = member_item(entry, index);
    fprintf(yacc_out,"member -> lvalue.id\n");
    return tableitem;
}

expr* Manage_member_lvalueExpr(expr * entry, expr* index){
    expr* tableitem;

    if(entry == NULL)
        {print_custom_error("lvalue not declared", "", scope);}
    else if(entry->type==programfunc_e || entry->type==libraryfunc_e){
        print_custom_error("Cant use function name as an lvalue[]",entry->sym->value.funcVal->name,scope);
    }

    entry = emit_iftableitem(entry);
    tableitem = newexpr(tableitem_e);
    tableitem->sym = entry->sym;
    tableitem->index = index;

    fprintf(yacc_out,"member -> lvalue[expr]\n");
    return tableitem;
}

void Manage_member_callID(){
    fprintf(yacc_out,"member -> call.id\n");
}

void Manage_member_callExpr(){
    fprintf(yacc_out,"member -> call[expr]\n");
}

void Manage_lvalue_id(SymTableEntry** new_entry, char* id, int scope, int line){
    fprintf(yacc_out,"lvalue -> id\n");
    
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
                entry = makeSymTableEntry(id, NULL,  scope, line, type,currscopespace,get_offset());
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
                puts("THIS IS WHERE I FOUND THE ERROR");
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
    fprintf(yacc_out,"lvalue -> local id\n");

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
                entry = makeSymTableEntry(id, NULL,  scope, line, VAR_GLOBAL,currscopespace,get_offset());
            else
                entry = makeSymTableEntry(id, NULL,  scope, line, VAR_LOCAL,currscopespace,get_offset());

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
    fprintf(yacc_out,"lvalue -> ::id\n");
    
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
    fprintf(yacc_out,"lvalue -> member\n");
}

expr* Manage_primary_lvalue(expr* lvalue){
    fprintf(yacc_out,"primary -> lvalue\n");
    return emit_iftableitem(lvalue);
}

void Manage_primary_call(){
    fprintf(yacc_out,"primary -> call\n");
}

void Manage_primary_objectdef(){
    fprintf(yacc_out,"primary -> objectdef\n");
}

void Manage_primary_funcdef(){
    fprintf(yacc_out,"primary -> (funcdec)\n"); 
}

void Manage_primary_const(){
    fprintf(yacc_out,"primary -> const\n");
}

expr* Manage_assignexpr(expr* lvalue, expr* rvalue){
    if(lvalue == NULL){return NULL;}
    if(lvalue->type==programfunc_e || lvalue->type==libraryfunc_e){
        print_custom_error("Cant make assignment to function",lvalue->sym->value.funcVal->name,scope);
    }

    if(lvalue->type==tableitem_e){
        if(rvalue->type== boolexpr_e){
            rvalue = emit_ifbool(rvalue);
        }
        emit(tablesetelem,lvalue,lvalue->index,rvalue,-1,currQuad);
        expr* e = emit_iftableitem(lvalue);
        e->type = var_e;
        return e;
    }
    expr* e  = rvalue;
    if(rvalue->type == boolexpr_e){
        e = emit_ifbool(rvalue); //in case merikis apotimisis
    }
    
    emit(assign, lvalue, e, NULL, -1, currQuad); // x = y;
    
    SymTableEntry *tmp = new_temp(); // create new tmp variable
    expr* tmp_expr = lvalue_to_expr(tmp); // make it an lvalue expr
    
    
    emit(assign, tmp_expr, lvalue, NULL, -1, currQuad); // _t0 = x;
    return tmp_expr;
}

void Manage_term_expr(){
    fprintf(yacc_out,"term -> (expr)\n");
}

expr* Manage_term_uminusExpr(expr * lvalue){
    if(lvalue == NULL){return NULL;}
    if(lvalue->type==programfunc_e || lvalue->type==libraryfunc_e){
        print_custom_error("Cant make uminus to function",lvalue->sym->value.funcVal->name,scope);
    }
    
    check_arith(lvalue);
    
    if (lvalue->sym && lvalue->sym->type<2 && lvalue->sym->value.varVal->name[0]=='_') // in case of tmp
    {
        emit(uminus, lvalue, lvalue, NULL, -1, currQuad);
        return lvalue;
    } else {
        expr* term = newexpr(arithexpr_e);
        term->sym = new_temp(); // create new tmp variable
        emit(uminus, term, lvalue, NULL, -1, currQuad); // _t0 = -x;
        fprintf(yacc_out,"term -> -expr\n");
        return term;
    }

}

expr* Manage_term_notExpr(expr* notExpr){

    true_test(notExpr);
    unsigned int tmp = notExpr->truelist;
    notExpr->truelist = notExpr->falselist;
    notExpr->falselist = tmp;
    
    fprintf(yacc_out,"term -> not expr\n");
   // printf("truelist%d\n", notExpr->truelist);
   // printf("falselist%d\n", notExpr->falselist);
    return notExpr;
}

expr* Manage_term_pluspluslvalue(expr *lvalue){
    if(lvalue == NULL){return NULL;}
    if(lvalue->type==programfunc_e || lvalue->type==libraryfunc_e){
        print_custom_error("Cant use a function as an lvalue",lvalue->sym->value.funcVal->name,scope);
    }

    expr* term = NULL;
    check_arith(lvalue);
    if(lvalue->type == tableitem_e){
        term = emit_iftableitem(lvalue);
        emit(add, term, term, newexpr_constint(1), -1, currQuad);
        emit(tablesetelem, lvalue, lvalue->index, term, -1, currQuad);
    }
    else{
        emit(add, lvalue, lvalue, newexpr_constint(1), -1, currQuad);
        term = newexpr(arithexpr_e);
        term->sym = new_temp();
        emit(assign, term, lvalue, NULL, -1, currQuad);
    }

    fprintf(yacc_out,"term -> ++lvalue\n");
    return term;
}

expr* Manage_term_lvalueplusplus(expr *lvalue){
    if(lvalue == NULL){return NULL;}
    if(lvalue->type==programfunc_e || lvalue->type==libraryfunc_e){
        print_custom_error("Cant use a function as an lvalue",lvalue->sym->value.funcVal->name,scope);
    }
    expr* term = NULL;
    check_arith(lvalue);
    term = newexpr(var_e);
    term->sym = new_temp();
    if(lvalue->type == tableitem_e){
        expr* val = emit_iftableitem(lvalue);
        emit(assign, term, val, NULL, -1, currQuad);
        emit(add, val, val, newexpr_constint(1), -1, currQuad);
        emit(tablesetelem, lvalue, lvalue->index, val, -1, currQuad);
    }
    else{
        emit(assign, term, lvalue, NULL, -1, currQuad);
        emit(add, lvalue, lvalue, newexpr_constint(1), -1, currQuad);
    }

    fprintf(yacc_out,"term -> lvalue++\n");
    return term;
}

expr* Manage_term_minusminuslvalue(expr *lvalue){
    if(lvalue == NULL){return NULL;}
    if(lvalue->type==programfunc_e || lvalue->type==libraryfunc_e){
        print_custom_error("Cant use a function as an lvalue",lvalue->sym->value.funcVal->name,scope);
    }

    expr* term = NULL;
    check_arith(lvalue);
    if(lvalue->type == tableitem_e){
        term = emit_iftableitem(lvalue);
        emit(sub, term, term, newexpr_constint(1), -1, currQuad);
        emit(tablesetelem, lvalue, lvalue->index, term, -1, currQuad);
    }
    else{
        emit(sub, lvalue, lvalue, newexpr_constint(1), -1, currQuad);
        term = newexpr(arithexpr_e);
        term->sym = new_temp();
        emit(assign, term, lvalue, NULL, -1, currQuad);
    }

    fprintf(yacc_out,"term -> --lvalue\n");
    return term;
}

expr* Manage_term_lvalueminusminus(expr *lvalue){
    if(lvalue == NULL){return NULL;}
    if(lvalue->type==programfunc_e || lvalue->type==libraryfunc_e){
        print_custom_error("Cant use a function as an lvalue",lvalue->sym->value.funcVal->name,scope);
    }

    expr* term = NULL;
    check_arith(lvalue);
    term = newexpr(var_e);
    term->sym = new_temp();
    if(lvalue->type == tableitem_e){
        expr* val = emit_iftableitem(lvalue);
        emit(assign, term, val, NULL, -1, currQuad);
        emit(sub, val, val, newexpr_constint(1), -1, currQuad);
        emit(tablesetelem, lvalue, lvalue->index, val, -1, currQuad);
    }
    else{
        emit(assign, term, lvalue, NULL, -1, currQuad);
        emit(sub, lvalue, lvalue, newexpr_constint(1), -1, currQuad);
    }

    fprintf(yacc_out,"term -> lvalue--\n");
    return term;
}

void Manage_term_primary(){
    fprintf(yacc_out,"term -> primary\n");
}

expr* Manage_arithmexpr(expr* arg1,char* op, expr* arg2){
    check_arith(arg1);
    check_arith(arg2);
    fprintf(yacc_out,"arithmexpr -> expr %s expr\n", op);
    
    SymTableEntry *tmp;
    expr* tmp_expr;
    
    
    if (arg1->sym && arg1->sym->type<2 && arg1->sym->value.varVal->name[0]=='_') // in case of tmp
    {
        tmp = arg1->sym;
    }else if(arg2->sym && arg2->sym->type<2 && arg2->sym->value.varVal->name[0]=='_'){
        tmp = arg2->sym;
    }else{
        tmp = new_temp(); // create new tmp variable
    }
    
    tmp_expr = lvalue_to_expr(tmp); // make it an lvalue exprs
    switch (op[0])
    {
    case '+':
        emit(add, tmp_expr, arg1, arg2, -1, currQuad);
        break;
    case '-':
        emit(sub, tmp_expr, arg1, arg2, -1, currQuad);
        break;
    case '*':
        emit(mul, tmp_expr, arg1, arg2, -1, currQuad);
        break;
    case '/':
        emit(_div, tmp_expr, arg1, arg2, -1, currQuad);
        break;
    case '%':
        emit(mod, tmp_expr, arg1, arg2, -1, currQuad);
        break;
    default:
        print_custom_error("Unknown operator",op,scope);
        return NULL;
    }
    return tmp_expr;
}

expr* Manage_relopexpr(expr* arg1,char* op, expr* arg2){
    fprintf(yacc_out,"relopexpr -> expr %s expr\n", op);
    expr* tmp_expr=newexpr(boolexpr_e);
    //tmp_expr->sym = new_temp(); // create new tmp variable
    if (arg1->type == boolexpr_e)
    {
        arg1 = emit_ifbool(arg1);
    }
    if (arg2->type == boolexpr_e)
    {
        arg2 = emit_ifbool(arg2);
    }
    switch (op[0]){
        case '>':
        tmp_expr->type = boolexpr_e;
        if (strcmp(op, ">=") == 0) 
        {
            emit(if_greatereq, NULL, arg1, arg2, 0, currQuad);
            emit(jump, NULL, NULL, NULL, 0, currQuad);
        }else{
            emit(if_greater, NULL, arg1, arg2, 0, currQuad);
            emit(jump, NULL, NULL, NULL, 0, currQuad);
        }
        tmp_expr->truelist  = newlist(nextquad()-2);
        tmp_expr->falselist = newlist(nextquad()-1);
        break;
    case '<':
        tmp_expr->type = boolexpr_e;
        if (strcmp(op, "<=") == 0) 
        {
            emit(if_lesseq, NULL, arg1, arg2, 0, currQuad);
            emit(jump, NULL, NULL, NULL, 0, currQuad);
        }else{
            emit(if_less, NULL, arg1, arg2, 0, currQuad);
            emit(jump, NULL, NULL, NULL, 0, currQuad);
        }
        tmp_expr->truelist  = newlist(nextquad()-2);
        tmp_expr->falselist = newlist(nextquad()-1);
        break;
    case '=':
        tmp_expr->type = boolexpr_e;

        emit(if_eq, NULL, arg1, arg2, 0, currQuad);
        emit(jump, NULL, NULL, NULL, 0, currQuad);
        tmp_expr->truelist  = newlist(nextquad()-2);
        tmp_expr->falselist = newlist(nextquad()-1);
        break;
    case '!':
        tmp_expr->type = boolexpr_e;
        
        emit(if_noteq, NULL, arg1, arg2, 0, currQuad);
        emit(jump, NULL, NULL, NULL, 0, currQuad);
        tmp_expr->truelist  = newlist(nextquad()-2);
        tmp_expr->falselist = newlist(nextquad()-1);
        break;
    default:
        print_custom_error("Unknown operator",op,scope);
        return NULL;
    }
    return tmp_expr;
}

expr* Manage_boolexpr(expr* arg1,char* op, expr* arg2, unsigned int Mlabel){
    fprintf(yacc_out,"boolexpr -> expr %s expr\n", op);
    expr* tmp_expr=newexpr(boolexpr_e);
    
    //tmp_expr->sym = new_temp(); // create new tmp variable
    // expr* tmp_expr = lvalue_to_expr(tmp); // make it an lvalue expr
    // tmp_expr->type = boolexpr_e;
    
    switch (op[0]){
        case 'o':
        //emit(or, tmp_expr, arg1, arg2, -1, currQuad);
        //if(true_test(arg1)) Mlabel += 2;
        //true_test(arg2);
        tmp_expr->type = boolexpr_e;
        patchlist(arg1->falselist, Mlabel);
        tmp_expr->truelist = mergelist(arg1->truelist, arg2->truelist);
        tmp_expr->falselist = arg2->falselist;
        break;
    case 'a':
        //emit(and, tmp_expr, arg1, arg2, -1, currQuad);
        //if(true_test(arg1)) Mlabel += 2;
        //true_test(arg2);
        tmp_expr->type = boolexpr_e;
        //printf("Mlabel = %d\n", Mlabel);
        patchlist(arg1->truelist, Mlabel);
        tmp_expr->truelist = arg2->truelist;
        tmp_expr->falselist = mergelist(arg1->falselist, arg2->falselist);
        break;
    default:
        printf("Invalid operator\n");
        return NULL;
        break;
    }
    
    return tmp_expr;
}



void Manage_expr_term(){
    fprintf(yacc_out,"expr -> term\n");
}

void Manage_expr_assignexpr(){
    fprintf(yacc_out,"expr -> assignexpr\n");
}

void Manage_stmt_expr(){
    fprintf(yacc_out,"stmt -> expr;\n");
}

void Manage_stmt_ifstmt(){
    fprintf(yacc_out,"stmt -> ifstmt\n");
}

void Manage_stmt_whilestmt(){
    fprintf(yacc_out,"stmt -> whilestmt\n");
}

void Manage_stmt_forstmt(){
    fprintf(yacc_out,"stmt -> forstmt\n");
}

void Manage_stmt_returnstmt(){
    fprintf(yacc_out,"stmt -> returnstmt\n");
}

stmt_t* Manage_stmt_break(){
    fprintf(yacc_out,"stmt -> break;\n");
    if(loopcounter == 0)
        fprintf(stderr , "\033[1;31mERROR\033[0m at line\033[0;35m %d\033[0m", yylineno);

    stmt_t* new_stmt = make_stmt();
    emit(jump, NULL, NULL, NULL, 0, currQuad);
    new_stmt->breaklist = newlist(nextquad() - 1);

    return new_stmt;
}

stmt_t* Manage_stmt_continue(){
    fprintf(yacc_out,"liststmt -> liststmt stmt\n");
    if(loopcounter == 0)
        fprintf(stderr , "\033[1;31mERROR\033[0m at line\033[0;35m %d\033[0m", yylineno);

    stmt_t* new_stmt = make_stmt();
    emit(jump, NULL, NULL, NULL, 0, currQuad);
    new_stmt->continuelist = newlist(nextquad() - 1);

    return new_stmt;
}

void Manage_stmt_block(){
    fprintf(yacc_out,"stmt -> block\n"); 
}

void Manage_stmt_funcdef(){
    fprintf(yacc_out,"stmt -> funcdef\n");
}

void Manage_stmt_semicolon(){
    fprintf(yacc_out,"stmt -> ;\n");
}

stmt_t* Manage_liststmt_liststmtStmt(stmt_t* liststmt, stmt_t* simple_stmt){
    fprintf(yacc_out,"liststmt -> liststmt stmt\n");
    
    stmt_t* new_stmt = make_stmt();
    new_stmt->breaklist = mergelist(liststmt->breaklist, simple_stmt->breaklist);
    new_stmt->continuelist = mergelist(liststmt->continuelist, simple_stmt->continuelist);
    new_stmt->returnlist = mergelist(liststmt->returnlist, simple_stmt->returnlist);

    return new_stmt;
}

void Manage_liststmt_stmt(){
    fprintf(yacc_out,"liststmt -> stmt\n");
}

void Manage_program_liststmt(){
    fprintf(yacc_out,"program -> stmt+\n");
}

void Manage_program_empty(){
    fprintf(yacc_out,"empty program\n");  
}

void Init_named_func(char * name){
    // puts the variable in the stack and the resets the counter
    int * tmp_loopcounter = (int *)malloc(sizeof(int));
    *tmp_loopcounter = loopcounter;
    stack_push(loopcounter_stack,(void *)tmp_loopcounter);
    loopcounter = 0;
    
    ScopeUp(1);

    // puts the quad number of jump to function in the stack
    int * tmp_currQuad = (int *)malloc(sizeof(int));
    *tmp_currQuad = nextquad();
    stack_push(func_init_jump_stack,(void *)tmp_currQuad);


    emit(jump, NULL, NULL, NULL, 0, currQuad);
    emit(funcstart,newexpr_conststring(name),NULL,NULL,-1,currQuad);
    
    currscopespace = formalarg;
    formalarg_offset = 0;

}
extern int infunction;
void End_named_func(char* name){
    // pops the loopcounter changes the global pointer and free's the used variable
    int *tmp_loopcounter = (int *) stack_pop(loopcounter_stack);
    loopcounter = *tmp_loopcounter;
    free(tmp_loopcounter);
    fprintf(yacc_out, "function id (idlist) block\n"); 
    emit(funcend,newexpr_conststring(name),NULL,NULL,-1,currQuad);
    
    
    //patches the jump created by funcstart
    int *tmp_currQuad = (int *) stack_pop(func_init_jump_stack);
    patchlabel(*tmp_currQuad, nextquad());
    free(tmp_currQuad);

    pop_function_local_offset();
    if (infunction == 1)
    {
        currscopespace = programvar;
    }
    
    
}

void Init_Anonymous_func(){
    //for the loop counter
    int * tmp_loopcounter = (int *)malloc(sizeof(int));
    *tmp_loopcounter = loopcounter;
    stack_push(loopcounter_stack,(void *)tmp_loopcounter);
    loopcounter = 0;

    // puts the quad number of jump to function in the stack
    int * tmp_currQuad = (int *)malloc(sizeof(int));
    *tmp_currQuad = nextquad();
    stack_push(func_init_jump_stack,(void *)tmp_currQuad);

    char * anonFuncName = invalid_funcname_generator();
    ScopeUp(1);
    emit(jump, NULL, NULL, NULL, 0, currQuad);
    stack_push(anon_func_names_stack, anonFuncName);
    emit(funcstart,newexpr_conststring(anonFuncName),NULL,NULL,-1,currQuad);

    currscopespace = formalarg;
    formalarg_offset = 0;
}

expr* make_call(expr* lv, expr* elist){
    expr* func = emit_iftableitem(lv);
    if(elist != NULL){
        while(elist->next){
            elist = elist->next;
        }
        while(elist){
            emit(param, elist, NULL, NULL, -1, currQuad);
            elist = elist->prev;
        }
    }
    emit(call, func, NULL, NULL, -1, currQuad);
    expr* result = newexpr(var_e);
    result->sym = new_temp();
    emit(getretval, result, NULL, NULL, -1, currQuad);
    return result;
}
#endif