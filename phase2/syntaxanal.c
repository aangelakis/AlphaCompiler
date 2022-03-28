#include "parser.h"
#include "scanner.h"
#include <stdio.h>

int main(int argc, char *argv[]){
    
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


    yyparse();
    return 24;
}