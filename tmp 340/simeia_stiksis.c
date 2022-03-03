
// { } [ ] ( ) ; , : :: . ..

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

char punctuation_names[12][20] = {
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
  "DOUBLE_STOP"
};



int isPunctuation(char c){
  if(c=='{'||c=='}'||c=='['||c==']'||c=='('||c==')'||c==';'||c==','||c==':'||c=='.'){
    return 1;
  }
  return 0;
}


int sf30(char c){
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
  if(c==':')  return STATE(31);
  if(c=='.')  return STATE(32);
}

//inside colon state
int sf31(char c){
  if(c==':'){ 
    ExtendLexeme(c);
    return TOKEN(DOUBLE_COLON);
  }
  Retract(c);
  return TOKEN(COLON);
}

//inside stop state
int sf32(char c){
  if(c=='.'){ 
    ExtendLexeme(c);
    return TOKEN(DOUBLE_STOP);
  }
  Retract(c);
  return TOKEN(STOP);
}
