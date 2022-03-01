#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char* replace_bs_with(char* s, char c, int first_time) {
    char *iter = s, *new_s = (char *) malloc(strlen(s) * sizeof(char));
    int i = 0;

    while(iter[i] != '\\') {
        new_s[i] = iter[i];
        i++;
    }
    new_s[i] = c;
    i++;
    while(iter[i]){
        new_s[i] = iter[i+1];
        i++;
    }

    if(!first_time)
        free(s);
    return new_s;
}

void backslash(char **s) {
    char *iter = *s;
    int first_time = 1;

    while(*iter) {
        if(*iter == '\\') {
            if(*(iter+1) == 'n') {
                *s = replace_bs_with(*s, '\n', first_time);
                first_time = 0;
            }
            else if(*(iter+1) == 't') {
                *s = replace_bs_with(*s, '\t', first_time);
                first_time = 0;
            }
            else if(*(iter+1) == 'b') {
                *s = replace_bs_with(*s, '\b', first_time);
                first_time = 0;
            }
        }
        iter++;
    }
}

int main(void) {
    char *s="This is\\na string\\n\\tmy\\t\\tbrotha";
    printf("Replacing in string '%s'\n", s);

    backslash(&s);

    puts(s);
    return 0;
}
