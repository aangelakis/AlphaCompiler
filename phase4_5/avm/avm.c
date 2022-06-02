#include "avm.h"
#define AVM_STACKENV_SIZE   4


unsigned char   executionFinished = 0;
unsigned        pc = 0;
unsigned        currLine = 0;
unsigned        codeSize = 0;
instruction*    code = NULL;
unsigned totalActuals = 0;


#define AVM_ENDING_PC   codeSize;

avm_memcell ax, bx, cx;
avm_memcell retval;
unsigned    top, topsp;

double  consts_getnumber(unsigned index);
char*   consts_getstring(unsigned index);
char*   libfuncs_getused(unsigned index);

void avm_memcellclear(avm_memcell* m);
void avm_assign(avm_memcell* lv, avm_memcell* rv);
char* avm_tostring(avm_memcell*);
void avm_calllibfunc(char* funcName);
void avm_callsaveenvironment(void);



void avm_tableincrefcounter(avm_table* t){
    ++t->refCounter;
}

void avm_tabledecrefcounter(avm_table* t){
    assert(t->refCounter > 0);
    if(!--t->refCounter){
        avm_tabledestroy(t);
    }
}

void avm_tablebucketsinit(avm_table_bucket** p){
    for(unsigned i = 0; i < AVM_TABLE_HASHSIZE; ++i){
        p[i] = NULL;
    }
}

avm_table* avm_tablenew(void){
    avm_table* t = malloc(sizeof(avm_table));
    AVM_WIPEOUT(*t);

    t->refCounter = t->total = 0;
    avm_tablebucketsinit(t->numIndexed);
    avm_tablebucketsinit(t->strIndexed);

    return t;
}


void avm_tablebucketsdestroy(avm_table_bucket** p){
    for(unsigned i = 0; i < AVM_TABLE_HASHSIZE; ++i, ++p){
        for(avm_table_bucket* b = *p; b;){
            avm_table_bucket* del = b;
            b = b->next;
            avm_memcellclear(&del->key);
            avm_memcellclear(&del->value);
            free(del);
        }
        p[i] = NULL;
    }
}

void avm_tabledestroy(avm_table* t){
    avm_tablebucketsdestroy(t->strIndexed);
    avm_tablebucketsdestroy(t->numIndexed);
    free(t);
}


avm_memcell* avm_translate_operand(vmarg* arg, avm_memcell* reg){
    switch(arg->type){

        case global_a:  return &stack[AVM_STACKSIZE - 1 - arg->val];
        case local_a:   return &stack[topsp - arg->val];   
        case formal_a:  return &stack[topsp + AVM_STACKENV_SIZE + 1 + arg->val];

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

void execute_cycle(void){
    if(executionFinished){
        return;
    }
    else if(pc == AVM_ENDING_PC){
        executionFinished = 1;
        return;
    }
    else{
        assert(pc < AVM_ENDING_PC);
        instruction* instr = code[pc];
        assert(
            instr->opcode >= 0 &&
            instr->opcode <= AVM_MAX_INSTRUCTIONS
        );
        if(instr->srcLine){
            currLine = instr->srcLine;
        }
        unsigned oldPC = pc;
        executeFuncs[instr->opcode](instr);
        if(pc == oldPC){
            ++pc;
        }
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

void avm_memcellclear(avm_memcell* m){
    if(m->type != undef_m){
        memclear_func_t f = memclearFuncs[m->type];
        if(f){
            f(m);
        }
        m->type = undef_m;
    }
}


void execute_assign(instruction* instr){
    avm_memcell* lv = avm_translate_operand(&instr->result, NULL);
    avm_memcell* rv = avm_translate_operand(&instr->arg1, &ax);

    assert(lv && (&stack[N-1] >= lv && lv > &stack[top] || lv == &retval));
    assert(rv); // should do similar assertion tests here

    avm_assign(lv, rv);
}

void avm_assign(avm_memcell* lv, avm_memcell* rv){

    if(lv == rv)
        return;
    
    if (lv->type == table_m &&
        rv->type == table_m &&
        lv->data.tableVal == rv->data.tableVal)
        return;

    if(rv->type == undef_m)
        printf("kane edo to avm_warning!\n");
    
    avm_memcellclear(lv);

    memcpy(lv, rv, sizeof(avm_memcell));

    if(lv->type == string_m){
        lv->data.strVal = strdup(rv->data.strVal);
    }
    else if(lv->type == table_m){
        avm_tableincrefcounter(lv->data.tableVal);
    }
}

void execute_call(instruction* instr){
    avm_memcell* func = avm_translate_operand(&instr->result, &ax);
    assert(func);
    avm_callsaveenvironment();

    switch(func->type){

        case userfunc_m: {
            pc = func->data.funcVal;
            assert(pc < AVM_ENDING_PC);
            assert(code[pc]->opcode == funcenter_v);
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

void avm_dec_top(void){
    if(!top){
        printf("kane edo to avm_error!\n");
        executionFinished = 1;
    }
    else{
        --top;
    }
}

void avm_push_envvalue(unsigned val){
    stack[top].type         = number_m;
    stack[top].data.numVal  = val;
    avm_dec_top();
}

void avm_callsaveenvironment(void){
    avm_push_envvalue(totalActuals);
    avm_push_envvalue(pc+1);
    avm_push_envvalue(top + totalActuals + 2);
    avm_push_envvalue(topsp);
}