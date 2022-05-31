#ifndef INSTRUCTION_HEADER
#define INSTRUCTION_HEADER

#include <stdio.h>
#include <stdlib.h>
#include "libs/SymTableEntry/SymTableEntry.h"
#include "instruction.h"
#include "libs/Vektor/Vektor.h"
#include "quads.h"
#include "expression.h"

void generate_ASSIGN(quad*);
void generate_ADD(quad*);
void generate_SUB(quad*);
void generate_MUL(quad*);
void generate_DIV(quad*);
void generate_MOD(quad*);
void generate_UMINUS(quad*);
void generate_AND(quad*);
void generate_OR(quad*);
void generate_NOT(quad*);
void generate_IF_EQ(quad*);
void generate_IF_NOTEQ(quad*);
void generate_IF_LESSEQ(quad*);
void generate_IF_GREATEREQ(quad*);
void generate_IF_LESS(quad*);
void generate_IF_GREATER(quad*);
void generate_CALL(quad*);
void generate_PARAM(quad*);
void generate_RETURN(quad*);
void generate_GETRETVAL(quad*);
void generate_FUNCSTART(quad*);
void generate_FUNCEND(quad*);
void generate_TABLECREATE(quad*);
void generate_TABLEGETELEM(quad*);
void generate_TABLESETELEM(quad*);
void generate_JUMP(quad*);
void generate_NOP(quad*);

typedef struct userfunc{
    unsigned address;
    unsigned localSize;
    const char* id;
} userfunc;

/* oi pinakes sta8eron gro8eeeeee */
Vektor*     numConsts;
Vektor*     stringConsts;
Vektor*     namedLibfuncs;
Vektor*     userFuncs;



typedef enum vmopcode{
    assign_v,       add_v,          sub_v,
    mul_v,          div_v,          mod_v,
    uminus_v,       and_v,          or_v,
    not_v,          jeq_v,          jne_v,
    jle_v,          jge_v,          jlt_v,
    jgt_v,          call_v,         pusharg_v,
    ret_v,          getretval_v,    funcstart_v,    
    funcend_v,      tablecreate_v,  tablegetelem_v, 
    tablesetelem_v, jump_v,         nop_v 
} vmopcode;

typedef enum vmarg_t{
    label_a     =0,
    global_a    =1,
    formal_a    =2,
    local_a     =3,
    number_a    =4,
    string_a    =5,
    bool_a      =6,
    nil_a       =7,
    userfunc_a  =8,
    libfunc_a   =9,
    retval_a    =10
} vmarg_t;


typedef struct vmarg{
    vmarg_t type;
    unsigned val;
} vmarg;

typedef struct instruction{
    vmopcode opcode;
    vmarg* result;
    vmarg* arg1;
    vmarg* arg2;
    unsigned srcLine;
} instruction;


typedef void (*generator_func_t)(quad*);
void quad_to_instruction(void* void_quad);
void make_operand(expr*, vmarg*);
void reset_operand(vmarg*);

void print_instruction(void* void_inst);

/*
typedef struct incomplete_jump {
    unsigned            instrNo; // The jump instruction number.
    unsigned            iaddress; // The i-code jump-target address
    struct incomplete_jump*    next;
} incomplete_jump;

incomplete_jump*    ij_head = NULL;
unsigned            ij_total = 0;
*/

void add_incomplete_jump(unsigned instrNo, unsigned iaddress);
void patch_incomplete_jumps();

void emit_t(instruction* t);

#endif