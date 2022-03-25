/* Definition Section */
%{
#include"lexanal.h"

#define YY_DECL int alpha_yylex(void* yylval)

alpha_token_t *tail = NULL;

extern int num_token;
int start_comments = 0;
int nested_comments = 0;
int string_flag = 0;
int nested_comment_starting_line[1024];

char* replace_bs_with(char*, int, char, int);
void backslash(char **);
int find_new_lines(char *);
void remove_quotes(char* s);
void insert_data(int numline, int numToken, char *content, char *type, alpha_token_t* yylval, char* specialty);
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
                            insert_data(yylineno, ++num_token, yytext, KEYWORD, yylval,"IF"); 
                            return 1;
                        }

"else"                  { 
                            insert_data(yylineno, ++num_token, yytext, KEYWORD, yylval,"ELSE"); 
                            return 1;
                        }

"while"                 {
                            insert_data(yylineno, ++num_token, yytext, KEYWORD, yylval,"WHILE"); 
                            return 1;
                        }

"for"                   { 
                            insert_data(yylineno, ++num_token, yytext, KEYWORD, yylval,"FOR"); 
                            return 1;
                        }

"function"              { 
                            insert_data(yylineno, ++num_token, yytext, KEYWORD, yylval,"FUNCTION"); 
                            return 1;
                        }

"return"                { 
                            insert_data(yylineno, ++num_token, yytext, KEYWORD, yylval,"RETURN"); 
                            return 1;
                        }

"break"                 { 
                            insert_data(yylineno, ++num_token, yytext, KEYWORD, yylval,"BREAK"); 
                            return 1;
                        }

"continue"              { 
                            insert_data(yylineno, ++num_token, yytext, KEYWORD, yylval,"CONTINUE"); 
                            return 1;
                        }

"and"                   { 
                            insert_data(yylineno, ++num_token, yytext, KEYWORD, yylval,"AND"); 
                            return 1;
                        }

"not"                   { 
                            insert_data(yylineno, ++num_token, yytext, KEYWORD, yylval,"NOT"); 
                            return 1;
                        }

"or"                    { 
                            insert_data(yylineno, ++num_token, yytext, KEYWORD, yylval,"OR"); 
                            return 1;
                        }

"local"                 { 
                            insert_data(yylineno, ++num_token, yytext, KEYWORD, yylval,"LOCAL"); 
                            return 1;
                        }

"true"                  { 
                            insert_data(yylineno, ++num_token, yytext, KEYWORD, yylval,"TRUE"); 
                            return 1;
                        }

"false"                 { 
                            insert_data(yylineno, ++num_token, yytext, KEYWORD, yylval,"FALSE"); 
                            return 1;
                        }

"nil"                   { 
                            insert_data(yylineno, ++num_token, yytext, KEYWORD, yylval,"NIL"); 
                            return 1;
                        }


"=="                    { 
                            insert_data(yylineno, ++num_token, yytext, OPERATOR, yylval,"EQUALS"); 
                            return 1;
                        }

"!="                    { 
                            insert_data(yylineno, ++num_token, yytext, OPERATOR, yylval,"NOT_EQUALS"); 
                            return 1;
                        }

"++"                    { 
                            insert_data(yylineno, ++num_token, yytext, OPERATOR, yylval,"PLUS_PLUS"); 
                            return 1;
                        }

"--"                    { 
                            insert_data(yylineno, ++num_token, yytext, OPERATOR, yylval,"MINUS_MINUS"); 
                            return 1;
                        }

">="                    { 
                            insert_data(yylineno, ++num_token, yytext, OPERATOR, yylval,"GREATER_EQUAL"); 
                            return 1;
                        }

"<="                    { 
                            insert_data(yylineno, ++num_token, yytext, OPERATOR, yylval,"LESS_EQUAL"); 
                            return 1;
                        }

"="                     { 
                            insert_data(yylineno, ++num_token, yytext, OPERATOR, yylval,"ASSIGNMENT"); 
                            return 1;
                        }

"+"                     { 
                            insert_data(yylineno, ++num_token, yytext, OPERATOR, yylval,"PLUS"); 
                            return 1;
                        }

"-"                     { 
                            insert_data(yylineno, ++num_token, yytext, OPERATOR, yylval,"MINUS"); 
                            return 1;
                        }

"*"                     { 
                            insert_data(yylineno, ++num_token, yytext, OPERATOR, yylval,"MULTIPLICATION"); 
                            return 1;
                        }

"/"                     { 
                            insert_data(yylineno, ++num_token, yytext, OPERATOR, yylval,"DIVISION"); 
                            return 1;
                        }

"%"                     { 
                            insert_data(yylineno, ++num_token, yytext, OPERATOR, yylval,"MODULO"); 
                            return 1;
                        }

">"                     { 
                            insert_data(yylineno, ++num_token, yytext, OPERATOR, yylval,"GREATER_THAN"); 
                            return 1;
                        }

