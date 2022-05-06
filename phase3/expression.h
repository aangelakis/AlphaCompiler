#ifndef EXPRESSION_HEADER
#define EXPRESSION_HEADER

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
    SymTableEntry*  sym;
    struct expr*    index;
    double          numConst;
    char*           strConst;
    unsigned char   boolConst;
    struct expr*    next;
} expr;

expr* newexpr(expr_t);

//  CONST VALUES
expr* newexpr_conststring(char*);
expr* newexpr_constnumber(double);
expr* newexpr_constnil();
expr* newexpr_constbool(unsigned char);

#endif