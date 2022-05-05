#ifndef QUAD_HEADER
#define QUAD_HEADER
#include"libs/Vektor/Vektor.h"

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


typedef enum expr_t {
    var_e,
    tableitem_e,

    programfunc_e,
    libraryfunc_e,

    arithexpr_e,
    boolexpr_e,
    assignexpr_e,
    newtable_e,

    costnum_e,
    constbool_e,
    conststring_e,

    nil_e
} expr_t;


typedef struct expr {
    expr_t          type;
    //symbol*         sym;
    struct expr*    index;
    double          numConst;
    char*           strConst;
    unsigned char   boolConst;
    struct expr*    next;
} expr;

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