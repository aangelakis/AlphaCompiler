#ifndef QUAD_HEADER
#define QUAD_HEADER
#include"expression.h"
#include"libs/Vektor/Vektor.h"
#include"libs/SymTableEntry/SymTableEntry.h"

typedef enum iopcode {
    assign, add, sub, 
    mul, div, mod, 
    uminus, and, or, 
    not, if_eq,  if_noteq, 
    if_lesseq, if_greatereq, if_less,
    if_greater, call, param,
    ret, getretval, funcstart,
    funcend, tablecreate,
    tablegetelem, tablesetelem
} iopcode;

typedef struct quad {
    iopcode     op;
    expr*       result;
    expr*       arg1;
    expr*       arg2;
    unsigned    label;
    unsigned    line;
} quad;

Vektor* quads = NULL;
unsigned total = 0;
unsigned int currQuad = 0 ;

void emit(iopcode, expr*, expr*, expr*, unsigned, unsigned);

#endif