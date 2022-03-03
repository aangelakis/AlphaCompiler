

//state 13 anoikse quote



int sf15(char c) {
  // kapws na briskume end of file oso sto state tu string
    if(c == '\\')
      return STATE(16);
    if(c == '\"')
      return TOKEN(STRING);
    return STATE(15);
}

int sf16(char c) {
    return STATE(15);
}