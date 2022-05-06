#include "expression.h"

expr* newexpr(expr_t t){
    expr* e = (expr*) malloc(sizeof(expr));
    memset(e,0,sizeof(expr));
    e->type = t;
    return e;
}


expr* newexpr_conststring(char* s){
    expr* e = new_expr(conststring_e)l
    e->strConst = strdup(s);
    return e;
}


expr* newexpr_constnumber(double i){
    expr* e = new_expr(costnum_e);
    e->numConst = i;
    return e;
}

expr* newexpr_constnil(){
    expr* e = new_expr(nil_e);
    return e;
}

expr* newexpr_constbool(unsigned char b){
    expr* e = new_expr(constbool_e);
    e->boolConst = b;
    return e;
}


// geia sou koukle


// gia so kokla
// iaso