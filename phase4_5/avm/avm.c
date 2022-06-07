#include "avm.h"
#include "read_binary/read_binary.h"

unsigned char   executionFinished = 0;
unsigned        pc = 0;
unsigned        currLine = 0;
unsigned        codeSize = 0;
instruction*    code = NULL;
unsigned totalActuals = 0;


avm_memcell ax, bx, cx;
avm_memcell retval;
int    top, topsp;


double  consts_getnumber(unsigned index) {
    return number_consts[index];
}
char*   consts_getstring(unsigned index) {
    return string_consts[index];
}
char*   libfuncs_getused(unsigned index){
    return libfuncs[index];
}

userfunc* avm_getfuncinfo(unsigned address) {
    for(int i = 0; i < userfuncsNum; ++i){
        if(userfuncs[i].address == address)
            return &userfuncs[i];
    }
    // if you got here it means that there does not exist a function with that address
    return NULL;
}

avm_memcell* avm_translate_operand(vmarg* arg, avm_memcell* reg){
    assert(arg);
    if(reg)
        avm_memcellclear(reg);
    //printf("arg type = %d\n", arg->type);
    switch(arg->type){
        case global_a:{
            return &avm_stack[AVM_STACKSIZE - 1 - arg->val];
        } 
        case local_a: {
            return &avm_stack[topsp - arg->val];   
        }  
        case formal_a:  return &avm_stack[topsp + AVM_STACKENV_SIZE + 1 + arg->val];

        case retval_a:  return &retval;

        case number_a:  {
            reg->type = number_m;
            reg->data.numVal = consts_getnumber(arg->val);
            return reg;
        }

        case string_a:  {
            reg->type = string_m;
            reg->data.strVal = strdup(consts_getstring(arg->val));
            return reg;
        }

        case bool_a:    {
            reg->type = bool_m;
            reg->data.boolVal = arg->val;
            return reg;
        }

        case nil_a:     {
            reg->type = nil_m;
            return reg;
        }

        case userfunc_a:{
            reg->type = userfunc_m;
            reg->data.funcVal = arg->val;
            return reg;
        }

        case libfunc_a: {
            reg->type = libfunc_m;
            reg->data.libfuncVal = libfuncs_getused(arg->val);
            return reg;
        }

        default: assert(0);
    }
}

void memclear_string(avm_memcell* m){
    assert(m->data.strVal);
    free(m->data.strVal);
}

void memclear_table(avm_memcell* m){
    assert(m->data.tableVal);
    avm_tabledecrefcounter(m->data.tableVal);
}

memclear_func_t memclearFuncs[] = {
     0,  /* number */
     memclear_string,
     0,  /* bool */
     memclear_table,
     0,  /* userfunc */
     0,  /* libfunc */
     0,  /* nil */
     0   /* undef */
 };

void avm_memcellclear(avm_memcell* m){
    if(m->type != undef_m){
        memclear_func_t f = memclearFuncs[m->type];
        if(f){
            f(m);
        }
        m->type = undef_m;
    }
}

void avm_dec_top(void){
    if(!top){
        avm_error("stack overflow");
        executionFinished = 1;
    }
    else{
        --top;
    }
}

void avm_push_envvalue(unsigned val){
    avm_stack[top].type         = number_m;
    avm_stack[top].data.numVal  = val;
    avm_dec_top();
}

void avm_callsaveenvironment(void){
    avm_push_envvalue(totalActuals);
    avm_push_envvalue(pc+1);
    avm_push_envvalue(top + totalActuals + 2);
    avm_push_envvalue(topsp);
}


void avm_error(char* error){
    fprintf(stderr, "\033[1;31mERROR:\033[0;31m %s\n\033[0m", error);
}

void avm_warning(char* warning){
    fprintf(stderr, "\033[1;33mWARNING: \033[0;33m%s\n\033[0m", warning);
}

char* avm_tostring(avm_memcell* cell) {
    assert(cell);
    char *str = NULL;
    switch (cell->type) {
        case number_m:
            str = (char*)malloc(sizeof(char) * 32);
            sprintf(str, "%f", cell->data.numVal);
            return str;
        case string_m:
            str = strdup(cell->data.strVal);
            return str;
        case bool_m:
            str = strdup(cell->data.boolVal ? "true" : "false");
            return str;
        case table_m:
            str = strdup("table"); //TODO na dume ti tha epistrefume
            return str;
        case userfunc_m:
            str = strdup(userfuncs[cell->data.funcVal].id);
            return str;
        case libfunc_m:
            str = strdup(cell->data.libfuncVal);
            return str;
        case nil_m:
            str = strdup("nil");
            return str;
        case undef_m:
            str = strdup("undef");
            return str;
        default:
            avm_warning("avm_tostring: unknown type");
            str = strdup("avm_tostring: unknown type");
            //exit(-1);
            return str;
    }
}