/* Definition Section */
%{
#include<stdio.h>
#include"parser.h"

int num_token = 0;
int start_comments = 0;
int nested_comments = 0;
int string_flag = 0;
int nested_comment_starting_line[1024];

char* replace_bs_with(char*, int, char, int);
void backslash(char **);
int find_new_lines(char *);
void remove_quotes(char* s);
void print_token(int numline, int numToken, char *content, char *type, char* specialty);
%}

/* FLEX Options */
%option header-file="scanner.h"
%option noyywrap
%option yylineno


/* FLEX Macros */
indentifier		  [a-zA-Z][a-zA-Z_0-9]*
integer         (0[xX][0-9A-Fa-f]+)|([0-9]+)
real            [0-9]*\.[0-9](e|E)?[0-9]*
space           [\r\n \t\v]
string         	\"(\\.|\\\n|[^"\\])*\" 

%x BLOCK_COMMENT
%x LINE_COMMENT
%x STRING
%%

\n                      {};

"if"                    { 
                            print_token(yylineno, ++num_token, yytext, "KEYWORD","IF");
                            yylval.strVal = strdup(yytext);
                            return IF;
                        }

"else"                  { 
                            print_token(yylineno, ++num_token, yytext, "KEYWORD","ELSE");
                            yylval.strVal = strdup(yytext);
                            return ELSE;
                        }

"while"                 {
                            print_token(yylineno, ++num_token, yytext, "KEYWORD", "WHILE");
                            yylval.strVal = strdup(yytext);
                            return WHILE;
                        }

"for"                   { 
                            print_token(yylineno, ++num_token, yytext, "KEYWORD", "FOR");
                            yylval.strVal = strdup(yytext);
                            return FOR;
                        }

"function"              { 
                            print_token(yylineno, ++num_token, yytext, "KEYWORD", "FUNCTION");
                            yylval.strVal = strdup(yytext);
                            return FUNCTION;
                        }

"return"                { 
                            print_token(yylineno, ++num_token, yytext, "KEYWORD", "RETURN");
                            yylval.strVal = strdup(yytext); 
                            return RETURN;
                        }

"break"                 { 
                            print_token(yylineno, ++num_token, yytext, "KEYWORD", "BREAK");
                            yylval.strVal = strdup(yytext); 
                            return BREAK;
                        }

"continue"              { 
                            print_token(yylineno, ++num_token, yytext, "KEYWORD", "CONTINUE");
                            yylval.strVal = strdup(yytext); 
                            return CONTINUE;
                        }

"and"                   { 
                            print_token(yylineno, ++num_token, yytext, "KEYWORD", "AND");
                            yylval.strVal = strdup(yytext); 
                            return AND;
                        }

"not"                   { 
                            print_token(yylineno, ++num_token, yytext, "KEYWORD", "NOT");
                            yylval.strVal = strdup(yytext); 
                            return NOT;
                        }

"or"                    { 
                            print_token(yylineno, ++num_token, yytext, "KEYWORD", "OR");
                            yylval.strVal = strdup(yytext); 
                            return OR;
                        }

"local"                 { 
                            print_token(yylineno, ++num_token, yytext, "KEYWORD", "LOCAL");
                            yylval.strVal = strdup(yytext); 
                            return LOCAL;
                        }

"true"                  { 
                            print_token(yylineno, ++num_token, yytext, "KEYWORD", "TRUE");
                            yylval.strVal = strdup(yytext); 
                            return TRUE;
                        }

"false"                 { 
                            print_token(yylineno, ++num_token, yytext, "KEYWORD", "FALSE");
                            yylval.strVal = strdup(yytext); 
                            return FALSE;
                        }

"nil"                   { 
                            print_token(yylineno, ++num_token, yytext, "KEYWORD", "NIL");
                            yylval.strVal = strdup(yytext); 
                            return NIL;
                        }


"=="                    { 
                            print_token(yylineno, ++num_token, yytext, "OPERATOR", "EQUALS");
                            yylval.strVal = strdup(yytext); 
                            return EQ;
                        }

"!="                    { 
                            print_token(yylineno, ++num_token, yytext, "OPERATOR", "NOT_EQUALS");
                            yylval.strVal = strdup(yytext); 
                            return NE;
                        }

