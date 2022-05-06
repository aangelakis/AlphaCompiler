#include "quads.h"

void emit(
        iopcode     op,
        expr*       result,
        expr*       arg1,
        expr*       arg2,
        unsigned    label,
        unsigned    line
        )
{

    quad* p     = malloc(sizeof(quad));
    assert(p);
    p->result   = result;
    p->arg1     = arg1;
    p->arg2     = arg2;
    p->label    = label;
    p->line     = line;
    vektor_set_element(quads, currQuad, (void*) p);
    currQuad++;
}