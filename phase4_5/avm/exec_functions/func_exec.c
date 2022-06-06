#include"../avm.h"

void execute_call(instruction* instr){
    avm_memcell* func = avm_translate_operand(instr->result, &ax);
    assert(func);
    avm_callsaveenvironment();

    switch(func->type){

        case userfunc_m: {
            pc = func->data.funcVal;
            assert(pc < AVM_ENDING_PC);
            assert(code[pc].opcode == enterfunc_v);
            break;
        }

        case string_m:  {
            avm_calllibfunc(func->data.strVal);
            break;
        }

        case libfunc_m: {
            avm_calllibfunc(func->data.libfuncVal);
            break;
        }

        default: {
            char* s = avm_tostring(func);
            printf("kane edo to avm_error!\n");
            free(s);
            executionFinished = 1;
        }
    }
}

void execute_funcenter(instruction* instr){
    avm_memcell* func = avm_translate_operand(instr->result, &ax);
    assert(func);
    assert(pc == func->data.funcVal);

    totalActuals = 0;
    userfunc* funcInfo = avm_getfuncinfo(pc);
    topsp = top;
    top = top - funcInfo->localSize;
}


unsigned avm_get_envvalue(unsigned i){  
    assert(avm_stack[i].type == number_m); 
    unsigned val = (unsigned)avm_stack[i].data.numVal;
    assert(avm_stack[i].data.numVal == ((double)val));
    return val;
}

void execute_funcexit(instruction* unused){
    unsigned oldTop = top;
    top = avm_get_envvalue(topsp+ AVM_SAVEDTOP_OFFSET);
    pc = avm_get_envvalue(topsp+ AVM_SAVEDPC_OFFSET);
    topsp = avm_get_envvalue(topsp+ AVM_SAVEDTOPSP_OFFSET);
    while(++oldTop < top){
        avm_memcellclear(&avm_stack[oldTop]);
    }
}

typedef void (*library_func_t)(void);
library_func_t avm_getlibraryfunc(char* id) {
    return NULL;
}

void avm_calllibfunc(char* id){
    library_func_t f = avm_getlibraryfunc(id);
    if(!f){
        char tmp[1024];
        sprintf(tmp, "unsupported lib func '%s' called!", id);
        avm_error(tmp);
        executionFinished = 1;
    }
    else{
        topsp = top;
        totalActuals = 0;
        (*f)();
        if(!executionFinished){
            execute_funcexit((instruction*)0);
        }
    }
}

unsigned avm_totalactuals(void){
    return avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET);
}

avm_memcell* avm_getactual(unsigned i){
    assert(i < avm_totalactuals());
    return &avm_stack[topsp + AVM_STACKENV_SIZE + i +1];
}

void avm_registerlibfunc(char* id, library_func_t addr);

void execute_pusharg(instruction* instr){
    avm_memcell* arg = avm_translate_operand(instr->arg1, &ax);
    assert(arg);
    avm_assign(&avm_stack[top],arg);
    ++totalActuals;
    avm_dec_top();
}


// lib funcs
void libfunc_print(void){
    unsigned n = avm_totalactuals();
    for(unsigned i = 0; i < n ; i++){
        char* s = avm_tostring(avm_getactual(i));
        puts(s);
        free(s);
    }
}

void libfunc_typeof(void){
    unsigned n = avm_totalactuals();
    if(n != 1){
        char tmp[1024];
        sprintf(tmp, "one argument (not %d) expected in 'typeof'!", n);
        avm_error(tmp);
    }else{
        avm_memcellclear(&retval);
        retval.type = string_m;
        retval.data.strVal = strdup(typeStrings[avm_getactual(0)->type]);
    }
}

void libfunc_totalarguments(void){
    unsigned p_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
    avm_memcellclear(&retval);
    if(!p_topsp){
        avm_error("'totalarguments' called outside a function!");
        retval.type = nil_m;
    }else{
        retval.type = number_m;
        retval.data.numVal = avm_get_envvalue(p_topsp + AVM_NUMACTUALS_OFFSET);
    }
}