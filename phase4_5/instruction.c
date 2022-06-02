#include "instruction.h"

unsigned int currInstruction = 1;
extern Vektor* instructions;
extern Vektor*     numConsts;
extern Vektor*     stringConsts;
extern Vektor*     namedLibfuncs;
extern Vektor*     userFuncs;
extern FILE*       instructions_out;


/* to stack gia ta funcstart*/
extern alpha_stack* funcstart_label_stack;

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

char instruction_opcode_names[27][15] = {
    "assign_v",       "add_v",          "sub_v",
    "mul_v",          "div_v",          "mod_v",
    "uminus_v",       "and_v",          "or_v",
    "not_v",          "jeq_v",          "jne_v",
    "jle_v",          "jge_v",          "jlt_v",
    "jgt_v",          "callfunc_v",     "pusharg_v",
    "ret_v",          "getretval_v",    "enterfunc_v",    
    "exitfunc_v",     "tablecreate_v",  "tablegetelem_v", 
    "tablesetelem_v", "jump_v",         "nop_v" 
};

char vmarg_type_names[11][15] = {
    "label_a",      "global_a",         "formal_a",
    "local_a",      "number_a",         "string_a",
    "bool_a",       "nil_a",            "userfunc_a",
    "libfunc_a",    "retval_a"
};

void push_funcstart_label(){
    int *tmp = malloc(sizeof(int));
    *tmp = vektor_active_size(userFuncs) -1;
    stack_push(funcstart_label_stack,(int*)tmp);
}

int pop_funcstart_label(){
    int *tmp = (int*)stack_pop(funcstart_label_stack);
    int ret = *tmp;
    free(tmp);
    return ret;
}

unsigned consts_newstring(char* s);
unsigned consts_newnumber(double n);
unsigned libfuncs_newused(const char* s);
unsigned userfuncs_newfunc(SymTableEntry* sym);

unsigned consts_newstring(char *s){
    char* tmp_s = strdup(s);
    vektor_add(stringConsts, tmp_s);
    return (vektor_active_size(stringConsts) - 1); // returning the index
}

unsigned consts_newnumber(double n){
    double* tmp_n = malloc(sizeof(double));
    *tmp_n = n;
    vektor_add(numConsts, tmp_n);
    return (vektor_active_size(numConsts) - 1);
}

unsigned libfuncs_newused(const char* s){
    char* tmp_s = strdup(s);
    vektor_add(namedLibfuncs, tmp_s);
    return (vektor_active_size(namedLibfuncs) - 1);
}

unsigned userfuncs_newfunc(SymTableEntry* sym){
    //assert(symtable(, sym->value.funcVal->name));
    assert(sym);
    userfunc* f = malloc(sizeof(userfunc));
    f->id = sym->value.funcVal->name;
    f->localSize = sym->value.funcVal->numOfLocalVars;
    f->address = sym->value.funcVal->quadfuncStartIndex;
    vektor_add(userFuncs, f);
    push_funcstart_label();
    return (vektor_active_size(userFuncs) - 1);
}

unsigned nextinstructionlabel(){
    return currInstruction;
}


void reset_operand(vmarg* arg){
    arg->val = 0;
}