"++"                    { 
                            print_token(yylineno, ++num_token, yytext, "OPERATOR", "PLUS_PLUS");
                            yylval.strVal = strdup(yytext); 
                            return PLUS_PLUS;
                        }

"--"                    { 
                            print_token(yylineno, ++num_token, yytext, "OPERATOR", "MINUS_MINUS");
                            yylval.strVal = strdup(yytext); 
                            return MINUS_MINUS;
                        }

">="                    { 
                            print_token(yylineno, ++num_token, yytext, "OPERATOR", "GREATER_EQUAL");
                            yylval.strVal = strdup(yytext); 
                            return GE;
                        }

"<="                    { 
                            print_token(yylineno, ++num_token, yytext, "OPERATOR", "LESS_EQUAL");
                            yylval.strVal = strdup(yytext); 
                            return LE;
                        }

"="                     { 
                            print_token(yylineno, ++num_token, yytext, "OPERATOR", "ASSIGNMENT");
                            yylval.strVal = strdup(yytext); 
                            return ASSIGN;
                        }

"+"                     { 
                            print_token(yylineno, ++num_token, yytext, "OPERATOR", "PLUS");
                            yylval.strVal = strdup(yytext); 
                            return PLUS;
                        }

"-"                     { 
                            print_token(yylineno, ++num_token, yytext, "OPERATOR", "MINUS");
                            yylval.strVal = strdup(yytext); 
                            return MINUS;
                        }

"*"                     { 
                            print_token(yylineno, ++num_token, yytext, "OPERATOR", "MULTIPLICATION");
                            yylval.strVal = strdup(yytext); 
                            return MULT;
                        }

"/"                     { 
                            print_token(yylineno, ++num_token, yytext, "OPERATOR", "DIVISION");
                            yylval.strVal = strdup(yytext); 
                            return DIV;
                        }

"%"                     { 
                            print_token(yylineno, ++num_token, yytext, "OPERATOR", "MODULO");
                            yylval.strVal = strdup(yytext); 
                            return MOD;
                        }

">"                     { 
                            print_token(yylineno, ++num_token, yytext, "OPERATOR", "GREATER_THAN");
                            yylval.strVal = strdup(yytext); 
                            return GT;
                        }

"<"                     { 
                            print_token(yylineno, ++num_token, yytext, "OPERATOR", "LESS_THAN");
                            yylval.strVal = strdup(yytext); 
                            return LT;
                        }

                
"{"                     { 
                            print_token(yylineno, ++num_token, yytext, "PUNCTUATION", "LEFT_BRACE");
                            yylval.strVal = strdup(yytext); 
                            return LEFT_BRACE;
                        }

"}"                     { 
                            print_token(yylineno, ++num_token, yytext, "PUNCTUATION", "RIGHT_BRACE");
                            yylval.strVal = strdup(yytext); 
                            return RIGHT_BRACE;
                        }

"["                     { 
                            print_token(yylineno, ++num_token, yytext, "PUNCTUATION", "LEFT_BRACKET");
                            yylval.strVal = strdup(yytext); 
                            return LEFT_BRACKET;
                        }

"]"                     { 
                            print_token(yylineno, ++num_token, yytext, "PUNCTUATION", "RIGHT_BRACKET");
                            yylval.strVal = strdup(yytext); 
                            return RIGHT_BRACKET;
                        }

"("                     { 
                            print_token(yylineno, ++num_token, yytext, "PUNCTUATION", "LEFT_PARENTHESIS");
                            yylval.strVal = strdup(yytext); 
                            return LEFT_PARENTHESIS;
                        }

")"                     { 
                            print_token(yylineno, ++num_token, yytext, "PUNCTUATION", "RIGHT_PARENTHESIS");
                            yylval.strVal = strdup(yytext); 
                            return RIGHT_PARENTHESIS;
                        }

";"                     { 
                            print_token(yylineno, ++num_token, yytext, "PUNCTUATION", "SEMICOLON");
                            yylval.strVal = strdup(yytext); 
                            return SEMICOLON;
                        }

