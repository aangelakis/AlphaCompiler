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

typedef double (*toarithm_func_t)(avm_memcell*);

double number_toarithm   (avm_memcell* m) { return m->data.numVal; }
double string_toarithm   (avm_memcell* m) { return strlen(m->data.strVal); }
double bool_toarithm     (avm_memcell* m) { assert(0); return 0; }      // should never be used
double table_toarithm    (avm_memcell* m) { return m->data.tableVal->total; }
double userfunc_toarithm (avm_memcell* m) { return m->data.numVal; }
double libfunc_toarithm  (avm_memcell* m) { return strlen(m->data.libfuncVal); }
double nil_toarithm      (avm_memcell* m) { assert(0); return 0; }      // should never be used
double undef_toarithm    (avm_memcell* m) { assert(0); return 0; }      // should never be used

toarithm_func_t toarithmFuncs[]={
    number_toarithm,
    string_toarithm,
    bool_toarithm,
    table_toarithm,
    userfunc_toarithm,
    libfunc_toarithm,
    nil_toarithm,
    undef_toarithm
};

int avm_toarithm (avm_memcell* m) {
    assert(m->type >= 0 && m->type < undef_m);
    return (*toarithmFuncs[m->type])(m);
}

char* typeStrings[] = {
    "number",
    "string",
    "bool",
    "table",
    "userfunc", // userfunc PROSTETHIKE
    "libfunc",
    "nil",
    "undef"
};

void execute_jeq (instruction* instr) {
    assert(instr->result->type == label_a);
    
    avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);

    unsigned char result = 0;

    if (rv1->type == undef_m || rv2->type == undef_m)
        avm_error("\'undef\' involved in equality", &code[pc]);
    else
    if (rv1->type == nil_m || rv2->type == nil_m)
        result = rv1->type == nil_m && rv2->type == nil_m;
    else
    if (rv1->type == bool_m || rv2->type == bool_m)
        result = (avm_tobool(rv1) == avm_tobool(rv2));
    else
    if(rv1->type != rv2->type){
        char tmp[1024];
        sprintf(tmp, "%s == %s is illegal!", typeStrings[rv1->type], typeStrings[rv2->type]);
        avm_error(tmp, &code[pc]);
    }
    else if(rv1->type == string_m && rv2->type == string_m){
        result = !strcmp(rv1->data.strVal, rv2->data.strVal);
    }
    else {
        result = (avm_toarithm(rv1) == avm_toarithm(rv2));
    }

    if(!executionFinished && result)
        pc = instr->result->val;
}

void execute_jge (instruction* instr) {
    assert(instr->result->type == label_a);
    
    avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);

    unsigned char result = 0;

    if (rv1->type == undef_m || rv2->type == undef_m)
        avm_error("\'undef\' involved in jge", &code[pc]);
    else
    if (rv1->type == nil_m || rv2->type == nil_m){
        if(rv1->type == nil_m && rv2->type == nil_m)
            result = 1;
        else if(rv1->type == nil_m)
            result = 0;
        else
            result = 1;
    }
    else
    if (rv1->type == bool_m || rv2->type == bool_m)
        result = (avm_tobool(rv1) >= avm_tobool(rv2));
    else
    if(rv1->type != rv2->type){
        char tmp[1024];
        sprintf(tmp, "%s >= %s is illegal!", typeStrings[rv1->type], typeStrings[rv2->type]);
        avm_error(tmp, &code[pc]);
    }
    else {
        result = (avm_toarithm(rv1) >= avm_toarithm(rv2));
    }

    if(!executionFinished && result)
        pc = instr->result->val;
}

