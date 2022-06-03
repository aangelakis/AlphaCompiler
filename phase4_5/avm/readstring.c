#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../instruction.h"

FILE* binary;


// WRITTEN BY OUR CLOWN MASCOT CZARKOS :D
char* make_string() { 
    char tmp[1024];
    char* new_string = (char*) 0; // ------> CRINGE
    char c = fgetc(binary);
    if(c == '\n')
        c = fgetc(binary);

    
    int i = 0;
    for(; c; ++i) {
        //putchar(c);
        tmp[i] = c;
        c = fgetc(binary);
    }
    tmp[i] = (char) 0; // ------> CRINGE

    new_string = malloc(i);

    int j = 0;
    for( ;tmp[j]; ++j)
        new_string[j] = tmp[j];
    new_string[j] = tmp[j];

    // ANTHONY SAVIDI PONAS?
    assert(i == j);

    return new_string;
}


int main(void) {
    binary = fopen("../binary.abc", "rw");
    long int magicnumber;
    fscanf(binary, "%ld", &magicnumber);
    assert(magicnumber == 133780085);

    unsigned totalConstNums, totalConstStrings, totalLibFuncs, totalUserFuncs;
    double* constNums;
    char**   constStrings;
    char**   libFuncs;
     

    fscanf(binary, "%u", &totalConstNums);
    constNums = malloc(totalConstNums * sizeof(int));
    for(int i = 0; i < totalConstNums; i++)
        fscanf(binary, "%lf", &constNums[i]);

    fscanf(binary, "%u", &totalConstStrings);
    constStrings = malloc(totalConstStrings * sizeof(char*));
    for(int i = 0; i < totalConstStrings; i++)
        constStrings[i] = make_string();
    
    fscanf(binary, "%u", &totalLibFuncs);
    libFuncs = malloc(totalLibFuncs * sizeof(char*));
    for(int i = 0; i < totalLibFuncs; i++)
        libFuncs[i] = make_string();
    
    fscanf(binary, "%u", &totalUserFuncs);

    printf("%ld\n", magicnumber);
    printf("%d\n", totalConstNums);
    for(int i = 0; i < totalConstNums; ++i)
        printf("%f\n", constNums[i]);
    printf("%d\n", totalConstStrings);
    for(int i = 0; i < totalConstStrings; i++)
        puts(constStrings[i]);
    printf("%d\n", totalLibFuncs);
    for(int i = 0; i < totalLibFuncs; i++)
        puts(libFuncs[i]);
    printf("%d\n", totalUserFuncs);

    char c = fgetc(binary);
    c = fgetc(binary);
    
    while(c != -1){
        putchar(c);
        c = fgetc(binary);
    }

    fclose(binary);
    return 24;
}