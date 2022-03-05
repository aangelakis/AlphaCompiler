#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<ctype.h>

#include"utilities.h"

#define UNKNOWN_TOKEN  -1
#define END_OF_FILE     0
/* OPERATORS */
#define LE              1
#define LT              2
#define NE              3
#define NOT             4
#define IDENTIFIER      5
#define GE              6
#define GT              7
#define EQ              8
#define ASSIGN          9
#define PLUS            10
#define MINUS           11
#define PLUS_PLUS       12
#define MINUS_MINUS     13
#define MULT            14
#define DIV             15
#define MOD             16
/* INTEGER */
#define INT             17
/* DOUBLE*/
#define DOUBLE          18

/* KEYWORDS */
#define IF              19
#define ELSE            20
#define WHILE           21
#define FOR             22
#define FUNCTION        23
#define RETURN          24
#define BREAK           25
#define CONTINUE        26
#define AND             27
#define NOTT            28
#define OR              29
#define LOCAL           30
#define TRUE            31
#define FALSE           32
#define NIL             33

/* PUNCTUATION */
#define LEFT_BRACE          34
#define RIGHT_BRACE         35
#define LEFT_BRACKET        36
#define RIGHT_BRACKET       37
#define LEFT_PARENTHESIS    38
#define RIGHT_PARENTHESIS   39
#define SEMICOLON           40
#define COMMA               41
#define COLON               42
#define DOUBLE_COLON        43
#define STOP                44
#define DOUBLE_STOP         45

/* STRING */
#define STRING              46

/* COMMENT */
#define LINE_COMMENT        47
#define BLOCK_COMMENT       48

/* UNCLOSED */
#define UNCLOSED_COMMENT    49
#define UNCLOSED_STRING     50

#define MAX_STATE 19
#define TOKEN_SHIFT (MAX_STATE+1)
#define TOKEN(t)    TOKEN_SHIFT+(t)
#define STATE(s)    s
#define istoken(s)  ((s)>MAX_STATE)

int sf0(char c);   int sf1(char c);   int sf2(char c); 
int sf3(char c);   int sf4(char c);   int sf5(char c);
int sf6(char c);   int sf7(char c);   int sf8(char c); 
int sf9(char c);   int sf10(char c);  int sf11(char c);
int sf12(char c);  int sf13(char c);  int sf14(char c);
int sf15(char c); int sf16(char c);  int sf17(char c);
int sf18(char c);  int sf19(char c);

int (*stateFuncs[MAX_STATE+1])(char) = { &sf0, &sf1, &sf2, &sf3, &sf4, &sf5, &sf6, &sf7, &sf8, &sf9, &sf10, &sf11, &sf12, &sf13, &sf14, &sf15, &sf16, &sf17, &sf18, &sf19};

unsigned gettoken(void);

char names[50][20] = {
    "LessEqual",
    "LessThan",
    "NotEqual",
    "Not",
    "Identfier",
    "GreaterEqual",
    "GreaterThan",
    "Equal",
    "Assignment",
    "Plus",
    "Minus",
    "Plus_Plus",
    "Minus_minus",
    "Mult",
    "Div",
    "Mod",
    "Int",
    "Double",
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
    "NIL",
    "LEFT_BRACE",
    "RIGHT_BRACE",
    "LEFT_BRACKET",
    "RIGHT_BRACKET",
    "LEFT_PARENTHESIS",
    "RIGHT_PARENTHESIS",
    "SEMICOLON",
    "COMMA",
    "COLON",
    "DOUBLE_COLON",
    "STOP",
    "DOUBLE_STOP",
    "STRING",
    "LINE_COMMENT",
    "BLOCK_COMMENT",
    "UNCLOSED_COMMENT",
    "UNCLOSED_STRING"
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
        return TOKEN(NOTT);
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

int isPunctuation(char c){
    if(c=='{'||c=='}'||c=='['||c==']'||c=='('||c==')'||c==';'||c==','||c==':'||c=='.') {
        //printf("c=%c", c);
        return 1;
    }

    return 0;
}
