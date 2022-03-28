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

program: liststmt   {   printf("program -> stmt*\n");   };

liststmt: liststmt stmt {   printf("liststmt -> liststmt stmt\n");  }
          | stmt        {   printf("liststmt -> stmt\n");   }
          ;

stmt: expr ";"      {   printf("stmt -> expr;\n");      }
      | ifstmt      {   printf("stmt -> ifstmt\n");     }
      | whilestmt   {   printf("stmt -> whilestmt\n");  }
      | forstmt     {   printf("stmt -> forstmt\n");    }
      | returnstmt  {   printf("stmt -> returnstmt\n"); }
      | BREAK ";"   {   printf("stmt -> break;\n");     }  
      | CONTINUE ";"{   printf("stmt -> continue;\n");  }
      | block       {   printf("stmt -> block\n");      }
      | funcdef     {   printf("stmt -> funcdef\n");    }
      | ";"         {   printf("stmt -> ;\n");          }
      ;

expr:   assignexpr        {     printf("expr -> assignexpr\n");     }
        | term            {     printf("expr -> term\n");           }
        | expr PLUS expr  {     printf("expr -> expr + expr\n");    }
        | expr MINUS expr {     printf("expr -> expr - expr\n");    }
        | expr MULT expr  {     printf("expr -> expr * expr\n");    }
        | expr DIV expr   {     printf("expr -> expr / expr\n");    }
        | expr MOD expr   {     printf("expr -> expr %% expr\n");   }
        | expr GE expr    {     printf("expr -> expr >= expr\n");   }
        | expr GT expr    {     printf("expr -> expr > expr\n");    }
        | expr LE expr    {     printf("expr -> expr <= expr\n");   }
        | expr LT expr    {     printf("expr -> expr < expr\n");    }
        | expr EQ expr    {     printf("expr -> expr == expr\n");   }
        | expr NE expr    {     printf("expr -> expr != expr\n");   }
        | expr AND expr   {     printf("expr -> expr and expr\n");  }
        | expr OR expr    {     printf("expr -> expr or expr\n");   }
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

term:   "(" expr ")"            {   printf("term -> (expr)\n");     }
        | "-"expr  %prec UMINUS {   printf("term -> -expr\n");      }
        | NOT expr              {   printf("term -> not expr\n");   }
        | "++"lvalue            {   printf("term -> ++lvalue\n");   }
        | lvalue"++"            {   printf("term -> lvalue++\n");   }
        | "--"lvalue            {   printf("term -> --lvalue\n");   }
        | primary               {   printf("term -> primary\n");    }
        ;

assignexpr: lvalue"="expr       {   printf("assignexpr -> lvalue=expr\n");  };

primary:  lvalue            {   printf("primary -> lvalue\n");      }
          | call            {   printf("primary -> call\n");        }
          | objectdef       {   printf("primary -> objectdef\n");   }
          | "("funcdef")"   {   printf("primary -> (funcdec)\n");   }
          | const           {   printf("primary -> const\n");       }
          ;

lvalue: ID                    { printf("lvalue -> id\n");       }
        | LOCAL ID            { printf("lvalue -> local id\n"); }
        | DOUBLE_COLON ID     { printf("lvalue -> ::id\n");     }
        | member              { printf("lvalue -> member\n");   }
        ;

member: lvalue "." ID           {   printf("member -> lvalue.id\n");    }
        | lvalue "[" expr "]"   {   printf("member -> lvalue[expr]\n"); }
        | call "." ID           {   printf("member -> call.id\n");      }
        | call "[" expr "]"     {   printf("member -> call[expr]\n");   }
        ;

call: call "(" elist ")"                 {  printf("call -> call(elist)\n");        }
      | lvalue callsuffix                {  printf("call -> lvalue callsuffix\n");  }
      | "(" funcdef ")" "(" elist ")"    {  printf("call -> (funcdef)(elist)\n");   }
      ;

callsuffix: normcall      { printf("callsuffix -> normcall\n");     }
            | methodcall  { printf("callsuffix -> methodcall\n");   }
            ;

normcall:   "(" elist ")"   {   printf("normcall -> (elist)\n");    };          

methodcall: DOUBLE_STOP ID "(" elist ")"    {   printf("methodcall -> ..id(elist)\n");  };

elist:  %empty            {     printf("elist -> ε\n");             }
        | elist "," expr  {     printf("elist -> elist,expr\n");    }
        | expr            {     printf("elist -> epxr\n");          }      
        ;

objectdef:  "[" elist "]"     {     printf("objectdef -> [elist]\n");   }
        |   "[" indexed "]"   {     printf("objectdef -> [indexed]\n"); }
        ;

indexed:  indexed"," indexedelem    {   printf("indexed -> indexed,indexedelem\n"); }
          | indexedelem             {   printf("indexed -> indexedelem\n");         }
          ;

indexedelem: "{" expr ":" expr "}"  {   printf("indexedelem -> {expr:expr}\n"); };

block: "{" liststmt "}" {   printf("block -> stmt*\n"); }
        | "{" "}"        {  printf("block -> {}\n");    }
        ;

funcdef: FUNCTION ID "("idlist")" block {   printf("function id (idlist) block\n"); }
        | FUNCTION "("idlist")" block   {   printf("function (idlist) block\n");    }
        ;

const:  INT       { printf("const -> number\n");    }
        | DOUBLE  { printf("const -> number\n");    }
        | STRING  { printf("const -> string\n");    }
        | NIL     { printf("const -> nil\n");       }
        | TRUE    { printf("const -> true\n");      }
        | FALSE   { printf("const -> false\n");     }
        ;

idlist: %empty          {   printf("idlist -> ε\n");        }
        | idlist "," ID {   printf("idlist -> id,id*\n");   }
        | ID            {   printf("idlist -> id\n");       }
        ;

ifstmt: IF "(" expr ")" stmt ELSE stmt {    printf("ifstmt -> if (expr) stmt else\n");  }
        | IF "(" expr ")" stmt         {    printf("ifstmt -> if (expr)\n");            }
        ;

whilestmt: WHILE "(" expr ")" stmt     {    printf("whilestmt -> while(expr) stmt\n");  };

forstmt: FOR "(" elist ";" expr ";" elist ")" stmt  {   printf("forstmt -> for(elist;expr;elist) stmt\n");  };

returnstmt: RETURN expr";"  {   printf("returnstmt -> return expr;\n"); }
            | RETURN";"     {   printf("returnstmt -> return;\n");      }
            ;

%%

int yyerror(char* yaccProvideMessage)
{
    fprintf(stderr, "%s:at line %d, before token: \'%s\'\n",  yaccProvideMessage, yylineno, yytext);
    fprintf(stderr , "INPUT NOT VALID\n");
}