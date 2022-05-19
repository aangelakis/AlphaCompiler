#ifndef QUAD_HEADER
#define QUAD_HEADER
#include"expression.h"
#include"libs/Vektor/Vektor.h"
#include"libs/SymTableEntry/SymTableEntry.h"


extern char quad_opcode_names[26][15];

//NA DUME TO DIV STO ENUM
typedef enum iopcode {
    assign, add, sub, 
    mul, _div, mod, 
    uminus, and, or, 
    not, if_eq,  if_noteq, 
    if_lesseq, if_greatereq, if_less,
    if_greater, call, param,
    ret, getretval, funcstart,
    funcend, tablecreate,
    tablegetelem, tablesetelem , jump
} iopcode;

typedef struct quad {
    iopcode     op;
    expr*       result;
    expr*       arg1;
    expr*       arg2;
    unsigned    label;
    unsigned    line;
    unsigned    source_code_line;
} quad;

void print_quad(void*);

#endif