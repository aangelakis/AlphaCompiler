%{
	
	#include "yacc_utilities.h"
	

        FILE* yacc_out; 
	int yylex();
        extern int loopcounter;
	extern int yylineno;
	extern char* yytext;
        int infunction = 0;
	int scope = 0;
	int flag_scope = 0 ; // 0 == block ; 1 == function
        char* anonFuncName = NULL;
%}

%output "parser.c"
%defines

%union {
    char*               strVal;
    int                 intVal;
    unsigned int        labelVal;
    double              realVal;
    unsigned char       boolVal;
    SymTableEntry*      symEntr;
    idList*             args;
    expr*               express;
    stmt_t*             statement;
    call_t*              callVal;
    forprefix_t*        forprefixVal;                
}

%initial-action
{
    yacc_out = fopen("yacc_output.txt", "w");    
};

%start program
%expect 1

/* Terminal Symbols */
%token<strVal> ID
%token<strVal> STRING
%token<intVal> INT
%token<realVal> DOUBLE
%token<boolVal> TRUE
%token<boolVal> FALSE

%token LE              "<="
%token LT              "<"
%token NE              "!="
%token GE              ">="
%token GT              ">"
%token EQ              "=="
%token ASSIGN          "="
%token PLUS            "+"
%token MINUS           "-"
%token PLUS_PLUS       "++"
%token MINUS_MINUS     "--"
%token MULT            "*"
%token DIV             "/"
%token MOD             "%"

%token IF              "if"
%token ELSE            "else"
%token WHILE           "while"
%token FOR             "for"
%token FUNCTION        "function"
%token RETURN          "return"
%token<statement> BREAK           "break"
%token<statement> CONTINUE        "continue"
%token AND             "and"
%token NOT             "not"
%token OR              "or"
%token LOCAL           "local"
//%token TRUE            "true"
//%token FALSE           "false"
%token NIL             "nil"

%token LEFT_BRACKET        "["
%token RIGHT_BRACKET       "]"
%token LEFT_BRACE          "{"
%token RIGHT_BRACE         "}"
%token LEFT_PARENTHESIS    "("
%token RIGHT_PARENTHESIS   ")"
%token SEMICOLON           ";"
%token COMMA               ","
%token COLON               ":"
%token DOUBLE_COLON        "::"
%token STOP                "."
%token DOUBLE_STOP         ".."

/* Operator Associativity and Priority (Bottom-to-Top Priority)*/
%right ASSIGN
%left OR
%left AND
%nonassoc NE EQ
%nonassoc GT GE LT LE
%left PLUS 
%right MINUS
%left MULT DIV MOD
%right NOT PLUS_PLUS MINUS_MINUS
%left STOP DOUBLE_STOP
%left LEFT_BRACKET RIGHT_BRACKET
%nonassoc UMINUS
%left LEFT_PARENTHESIS RIGHT_PARENTHESIS

/* Non Terminal Symbols */
%type<args> idlist
%type<express> lvalue

%type<statement> loopstmt
%type<statement> stmt
%type<statement> liststmt
%type<express> expr
%type<express> term
%type<express> assignexpr
%type<express> primary
%type<express> member
%type<express> call
%type<callVal> callsuffix
%type<callVal> normcall
%type<callVal> methodcall
%type<express> elist
%type<express> objectdef
%type<express> indexed
%type<express> indexedelem
%type<statement> block
%type<symEntr> funcdef
%type<express> const
%type<labelVal> ifprefix 
%type<labelVal> elseprefix
%type<labelVal> whilestart
%type<labelVal> whilecond
%type<labelVal> M
%type<labelVal> N 
%type<statement> ifstmt
%type<statement> whilestmt
%type<statement> forstmt
%type<statement> returnstmt
%type<forprefixVal> forprefix
%type<statement> program

%%

program: liststmt   { $$=$1;   Manage_program_liststmt();     fclose(yacc_out); }
        |%empty     {   Manage_program_empty();        fclose(yacc_out); }
        ;

liststmt: liststmt stmt {  $$ = Manage_liststmt_liststmtStmt($1, $2);      }
          | stmt        {  $$=$1; Manage_liststmt_stmt();             }
          ;

