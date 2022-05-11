%{
	
	#include "yacc_utilities.h"
	

    FILE* yacc_out; 
	int yylex();

	extern int yylineno;
	extern char* yytext;
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
%token BREAK           "break"
%token CONTINUE        "continue"
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

%type stmt
%type<express> expr
%type<express> term
%type<express> assignexpr
%type<express> primary
%type<express> member
%type call
%type callsuffix
%type normcall
%type methodcall
%type elist
%type objectdef
%type indexed
%type indexedelem
%type block
%type funcdef
%type<express> const
%type<labelVal> ifprefix 
%type<labelVal> elseprefix
%type<labelVal> whilestart
%type<labelVal> whilecond
%type<labelVal> M
%type<labelVal> Me
%type<labelVal> N 
%type<statement> ifstmt
%type<statement> whilestmt
%type<statement> forstmt
%type<statement> returnstmt
%type<forprefixVal> forprefix
%type<statement> program

%%

program: liststmt   {   Manage_program_liststmt();     fclose(yacc_out); }
        |%empty     {   Manage_program_empty();        fclose(yacc_out); }
        ;

liststmt: liststmt stmt {  Manage_liststmt_liststmtStmt();      }
          | stmt        {   Manage_liststmt_stmt();             }
          ;

stmt: expr ";"  {       $$ = make_stmt(); Manage_stmt_expr();   reset_temp_counter();
                        printf("type: %d\n", $1->type);
                        if($1->type == boolexpr_e){
                                patchlist($1->truelist, nextquad());
                                patchlist($1->falselist, nextquad()+2);

                                expr* tmp = newexpr(var_e);
                                tmp->sym = new_temp();

                                emit(assign, tmp, newexpr_constbool(1), NULL, -1, currQuad);
                                emit(jump, NULL, NULL, NULL, nextquad() + 2 , currQuad);
                                emit(assign, tmp, newexpr_constbool(0), NULL, -1, currQuad);
                        }
                }
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

Me :%empty { $$ = nextquad();};

expr:   assignexpr        {     Manage_expr_assignexpr();       }
        | term            {     Manage_expr_term();             }
        | expr PLUS expr  {    $$ = Manage_expr_exprOPexpr($1,"+",$3, -1);    }
        | expr MINUS expr {    $$ = Manage_expr_exprOPexpr($1,"-",$3, -1);    }
        | expr MULT expr  {    $$ = Manage_expr_exprOPexpr($1,"*",$3, -1);    }
        | expr DIV expr   {    $$ = Manage_expr_exprOPexpr($1,"/",$3, -1);    }
        | expr MOD expr   {    $$ = Manage_expr_exprOPexpr($1,"%",$3, -1);    }
        | expr GE expr    {    $$ = Manage_expr_exprOPexpr($1,">=",$3, -1);   }
        | expr GT expr    {    $$ = Manage_expr_exprOPexpr($1,">",$3, -1);    }
        | expr LE expr    {    $$ = Manage_expr_exprOPexpr($1,"<=",$3, -1);   }
        | expr LT expr    {    $$ = Manage_expr_exprOPexpr($1,"<",$3, -1);    }
        | expr EQ expr    {    $$ = Manage_expr_exprOPexpr($1,"==",$3, -1);   }
        | expr NE expr    {    $$ = Manage_expr_exprOPexpr($1,"!=",$3, -1);   }
        | expr AND {true_test($1);} Me expr {  printf("M -> %d\n", $4); true_test($5);  $$ = Manage_expr_exprOPexpr($1,"and",$5, $4);}
        | expr OR Me expr  {    $$ = Manage_expr_exprOPexpr($1,"or",$4, $3);  }
        ;

term:   "(" expr ")"            {   $$ = $2; Manage_term_expr();               }
        | "-"expr  %prec UMINUS {   $$ = Manage_term_uminusExpr($2);           }
        | NOT expr              {   //thelei kialla logo tis olikis/merikis apotimisis.
                                    $$ = Manage_term_notExpr($2);              }
        | "++"lvalue            {   $$ = Manage_term_pluspluslvalue($2);       }
        | lvalue"++"            {   $$ = Manage_term_lvalueplusplus($1);       }
        | "--"lvalue            {   $$ = Manage_term_minusminuslvalue($2);     }
        | lvalue"--"            {   $$ = Manage_term_lvalueminusminus($1);     }
        | primary               {   $$ = $1; Manage_term_primary();            }
        ;

assignexpr: lvalue"="expr       {  $$ = Manage_assignexpr($1, $3);  $$->type = $3->type; };

primary:  lvalue            {  $$ = Manage_primary_lvalue($1);      }
          | call            {   Manage_primary_call();        }
          | objectdef       {   Manage_primary_objectdef();   }
          | "("funcdef")"   {   Manage_primary_funcdef();     }
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
        | call "." ID           {   Manage_member_callID();     }
        | call "[" expr "]"     {   Manage_member_callExpr();   }
        ;

call: call "(" elist ")"                 {  Manage_call_callElist();        }
      | lvalue callsuffix                {  Manage_call_lvalueCallsuffix($1); }
      | "(" funcdef ")" "(" elist ")"    {  Manage_call_funcdefElist();     }
      ;

callsuffix: normcall      { Manage_callsuffix_normcall();     }
            | methodcall  { Manage_callsuffix_methodcall();   }
            ;

normcall:   "(" elist ")"   {   Manage_normcall();    };          

methodcall: DOUBLE_STOP ID "(" elist ")"    {   Manage_methodcall();  };

elist:  %empty            {     Manage_elist_empty();           }
        | elist "," expr  {     Manage_elist_elistExpr();       }
        | expr            {     Manage_elist_expr();            }      
        ;

objectdef:  "[" elist "]"     {     Manage_objectdef_elist();   }
        |   "[" indexed "]"   {     Manage_objectdef_indexed(); }
        ;

indexed:  indexed"," indexedelem    {   Manage_indexed_indexedIndexedelem(); }
          | indexedelem             {   Manage_indexed_indexedelem();        }
          ;

indexedelem: "{" expr ":" expr "}"  {   Manage_indexedelem(); };

block: "{" {ScopeUp(0);} liststmt "}" {ScopeDown(0);} {   Manage_block_liststmt();    }
        |  "{" {ScopeUp(0);} "}" {ScopeDown(0);}       {  Manage_block_emptyblock();   }
        ;

funcdef: FUNCTION ID {Init_named_func($2);} "("idlist")" {Manage_funcdef_functionId($2,$5);} block 
                        {  End_named_func($2); }
                        
        | FUNCTION{Init_Anonymous_func();} "("idlist")" block   {   Manage_funcdef_function($4);   }
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

ifstmt:   ifprefix stmt elseprefix stmt { patchlabel($1, $3 + 1); patchlabel($3, nextquad());  Manage_ifstmt_ifelse();  }
        | ifprefix stmt         {   patchlabel($1, nextquad()); Manage_ifstmt_if();     }
        ;


loopstart:%empty  {/*++loopcounter;*/}

loopend:%empty  {/*--loopcounter;*/}

loopstmt: loopstart stmt loopend {  }

whilestart: WHILE {     printf("whilestart -> while\n");
                        $$ = nextquad();
                  }

whilecond: "(" expr ")" {       printf("whilecond -> (expr)\n");
                                emit(if_eq, NULL, $2, newexpr_constbool(1), nextquad() + 2, currQuad);
                                $$ = nextquad();
                                emit(jump, NULL, NULL, NULL, 0, currQuad);
                        }

whilestmt: whilestart whilecond loopstmt     {      Manage_whilestmt();  
                                                emit(jump, NULL, NULL, NULL, $1, currQuad);
                                                patchlabel($2, nextquad());  
                                                // patchlist(stmt.breaklist, nextquad());
                                                // patchlist(stmt.contlist, $1);
                                         }

/* N:%empty { $$ = nextquad(); emit(jump, NULL, NULL, NULL, 0, currQuad);}

M:%empty { $$ = nextquad();}

forprefix: FOR "(" elist ";" M expr ";" {

} */


forstmt: FOR "(" elist ";" expr ";" elist ")" loopstmt  {   Manage_forstmt();  };

returnstmt: RETURN expr";"  {   Manage_returnstmt_returnexpr(); }
            | RETURN";"     {   Manage_returnstmt_return();     }
            ;

%%
