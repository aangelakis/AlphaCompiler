struct alpha_token_t{
  unsigned int numline;
  unsigned int numToken;
  char *content;
  char *type;
  struct alpha_token_t *next;
};

typedef struct alpha_token_t alpha_token_t;

struct token_list {
    alpha_token_t* head;
    alpha_token_t* tail;
} tokens;

void insert_token(int numline, int numToken, char *content, char* type) {
    new_token = (alpha_token_t*) malloc(sizeof(alpha_token_t));
    new_token->numline = numline;
    new_token->numToken = numToken;
    new_token->content = content;
    new_token->type = type;
    new_token->next = NULL;

    if(tokens.head == NULL)
        tokens.head = new_token;
    else if(tokens.tail == NULL) {
        tokens.tail = new_token;
        tokens.head->next = new_token;
    }
    else {
        tokens.tail->next = new_token;
        tokens.tail = new_token;
    }
}

void print_all() {
    alpha_token_t* iter = tokens.head;
    printf("------------------- Lexical Analysis ----------------------");
    printf("line\tnumofToken\tContent\tType\n");
    while(iter) {
        printf("%u/t%u/t%s/t%s", iter->numline, iter->numToken, iter->content, iter->type);
        iter = iter->next
    }
}
