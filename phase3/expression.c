#include "expression.h"

expr* newexpr(expr_t t){
    expr* e = (expr*) malloc(sizeof(expr));
    memset(e,0,sizeof(expr));
    e->type = t;
    e->truelist = 0;
    e->falselist = 0;
    return e;
}


expr* newexpr_conststring(char* s){
    expr* e = newexpr(conststring_e);
    e->content.strConst = strdup(s);
    return e;
}


expr* newexpr_constdouble(double i){
    expr* e = newexpr(constdouble_e);
    e->content.doubleConst = i;
    return e;
}

expr* newexpr_constnil(){
    expr* e = newexpr(nil_e);
    return e;
}

expr* newexpr_constbool(unsigned char b){
    expr* e = newexpr(constbool_e);
    e->content.boolConst = b;
    return e;
}

expr* newexpr_constint(int i){
    expr* e = newexpr(constint_e);
    e->content.intConst = i;
    return e;
}


expr* lvalue_to_expr(SymTableEntry* tmpSymbol){
    assert(tmpSymbol);
    expr *e;
    switch (tmpSymbol->type) {
        case VAR_GLOBAL:
            e = newexpr(var_e);
            break;
        case VAR_LOCAL:
            e = newexpr(var_e);
            break;
        case VAR_FORMAL:
            e = newexpr(var_e);
            break;
        case USERFUNC:
            e = newexpr(programfunc_e);
            break;
        case LIBFUNC:
            e = newexpr(libraryfunc_e);
            break;
        default:
            return NULL;
    }
    e->next =(expr*) 0;
    e->sym = tmpSymbol;
    return e;
}

