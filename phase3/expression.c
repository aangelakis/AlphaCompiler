#include "expression.h"

expr* newexpr(expr_t t){
    expr* e = (expr*) malloc(sizeof(expr));
    memset(e,0,sizeof(expr));
    e->type = t;
    return e;
}


expr* newexpr_conststring(char* s){
    expr* e = newexpr(conststring_e);
    e->strConst = strdup(s);
    return e;
}


expr* newexpr_constnumber(double i){
    expr* e = newexpr(costnum_e);
    e->numConst = i;
    return e;
}

expr* newexpr_constnil(){
    expr* e = newexpr(nil_e);
    return e;
}

expr* newexpr_constbool(unsigned char b){
    expr* e = newexpr(constbool_e);
    e->boolConst = b;
    return e;
}


// geia sou koukle


// gia so kokla
// iaso