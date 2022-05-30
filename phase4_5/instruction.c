#include <stdio.h>
#include "libs/SymTableEntry.h"
#include "instructino.h"

unsigned consts_newstring(char* s);
unsigned consts_newnumber(double n);
unsigned libfuncs_newused(char* s);
unsigned userfuncs_newfunc(SymTableEntry* sym);

/* isos baloume sto symtableentry ekei to scopespace kai to offset opos to exei o sav */
void make_operand(expr* e, vmarg* arg){
    switch(e->type){
        case var_e:
        case tableitem_e:
        case arithexpr_e:
        case boolexpr_e:

        case newtable_e: {
            assert(e-sym);
            arg->val = e->sym->value.varVal->offset;

            switch(e->sym->value.varVal->scopespace){
                case programvar:    arg->type = global_a;   break;
                case functionlocal: arg->type = local_a;    break;
                case formalarg:     arg->type = formal_a;   break;
                default: assert(0);
            }
            break;
        }

        case constbool_e: {
            arg->val = e.content.boolConst;
            arg->type = bool_a;
            break;
        }

        case conststring_e: {
            arg->val = consts_newstring(e.content->strConst);
            arg->type = string_a; 
            break;
        }

        case constnum_e: {
            if(intConst == NULL)
                arg->val = consts_newnumber(e.content->doubleConst);
            else
                arg->val = consts_newnumber(e.content->intConst);
            
            arg->type = number_a;
            break;
        }

        case nil_e: arg->type = nil_a;  break;

        case programfunc_e: {
            arg->type = userfunc_a;
            arg->val = userfuncs_newfunc(e->sym); //slide 11 lec 14
            break;
        }

        case libraryfunc_e: {
            arg->type = libfunc_a;
            arg->val = libfuncs_newused(e->sym->name);
            break;
        }

        default: assert(0);
    }
}

void make_numberoperand(vmarg* arg, double val){
    arg->val = consts_newnumber(val);
    arg->type = number_a;
}

void make_booloperand(vmarg* arg, unsigned val){
    arg->val = val;
    arg->type = bool_a;
}

void make_retvaloperand(vmarg* arg){
    arg->type = retval_a;
}

void generate(vmopcode op, quad* q){
    instruction* t = malloc(sizeof(instruction));
    t->opcode = op;
    make_operand(q->arg1, t->arg1);
    make_operand(q->arg2, t->arg2);
    make_operand(q->result, t->result);
    quad->taddress = nextinstructionlabel(); // den yparxei to taddress alla logika einai o ari8mos tou current instruction ston pinaka apo instructions.
    emit_t(t);
}

void generate_ADD(quad* q) { generate(add_v, q); }
void generate_SUB(quad* q) { generate(sub_v, q); }
void generate_MUL(quad* q) { generate(mul_v, q); }
void generate_DIV(quad* q) { generate(div_v, q); }
void generate_MOD(quad* q) { generate(mod_v, q); }

void generate_TABLECREATE(quad* q)      { generate(tablecreate_v, q); }
void generate_TABLEGETELEM(quad* q)     { generate(tablegetelem_v, q); }
void generate_TABLESETELEM(quad* q)     { generate(tablesetelem_v, q); }
void generate_ASSIGN(quad *q)           { generate(assign_v, q); }

void generate_NOP(){
    instruction* t = malloc(sizeof(instruction));
    t->opcode = nop_v;
    emit_t(t);
}

void generate_relational(vmopcode op, quad* q){
    instruction* t = malloc(sizeof(instruction));
    t->opcode = op;
    make_operand(q->arg1, t->arg1);
    make_operand(q->arg2, t->arg2);

    t->result->type = label_a;
    if(q->label < currprocessedquad())
        t->result->value = quads[q->label].taddress; // taddress add in quad struct
    else   
        add_incomplete_jump(nextinstructionlabel(), q->label);
    q->taddress = nextinstructionlabel();
    emit_t(t);
}


void generate_tcode(unsigned total){
    for(unsigned i = 0; i < total; ++i){
        (*generators[quads[i]->iopcode])(quads[i]);
    }
}