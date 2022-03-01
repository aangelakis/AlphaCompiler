#define IDENTIFIER "IDENTIFIER"
#define STRING_ "STRING"
#define COMMENT "COMMENT"
#define INTEGER "CONST_INT"
#define OPERATOR "OPERATOR"
#define KEYWORD "KEYWORD"
#define PUNCTUATION "PUNCTUATION"
#define DOUBLE "CONST_DOUBLE"
struct alpha_token_t
{
    unsigned int numline;
    unsigned int numToken;
    char *content;
    char *type;
    struct alpha_token_t *next;
    char *specialty;

};

typedef struct alpha_token_t alpha_token_t;