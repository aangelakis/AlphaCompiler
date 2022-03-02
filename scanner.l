%{
#include"lexanal.h"

#define YY_DECL int alpha_yylex(void* yylval)

alpha_token_t *tail = NULL;

extern int  num_chars, num_token;
int total_comments = 0;
int start_comments = 0;
int string_flag = 0;

char* replace_bs_with(char*, int, char, int);
void backslash(char **);

void insert_data(int numline, int numToken, char *content, char *type, alpha_token_t* yylval, char* specialty);
%}

%option header-file="scanner.h"
%option noyywrap
%option yylineno

indentifier		  [a-zA-Z][a-zA-Z_0-9]*
integer         (0[xX][0-9A-Fa-f]+)|([0-9]+)
real            [0-9]*\.[0-9](e|E)?[0-9]*
space           [\r\n \t\v]
string          \"(\\.|[^"\\])*\"

%x BLOCK_COMMENT
%x LINE_COMMENT
%x STRING
%%

\n                   {};

"if"                    { insert_data(yylineno, ++num_token, yytext, KEYWORD, yylval,"IF"); return 1;}
"else"                  { insert_data(yylineno, ++num_token, yytext, KEYWORD, yylval,"ELSE"); return 1;}
"while"                 { insert_data(yylineno, ++num_token, yytext, KEYWORD, yylval,"WHILE"); return 1;}
"for"                   { insert_data(yylineno, ++num_token, yytext, KEYWORD, yylval,"FOR"); return 1;}
"function"              { insert_data(yylineno, ++num_token, yytext, KEYWORD, yylval,"FUNCTION"); return 1;}
"return"                { insert_data(yylineno, ++num_token, yytext, KEYWORD, yylval,"RETURN"); return 1;}                
"break"                 { insert_data(yylineno, ++num_token, yytext, KEYWORD, yylval,"BREAK"); return 1;}               
"continue"              { insert_data(yylineno, ++num_token, yytext, KEYWORD, yylval,"CONTINUE"); return 1;}             
"and"                   { insert_data(yylineno, ++num_token, yytext, KEYWORD, yylval,"AND"); return 1;}                  
"not"                   { insert_data(yylineno, ++num_token, yytext, KEYWORD, yylval,"NOT"); return 1;}                   
"or"                    { insert_data(yylineno, ++num_token, yytext, KEYWORD, yylval,"OR"); return 1;}
"local"                 { insert_data(yylineno, ++num_token, yytext, KEYWORD, yylval,"LOCAL"); return 1;}
"true"                  { insert_data(yylineno, ++num_token, yytext, KEYWORD, yylval,"TRUE"); return 1;}
"false"                 { insert_data(yylineno, ++num_token, yytext, KEYWORD, yylval,"FALSE"); return 1;}
"nil"                   { insert_data(yylineno, ++num_token, yytext, KEYWORD, yylval,"NIL"); return 1;}


"=="                    { insert_data(yylineno, ++num_token, yytext, OPERATOR, yylval,"EQUALS"); return 1;}
"!="                    { insert_data(yylineno, ++num_token, yytext, OPERATOR, yylval,"NOT_EQUALS"); return 1;}
"++"                    { insert_data(yylineno, ++num_token, yytext, OPERATOR, yylval,"PLUS_PLUS"); return 1;}
"--"                    { insert_data(yylineno, ++num_token, yytext, OPERATOR, yylval,"MINUS_MINUS"); return 1;}
">="                    { insert_data(yylineno, ++num_token, yytext, OPERATOR, yylval,"GREATER_EQUAL"); return 1;}
"<="                    { insert_data(yylineno, ++num_token, yytext, OPERATOR, yylval,"LESS_EQUAL"); return 1;}
"="                     { insert_data(yylineno, ++num_token, yytext, OPERATOR, yylval,"ASSIGN"); return 1;}
"+"                     { insert_data(yylineno, ++num_token, yytext, OPERATOR, yylval,"PLUS"); return 1;}
"-"                     { insert_data(yylineno, ++num_token, yytext, OPERATOR, yylval,"MINUS"); return 1;}
"*"                     { insert_data(yylineno, ++num_token, yytext, OPERATOR, yylval,"ASTERISK"); return 1;}
"/"                     { insert_data(yylineno, ++num_token, yytext, OPERATOR, yylval,"SLASH"); return 1;}
"%"                     { insert_data(yylineno, ++num_token, yytext, OPERATOR, yylval,"PERCENT"); return 1;}
">"                     { insert_data(yylineno, ++num_token, yytext, OPERATOR, yylval,"GREATER_THAN"); return 1;}
"<"                     { insert_data(yylineno, ++num_token, yytext, OPERATOR, yylval,"LESS_THAN"); return 1;}

                 
"{"                     { insert_data(yylineno, ++num_token, yytext, PUNCTUATION, yylval,"LEFT_BRACE"); return 1;}
"}"                     { insert_data(yylineno, ++num_token, yytext, PUNCTUATION, yylval,"RIGHT_BRACE"); return 1;}
"["                     { insert_data(yylineno, ++num_token, yytext, PUNCTUATION, yylval,"LEFT_BRACKET"); return 1;}
"]"                     { insert_data(yylineno, ++num_token, yytext, PUNCTUATION, yylval,"RIGHT_BRACKET"); return 1;}
"("                     { insert_data(yylineno, ++num_token, yytext, PUNCTUATION, yylval,"LEFT_PARENTHESIS"); return 1;}
")"                     { insert_data(yylineno, ++num_token, yytext, PUNCTUATION, yylval,"RIGHT_PARENTHESIS"); return 1;}
";"                     { insert_data(yylineno, ++num_token, yytext, PUNCTUATION, yylval,"SEMICOLON"); return 1;}
","                     { insert_data(yylineno, ++num_token, yytext, PUNCTUATION, yylval,"COMMA"); return 1;}
":"                     { insert_data(yylineno, ++num_token, yytext, PUNCTUATION, yylval,"COLON"); return 1;}
"::"                    { insert_data(yylineno, ++num_token, yytext, PUNCTUATION, yylval,"DOUBLE_COLON"); return 1;}
"."                     { insert_data(yylineno, ++num_token, yytext, PUNCTUATION, yylval,"STOP"); return 1;}
".."                    { insert_data(yylineno, ++num_token, yytext, PUNCTUATION, yylval,"DOUBLE_STOP"); return 1;}




