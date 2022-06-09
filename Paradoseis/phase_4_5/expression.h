#ifndef EXPRESSION_CUSTOM_HEADER
#define EXPRESSION_CUSTOM_HEADER
#include <stdlib.h>
#include <string.h>
#include "libs/SymTableEntry/SymTableEntry.h"

typedef enum expr_t {
    var_e,
    tableitem_e,

    programfunc_e,
    libraryfunc_e,

    arithexpr_e,
    boolexpr_e,
    assignexpr_e,
    newtable_e,

    constdouble_e,
    constint_e,
    constbool_e,
    conststring_e,

    nil_e
} expr_t;

typedef struct expr {
    expr_t          type;
    SymTableEntry*  sym;
    union {
        int             intConst;
        double          doubleConst;
        char*           strConst;
        unsigned char   boolConst;
    } content;
    struct expr*    index;
    struct expr*    next;
    struct expr*    prev;
    //int is_also_const;
    int truelist;
    int falselist;
} expr;

typedef struct call_t{
    expr*           elist;
    unsigned char   method;
    char*           name;
} call_t;

typedef struct stmt_t {
    int breaklist;
    int continuelist;
    int returnlist;
} stmt_t;

typedef struct forprefix_t {
    int test;
    int enter;
} forprefix_t;

expr* newexpr(expr_t);

//  CONST VALUES
expr* newexpr_conststring(char*);
expr* newexpr_constint(int);
expr* newexpr_constdouble(double);
expr* newexpr_constnil();
expr* newexpr_constbool(unsigned char);

expr* lvalue_to_expr(SymTableEntry* tmpSymbol);
#endif