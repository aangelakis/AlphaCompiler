#include"../avm.h"

typedef unsigned char (*tobool_func_t)(avm_memcell*);

unsigned char number_tobool   (avm_memcell* m) { return m->data.numVal != 0; }
unsigned char string_tobool   (avm_memcell* m) { return m->data.strVal[0] != 0; }
unsigned char bool_tobool     (avm_memcell* m) { return m->data.boolVal; }
unsigned char table_tobool    (avm_memcell* m) { return 1; }
unsigned char userfunc_tobool (avm_memcell* m) { return 1; }
unsigned char libfunc_tobool  (avm_memcell* m) { return 1; }
unsigned char nil_tobool      (avm_memcell* m) { return 0; }
unsigned char undef_tobool    (avm_memcell* m) { assert(0); return 0; }

tobool_func_t toboolFuncs[]={
    number_tobool,
    string_tobool,
    bool_tobool,
    table_tobool,
    userfunc_tobool,
    libfunc_tobool,
    nil_tobool,
    undef_tobool
};

unsigned char avm_tobool (avm_memcell* m) {
    assert(m->type >= 0 && m->type < undef_m);
    return (*toboolFuncs[m->type])(m);
}

char* typeStrings[] = {
    "number",
    "string",
    "bool",
    "table",
    "libfunc",
    "nil",
    "undef"
};

void execute_jeq (instruction* instr) {
    assert(instr->result->type == label_a);
    
    avm_memcell* rv1 = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(&instr->arg2, &bx);

    unsigned char result = 0;

    if (rv1->type == undef_m || rv2->type == undef_m)
        avm_error("\'undef\' involved in equality");
    else
    if (rv1->type == nil_m || rv2->type == nil_m)
        result = rv1->type == nil_m && rv2->type == nil_m;
    else
    if (rv1->type == bool_m || rv2->type == bool_m)
        result = (avm_tobool(rv1) == avm_tobool(rv2));
    else
    if(rv1->type != rv2->type)
        avm_error("%s == %s is illegal!", typeStrings[rv1->type], typeStrings[rv2->type]);
    else {
        /* Equality check with dispatching */
    }

    if(!executionFinished && result)
        pc = instr->result->val;
}