"<"                     { 
                            insert_data(yylineno, ++num_token, yytext, OPERATOR, yylval,"LESS_THAN"); 
                            return 1;
                        }

                
"{"                     { 
                            insert_data(yylineno, ++num_token, yytext, PUNCTUATION, yylval,"LEFT_BRACE"); 
                            return 1;
                        }

"}"                     { 
                            insert_data(yylineno, ++num_token, yytext, PUNCTUATION, yylval,"RIGHT_BRACE"); 
                            return 1;
                        }

"["                     { 
                            insert_data(yylineno, ++num_token, yytext, PUNCTUATION, yylval,"LEFT_BRACKET"); 
                            return 1;
                        }

"]"                     { 
                            insert_data(yylineno, ++num_token, yytext, PUNCTUATION, yylval,"RIGHT_BRACKET"); 
                            return 1;
                        }

"("                     { 
                            insert_data(yylineno, ++num_token, yytext, PUNCTUATION, yylval,"LEFT_PARENTHESIS"); 
                            return 1;
                        }

")"                     { 
                            insert_data(yylineno, ++num_token, yytext, PUNCTUATION, yylval,"RIGHT_PARENTHESIS"); 
                            return 1;
                        }

";"                     { 
                            insert_data(yylineno, ++num_token, yytext, PUNCTUATION, yylval,"SEMICOLON"); 
                            return 1;
                        }

","                     { 
                            insert_data(yylineno, ++num_token, yytext, PUNCTUATION, yylval,"COMMA"); 
                            return 1;
                        }

":"                     { 
                            insert_data(yylineno, ++num_token, yytext, PUNCTUATION, yylval,"COLON"); 
                            return 1;
                        }

"::"                    { 
                            insert_data(yylineno, ++num_token, yytext, PUNCTUATION, yylval,"DOUBLE_COLON"); 
                            return 1;
                        }

"."                     { 
                            insert_data(yylineno, ++num_token, yytext, PUNCTUATION, yylval,"STOP"); 
                            return 1;
                        }

".."                    { 
                            insert_data(yylineno, ++num_token, yytext, PUNCTUATION, yylval,"DOUBLE_STOP"); 
                            return 1;
                        }


"//"                    {BEGIN(LINE_COMMENT);}

<LINE_COMMENT>.         {}

<LINE_COMMENT>\n        {
                            insert_data(yylineno-1, ++num_token, "", COMMENT, yylval,"LINE_COMMENT");
                            BEGIN(INITIAL);
                            return 1;
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
                                insert_data(start_comments, ++num_token, str_final, COMMENT, yylval,"BLOCK_COMMENT");
                                BEGIN(INITIAL);
                            }else{
                                nested_comments--;
                                char str_final[1024];
                                sprintf(str_final, "%d%s%d",nested_comment_starting_line[nested_comments]," - ",yylineno);
                                nested_comment_starting_line[nested_comments] = 0;
                                insert_data(yylineno, ++num_token, str_final, COMMENT, yylval,"NESTED_COMMENT");
                            }
                            return 1;
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
                            insert_data(yylineno, ++num_token, yytext, DOUBLE, yylval,NULL); 
                            return 1; 
                        }

{integer}               {
                           insert_data(yylineno, ++num_token, yytext, INTEGER, yylval,NULL); 
                           return 1; 
                        }

{indentifier}           {
                           insert_data(yylineno, ++num_token, yytext, IDENTIFIER, yylval,NULL); 
                           return 1; 
                        }

{string}                {
                            int new_lines = find_new_lines(yytext);
                            backslash(&yytext);
                            remove_quotes(yytext);
                            insert_data(yylineno - new_lines, ++num_token, yytext, STRING_, yylval,NULL); return 1;
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
                        }

<<EOF>>                 {return -1;}

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


/* Inserts the data of a token in its struct node alpha_token_t. */
void insert_data(int numline, int numToken, char *content, char *type, alpha_token_t* yylval, char* specialty)
{
    yylval->numline = numline;
    yylval->numToken = numToken;
    yylval->content = (char *) malloc((strlen(content) + 1) * sizeof(char));
    strcpy(yylval->content, content);
    yylval->content[strlen(content)] = '\0'; // just to be sure.
   // yylval->content = (char *) malloc(strlen(content) * sizeof(char));
    //strcpy(yylval->content, content);
    yylval->type = type;
    yylval->next = NULL;

    //if specialty is null it means copy the content to the specialty else assign the new one
    if(specialty==NULL){
      yylval->specialty = yylval->content;
    }else{
      yylval->specialty = specialty;
    }    
    if((strcmp(type,STRING_) == 0) || (strcmp(type,IDENTIFIER) == 0)){
      yylval->category = "char*";
    }else if(strcmp(type,INTEGER) == 0){
      yylval->category = "integer";
    }else if(strcmp(type,DOUBLE) == 0){
      yylval->category = "double";
    }else{
      yylval->category = "enumerated";
    }  
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