void execute_jgt (instruction* instr) {
    assert(instr->result->type == label_a);
    
    avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);

    unsigned char result = 0;

    if (rv1->type == undef_m || rv2->type == undef_m)
        avm_error("\'undef\' involved in jgt", &code[pc]);
    else
    if (rv1->type == nil_m || rv2->type == nil_m){
        if(rv1->type == nil_m && rv2->type == nil_m)
            result = 0;
        else if(rv1->type == nil_m)
            result = 0;
        else
            result = 1;
    }
    else
    if (rv1->type == bool_m || rv2->type == bool_m)
        result = (avm_tobool(rv1) > avm_tobool(rv2));
    else
    if(rv1->type != rv2->type){
        char tmp[1024];
        sprintf(tmp, "%s > %s is illegal!", typeStrings[rv1->type], typeStrings[rv2->type]);
        avm_error(tmp, &code[pc]);
    }
    else {
        result = (avm_toarithm(rv1) > avm_toarithm(rv2));
    }

    if(!executionFinished && result)
        pc = instr->result->val;
}

void execute_jle (instruction* instr) {
    assert(instr->result->type == label_a);
    
    avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);

    unsigned char result = 0;

    if (rv1->type == undef_m || rv2->type == undef_m)
        avm_error("\'undef\' involved in jle", &code[pc]);
    else
    if (rv1->type == nil_m || rv2->type == nil_m){
        if(rv1->type == nil_m && rv2->type == nil_m)
            result = 1;
        else if(rv1->type == nil_m)
            result = 1;
        else
            result = 0;
    }
    else
    if (rv1->type == bool_m || rv2->type == bool_m)
        result = (avm_tobool(rv1) <= avm_tobool(rv2));
    else
    if(rv1->type != rv2->type){
        char tmp[1024];
        sprintf(tmp, "%s <= %s is illegal!", typeStrings[rv1->type], typeStrings[rv2->type]);
        avm_error(tmp, &code[pc]);
    }
    else {
        result = (avm_toarithm(rv1) <= avm_toarithm(rv2));
    }

    if(!executionFinished && result)
        pc = instr->result->val;
}

void execute_jlt (instruction* instr) {
    assert(instr->result->type == label_a);
    
    avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);

    unsigned char result = 0;

    if (rv1->type == undef_m || rv2->type == undef_m)
        avm_error("\'undef\' involved in jlt", &code[pc]);
    else
    if (rv1->type == nil_m || rv2->type == nil_m){
        if(rv1->type == nil_m && rv2->type == nil_m)
            result = 0;
        else if(rv1->type == nil_m)
            result = 0;
        else
            result = 1;
    }
    else
    if (rv1->type == bool_m || rv2->type == bool_m)
        result = (avm_tobool(rv1) < avm_tobool(rv2));
    else
    if(rv1->type != rv2->type){
        char tmp[1024];
        sprintf(tmp, "%s < %s is illegal!", typeStrings[rv1->type], typeStrings[rv2->type]);
        avm_error(tmp, &code[pc]);
    }
    else {
        result = (avm_toarithm(rv1) < avm_toarithm(rv2));
    }

    if(!executionFinished && result)
        pc = instr->result->val;
}

void execute_jne (instruction* instr) {
    assert(instr->result->type == label_a);
    
    avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);

    unsigned char result = 0;

    if (rv1->type == undef_m || rv2->type == undef_m)
        avm_error("\'undef\' involved in inequality",&code[pc]);
    else
    if (rv1->type == nil_m || rv2->type == nil_m){
        if(rv1->type == nil_m && rv2->type == nil_m)
            result = 0;
        else
            result = 1;
    }
    else
    if (rv1->type == bool_m || rv2->type == bool_m)
        result = (avm_tobool(rv1) != avm_tobool(rv2));
    else
    if(rv1->type != rv2->type){
        char tmp[1024];
        sprintf(tmp, "%s != %s is illegal!", typeStrings[rv1->type], typeStrings[rv2->type]);
        avm_error(tmp,&code[pc]);
    }
    else {
        result = (avm_toarithm(rv1) != avm_toarithm(rv2));
    }

    if(!executionFinished && result)
        pc = instr->result->val;
}

void execute_jump (instruction* instr) {
    assert(instr->result->type == label_a);

    if(!executionFinished)
        pc = instr->result->val;
}

void execute_and (instruction* instr) { assert(0); return; }
void execute_or  (instruction* instr) { assert(0); return; }
void execute_not (instruction* instr) { assert(0); return; }