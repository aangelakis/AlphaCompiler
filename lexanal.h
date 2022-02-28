struct alpha_token_t{
  unsigned int numline;
  unsigned int numToken;
  char *content;
  char *type;
  struct alpha_token_t *alpha_yylex;
};

typedef struct alpha_token_t alpha_token_t;