#include"scanner.h"
#include"lexanal.h"

int num_lines = 1, num_chars = 0, num_token = 0;

int main(int argc, char** argv)
{
    if(argc > 1){
        if(!(yyin = fopen(argv[1], "r"))){
            fprintf(stderr, "Cannot read file: %s\n", argv[1]);
            return 1;
        }
    }
    else{
        yyin = stdin;
    }
    printf("--------------LEXICAL ANALYSIS--------------\n");
    yylex();
    printf("# of lines = %d, # of chars = %d, # of tokens = %d\n", num_lines, num_chars, num_token);

    return 0;
}