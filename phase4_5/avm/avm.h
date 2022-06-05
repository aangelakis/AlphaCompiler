#ifndef AVM_HEADER
#define AVM_HEADER
#include <stdio.h>
#include "../instruction.h"

typedef enum avm_memcell_t {
    number_m    = 0,
    string_m    = 1,
    bool_m      = 2,
    table_m     = 3,
    userfunc_m  = 4,
    libfunc_m   = 5,
    nil_m       = 6,
    undef_m     = 7
} avm_memcell_t;

#define AVM_TABLE_HASHSIZE  211
#define AVM_ENDING_PC   codeSize
#define AVM_STACKENV_SIZE   4
#define AVM_NUMACTUALS_OFFSET +4
#define AVM_SAVEDPC_OFFSET +3
#define AVM_SAVEDTOP_OFFSET +2
#define AVM_SAVEDTOPSP_OFFSET +1

/*  For simplicity, we only show support for numeric and
    string keys. Bonus for teams implementing keys
    for user functions, library functions and booleans.
*/
typedef struct avm_table avm_table;

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

typedef struct avm_table_bucket {
    avm_memcell         key;
    avm_memcell         value;
    struct avm_table_bucket*   next;
} avm_table_bucket;

struct avm_table{
    unsigned refCounter;
    avm_table_bucket*   strIndexed[AVM_TABLE_HASHSIZE];
    avm_table_bucket*   numIndexed[AVM_TABLE_HASHSIZE];
    unsigned            total;
};

avm_table*      avm_tablenew(void);
void            avm_tabledestroy(avm_table* t);
avm_memcell*    avm_tablegetelem(avm_memcell* key);
void            avm_tablesetelem(avm_memcell* key, avm_memcell* value);


//GIA STACK
#define AVM_STACKSIZE   4096
#define AVM_WIPEOUT(m)  memset(&(m), 0, sizeof(m))
extern avm_memcell avm_stack[AVM_STACKSIZE];

typedef void (*execute_func_t) (instruction*);

#define AVM_MAX_INSTRUCTIONS (unsigned) nop_v

void execute_assign(instruction*);
void execute_add(instruction*);
void execute_sub(instruction*);
void execute_mul(instruction*);
void execute_div(instruction*);
void execute_mod(instruction*);
void execute_uminus(instruction*);      // USELESS
void execute_and(instruction*);         // USELESS
void execute_or(instruction*);          // USELESS
void execute_not(instruction*);         // USELESS
void execute_jeq(instruction*); 
void execute_jne(instruction*);
void execute_jle(instruction*);
void execute_jge(instruction*);
void execute_jlt(instruction*);
void execute_jgt(instruction*);
void execute_call(instruction*);
void execute_pusharg(instruction*);
void execute_return(instruction*);      // USELESS
void execute_getretval(instruction*);   // USELESS
void execute_funcenter(instruction*);
void execute_funcexit(instruction*);
void execute_newtable(instruction*);
void execute_tablegetelem(instruction*);
void execute_tablesetelem(instruction*);
void execute_jump(instruction*);
void execute_nop(instruction*);         // USELESS

extern execute_func_t executeFuncs[];

typedef void (*memclear_func_t) (avm_memcell*);

extern memclear_func_t memclearFuncs[];

// memclear_func_t memclearFuncs[] = {
//     0,  /* number */
//     memclear_string,
//     0,  /* bool */
//     memclear_table,
//     0,  /* userfunc */
//     0,  /* libfunc */
//     0,  /* nil */
//     0   /* undef */
// };

#define AVM_STACKENV_SIZE 4
extern avm_memcell ax, bx, cx;
extern avm_memcell retval;
extern unsigned top, topsp;



extern unsigned char   executionFinished;
extern unsigned        pc ;
extern unsigned        currLine ;
extern unsigned        codeSize ;
extern instruction*    code ;
extern unsigned totalActuals ;


extern char* typeStrings[];

void avm_initstack(void);

void execute_cycle();

avm_memcell* avm_translate_operand(vmarg* arg, avm_memcell* reg);

void avm_calllibfunc(char* id);
#endif