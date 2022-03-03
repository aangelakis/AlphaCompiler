#define IF              19
#define ELSE            20
#define WHILE           21
#define FOR             22
#define FUNCTION        23
#define RETURN          24
#define BREAK           25
#define CONTINUE        26
#define AND             27
#define NOT             28
#define OR              29
#define LOCAL           30
#define TRUE            31
#define FALSE           32
#define NIL             33

#include <string.h>

char keyword_names[15][20] = {
  "IF",
  "ELSE",
  "WHILE",
  "FOR",
  "FUNCTION",
  "RETURN",
  "BREAK",
  "CONTINUE",
  "AND",
  "NOT",
  "OR",
  "LOCAL",
  "TRUE",
  "FALSE",
  "NIL"
};

int iskeyword(char *s){
    if(strcmp(s, "if") == 0){
        return TOKEN(IF);
    }
    if(strcmp(s, "else") == 0){
        return TOKEN(ELSE);
    }
    if(strcmp(s, "while") == 0){
        return TOKEN(WHILE);
    }
    if(strcmp(s, "for") == 0){
        return TOKEN(FOR);
    }
    if(strcmp(s, "function") == 0){
        return TOKEN(FUNCTION);
    }
    if(strcmp(s, "return") == 0){
        return TOKEN(RETURN);
    }
    if(strcmp(s, "break") == 0){
        return TOKEN(BREAK);
    }
    if(strcmp(s, "continue") == 0){
        return TOKEN(CONTINUE);
    }
    if(strcmp(s, "and") == 0){
        return TOKEN(AND);
    }
    if(strcmp(s, "not") == 0){
        return TOKEN(NOT);
    }
    if(strcmp(s, "or") == 0){
        return TOKEN(OR);
    }
    if(strcmp(s, "local") == 0){
        return TOKEN(LOCAL);
    }
    if(strcmp(s, "true") == 0){
        return TOKEN(TRUE);
    }
    if(strcmp(s, "false") == 0){
        return TOKEN(FALSE);
    }
    if(strcmp(s, "nil") == 0){
        return TOKEN(NIL);
    }

    return -24;
}