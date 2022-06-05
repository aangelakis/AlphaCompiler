#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../instruction.h"
#include "read_binary/read_binary.h"
#include "avm.h"


FILE* binary;

//GLOBALS
int total_global_var;
double * number_consts;
char ** string_consts;
char ** libfuncs;
userfunc * userfuncs;
instruction * code;
unsigned codeSize;



void avm_initialize(void) {
    avm_initstack();

    //avm_registerlibfunc("print", libfunc_print);
    //avm_registerlibfunc("typeof", libfunc_typeof);

    topsp = AVM_STACKSIZE-1;
    top   = AVM_STACKSIZE-1-total_global_var;
}


int main(void) {
    read_binary();
    avm_initialize();
  
    while(executionFinished == 0)
        execute_cycle();

    return 24;
}