stmt: expr ";"      {   $$ = make_stmt(); Manage_stmt_expr();   reset_temp_counter();      }
      | ifstmt      {   $$ = $1; Manage_stmt_ifstmt();       }
      | whilestmt   {   $$ = $1; Manage_stmt_whilestmt();    }
      | forstmt     {   $$ = $1; Manage_stmt_forstmt();      }
      | returnstmt  {   $$ = $1; Manage_stmt_returnstmt();   }
      | BREAK ";"   {   $$ = Manage_stmt_break();        }  
      | CONTINUE ";"{   $$ = Manage_stmt_continue();     }
      | block       {   $$ = $1; Manage_stmt_block();        }
      | funcdef     {   $$ = make_stmt(); Manage_stmt_funcdef();      }
      | ";"         {   $$ = make_stmt(); Manage_stmt_semicolon();   reset_temp_counter(); }
      ;

expr:   assignexpr        {     Manage_expr_assignexpr();       }
        | term            {     Manage_expr_term();             }
        | expr PLUS expr  {    $$ = Manage_expr_exprOPexpr($1,"+",$3);    }
        | expr MINUS expr {    $$ = Manage_expr_exprOPexpr($1,"-",$3);    }
        | expr MULT expr  {    $$ = Manage_expr_exprOPexpr($1,"*",$3);    }
        | expr DIV expr   {    $$ = Manage_expr_exprOPexpr($1,"/",$3);    }
        | expr MOD expr   {    $$ = Manage_expr_exprOPexpr($1,"%",$3);    }
        | expr GE expr    {    $$ = Manage_expr_exprOPexpr($1,">=",$3);   }
        | expr GT expr    {    $$ = Manage_expr_exprOPexpr($1,">",$3);    }
        | expr LE expr    {    $$ = Manage_expr_exprOPexpr($1,"<=",$3);   }
        | expr LT expr    {    $$ = Manage_expr_exprOPexpr($1,"<",$3);    }
        | expr EQ expr    {    $$ = Manage_expr_exprOPexpr($1,"==",$3);   }
        | expr NE expr    {    $$ = Manage_expr_exprOPexpr($1,"!=",$3);   }
        | expr AND expr   {    $$ = Manage_expr_exprOPexpr($1,"and",$3);  }
        | expr OR expr    {    $$ = Manage_expr_exprOPexpr($1,"or",$3);   }
        ;

term:   "(" expr ")"            {   $$ = $2; Manage_term_expr();                 }
        | "-"expr  %prec UMINUS {   $$ = Manage_term_uminusExpr($2);           }
        | NOT expr              {   //thelei kialla logo tis olikis/merikis apotimisis.
                                    $$ = Manage_term_notExpr($2);              }
        | "++"lvalue            {   $$ = Manage_term_pluspluslvalue($2);       }
        | lvalue"++"            {   $$ = Manage_term_lvalueplusplus($1);       }
        | "--"lvalue            {   $$ = Manage_term_minusminuslvalue($2);     }
        | lvalue"--"            {   $$ = Manage_term_lvalueminusminus($1);     }
        | primary               {   $$ = $1; Manage_term_primary();              }
        ;

assignexpr: lvalue"="expr       {  $$ = Manage_assignexpr($1, $3);  };

primary:  lvalue            {  $$ = Manage_primary_lvalue($1);      }
          | call            {   Manage_primary_call();        }
          | objectdef       {   Manage_primary_objectdef();   }
          | "("funcdef")"   {   $$ = newexpr(programfunc_e); $$->sym = $2; Manage_primary_funcdef();     }
          | const           {   Manage_primary_const();       }
          ;

lvalue: ID                    { SymTableEntry *tmpSymbol = NULL;
                                Manage_lvalue_id(&(tmpSymbol), $1, scope, yylineno);
                                $$ = lvalue_to_expr(tmpSymbol);
                              } 
        | LOCAL ID            { SymTableEntry *tmpSymbol = NULL; 
                                Manage_lvalue_localID(&(tmpSymbol), $2, scope, yylineno);    
                                $$ = lvalue_to_expr(tmpSymbol);
                              }
        | DOUBLE_COLON ID     { SymTableEntry *tmpSymbol = NULL;
                                Manage_lvalue_globalID(&(tmpSymbol), $2);
                                $$ = lvalue_to_expr(tmpSymbol);
                              }
        | member              { //$$ = makeSymTableEntry("dc",NULL,0,0,VAR_LOCAL);        // ultimate hackeria, saved infinite lines of code
                                Manage_lvalue_member(); }
        ;

