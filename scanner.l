%{

extern int num_lines, num_chars, num_token;

%}

%option header-file="scanner.h"
%option noyywrap
%option yylineno

indentifier		[a-zA-Z][a-zA-Z_0-9]*
integer         (0[xX][0-9A-Fa-f]+)|([0-9]+)
real            [0-9]*\.[0-9](e|E)?[0-9]
space           [\r\n \t\v]
string          \"[^\n"]*\"

%x COMMENT INCLUDE

%%
<*>\n                   ++num_lines;
"if"                    { printf("found token#%d IF in line %d with value: \'%s\'\n", ++num_token, num_lines , yytext);}
"else"                  { printf("found token#%d ELSE in line %d with value: \'%s\'\n", ++num_token, num_lines , yytext);}
"while"                 { printf("found token#%d WHILE in line %d with value: \'%s\'\n", ++num_token, num_lines , yytext);}
"for"                   { printf("found token#%d FOR in line %d with value: \'%s\'\n", ++num_token, num_lines , yytext);}
"function"              { printf("found token#%d FUNCTION in line %d with value: \'%s\'\n", ++num_token, num_lines , yytext);}
"return"                { printf("found token#%d RETURN in line %d with value: \'%s\'\n", ++num_token, num_lines , yytext);}                
"break"                 { printf("found token#%d BREAK in line %d with value: \'%s\'\n", ++num_token, num_lines , yytext);}               
"continue"              { printf("found token#%d CONTINUE in line %d with value: \'%s\'\n", ++num_token, num_lines , yytext);}             
"and"                   { printf("found token#%d AND in line %d with value: \'%s\'\n", ++num_token, num_lines , yytext);}                  
"not"                   { printf("found token#%d NOT in line %d with value: \'%s\'\n", ++num_token, num_lines , yytext);}                   
"or"                    { printf("found token#%d OR in line %d with value: \'%s\'\n", ++num_token, num_lines , yytext);}
"local"                 { printf("found token#%d LOCAL in line %d with value: \'%s\'\n", ++num_token, num_lines , yytext);}
"true"                  { printf("found token#%d TRUE in line %d with value: \'%s\'\n", ++num_token, num_lines , yytext);}
"false"                 { printf("found token#%d FALSE in line %d with value: \'%s\'\n", ++num_token, num_lines , yytext);}
"nil"                   { printf("found token#%d NIL in line %d with value: \'%s\'\n", ++num_token, num_lines , yytext);}









"/*"                    BEGIN(COMMENT);
<COMMENT>[^*]*          {}
<COMMENT>"*"+[^*/\n]*   {}
<COMMENT>"*"+"/"        BEGIN(INITIAL);
<COMMENT><<EOF>>        { printf("error: unclosed comment in line %d\n", num_lines); exit(-1);}
{keyword}               { printf("found token#%d KEYWORD in line %d with value: \'%s\'\n", ++num_token, num_lines , yytext); }
{indentifier}           { printf("found token#%d IDENTIFIER in line %d with value: \'%s\'\n", ++num_token, num_lines , yytext); }
.
%%