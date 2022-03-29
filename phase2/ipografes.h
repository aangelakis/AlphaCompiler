extern int scope;
extern int flag_scope;


//if the the last who called this function is a block(0) and you are a block(0) scope++
//else if you are a function(1) scope++
//else if the last was a function and you are a block you change the flag
void ScopeUp(int callee){
    if (callee == 0 && flag_scope == 0)
    {
      scope ++;
      printf("Scope up to %d\n",scope);
    }else if (callee == 1){
      scope ++;
      flag_scope = 1 ;
      printf("Scope up to %d\n",scope);
    }else {
      flag_scope = 0;
    }
    
    
}
void ScopeDown(int callee){
    printf("Scope down to %d\n",--scope);
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

void Manage_idlist_empty(){
    printf("idlist -> ε\n"); 
}

void Manage_idlist_idlistId(){
    printf("idlist -> id,id*\n");
}

void Manage_idlist_id(){
    printf("idlist -> id\n");
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

void Manage_funcdef_functionId(){
    printf("function id (idlist) block\n");
}

void Manage_funcdef_function(){
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

void Manage_call_lvalueCallsuffix(){
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

void Manage_lvalue_id(){
    printf("lvalue -> id\n");
}

void Manage_lvalue_localID(){
    printf("lvalue -> local id\n");
}

void Manage_lvalue_globalID(){
    printf("lvalue -> ::id\n");
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

void Manage_term_expr(){
    printf("term -> (expr)\n");
}

void Manage_term_uminusExpr(){
    printf("term -> -expr\n");
}

void Manage_term_notExpr(){
    printf("term -> not expr\n");
}

void Manage_term_pluspluslvalue(){
    printf("term -> ++lvalue\n");
}

void Manage_term_lvalueplusplus(){
    printf("term -> lvalue++\n");
}

void Manage_term_minusminuslvalue(){
    printf("term -> --lvalue\n");
}

void Manage_term_lvalueminusminus(){
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