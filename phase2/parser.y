%{
int yyerror(char *yaccProvideMessage);
int yylex();

#include <stdio.h>
extern int yylineno;
extern char* yytext;
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

%token LEFT_BRACE          "["
%token RIGHT_BRACE         "]"
%token LEFT_BRACKET        "{"
%token RIGHT_BRACKET       "}"
%token LEFT_PARENTHESIS    "("
%token RIGHT_PARENTHESIS   ")"
%token SEMICOLON           ";"
%token COMMA               ","
%token COLON               ":"
%token DOUBLE_COLON        "::"
%token STOP                "."
%token DOUBLE_STOP         ".."

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
%left LEFT_BRACE RIGHT_BRACE
%nonassoc UMINUS
%left LEFT_PARENTHESIS RIGHT_PARENTHESIS

%type<allVal> stmt
%type<allVal> expr
//%type<strVal> op

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

program: liststmt;

liststmt: liststmt stmt
          | stmt
          ;

stmt: expr ";"      {}
      | ifstmt      {}
      | whilestmt   {}
      | forstmt     {}
      | returnstmt  {}
      | BREAK ";"   {}  
      | CONTINUE ";"{}
      | block       {}
      | funcdef     {}
      | ";"           {}
      ;

expr:   assignexpr        {}
        | term            {}
        | expr PLUS expr  {}
        | expr MINUS expr {}
        | expr MULT expr  {}
        | expr DIV expr   {}
        | expr MOD expr   {}
        | expr GE expr    {}
        | expr GT expr    {}
        | expr LE expr    {}
        | expr LT expr    {}
        | expr EQ expr    {}
        | expr NE expr    {}
        | expr AND expr   {}
        | expr OR expr    {}
        ;

// Check this!
/*op: PLUS    {}
  | MINUS   {}
  | MULT    {} 
  | DIV     {}
  | MOD     {}
  | GE      {}
  | GT      {}
  | LE      {}
  | LT      {}
  | EQ      {}
  | NE      {}
  | AND     {}
  | OR      {}
  ; 
*/

term:   "(" expr ")"            {}
        | "-"expr  %prec UMINUS {}
        | NOT expr              {}
        | "++"lvalue          {}
        | lvalue"++"          {}
        | "--"lvalue          {}
        | primary               {}
        ;

assignexpr: lvalue"="expr  {};

primary:  lvalue            {}
          | call            {}
          | objectdef       {}
          | "("funcdef")"   {}
          | const           {}
          ;

lvalue: ID                    {}
        | LOCAL ID            {}
        | DOUBLE_COLON ID     {}
        | member              {}
        ;

member: lvalue "." ID           {}
        | lvalue "[" expr "]"   {}
        | call "." ID           {}
        | call "[" expr "]"     {}
        ;

call: call "(" elist ")"                 {}
      | lvalue callsuffix                {}
      | "(" funcdef ")" "(" elist ")"    {}
      ;

callsuffix: normcall      {}
            | methodcall  {}
            ;

normcall:   "(" elist ")"   {};          

methodcall: DOUBLE_STOP ID "(" elist ")"    {};

elist:  %empty            {}
        | elist "," expr  {}
        | expr            {}      
        ;

objectdef:  "[" elist "]"     {}
        |   "[" indexed "]"   {}
        ;

indexed:  indexed"," indexedelem    {}
          | indexedelem               {}
          ;

indexedelem: "{" expr ":" expr "}" {};

block: "{" liststmt "}" {}
        | "{" "}"        {}
        ;

funcdef: FUNCTION ID "("idlist")" block {}
        | FUNCTION "("idlist")" block {}
        ;

const:  INT       {}
        | DOUBLE  {}
        | STRING  {}
        | NIL     {}
        | TRUE    {}
        | FALSE   {}
        ;

idlist: %empty          {}
        | idlist "," ID {}
        | ID            {}
        ;

ifstmt: IF "(" expr ")" stmt ELSE stmt {}
        | IF "(" expr ")" stmt {}
        ;

whilestmt: WHILE "(" expr ")" stmt  {};

forstmt: FOR "(" elist ";" expr ";" elist ")" stmt  {};

returnstmt: RETURN expr";"  {}
            | RETURN";"     {}
            ;

%%

int yyerror(char* yaccProvideMessage)
{
    fprintf(stderr, "%s:at line %d, before token: %s\n",  yaccProvideMessage, yylineno, yytext);
    fprintf(stderr , "INPUT NOT VALID\n");
}