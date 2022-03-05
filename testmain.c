#include<stdio.h>
#include<stdlib.h>

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
    alpha_token_t* new_token = (alpha_token_t*) malloc(sizeof(alpha_token_t));
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
    puts("------------------- Lexical Analysis ----------------------");
    printf("line\tnumofToken\t\tContent\t\tType\n");
    while(iter) {
        printf("%u\t\t%u\t\t%s\t\t%s\n", iter->numline, iter->numToken, iter->content, iter->type);
        iter = iter->next;
    }
}

void free_all() {
    alpha_token_t* iter = tokens.head, *tmp;
    tokens.head = NULL;
    tokens.tail = NULL;

    while(iter) {
        tmp = iter;
        iter = iter -> next;
        free(tmp);
    }
}

int main() {
    insert_token(1, 1, "if", "KEYWORD_IF");
    insert_token(2, 2, "else", "KEYWORD_IF");
    insert_token(3, 3, "true", "KEYWORD_TRUE");
    insert_token(4, 4, "false", "KEYWORD_FALSE");
    insert_token(5, 5, "while", "KEYWORD_WHILE");

    print_all();
    return 0;
}
