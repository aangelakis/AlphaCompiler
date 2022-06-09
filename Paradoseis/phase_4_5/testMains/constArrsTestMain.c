#include<stdio.h>
#include<string.h>
#include"../libs/Vektor/Vektor.h"
#include "libs/SymTableEntry/SymTableEntry.h"

Vektor*     numConsts;
Vektor*     stringConsts;
Vektor*     namedLibfuncs;
Vektor*     userFuncs;

typedef struct userfunc{
    unsigned address;
    unsigned localSize;
    char* id;
} userfunc;

unsigned consts_newstring(char* s);
unsigned consts_newnumber(double n);
unsigned libfuncs_newused(char* s);
unsigned userfuncs_newfunc(SymTableEntry* sym);

char names[6][20] = {
    "alekoukos",
    "aliekmonas",
    "dodoslayer",
    "zarkoulis",
    "hrodotos",
    "peos"
};

void print_string(void * void_str) {
    char* s = (char*) void_str;
    puts(s);
}

void print_int(void* void_int){
    int* i = (int*) void_int;
    printf("%d\n",i);
}

int main(void) {
    stringConsts = vektor_initialize();
    for(int i = 0; i < 6; ++i) {
        unsigned tmp = consts_newstring(names[i]);
        printf("index=%u\n", tmp);
    }

    printf("There are %d strings in the vektor\n", vektor_active_size(stringConsts));
    vektor_apply(stringConsts, print_string);

    print_string(vektor_get_element(stringConsts, 0));
    return 24;
}


unsigned consts_newstring(char *s){
    char* tmp_s = strdup(s);
    vektor_add(stringConsts, tmp_s);
    return (vektor_active_size(stringConsts) - 1); // returning the index
}

unsigned consts_newnumber(double n){
    int* tmp_n = malloc(sizeof int);
    *tmp_n = n;
    vektor_add(numConsts, tmp_n);
    return (vektor_active_size(numConsts) - 1);
}

unsigned libfuncs_newused(char* s){
    char* tmp_s = strdup(s);
    vektor_add(namedLibfuncs, tmp_s);
    return (vektor_active_size(namedLibfuncs) - 1);
}

unsigned userfuncs_newfunc(SymTableEntry* sym){
    //assert(symtable(, sym->value.funcVal->name));

    userfunc* f = malloc(sizeof(userfunc));
    f->id = sym->value.funcVal->name;
    f->localSize = sym->value.funcVal.numOfLocalVars;
    f->address = sym->value.funcVal.quadfuncStartIndex;
    vektor_add(userFuncs, f);
    return (vektor_active_size(userFuncs) - 1);
}