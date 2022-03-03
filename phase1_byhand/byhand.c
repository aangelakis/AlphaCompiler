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
#define PLUS            10
#define MINUS           11
#define PLUS_PLUS       12
#define MINUS_MINUS     13
#define MULT            14
#define DIV             15
#define MOD             16
#define INT             17
#define DOUBLE          18


#define MAX_STATE 12
#define TOKEN_SHIFT (MAX_STATE+1)
#define TOKEN(t)    TOKEN_SHIFT+(t)
#define STATE(s)    s
#define istoken(s)  ((s)>MAX_STATE)

int sf0(char c); int sf1(char c); int sf2(char c); int sf3(char c); int sf4(char c); int sf5(char c);
int sf6(char c); int sf7(char c); int sf8(char c); int sf9(char c); int sf10(char c);  int sf11(char c);

int (*stateFuncs[MAX_STATE+1])(char) = { &sf0, &sf1, &sf2, &sf3, &sf4, &sf5, &sf6, &sf7, &sf8, &sf9, &sf10, &sf11};

unsigned gettoken(void);

char names[18][20] = {
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
    "Double"
};

int main(int argc, char *argv[]) {
    if(argc > 1)
        inputFile = fopen(argv[1], "r");

    unsigned return_token;
    while((return_token = gettoken()) != END_OF_FILE) {
        if(return_token == -1)
            printf("UNKNOWN_TOKEN: \'%s\'\n", GetLexeme());
        else
            printf("%s\n", names[return_token-1]);
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
            printf("Found token \'%s\' with type ", GetLexeme());
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
    if(c == '+')    return STATE(7);
    if(c == '-')    return STATE(8);
    if(c == '*'){
        ExtendLexeme(c);
        return TOKEN(MULT);
    }    
    if(c == '/'){
        ExtendLexeme(c);
        return TOKEN(DIV);
    }
    if(c == '%') {
        ExtendLexeme(c);
        return TOKEN(MOD);
    }
    if(isalpha(c))  return STATE(5);
    if(isspace(c))
    { CheckLine(c); return STATE(6); }
    if(isdigit(c))  return STATE(9);
    
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

int sf7(char c) {
    if(c == '+') {
        ExtendLexeme(c);
        return TOKEN(PLUS_PLUS);
    }
    Retract(c);
    return TOKEN(PLUS);
}

int sf8(char c) {
    if(c == '-') {
        ExtendLexeme(c);
        return TOKEN(MINUS_MINUS);
    }
    Retract(c);
    return TOKEN(MINUS);
}

// state 9 integer state
// state 10 double state
// state 11 not accepted state (morfi tu stil 10a i 14.5o)

int sf9(char c) {
    if(isdigit(c))        return STATE(9);
    if(c == '.')          return STATE(10);
    if(isalpha(c))        return STATE(11);
    if(c == '_')          return STATE(11);

    Retract(c);
    return TOKEN(INT);
}

int sf10(char c) {
    if(isdigit(c))        return STATE(10);
    if(isalpha(c))        return STATE(11);
    if(c == '.')          return STATE(11);
    if(c == '_')          return STATE(11);

    Retract(c);
    return TOKEN(DOUBLE);
}

int sf11(char c){
    if(isalpha(c))          return STATE(11);
    if(isdigit(c))          return STATE(11);
    if(c == '.')            return STATE(11);
    if(c == '_')            return STATE(11);
    
    if(!isspace(c))
        Retract(c);
    return STATE(UNKNOWN_TOKEN);
}