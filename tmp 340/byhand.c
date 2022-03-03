#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<ctype.h>

#include"utilities.h"

#define UNKNOWN_TOKEN  -1
#define END_OF_FILE     0
#define LE              1
#define LT              2
#define NE              3
#define NOT             4
#define IDENTIFIER      5
#define GE              6
#define GT              7
#define EQ              8
#define ASSIGN          9


//#define MAX_STATE 6
//#define MAX_STATE 8
#define MAX_STATE 10
#define TOKEN_SHIFT (MAX_STATE+1)
#define TOKEN(t)    TOKEN_SHIFT+(t)
#define STATE(s)    s
#define istoken(s)  ((s)>MAX_STATE)

int sf0(char c); int sf1(char c); int sf2(char c); int sf3(char c); int sf4(char c); int sf5(char c); int sf6(char c);

int (*stateFuncs[MAX_STATE+1])(char) = { &sf0, &sf1, &sf2, &sf3, &sf4, &sf5, &sf6};

unsigned gettoken(void);

char names[9][20] = {
    "LessEqual",
    "LessThan",
    "NotEqual",
    "Not",
    "Identfier",
    "GreaterEqual",
    "GreaterThan",
    "Equal",
    "Assignment"
};

int main(int argc, char *argv[]) {
    if(argc > 1)
        inputFile = fopen(argv[1], "r");

    unsigned return_token;
    while((return_token = gettoken()) != END_OF_FILE) {
        printf("Found token of type %s\n", names[return_token-1]);
    }

    return 0;
}

unsigned gettoken() {
    int state = 0;
    ResetLexeme();
    //if(useLookAhead)
        //printf("Lookahead=%c and curr=%d\n", lookAhead, curr);

    while(1) {
        if(feof(inputFile))
            return END_OF_FILE;

        //if(useLookAhead)
            //puts("USING LOOKAHEAD NOW!");
        char c = GetNextChar();
        //printf("c=%c and curr=%d\n", c, curr);

        state = (*stateFuncs[state])(c);

        if(state == -1)
            return UNKNOWN_TOKEN;
        else if(istoken(state)) {
            printf("Found token \'%s\' with length %lu\n", GetLexeme(), strlen(GetLexeme()));
            //printf("Found token of type %d\n", state-TOKEN_SHIFT);
            return state - TOKEN_SHIFT;
        }
        else if(!isspace(c) && !useLookAhead)
            ExtendLexeme(c);
    }

}

int sf0(char c) {
    if(c == '<')    return STATE(1);
    if(c == '!')    return STATE(2);
    if(c == '=')    return STATE(3);
    if(c == '>')    return STATE(4);
    if(isalpha(c))  return STATE(5);
    if(isspace(c))
        { CheckLine(c); return STATE(6); }
    return STATE(-1);
}

int sf1(char c) {
    if(c == '=') { 
        ExtendLexeme(c);
        return TOKEN(LE);
    }
    Retract(c);
    return TOKEN(LT);
}

int sf2(char c) {
    if(c == '=') { 
        ExtendLexeme(c);
        return TOKEN(NE);
    }
    Retract(c);
    return TOKEN(NOT);
}

int sf3(char c) {
    if(c == '=') { 
        ExtendLexeme(c);
        return TOKEN(EQ);
    }
    Retract(c);
    return TOKEN(ASSIGN);
}

int sf4(char c) {
    if(c == '=') { 
        ExtendLexeme(c);
        return TOKEN(GE);
    }
    Retract(c);
    return TOKEN(GT);
}

int sf5(char c) {
    //printf("c=%c and curr=%d\n", c, curr);
    if(isalpha(c) || isdigit(c))
        return STATE(5);
    Retract(c);
    return TOKEN(IDENTIFIER);
}

int sf6(char c) {
    if(isspace(c)) {
        CheckLine(c);
        return STATE(6);
    }
    //printf("c=%c\n", c);
    Retract(c);
    return STATE(0);
}
