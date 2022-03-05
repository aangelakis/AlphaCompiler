#include"byhand.h"

struct alpha_token_t
{
    unsigned int numline;
    unsigned int numToken;
    char *content;
    char *type;
    struct alpha_token_t *next;
    char *specialty;
    char *category;
};

typedef struct alpha_token_t alpha_token_t;

struct token_list
{
    alpha_token_t *head;
    alpha_token_t *tail;
} tokens;

/* Inserts a token in the struct token list. */
void insert_token(alpha_token_t *new_token)
{
    if (tokens.head == NULL)
        tokens.head = new_token;
    else if (tokens.tail == NULL)
    {
        tokens.tail = new_token;
        tokens.head->next = new_token;
    }
    else
    {
        tokens.tail->next = new_token;
        tokens.tail = new_token;
    }
}

/* Prints the struct token list. */
void print_all()
{
    alpha_token_t *iter = tokens.head;
    printf("------------------- Lexical Analysis ----------------------\n");
    //printf("line\tnumofToken\tContent\tType\tSpecialty\tCategory\n");
    while (iter)
    {
        if (strcmp(iter->type, "STRING") == 0)
        {
            printf("%u:\t#%u\t\"%s\"\t%s\t\"%s\"\t<--%s\n", iter->numline, iter->numToken, iter->content, iter->type, iter->specialty, iter->category);
        }
        else if (strcmp(iter->type, "COMMENT") == 0)
        {

            printf("%u:\t#%u\t\"%s\"\t%s\t%s\t<--%s\n", iter->numline, iter->numToken, iter->content, iter->type, iter->specialty, iter->category);
        }
        else
        {
            printf("%u:\t#%u\t\"%s\"\t%s\t%s\t<--%s\n", iter->numline, iter->numToken, iter->content, iter->type, iter->specialty, iter->category);
        }

        iter = iter->next;
    }
}

/* Frees the struct token list. */
void free_all()
{
    alpha_token_t *iter = tokens.head, *tmp;
    while (iter)
    {
        tmp = iter;
        iter = iter->next;
        free(tmp->content);
        free(tmp);
    }
}

/* Inserts the data of a token in its struct node alpha_token_t. */
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
    if((strcmp(type,"STRING") == 0) || (strcmp(type,"IDENTIFIER") == 0)){
      yylval->category = "char*";
    }else if(strcmp(type,"CONST_INT") == 0){
      yylval->category = "integer";
    }else if(strcmp(type,"CONST_DOUBLE") == 0){
      yylval->category = "double";
    }else{
      yylval->category = "enumerated";
    }  
}

int inside_block=0;
int nested_comments = 0;
int nested_comment_starting_line[1024];
int num_tokens=0;

int main(int argc, char *argv[]) {
    if(argc > 1)
        inputFile = fopen(argv[1], "r");

    int isk;
    unsigned return_token;
    while((return_token = gettoken()) != END_OF_FILE) {
        if(return_token == UNKNOWN_TOKEN){
            printf("ERROR: UNKNOWN_TOKEN: \'%s\' in line %d\n", GetLexeme(), lineNo);
        }
        else if(return_token == 50)
            printf("ERROR: UNCLOSED_STRING in line %d\n", lineNo);  
        else {
            alpha_token_t* curr = malloc(sizeof(alpha_token_t));
            
            if(return_token == IDENTIFIER){
                if((isk = iskeyword(GetLexeme())) > 0)
                    insert_data(lineNo, ++num_tokens, lexeme, "KEYWORD", curr, names[isk-TOKEN_SHIFT-1]);
                else
                insert_data(lineNo, ++num_tokens, lexeme, "IDENTIFIER", curr, NULL);
                //printf("%s in line %d\n", names[return_token-1], lineNo);
            }
            else if(return_token == INT)
                insert_data(lineNo, ++num_tokens, GetLexeme(), "CONST_INT", curr, NULL);
            else if(return_token == DOUBLE)
                insert_data(lineNo, ++num_tokens, GetLexeme(), "CONST_DOUBLE", curr, NULL);
            else if(return_token == STRING)
                insert_data(lineNo, ++num_tokens, GetLexeme(), "STRING", curr, NULL);
            else if(return_token > 0 && return_token < 17)
                insert_data(lineNo, ++num_tokens, GetLexeme(), "OPERATOR", curr, names[return_token-1]);
            else if(return_token > 33 && return_token < 46)
                insert_data(lineNo, ++num_tokens, GetLexeme(), "PUNCTUATION", curr, names[return_token-1]);
            else if(return_token > 46 && return_token < 50){
                char str_final[1024]="";
                if(return_token != 47){
                    sprintf(str_final, "%d%s%d",nested_comment_starting_line[0]," - ",lineNo);
                }
                
                insert_data(lineNo, ++num_tokens, str_final, "COMMENT", curr, names[return_token-1]);
            }  
            
            insert_token(curr);
        }
    }

    print_all();
    free_all();
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
            //printf("Found token \'%s\' with type ", GetLexeme());
            return state - TOKEN_SHIFT;
        }
        else if(!isspace(c) && !useLookAhead && c != '\"')
            ExtendLexeme(c);
    }
}

