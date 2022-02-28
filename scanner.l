%{

extern int  num_chars, num_token;
int total_comments = 0;
int start_comments = 0;
int string_flag = 0;
%}

%option header-file="scanner.h"
%option noyywrap
%option yylineno

indentifier		[a-zA-Z][a-zA-Z_0-9]*
integer         (0[xX][0-9A-Fa-f]+)|([0-9]+)
real            [0-9]*\.[0-9](e|E)?[0-9]
space           [\r\n \t\v]
string          \"[^\n"]*\"

%x BLOCK_COMMENT
%x LINE_COMMENT
%x STRING
%%

\n                   {};


"if"                    { printf("found token#%d IF in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}
"else"                  { printf("found token#%d ELSE in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}
"while"                 { printf("found token#%d WHILE in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}
"for"                   { printf("found token#%d FOR in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}
"function"              { printf("found token#%d FUNCTION in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}
"return"                { printf("found token#%d RETURN in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}                
"break"                 { printf("found token#%d BREAK in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}               
"continue"              { printf("found token#%d CONTINUE in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}             
"and"                   { printf("found token#%d AND in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}                  
"not"                   { printf("found token#%d NOT in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}                   
"or"                    { printf("found token#%d OR in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}
"local"                 { printf("found token#%d LOCAL in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}
"true"                  { printf("found token#%d TRUE in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}
"false"                 { printf("found token#%d FALSE in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}
"nil"                   { printf("found token#%d NIL in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}


"=="                    { printf("found token#%d EQUAL in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}
"!="                    { printf("found token#%d NOT_EQUAL in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}
"++"                    { printf("found token#%d PLUS_PLUS in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}
"--"                    { printf("found token#%d MINUS_MINUS in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}
">="                    { printf("found token#%d GREATER_EQUAL in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}
"<="                    { printf("found token#%d LESS_EQUAL in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}
"="                     { printf("found token#%d ASSIGNMENT in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}
"+"                     { printf("found token#%d PLUS in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}
"-"                     { printf("found token#%d MINUS in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}
"*"                     { printf("found token#%d ASTERISKOS in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}
"/"                     { printf("found token#%d SLASH in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}
"%"                     { printf("found token#%d PERCENT in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}
">"                     { printf("found token#%d GREATER in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}
"<"                     { printf("found token#%d LESS in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}

                 
"{"                     { printf("found token#%d LEFT_BRACE in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}
"}"                     { printf("found token#%d RIGHT_BRACE in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}
"["                     { printf("found token#%d LEFT_BRACKET in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}
"]"                     { printf("found token#%d RIGHT_BRACKET in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}
"("                     { printf("found token#%d LEFT_PARENTHESIS in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}
")"                     { printf("found token#%d RIGHT_PARENTHESIS in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}
";"                     { printf("found token#%d SEMICOLON in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}
","                     { printf("found token#%d COMA in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}
":"                     { printf("found token#%d COLON in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}
"::"                    { printf("found token#%d DOUBLE_COLON in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}
"."                     { printf("found token#%d STOP in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}
".."                    { printf("found token#%d DOUBLE_STOP in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);}





"//"                    {BEGIN(LINE_COMMENT);}
<LINE_COMMENT>.         {}
<LINE_COMMENT>\n        {
  printf("found token#%d COMMENT LINE_COMMENT in line %d\n",++num_token,yylineno-1);
  BEGIN(INITIAL);
}

"/*"                    {BEGIN(BLOCK_COMMENT);total_comments++;start_comments=yylineno;}
<BLOCK_COMMENT>"/*"           {total_comments++;}
<BLOCK_COMMENT>[^*]*          {}
<BLOCK_COMMENT>"*"+[^*/]*   {total_comments++;}
<BLOCK_COMMENT>"*"+"/"        {
  
  if((--total_comments)==0){
    printf("found token#%d COMMENT BLOCK_COMMENT from line %d till line %d \n",++num_token, start_comments, yylineno);
    BEGIN(INITIAL);
  }

}
<BLOCK_COMMENT><<EOF>>        { printf("error: unclosed comment in line %d\n", start_comments); exit(-1);}


{real}                  { printf("found token#%d DOUBLE INTEGER in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext); }
{integer}               { printf("found token#%d INTEGER in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext); }
{indentifier}           { printf("found token#%d IDENTIFIER in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext); }


{string}                {
   printf("found token#%d STRING in line %d with value: \'%s\'\n", ++num_token, yylineno , yytext);
   }


<*>. {}
%%