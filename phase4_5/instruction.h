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

struct userfunc{
    unsigned address;
    unsigned localSize;
    char* id;
};


/* oi pinakes sta8eron gro8eeeeee */
double*     numConsts;
unsigned    totalNumConsts;
char**      stringConsts;
unsigned    totalStringConsts;
char**      namedLibfuncs;
userfunc*   userFuncs;
unsigned    totalUserFuncs;



typedef enum vmopcode{
    assign_v,       add_v,          sub_v,
    mul_v,          div_v,          mod_v,
    uminus_v,       and_v,          or_v,
    not_v,          jeq_v,          jne_v,
    jle_v,          jge_v,          jlt_v,
    jgt_v,          call_v,         pusharg_v,
    ret_v,          funcstart_v,    funcend_v,      
    tablecreate_v,  tablegetelem_v, tablesetelem_v, 
    jump_v,         nop_v 
} vmopcode;

enum vmarg_t{
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
};


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
void make_operand(expr*, vmarg*);


generator_func_t generators[] = {
    generate_ASSIGN,
    generate_ADD,
    generate_SUB,
    generate_MUL,
    generate_DIV,
    generate_MOD,
    generate_UMINUS,
    generate_AND,
    generate_OR,
    generate_NOT,
    generate_IF_EQ,
    generate_IF_NOTEQ,
    generate_IF_LESSEQ,
    generate_IF_GREATEREQ,
    generate_IF_LESS,
    generate_IF_GREATER,
    generate_CALL,
    generate_PARAM,
    generate_RETURN,
    generate_GETRETVAL,
    generate_FUNCSTART,
    generate_FUNCEND,
    generate_TABLECREATE,
    generate_TABLEGETELEM,
    generate_TABLESETELEM,
    generate_JUMP,
    generate_NOP
};

struct incomplete_jump {
    unsigned            instrNo; // The jump instruction number.
    unsigned            iaddress; // The i-code jump-target address
    incomplete_jump*    next;
};

incomplete_jump*    ij_head = NULL;
unsigned            ij_total = 0;

void add_incomplete_jump(unsigned instrNo, unsigned iaddress);
void patch_incomplete_jumps();