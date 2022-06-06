#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../instruction.h"
#include "read_binary/read_binary.h"
#include "avm.h"


FILE* binary;

//GLOBALS
int total_global_var; //total global variables
int number_constsNum; //total number of number consts
double * number_consts; //array of number consts
int string_constsNum; //total number of string consts
char ** string_consts; //array of string consts
int libfuncsNum; //total number of libfuncs
char ** libfuncs; //array of libfuncs
int userfuncsNum; //total number of userfuncs
userfunc * userfuncs; //array of userfuncs
instruction * code; //array of instructions
unsigned codeSize; //total number of instructions



void avm_initialize(void) {
    avm_initstack();
    avm_init_libfuncs_hash();

    avm_registerlibfunc("print", libfunc_print);
    avm_registerlibfunc("typeof", libfunc_typeof);
    avm_registerlibfunc("totalarguments", libfunc_totalarguments);

    topsp = AVM_STACKSIZE-1;
    top   = AVM_STACKSIZE-1-total_global_var;
    pc = 1;
}


int main(void) {
    read_binary();
    avm_initialize();
  
    while(executionFinished == 0)
        execute_cycle();
    
    return 24;
}