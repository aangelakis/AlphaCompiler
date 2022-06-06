#ifndef READ_BINARY_HEADER
#define READ_BINARY_HEADER

#define MAGIC_NUMBER_OFFSET 133780085
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "read_binary.h"
#include "../../instruction.h"
#include "../avm.h" 

//GLOBALS
extern FILE* binary;
extern int total_global_var;
extern int number_constsNum;
extern double * number_consts;
extern int string_constsNum;
extern char ** string_consts;
extern int libfuncsNum;
extern char ** libfuncs;
extern int userfuncsNum;
extern userfunc * userfuncs;
extern instruction * code;
extern unsigned codeSize;


void read_binary();

#endif