/* isos baloume sto symtableentry ekei to scopespace kai to offset opos to exei o sav */
void make_operand(expr* e, vmarg* arg){
    switch(e->type){
        case var_e:
        case tableitem_e:
        case arithexpr_e:
        case boolexpr_e:
        case assignexpr_e:

        case newtable_e: {
            printf("Type=%d\n", e->type);
            assert(e->sym);
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
            arg->val = e->content.boolConst;
            arg->type = bool_a;
            break;
        }

        case conststring_e: {
            arg->val = consts_newstring(e->content.strConst);
            arg->type = string_a; 
            break;
        }

        case constint_e: {
            arg->val = consts_newnumber(e->content.intConst);
            arg->type = number_a;
            break;
        }

        case constdouble_e: {
            arg->val = consts_newnumber(e->content.doubleConst);
            arg->type = number_a;
            break;
        }

        case nil_e: arg->type = nil_a;  break;

        case programfunc_e: {
            arg->type = userfunc_a;
            arg->val = userfuncs_newfunc(e->sym); 
            break;
        }

        case libraryfunc_e: {
            arg->type = libfunc_a;
            arg->val = libfuncs_newused(e->sym->value.funcVal->name);
            break;
        }

        default: {
            if(e->type == assignexpr_e)
                puts("There is an assignment here");
            else
                printf("Type=%d", e->type);
            assert(0);
        }
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
    arg->val = -1;
}

static int times_here = 1;
void emit_t(instruction* t){
    assert(t);
    //printf("instruction's opcode-> %d\n", t->opcode);
    vektor_set_element(instructions, currInstruction++, (void*) t);
}

void generate(vmopcode op, quad* q){
    instruction* t = malloc(sizeof(instruction));
    t->opcode = op;
    t->srcLine = q->source_code_line;
    t->arg1 = NULL;
    t->arg2 = NULL;
    t->result = NULL;

    if(q->arg1) {
        t->arg1 = malloc(sizeof(vmarg));
        make_operand(q->arg1, t->arg1);
    }
    if(q->arg2) {
        t->arg2 = malloc(sizeof(vmarg));
        make_operand(q->arg2, t->arg2);
    }
    if(q->result) {
        t->result = malloc(sizeof(vmarg));
        make_operand(q->result, t->result);
    }

    //quad->taddress = nextinstructionlabel(); // (an xreiastei) den yparxei to taddress alla logika einai o ari8mos tou current instruction ston pinaka apo instructions.
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

void generate_NOP(quad* unused){
    instruction* t = malloc(sizeof(instruction));
    t->opcode = nop_v;
    t->arg1 = NULL;
    t->arg2 = NULL;
    t->result = NULL;
    emit_t(t);
}

void generate_UMINUS(quad* q){
    instruction* t = malloc(sizeof(instruction));
    t->opcode = mul_v;
    t->srcLine = q->source_code_line;  
    t->arg1 = NULL;
    t->arg2 = NULL;
    t->result = NULL;

    if(q->arg1){
        t->arg1 = malloc(sizeof(vmarg));
        make_operand(q->arg1, t->arg1);
    }

    t->arg2 = malloc(sizeof(vmarg));
    make_numberoperand(t->arg2, -1);
    
    if(q->result){
        t->result = malloc(sizeof(vmarg));
        make_operand(q->result, t->result);
    }
    
    emit_t(t);
}

void generate_AND(quad* q){
    return;
}

void generate_OR(quad* q){
    return;
}

void generate_NOT(quad* q){
    return;
}

void generate_relational(vmopcode op, quad* q){
    instruction* t = malloc(sizeof(instruction));
    t->opcode = op;
    t->srcLine = q->source_code_line;
    t->arg1 = NULL;
    t->arg2 = NULL;
    t->result = NULL;

    if(q->arg1){
        t->arg1 = malloc(sizeof(vmarg));
        make_operand(q->arg1, t->arg1);
    }
    if(q->arg2){
        t->arg2 = malloc(sizeof(vmarg));
        make_operand(q->arg2, t->arg2);
    }

    t->result = malloc(sizeof(vmarg));
    t->result->type = label_a;
    t->result->val = q->label; // na to doume me zarkouli
    emit_t(t);
}

void generate_JUMP(quad* q){
    generate_relational(jump_v, q);
}

void generate_IF_EQ(quad* q){
    generate_relational(jeq_v, q);
}

void generate_IF_NOTEQ(quad* q){
    generate_relational(jne_v, q);
}

void generate_IF_LESSEQ(quad* q){
    generate_relational(jle_v, q);
}

void generate_IF_GREATEREQ(quad* q){
    generate_relational(jge_v, q);
}

void generate_IF_LESS(quad* q){
    generate_relational(jlt_v, q);
}

void generate_IF_GREATER(quad* q){
    generate_relational(jgt_v, q);
}

void generate_CALL(quad* q){
    instruction* t = malloc(sizeof(instruction));
    t->opcode = callfunc_v;
    t->srcLine = q->source_code_line;
    t->arg1 = NULL;
    t->arg2 = NULL;
    t->result = NULL;
    if(q->result){
        t->result = malloc(sizeof(vmarg));
        make_operand(q->result, t->result);
    }
    emit_t(t);
}

void generate_PARAM(quad* q){
    instruction* t = malloc(sizeof(instruction));
    t->opcode = pusharg_v;
    t->srcLine = q->source_code_line;
    t->arg1 = NULL;
    t->arg2 = NULL;
    t->result = NULL;
    if(q->result){
        t->result = malloc(sizeof(vmarg));
        make_operand(q->result, t->result);
    }
    emit_t(t);
}

void generate_RETURN(quad* q){
    instruction* t = malloc(sizeof(instruction));
    t->opcode = assign_v;
    t->srcLine = q->source_code_line;
    t->arg1 = NULL;
    t->arg2 = NULL;
    t->result = NULL;

    t->result = malloc(sizeof(vmarg));
    make_retvaloperand(t->result);
    if(q->result){
        t->arg1 = malloc(sizeof(vmarg));
        make_operand(q->result, t->arg1);
    }
    emit_t(t);

    // EDW NA DOUME GIA TI STOIBA ME TA FUNCTIONS KAI TIN RETURNLIST 
    // f = top(funcstack);
    // append(f.returnList, nextinstructionlabel())
}

void generate_GETRETVAL(quad* q){
    instruction* t = malloc(sizeof(instruction));
    t->opcode = assign_v;
    t->srcLine = q->source_code_line;
    t->arg1 = NULL;
    t->arg2 = NULL;
    t->result = NULL;
    if(q->result){
        t->result = malloc(sizeof(vmarg));
        make_operand(q->result, t->result);
    }
    t->arg1 = malloc(sizeof(vmarg));
    make_retvaloperand(t->arg1);
    emit_t(t);
}

void generate_FUNCSTART(quad* q){

    SymTableEntry* f = q->result->sym;
    
    //userfuncs_newfunc(f);

    //push(funcstack, f);

    instruction* t = malloc(sizeof(instruction));
    t->opcode = enterfunc_v;
    t->srcLine = q->source_code_line;
    t->arg1 = NULL;
    t->arg2 = NULL;
    t->result = NULL;
    //printf("funcstart type of q->result: %d\n", q->result->type);
    if(q->result){
        t->result = malloc(sizeof(vmarg));
        make_operand(q->result, t->result);
    }
    emit_t(t);
}

void generate_FUNCEND(quad* q){
    //SymTableEntry f = pop(funcstack);
    //backpatch(f.returnList, nextinstructionlabel());
    //pop_funcstart_label();
    instruction* t = malloc(sizeof(instruction));
    t->opcode = exitfunc_v;
    t->srcLine = q->source_code_line;
    t->arg1 = NULL;
    t->arg2 = NULL;
    t->result = NULL;
    
    //printf("funcend type of q->result: %d\n", q->result->type);
    if(q->result){
        t->result = malloc(sizeof(vmarg));
        t->result->type = userfunc_a;
        t->result->val = pop_funcstart_label();
        //make_operand(q->result, t->result);
    }
    emit_t(t);
}

void quad_to_instruction(void* void_quad){
    if(void_quad == NULL){
        return;
    }
    printf("Times_here=%d\n", times_here++);
    quad* q = (quad*) void_quad;
    //printf("opcode: %d\n", q->op);
    generators[q->op](q);
    return;
}

void print_instruction(void* void_inst, int i) {
    if(void_inst == NULL) {
        //fprintf(instructions_out,"FOUND NULL\n"); 
        return;
    }

    instruction* instr = (instruction*) void_inst;
    vmarg* res = instr->result, *arg1 = instr->arg1, *arg2 = instr->arg2;

    char* opcode = instruction_opcode_names[instr->opcode];
    char* result_name = NULL, *arg1_name = NULL, *arg2_name = NULL; 
    int result_val = -1, arg1_val = -1, arg2_val = -1;
    
    fprintf(instructions_out,"%d: instruction: %s", i, opcode);
    if(res) {
        result_name = vmarg_type_names[res->type]; 
        result_val = res->val;
        fprintf(instructions_out," result:(%s, %d)", result_name, result_val);
    }
    if(arg1) {
        arg1_name = vmarg_type_names[arg1->type]; 
        arg1_val = arg1->val;
        fprintf(instructions_out," arg1:(%s, %d)", arg1_name, arg1_val);
    }
    if(arg2) {
        arg2_name = vmarg_type_names[arg2->type]; 
        arg2_val = arg2->val;
        fprintf(instructions_out," arg2:(%s, %d)", arg2_name, arg2_val);
    }
    fprintf(instructions_out, "\n");

    unsigned srcLine = instr->srcLine;
}