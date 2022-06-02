#ifndef AVM_HEADER
#define AVM_HEADER
#include <stdio.h>
#include "../instruction.h"


typedef enum avm_memcell_t {
    number_m    = 0;
    string_m    = 1;
    bool_m      = 2;
    table_m     = 3;
    userfunc_m  = 4;
    libfunc_m   = 5;
    nil_m       = 6;
    undef_m     = 7;
} avm_memcell_t;

avm_table*      avm_tablenew(void);
void            avm_tabledestroy(avm_table* t);
avm_memcell*    avm_tablegetelem(avm_memcell* key);
void            avm_tablesetelem(avm_memcell* key, avm_memcell* value);

#define AVM_TABLE_HASHSIZE  211

typedef struct avm_table_bucket {
    avm_memcell         key;
    avm_memcell         value;
    avm_table_bucket*   next;
} avm_table_bucket;


/*  For simplicity, we only show support for numeric and
    string keys. Bonus for teams implementing keys
    for user functions, library functions and booleans.
*/
typedef struct avm_table{
    unsigned refCounter;
    avm_table_bucket*   strIndexed[AVM_TABLE_HASHSIZE];
    avm_table_bucket*   numIndexed[AVM_TABLE_HASHSIZE];
    unsigned            total;
} avm_table;

typedef struct avm_memcell {
    avm_memcell_t type;
    union {
        double          numVal;
        char*           strVal;
        unsigned char   boolVal;
        avm_table*      tableVal;
        unsigned        funcVal;
        char*           libfuncVal;
    } data;
} avm_memcell;

#define AVM_STACKSIZE   4096;
#define AVM_WIPEOUT(m)  memset(&(m), 0, sizeof(m))

avm_memcell stack[AVM_STACKSIZE];

static void avm_initstack(void){
    for(unsigned i = 0; i < AVM_STACKSIZE; ++i){
        AVM_WIPEOUT(stack[i]);
        stack[i].type = undef_m;
    }
}

typedef void (*execute_func_t) (instruction*);

#define AVM_MAX_INSTRUCTIONS (unsigned) nop_v

void execute_assign(instruction*);
void execute_add(instruction*);
void execute_sub(instruction*);
void execute_mul(instruction*);
void execute_div(instruction*);
void execute_mod(instruction*);
void execute_uminus(instruction*);
void execute_and(instruction*);
void execute_or(instruction*);
void execute_not(instruction*);
void execute_jeq(instruction*);
void execute_jne(instruction*);
void execute_jle(instruction*);
void execute_jge(instruction*);
void execute_jlt(instruction*);
void execute_jgt(instruction*);
void execute_call(instruction*);
void execute_pusharg(instruction*);
void execute_return(instruction*);
void execute_getretval(instruction*);
void execute_funcenter(instruction*);
void execute_funcexit(instruction*);
void execute_newtable(instruction*);
void execute_tablegetelem(instruction*);
void execute_tablesetelem(instruction*);
void execute_jump(instruction*);
void execute_nop(instruction*);

execute_func_t executeFuncs[] = {
    execute_assign,
    execute_add,
    execute_sub,
    execute_mul,
    execute_div,
    execute_mod,
    execute_uminus,
    execute_and,
    execute_or,
    execute_not,
    execute_jeq,
    execute_jne,
    execute_jle,
    execute_jge,
    execute_jlt,
    execute_jgt,
    execute_call,
    execute_pusharg,
    execute_return,
    execute_getretval,
    execute_funcenter,
    execute_funcexit,
    execute_newtable,
    execute_tablegetelem,
    execute_tablesetelem,
    execute_jump,
    execute_nop
};

typedef void (*memclear_func_t) (avm_memcell*);

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









#endif