member: lvalue "." ID           {   $$ = Manage_member_lvalueID($1, $3);   }
        | lvalue "[" expr "]"   {   $$ = Manage_member_lvalueExpr($1, $3); }
        | call "." ID           {   $$ = member_item($1, $3); Manage_member_callID();     }
        | call "[" expr "]"     {       $$ = member_item_expr($1, $3);
                                        Manage_member_callExpr();   
                                }
        ;

call: call "(" elist ")"                {       $$ = make_call($1, $3); 
                                                Manage_call_callElist();        
                                        }
      | lvalue callsuffix               {       $1 = emit_iftableitem($1);
                                                if($2->method){
                                                        expr* t = $1;
                                                        $1 = emit_iftableitem(member_item(t, $2->name));
                                                        $2->elist->prev = t;
                                                        $2->elist->prev->next = $2->elist;
                                                        $2->elist = $2->elist->prev;
                                                }
                                                $$ = make_call($1, $2->elist);
                                                Manage_call_lvalueCallsuffix($1); 
                                        }
      | "(" funcdef ")" "(" elist ")"   {       expr* func = newexpr(programfunc_e);
                                                func->sym = $2;
                                                $$ = make_call(func, $5);
                                                Manage_call_funcdefElist();     
                                        }
      ;

callsuffix: normcall      { $$ = $1; Manage_callsuffix_normcall();     }
            | methodcall  { $$ = $1; Manage_callsuffix_methodcall();   }
            ;

normcall:   "(" elist ")"   {   
                                call_t* call = malloc(sizeof(call_t));
                                memset(call, 0, sizeof(call_t));
                                call->elist = $2;
                                call->method = 0;
                                call->name = NULL;
                                $$ = call;
                                Manage_normcall();
                            }         

methodcall: DOUBLE_STOP ID "(" elist ")"        {       
                                                        call_t* call = malloc(sizeof(call_t));
                                                        memset(call, 0, sizeof(call_t));
                                                        call->elist = $4;
                                                        call->method = 1;
                                                        call->name = $2;
                                                        $$ = call;
                                                        Manage_methodcall();  
                                                }

elist:  %empty            {     $$ = NULL;  Manage_elist_empty();           }
        | elist "," expr        {       while($1->next){
                                                $1 = $1->next;
                                        } 
                                        $1->next = $3; 
                                        $3->prev = $1; 
                                        Manage_elist_elistExpr();     
                                }
        | expr            {   $$ = $1; Manage_elist_expr();            }      
        ;

objectdef:  "[" elist "]"      {        expr* t = newexpr(newtable_e);
                                        t->sym = new_temp();
                                        emit(tablecreate, t, NULL, NULL, -1, currQuad);
                                        for(int i = 0; $2; $2 = $2->next)
                                                emit(tablesetelem, t, newexpr_constint(i++), $2, -1, currQuad);
                                        $$ = t;
                                        Manage_objectdef_elist();   
                                }
        |   "[" indexed "]"     {       expr* t = newexpr(newtable_e);
                                        t->sym = new_temp();
                                        emit(tablecreate, t, NULL, NULL, -1, currQuad);
                                        while($2){
                                                emit(tablesetelem, t, $2->index, $2, -1, currQuad);
                                                $2 = $2->next;
                                        }
                                        $$ = t;
                                        Manage_objectdef_indexed(); }
        ;

indexed:  indexed "," indexedelem       {       
                                                while($1->next){  
                                                        $1 = $1->next;
                                                }        
                                                $1->next = $3; 
                                                Manage_indexed_indexedIndexedelem(); 
                                        }
          | indexedelem             {   $$ = $1; Manage_indexed_indexedelem();        }
          ;

indexedelem: "{" expr ":" expr "}"  {   $4->index = $2;
                                        $$ = $4;
                                        Manage_indexedelem(); 
                                }

block: "{" {ScopeUp(0);} liststmt "}" {ScopeDown(0);} { $$=$3;  Manage_block_liststmt();    }
        |  "{" {ScopeUp(0);} "}" {ScopeDown(0);}       { $$=make_stmt();  Manage_block_emptyblock();   }
        ;

funcdef: FUNCTION ID {Init_named_func($2);infunction++;} "("idlist")" {$<symEntr>$ = Manage_funcdef_functionId($2,$5);} block 
                        {  End_named_func($2); patchlist($8->returnlist,nextquad()-1); infunction--;}
                        
        | FUNCTION{Init_Anonymous_func(); infunction++;} "("idlist")" block   {  $$ = Manage_funcdef_function($4);  patchlist($6->returnlist,nextquad()-1);infunction--; }
        ;

