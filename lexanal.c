#include "scanner.h"
#include "lexanal.h"

int num_lines = 1, num_token = 0;

struct token_list
{
    alpha_token_t *head;
    alpha_token_t *tail;
} tokens;

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

void print_all()
{
    alpha_token_t *iter = tokens.head;
    printf("------------------- Lexical Analysis ----------------------\n");
    printf("line\tnumofToken\tContent\tType\tSpecialty\n");
    while (iter)
    {
        if (strcmp(iter->type, STRING_) == 0)
        {
            printf("%u:\t#%u\t%s\t%s\t%s\n", iter->numline, iter->numToken, iter->content, iter->type, iter->specialty);
        }
        else if (strcmp(iter->type, COMMENT) == 0)
        {

            printf("%u:\t#%u\t\"%s\"\t%s\t%s\n", iter->numline, iter->numToken, iter->content, iter->type, iter->specialty);
        }
        else
        {
            printf("%u:\t#%u\t\"%s\"\t%s\t%s\n", iter->numline, iter->numToken, iter->content, iter->type, iter->specialty);
        }

        iter = iter->next;
    }
}

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

int main(int argc, char **argv)
{
    alpha_token_t *curr = NULL;
    if (argc > 1)
    {
        if (!(yyin = fopen(argv[1], "r")))
        {
            fprintf(stderr, "Cannot read file: %s\n", argv[1]);
            return 1;
        }
    }
    else
    {
        yyin = stdin;
    }

    while (1)
    {
        curr = (alpha_token_t *)malloc(sizeof(alpha_token_t));
        if (alpha_yylex(curr) == -1)
            break;
        else
            insert_token(curr);
    }
    printf("# of lines = %d, # of tokens = %d\n", num_lines, num_token);

    print_all();
    free_all();
    return 0;
}