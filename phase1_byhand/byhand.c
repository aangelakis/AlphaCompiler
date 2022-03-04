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

/* SHMEIA STIKSIS */
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

#define STRING              46

#define LINE_COMMENT        47
#define BLOCK_COMMENT       48
#define UNCLOSED_COMMENT    49

#define MAX_STATE 19
#define TOKEN_SHIFT (MAX_STATE+1)
#define TOKEN(t)    TOKEN_SHIFT+(t)
#define STATE(s)    s
#define istoken(s)  ((s)>MAX_STATE)

int sf0(char c);   int sf1(char c);   int sf2(char c); int sf3(char c);   int sf4(char c);   int sf5(char c);
int sf6(char c);   int sf7(char c);   int sf8(char c); int sf9(char c);   int sf10(char c);  int sf11(char c);
int sf12(char c);  int sf13(char c);  int sf14(char c); int sf15(char c); int sf16(char c);  int sf17(char c);
int sf18(char c);  int sf19(char c);

int (*stateFuncs[MAX_STATE+1])(char) = { &sf0, &sf1, &sf2, &sf3, &sf4, &sf5, &sf6, &sf7, &sf8, &sf9, &sf10, &sf11, &sf12, &sf13, &sf14, &sf15, &sf16, &sf17, &sf18, &sf19};

unsigned gettoken(void);

char names[49][20] = {
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
    "BLOCk_COMMENT",
    "UNCLOSED_COMMENT"
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

int main(int argc, char *argv[]) {
    if(argc > 1)
        inputFile = fopen(argv[1], "r");

    int isk;
    unsigned return_token;
    while((return_token = gettoken()) != END_OF_FILE) {
        if(return_token == UNKNOWN_TOKEN){
            printf("UNKNOWN_TOKEN: \'%s\'\n", GetLexeme());
        }
        else if((isk = iskeyword(lexeme)) > 0)
            printf("%s which is a KEYWORD in line %d\n", names[isk-TOKEN_SHIFT-1], lineNo);
        else
            printf("%s in line %d\n", names[return_token-1], lineNo);
    }

    return 0;
}

unsigned gettoken() {
    int state = 0;
    ResetLexeme();

    while(1) {
        if(feof(inputFile)){
            return END_OF_FILE;
        }

        char c = GetNextChar();

        state = (*stateFuncs[state])(c);

        if(state == -1) {
            if(curr == 0)
                ExtendLexeme(c);
            return UNKNOWN_TOKEN;
        }
        else if(istoken(state)) {
            printf("Found token \'%s\' with type ", GetLexeme());
            return state - TOKEN_SHIFT;
        }
        else if(!isspace(c) && !useLookAhead && c != '\"')
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
    // Could be either DIV or COMMENT, will see in state17
    if(c == '/')    return STATE(17);
    if(c == '*'){
        ExtendLexeme(c);
        return TOKEN(MULT);
    }    
    if(c == '%') {
        ExtendLexeme(c);
        return TOKEN(MOD);
    }
    if(isPunctuation(c)) {
        Retract(c);
        return STATE(12);
    }
    if(c == '\"')
        return STATE(15);
    if(isalpha(c))
        return STATE(5);
    if(isspace(c)) { 
        CheckLine(c);
        return STATE(6);
    }
    if(isdigit(c))
        return STATE(9);
    
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
    if(isalpha(c) || isdigit(c) || c == '_')
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

/*  
state 9 integer state
state 10 double state
state 11 not accepted state (morfi tu stil 10a i 14.5o)
*/
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

int sf12(char c){
    if(c=='{'){
        ExtendLexeme(c);
        return TOKEN(LEFT_BRACE);
    }
    if(c=='}'){
        ExtendLexeme(c);
        return TOKEN(RIGHT_BRACE);
    }
    if(c=='['){ 
        ExtendLexeme(c);
        return TOKEN(LEFT_BRACKET);
    }
    if(c==']'){
        ExtendLexeme(c);
        return TOKEN(RIGHT_BRACKET);
    }
    if(c=='('){
        ExtendLexeme(c);
        return TOKEN(LEFT_PARENTHESIS);
    }
    if(c==')'){
        ExtendLexeme(c);
        return TOKEN(RIGHT_PARENTHESIS);
    }
    if(c==';'){
        ExtendLexeme(c);
        return TOKEN(SEMICOLON);
    }
    if(c==','){ 
        ExtendLexeme(c);
        return TOKEN(COMMA);
    }
    if(c==':')  return STATE(13);
    if(c=='.')  return STATE(14);

    return STATE(UNKNOWN_TOKEN);
}

//inside colon state
int sf13(char c){
    if(c==':'){ 
        ExtendLexeme(c);
        return TOKEN(DOUBLE_COLON);
    }
    Retract(c);
    return TOKEN(COLON);
}

//inside stop state
int sf14(char c){
    if(c=='.'){ 
        ExtendLexeme(c);
        return TOKEN(DOUBLE_STOP);
    }
    Retract(c);
    return TOKEN(STOP);
}

int sf15(char c) {
    if(c == '\\'){
        Retract(c);
        return STATE(16);
    }
    if(c == '\"') {
        return TOKEN(STRING);
    }

    if(isspace(c)) {
        CheckLine(c);
        ExtendLexeme(c);
    }

    return STATE(15);
}

int sf16(char c) {
    int c2 = GetNextChar();
    //printf("c=%c and c2=%c\n",c, c2);
    assert(c == '\\');
    if(c2 == 'n')
        ExtendLexeme('\n');
    else if(c2 == 't')
        ExtendLexeme('\t');
    else if(c2 == '\\')
        ExtendLexeme('\\');
    else if(c2 == '\"')
        ExtendLexeme('\"');
    else {
        ExtendLexeme(c);
        puts("WARNING: unrecognized escape character");
    }

    Retract(GetNextChar());
    return STATE(15);
}

int inside_block=0;
int nested_comments = 0;

// prwto / brethike
int sf17(char c){
  if(c=='/')                        return STATE(18);   //arxise line comment
  if(c=='*'){ nested_comments=0;    return STATE(19);}  //arxise block comment

  //ExtendLexeme(c);

  //edw mporei na einai kai to operand slash
  return TOKEN(DIV);
  
}

//mesa se line comment
int sf18(char c){
    while(c != '\n')
      c = GetNextChar();
    //CheckLine(c);
    //if(c!='\n') return STATE(21);

    Retract(c);
    //ExtendLexeme(c);
    return TOKEN(LINE_COMMENT);
}

// sigoura mesa se block comment
int sf19(char c){
    int total_comments = 1;
    CheckLine(c);

    while(total_comments != 0){
        if(c == '/'){
            c = GetNextChar();
            CheckLine(c);
            if(c == '*'){
                total_comments++;
            }
        }
        if(c == '*'){
            c = GetNextChar();
            CheckLine(c);
            if(c == '/'){
                total_comments--;
                if(total_comments != 0)
                    printf("Found token of type NESTED_COMMENT in line %d\n", lineNo);
            }
        }
        c = GetNextChar();
        if(c == EOF)
            return TOKEN(UNCLOSED_COMMENT);
        CheckLine(c);
    }

    Retract(c);
    if(c == '\n')
        lineNo--;

    return TOKEN(BLOCK_COMMENT);
}