const:  INT       { $$ = Manage_const_int($1);    }
        | DOUBLE  { $$ = Manage_const_double($1);    }
        | STRING  { $$ = Manage_const_string($1);    }
        | NIL     { $$ = Manage_const_nil();       }
        | TRUE    { $$ = Manage_const_bool(1);      }
        | FALSE   { $$ = Manage_const_bool(0);     }
        ;

idlist: %empty          {   Manage_idlist_empty(&($$));      }
        | idlist "," ID {   Manage_idlist_idlistId(&($$),$1,$3);   }
        | ID            {   Manage_idlist_id(&($$),$1);         } 
        ;

ifprefix: IF "(" expr ")" {     printf("DULEUEI TO IF\n"); 
                                emit(if_eq, NULL, $3, newexpr_constbool(1), nextquad() + 2, currQuad);
                                $$ = nextquad();
                                emit(jump, NULL, NULL, NULL, 0, currQuad);
                        }

elseprefix: ELSE {      printf("DOULEUEI TO IF ELSE\n");
                        $$ = nextquad();
                        emit(jump, NULL, NULL, NULL, 0, currQuad);
                }

ifstmt:   ifprefix stmt elseprefix stmt {  patchlabel($1, $3 + 1); patchlabel($3, nextquad());  Manage_ifstmt_ifelse();
                                        $$ = make_stmt();
                                        $$->breaklist = mergelist($2->breaklist, $4->breaklist); 
                                        $$->continuelist = mergelist($2->continuelist, $4->continuelist);
                                        $$->returnlist = mergelist($2->returnlist, $4->returnlist);
                                        }
        | ifprefix stmt         {  $$ = $2; patchlabel($1, nextquad()); Manage_ifstmt_if();     }
        ;


loopstart:%empty  {++loopcounter;}

loopend:%empty  {--loopcounter;}

loopstmt: loopstart stmt loopend { $$ =$2;}

whilestart: WHILE {     printf("whilestart -> while\n");
                        $$ = nextquad();
                  }

whilecond: "(" expr ")" {       printf("whilecond -> (expr)\n");
                                emit(if_eq, NULL, $2, newexpr_constbool(1), nextquad() + 2, currQuad);
                                $$ = nextquad();
                                emit(jump, NULL, NULL, NULL, 0, currQuad);
                        }

whilestmt: whilestart whilecond loopstmt     {      Manage_whilestmt();  
                                                $$ = $3;
                                                emit(jump, NULL, NULL, NULL, $1, currQuad);
                                                patchlabel($2, nextquad());  
                                                patchlist($3->breaklist, nextquad());
                                                patchlist($3->continuelist, $1);
                                         }

N:%empty { $$ = nextquad(); emit(jump, NULL, NULL, NULL, 0, currQuad);}

M:%empty { $$ = nextquad(); }

forprefix: FOR "(" elist ";" M expr ";" {
        $$ = malloc(sizeof(forprefix_t));
        $$->test = $5; 
        //dummy emits
        emit(jump,NULL,NULL,NULL,-1,currQuad);
        emit(jump,NULL,NULL,NULL,-1,currQuad);
        emit(jump,NULL,NULL,NULL,-1,currQuad);
        emit(jump,NULL,NULL,NULL,-1,currQuad);
        $$->enter = nextquad();
        emit(if_eq, NULL, $6, newexpr_constbool(1), 0, nextquad());
}


forstmt: forprefix N elist ")" N loopstmt N {   
        patchlabel($1->enter, $5+1);
        patchlabel($2, nextquad());
        patchlabel($5, $1->test);
        patchlabel($7, $2 + 1);
        
        

        patchlist($6->breaklist, nextquad());
        patchlist($6->continuelist, $2+1);
        $$ = $6;
        Manage_forstmt();
};

returnstmt: RETURN expr";"  {  
                                if(infunction==0){
                                        print_custom_error("return outside of function","return",scope);
                                } 
                                $$ = Manage_returnstmt_returnexpr($2); 
                        }
            | RETURN";"     
                        {       if(infunction==0){
                                        print_custom_error("return outside of function","return",scope);
                                } 
                                $$ = Manage_returnstmt_return();     
                        }
            ;

%%