"//"                    {BEGIN(LINE_COMMENT);}
<LINE_COMMENT>.         {}
<LINE_COMMENT>\n        {
  insert_data(yylineno-1, ++num_token, " ", COMMENT, yylval,"LINE_COMMENT");
  BEGIN(INITIAL);
  return 1;
}

"/*"                    {BEGIN(BLOCK_COMMENT);total_comments++;start_comments=yylineno;}
<BLOCK_COMMENT>"/*"           {total_comments++;}
<BLOCK_COMMENT>[^*]*          {}
<BLOCK_COMMENT>"*"+[^*/]*   {total_comments++;}
<BLOCK_COMMENT>"*"+"/"        {
  
  if((--total_comments)==0){
    char str_final[1024];
    sprintf(str_final, "%d%s%d",start_comments," - ",yylineno);
    
    insert_data(yylineno, ++num_token, str_final, COMMENT, yylval,"BLOCK_COMMENT");
    BEGIN(INITIAL);
  }else{
    insert_data(yylineno, ++num_token, " ", COMMENT, yylval,"NESTED_COMMENT");
  }
  return 1;

}
<BLOCK_COMMENT><<EOF>>        { printf("error: unclosed comment in line %d\n", start_comments); exit(-1);}


{real}                  {   insert_data(yylineno, ++num_token, yytext, DOUBLE, yylval,NULL); return 1; }
{integer}               {   insert_data(yylineno, ++num_token, yytext, INTEGER, yylval,NULL); return 1; }
{indentifier}           {   insert_data(yylineno, ++num_token, yytext, IDENTIFIER, yylval,NULL); return 1; }


{string}                {
    
    //printf("testing before removing things string :\n %s\n\n",yytext);

    backslash(&yytext);

    //printf("testing string :\n %s\n\n",yytext);

    insert_data(yylineno, ++num_token, yytext, STRING_, yylval,NULL); return 1;
}


([0-9]+)([a-zA-Z_]+)          {printf("Error in line %d token: %s not accepted\n",yylineno,yytext);}


<<EOF>> {return -1;}

<*>. {
  if(strcmp(yytext,"\"") == 0){
    printf("unclosed string starting in line %d\n",yylineno);
    exit(0);
  }  
}

%%

char* replace_bs_with(char* s, int stop, char c, int first_time) {
    char *iter = s, *new_s = (char *) malloc(strlen(s) * sizeof(char));
    int i = 0;

    while(i != stop) {
        new_s[i] = iter[i];
        i++;
    }
    new_s[i] = c;
    i++;
    while(iter[i]){
        new_s[i] = iter[i+1];
        i++;
    }

    if(!first_time)
        free(s);
    return new_s;
}

void backslash(char **s) {
    char *iter = *s;
    int first_time = 1, chars = 0, count=0;

    while(*iter) {
        if(*iter == '\\') {
            //printf("count=%d, ", count++);
            //puts(*s);
            if(*(iter+1) == 'n') {
                *s = replace_bs_with(*s, chars, '\n', first_time);
                chars--;
                first_time = 0;
            }
            else if(*(iter+1) == 't') {
                *s = replace_bs_with(*s, chars, '\t', first_time);
                chars--;
                first_time = 0;
            }
            else if(*(iter+1) == '\\') {
                *s = replace_bs_with(*s, chars, '\\', first_time);
                chars--;
                first_time = 0;
            }else if(*(iter+1) == '\"') {
                *s = replace_bs_with(*s, chars, '\"', first_time);
                chars--;
                first_time = 0;
            }
            
            /* START FIX */
            if(*iter == '\\') {
                chars++;
                iter++;
            }
            /* END FIX */
        }
        chars++;
        iter++;
    }
}

void insert_data(int numline, int numToken, char *content, char *type, alpha_token_t* yylval, char* specialty)
{
    yylval->numline = numline;
    yylval->numToken = numToken;
    yylval->content = (char *) malloc(strlen(content) * sizeof(char));
    strcpy(yylval->content, content);
    yylval->type = type;
    yylval->next = NULL;

    //if specialty is null it means copy the content to the specialty else assign the new one
    if(specialty==NULL){
      yylval->specialty = yylval->content;
    }else{
      yylval->specialty = specialty;
    }
    
}
