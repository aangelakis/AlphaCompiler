%{
int yyerror(char *yaccProvideMessage);
int yylex();

#include <stdio.h>
#include "ipografes.h"
extern int yylineno;
extern char* yytext;
int scope = 0;
int flag_scope = 0 ; // 0 == block ; 1 == function
%}

%output "parser.c"
%defines

%union {
    char*   strVal;
    int     intVal;
    double  realVal;
    void*   allVal;
}

%start program
%expect 1

/* Terminal Symbols */
%token<strVal> ID
%token<strVal> STRING
%token<intVal> INT
%token<realVal> DOUBLE

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
%token TRUE            "true"
%token FALSE           "false"
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
%type<allVal> stmt
%type<allVal> expr
%type<allVal> term
%type<allVal> assignexpr
%type<allVal> primary
%type<allVal> lvalue
%type<allVal> member
%type<allVal> call
%type<allVal> callsuffix
%type<allVal> normcall
%type<allVal> methodcall
%type<allVal> elist
%type<allVal> objectdef
%type<allVal> indexed
%type<allVal> indexedelem
%type<allVal> block
%type<allVal> funcdef
%type<allVal> const
%type<allVal> idlist
%type<allVal> ifstmt
%type<allVal> whilestmt
%type<allVal> forstmt
%type<allVal> returnstmt

%%

program: liststmt   {   Manage_program_liststmt();      }
        |%empty     {   Manage_program_empty();         }
        ;

liststmt: liststmt stmt {  Manage_liststmt_liststmtStmt();      }
          | stmt        {   Manage_liststmt_stmt();             }
          ;

stmt: expr ";"      {   Manage_stmt_expr();         }
      | ifstmt      {   Manage_stmt_ifstmt();       }
      | whilestmt   {   Manage_stmt_whilestmt();    }
      | forstmt     {   Manage_stmt_forstmt();      }
      | returnstmt  {   Manage_stmt_returnstmt();   }
      | BREAK ";"   {   Manage_stmt_break();        }  
      | CONTINUE ";"{   Manage_stmt_continue();     }
      | block       {   Manage_stmt_block();        }
      | funcdef     {   Manage_stmt_funcdef();      }
      | ";"         {   Manage_stmt_semicolon();    }
      ;

expr:   assignexpr        {     Manage_expr_assignexpr();       }
        | term            {     Manage_expr_term();             }
        | expr PLUS expr  {     Manage_expr_exprOPexpr("+");    }
        | expr MINUS expr {     Manage_expr_exprOPexpr("-");    }
        | expr MULT expr  {     Manage_expr_exprOPexpr("*");    }
        | expr DIV expr   {     Manage_expr_exprOPexpr("/");    }
        | expr MOD expr   {     Manage_expr_exprOPexpr("%");    }
        | expr GE expr    {     Manage_expr_exprOPexpr(">=");   }
        | expr GT expr    {     Manage_expr_exprOPexpr(">");    }
        | expr LE expr    {     Manage_expr_exprOPexpr("<=");   }
        | expr LT expr    {     Manage_expr_exprOPexpr("<");    }
        | expr EQ expr    {     Manage_expr_exprOPexpr("==");   }
        | expr NE expr    {     Manage_expr_exprOPexpr("!=");   }
        | expr AND expr   {     Manage_expr_exprOPexpr("and");  }
        | expr OR expr    {     Manage_expr_exprOPexpr("or");   }
        ;

term:   "(" expr ")"            {   Manage_term_expr();                 }
        | "-"expr  %prec UMINUS {   Manage_term_uminusExpr();           }
        | NOT expr              {   Manage_term_notExpr();              }
        | "++"lvalue            {   Manage_term_pluspluslvalue();       }
        | lvalue"++"            {   Manage_term_lvalueplusplus();       }
        | "--"lvalue            {   Manage_term_minusminuslvalue();     }
        | lvalue"--"            {   Manage_term_lvalueminusminus();     }
        | primary               {   Manage_term_primary();              }
        ;

assignexpr: lvalue"="expr       {   printf("assignexpr -> lvalue=expr\n");  };

primary:  lvalue            {   Manage_primary_lvalue();      }
          | call            {   Manage_primary_call();        }
          | objectdef       {   Manage_primary_objectdef();   }
          | "("funcdef")"   {   Manage_primary_funcdef();     }
          | const           {   Manage_primary_const();       }
          ;

lvalue: ID                    { Manage_lvalue_id();         }
        | LOCAL ID            { Manage_lvalue_localID();    }
        | DOUBLE_COLON ID     { Manage_lvalue_globalID();   }
        | member              { Manage_lvalue_member();     }
        ;

member: lvalue "." ID           {   Manage_member_lvalueID();   }
        | lvalue "[" expr "]"   {   Manage_member_lvalueExpr(); }
        | call "." ID           {   Manage_member_callID();     }
        | call "[" expr "]"     {   Manage_member_callExpr();   }
        ;

call: call "(" elist ")"                 {  Manage_call_callElist();        }
      | lvalue callsuffix                {  Manage_call_lvalueCallsuffix(); }
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
        |  "{" {ScopeUp(0);} "}" {ScopeDown(0);}       {  Manage_block_emptyblock();  }
        ;

funcdef: FUNCTION ID {ScopeUp(1);}"("idlist")" block {   Manage_funcdef_functionId(); }
        | FUNCTION{ScopeUp(1);} "("idlist")" block   {   Manage_funcdef_function();   }
        ;

const:  INT       { Manage_const_number();    }
        | DOUBLE  { Manage_const_number();    }
        | STRING  { Manage_const_string();    }
        | NIL     { Manage_const_nil();       }
        | TRUE    { Manage_const_true();      }
        | FALSE   { Manage_const_false();     }
        ;

idlist: %empty          {   Manage_idlist_empty();      }
        | idlist "," ID {   Manage_idlist_idlistId();   }
        | ID            {   Manage_idlist_id();         }
        ;

ifstmt: IF "(" expr ")" stmt ELSE stmt {   Manage_ifstmt_ifelse();  }
        | IF "(" expr ")" stmt         {    Manage_ifstmt_if();     }
        ;

whilestmt: WHILE  "(" expr ")" stmt     {    Manage_whilestmt();  };

forstmt: FOR "(" elist ";" expr ";" elist ")" stmt  {   Manage_forstmt();  };

returnstmt: RETURN expr";"  {   Manage_returnstmt_returnexpr(); }
            | RETURN";"     {   Manage_returnstmt_return();     }
            ;

%%

int yyerror(char* yaccProvideMessage)
{
    fprintf(stderr, "%s:at line %d, before token: \'%s\'\n",  yaccProvideMessage, yylineno, yytext);
    fprintf(stderr , "INPUT NOT VALID\n");
}