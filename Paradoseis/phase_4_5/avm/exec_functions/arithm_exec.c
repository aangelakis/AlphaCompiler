#include"../avm.h"

typedef double (*arithmetic_func_t)(double x, double y);

double add_impl (double x, double y) { return x+y; }
double sub_impl (double x, double y) { return x-y; }
double mul_impl (double x, double y) { return x*y; }
double div_impl (double x, double y) { assert(y); return x/y; }     // Maybe needs more errorchecking
double mod_impl (double x, double y) { //Maybe needs more errorchecking
    assert(y);
    //assert(x > 0);
    assert(y > 0);
    return ((unsigned) x) % ((unsigned) y);

}

/* Dispatcher for arithmetic functions. */
arithmetic_func_t arithmeticFuncs[] = {
    add_impl,
    sub_impl,
    mul_impl,
    div_impl,
    mod_impl
};

void execute_arithmetic (instruction* instr) {
    avm_memcell* lv =  avm_translate_operand(instr->result, (avm_memcell*) 0);
    avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);

    //assert(lv && (&stack[N-1] >= lv && lv lv > &stack[top] || lv==&retval));
    assert(rv1 && rv2);

    if(rv1->type != number_m || rv2->type != number_m) {
        avm_error("not a number in arithmetic", &code[pc]);
        executionFinished = 1;
    }
    else {
        // peos peos peos
        arithmetic_func_t op = arithmeticFuncs[instr->opcode - add_v];
        avm_memcellclear(lv);
        lv->type            = number_m;
        lv->data.numVal     = (*op)(rv1->data.numVal, rv2->data.numVal);
    }
}

void execute_add (instruction* instr) { execute_arithmetic(instr); return; }
void execute_sub (instruction* instr) { execute_arithmetic(instr); return; }
void execute_mul (instruction* instr) { execute_arithmetic(instr); return; }
void execute_div (instruction* instr) { execute_arithmetic(instr); return; }
void execute_mod (instruction* instr) { execute_arithmetic(instr); return; }


void execute_uminus (instruction* instr) { assert(0); return; }