/* start state */
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

/* '>' state */
int sf1(char c) {
    if(c == '=') { 
        ExtendLexeme(c);
        return TOKEN(LE);
    }
    Retract(c);
    return TOKEN(LT);
}

/* '!' state */
int sf2(char c) {
    if(c == '=') { 
        ExtendLexeme(c);
        return TOKEN(NE);
    }
    Retract(c);
    return UNKNOWN_TOKEN;
}

/* '=' state */
int sf3(char c) {
    if(c == '=') { 
        ExtendLexeme(c);
        return TOKEN(EQ);
    }
    Retract(c);
    return TOKEN(ASSIGN);
}

/* '<' state */
int sf4(char c) {
    if(c == '=') { 
        ExtendLexeme(c);
        return TOKEN(GE);
    }
    Retract(c);
    return TOKEN(GT);
}

/* IDENTIFIER state */
int sf5(char c) {
    //printf("c=%c and curr=%d\n", c, curr);
    if(isalpha(c) || isdigit(c) || c == '_')
        return STATE(5);
    Retract(c);

    return TOKEN(IDENTIFIER);
}

/* whitespace state */
int sf6(char c) {
    if(isspace(c)) {
        CheckLine(c);
        return STATE(6);
    }
    //printf("c=%c\n", c);
    Retract(c);
    return STATE(0);
}

/* '+' state */
int sf7(char c) {
    if(c == '+') {
        ExtendLexeme(c);
        return TOKEN(PLUS_PLUS);
    }
    Retract(c);
    return TOKEN(PLUS);
}

/* '-' state */
int sf8(char c) {
    if(c == '-') {
        ExtendLexeme(c);
        return TOKEN(MINUS_MINUS);
    }
    Retract(c);
    return TOKEN(MINUS);
}

/* CONST_INT state */
int sf9(char c) {
    if(isdigit(c))        return STATE(9);
    if(c == '.')          return STATE(10);
    if(isalpha(c))        return STATE(11);
    if(c == '_')          return STATE(11);

    Retract(c);
    return TOKEN(INT);
}

/* CONST_DOUBLE state */
int sf10(char c) {
    if(isdigit(c))        return STATE(10);
    if(isalpha(c))        return STATE(11);
    if(c == '.')          return STATE(11);
    if(c == '_')          return STATE(11);

    Retract(c);
    return TOKEN(DOUBLE);
}

/* wrong_identifier state (morfi tu stil 10a i 14.5o) */
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

/* ":" state */
int sf13(char c){
    if(c==':'){ 
        ExtendLexeme(c);
        return TOKEN(DOUBLE_COLON);
    }
    Retract(c);
    return TOKEN(COLON);
}

/* "." state */
int sf14(char c){
    if(c=='.'){ 
        ExtendLexeme(c);
        return TOKEN(DOUBLE_STOP);
    }
    Retract(c);
    return TOKEN(STOP);
}

/* STRING state */
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

    if(c == EOF){
        return TOKEN(UNCLOSED_STRING);
    }
    return STATE(15);
}

/* '\' in STRING state */
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

    Retract(c2);
    return STATE(15);
}

/* "/" state */
int sf17(char c){
  if(c=='/')                        return STATE(18);   //arxise line comment
  if(c=='*'){ nested_comments=0; nested_comment_starting_line[0]=lineNo;    return STATE(19);}  //arxise block comment

  //ExtendLexeme(c);

  //edw mporei na einai kai to operand slash
  return TOKEN(DIV);
}

/* "LINE_COMMENT" state */
int sf18(char c){
    while(c != '\n')
      c = GetNextChar();
    //CheckLine(c);
    //if(c!='\n') return STATE(21);

    Retract(c);
    //ExtendLexeme(c);
    return TOKEN(LINE_COMMENT);
}

/* "BLOCK_COMMENT" state */
int sf19(char c){
    int total_comments = 1;
    CheckLine(c);

    while(total_comments != 0){
        
        if(c == '/'){
            c = GetNextChar();
            CheckLine(c);
            if(c == '*'){
                if(total_comments>1023){
                    printf("ERROR : too many nested comments too handle \n");
                    exit(0);
                }
                nested_comment_starting_line[total_comments] = lineNo ;
                total_comments++;
            }
        }
        if(c == '*'){
            c = GetNextChar();
            CheckLine(c);
            if(c == '/'){
                printf("%d <---\n",total_comments);
                total_comments--;
                int tmp = nested_comment_starting_line[total_comments];

                char str_final[1024];
                sprintf(str_final, "%d%s%d",tmp," - ",lineNo);

                if(total_comments != 0){
                    //printf("Found token of type NESTED_COMMENT from line %d till line %d\n",tmp, lineNo);
                    alpha_token_t* curr = malloc(sizeof(alpha_token_t));
                    insert_data(lineNo, ++num_tokens, str_final, "COMMENT", curr, "NESTED_COMMENT");
                    insert_token(curr);
                }else{
                    
    if(c == '\n')
        lineNo--;

    return TOKEN(BLOCK_COMMENT);
                }
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
