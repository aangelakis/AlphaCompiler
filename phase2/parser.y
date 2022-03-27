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

%token<strVal> IDENTIFIER
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
%left LEFT_PARENTHESIS RIGHT_PARENTHESIS

%type<allVal> stmt
%type<intVal> expr
%type<strVal> op

%%

program: stmt;

stmt: expr  {};

expr:   INT
        |expr op expr
        ;

op: PLUS    {}
  | MINUS   {}
  | MULT    {}
  | DIV     {}
  | MOD     {}
  | GT      {}
  | GE      {}
  | LT      {}
  | LE      {}
  | EQ      {}
  | NE      {}
  | AND     {}
  | OR      {}; 

%%

int yyerror(char* yaccProvideMessage)
{
    fprintf(stderr, "%s:at line %d, before token: %s\n",  yaccProvideMessage, yylineno, yytext);
    fprintf(stderr , "INPUT NOT VALID\n");
}