","                     { 
                            print_token(yylineno, ++num_token, yytext, "PUNCTUATION", "COMMA");
                            yylval.strVal = strdup(yytext); 
                            return COMMA;
                        }

":"                     { 
                            print_token(yylineno, ++num_token, yytext, "PUNCTUATION", "COLON");
                            yylval.strVal = strdup(yytext); 
                            return COLON;
                        }

"::"                    { 
                            print_token(yylineno, ++num_token, yytext, "PUNCTUATION", "DOUBLE_COLON");
                            yylval.strVal = strdup(yytext); 
                            return DOUBLE_COLON;
                        }

"."                     { 
                            print_token(yylineno, ++num_token, yytext, "PUNCTUATION", "STOP");
                            yylval.strVal = strdup(yytext); 
                            return STOP;
                        }

".."                    { 
                            print_token(yylineno, ++num_token, yytext, "PUNCTUATION", "DOUBLE_STOP");
                            yylval.strVal = strdup(yytext); 
                            return DOUBLE_STOP;
                        }


"//"                    {BEGIN(LINE_COMMENT);}

<LINE_COMMENT>.         {}

<LINE_COMMENT>\n        {
                            print_token(yylineno-1, ++num_token, "", "COMMENT", "LINE_COMMENT");
                            BEGIN(INITIAL);
                            //return LINE_COMMENT;
                        }

"/*"                    {
                            BEGIN(BLOCK_COMMENT);
                            start_comments=yylineno;
                        }

<BLOCK_COMMENT>"/*"     {
                            nested_comment_starting_line[nested_comments]=yylineno;
                            if(nested_comments > 1024){ 
                                printf("\033[1;31mERROR\033[0m: exceeded amount of nested comments.\n"); return -1;
                            }	
			                nested_comments++;
                        }

<BLOCK_COMMENT>"*"+"/"  {
                            if(nested_comments==0){
                                char str_final[1024];
                                sprintf(str_final, "%d%s%d",start_comments," - ",yylineno);
                                print_token(start_comments, ++num_token, str_final, "COMMENT", "BLOCK_COMMENT");
                                BEGIN(INITIAL);
                                //return BLOCK_COMMENT;
                            }else{
                                nested_comments--;
                                char str_final[1024];
                                sprintf(str_final, "%d%s%d",nested_comment_starting_line[nested_comments]," - ",yylineno);
                                nested_comment_starting_line[nested_comments] = 0;
                                print_token(yylineno, ++num_token, str_final, "COMMENT", "NESTED_COMMENT");
                                //return NESTED_COMMENT;
                            }
                        }

