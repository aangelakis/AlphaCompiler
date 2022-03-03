

// state 9 integer state
// state 10 double state
// state 12 not accepted state (morfi tu stil 10a i 14.5o)

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
        ExtendLexeme(c);
  return STATE(UNKNOWN_TOKEN);
}