<BLOCK_COMMENT>"*"+     {}
<BLOCK_COMMENT>[^/*\n]+ {}
<BLOCK_COMMENT>[/]      {}
<BLOCK_COMMENT>\n       {}

<BLOCK_COMMENT><<EOF>>  { 
                            printf("\033[1;31mERROR\033[0m: unclosed comment in line %d\n", start_comments); 
                            return -1;
                        }


{real}                  {  
                            print_token(yylineno, ++num_token, yytext, "CONST_DOUBLE", NULL);
                            yylval.realVal = atof(yytext);
                            return DOUBLE; 
                        }

{integer}               {
                           print_token(yylineno, ++num_token, yytext, "CONST_INT", NULL);
                           yylval.intVal = atoi(yytext); 
                           return INT; 
                        }

{indentifier}           {
                           print_token(yylineno, ++num_token, yytext, "IDENTIFIER", NULL);
                           yylval.strVal = strdup(yytext); 
                           return IDENTIFIER; 
                        }

{string}                {
                            int new_lines = find_new_lines(yytext);
                            backslash(&yytext);
                            remove_quotes(yytext);
                            print_token(yylineno - new_lines, ++num_token, yytext, "STRING", NULL);
                            yylval.strVal = strdup(yytext); 
                            return STRING;
                        }

[\"][^"]*               { 
                            int new_lines = find_new_lines(yytext);
                            printf("\033[1;31m");
                            printf("ERROR:");
                            printf("\033[0m");
                            printf(" unclosed string starting in line %d\n",yylineno - new_lines);
                            return -1;
                        }

([0-9]+)([a-zA-Z_]+)    {
                            printf("\033[1;31mERROR\033[0m: not accepted token -> \033[0;35m \'%s\'\033[0m in line %d\n",yytext,yylineno);
                            return -1;
                        }

<<EOF>>                 {return 0;} //YYEOF

{space}                 {}

<*>.                    {
                            printf("\033[1;31m");
                            printf("ERROR");
                            printf("\033[0m");
                            printf(": not accepted character -> \033[0;35m \'%s\'\033[0m in line %d\n", yytext,yylineno);
                        }

%%


/* Replaces every backshlash we've seen so far in the string 's' with its' true character and returns 
   a new string 'new_s', without the backslash characters.
*/
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


/* Iterates the string 's' and if it finds a backslash, the function replaces it
   with its true value. Throws a warning if it finds a not accepted character.
*/
void backslash(char **s) {
    int bad_string_flag = 0;
    char *iter = *s, *old = *s;
    int first_time = 1, chars = 0, count=0;
    char bad_character[1];

    while(*iter) {
        if(*iter == '\\') {
            if(*(iter+1) == 'n') { // '\n'
                *s = replace_bs_with(*s, chars, '\n', first_time);
                chars--;
                first_time = 0;
            }
            else if(*(iter+1) == 't') { // '\t'
                *s = replace_bs_with(*s, chars, '\t', first_time);
                chars--;
                first_time = 0;
            }
            else if(*(iter+1) == '\\') { // '\\'
                *s = replace_bs_with(*s, chars, '\\', first_time);
                chars--;
                first_time = 0;
            }else if(*(iter+1) == '\"') { // '\"'
                *s = replace_bs_with(*s, chars, '\"', first_time);
                chars--;
                first_time = 0;
            }else{ // backshlash character not accepted
              bad_character[0] = *(iter+1);
              bad_string_flag=1;
            }
            
            if(*iter == '\\') {
                chars++;
                iter++;
            }
        }
        chars++;
        iter++;
    }
    if(bad_string_flag){
      printf("\033[1;35m");
      printf("WARNING");
      printf("\033[0m");
      printf(": not accepted escape character -> \033[0;35m \'\\%c\'\033[0m, in string\033[0;35m %s\033[0m in line %d\n", bad_character[0],old,yylineno);
    }
}


/* Returns the number of new lines '\n' in the string 's'. */
int find_new_lines(char *s){
  char *iter = s;
  int new_lines = 0;

  while(*iter){
    if(*iter == '\n'){
      new_lines++;
    }
    iter++;
  }

  return new_lines;
}

void print_token(int numline, int numToken, char * content, char *type, char * specialty){
    FILE *fp;
    fp = fopen("lex_output.txt", "w+");

    char * category ;

    if((strcmp(type,"STRING") == 0) || (strcmp(type,"IDENTIFIER") == 0)){
        category = strdup("char*");
    }else if(strcmp(type,"CONST_INT") == 0){
        category = strdup("integer");
    }else if(strcmp(type,"CONST_DOUBLE") == 0){
        category = strdup("double");
    }else{
        category = strdup("enumerated");
    }

    if (strcmp(type, "STRING") == 0)
        {
            fprintf(fp,"%u:\t#%u\t\"%s\"\t%s\t\"%s\"\t<--%s\n", numline, numToken, content, type, specialty, category);
        }
        else if (strcmp(type, "COMMENT") == 0)
        {
            fprintf(fp,"%u:\t#%u\t\"%s\"\t%s\t%s\t<--%s\n", numline, numToken, content, type, specialty, category);
        }
        else
        {
            fprintf(fp,"%u:\t#%u\t\"%s\"\t%s\t%s\t<--%s\n", numline, numToken, content, type, specialty, category);
        }
    
    free(category);
    fclose(fp);
}


/* Removes first and last quote from a string */
void remove_quotes(char* s){
    char * tmp = s;

    //find the end and one before it
    while(*(tmp+1)!='\0'){
        tmp++;
    }
    //make the last " in a string \0
    *tmp='\0';

    //reseting the pointer
    tmp = s ;

    //left shift everyting
    while(*tmp!='\0'){
        *tmp = *(tmp+1);
        tmp++;
    }
}
