#include"../avm.h"

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
        instruction* instr = &code[pc]; // NA DW GIATI KANW &
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

// USELESS, i.e. will never be used by the program
void execute_nop (instruction* instr) { assert(0); return; }
void execute_getretval (instruction* instr) { assert(0); return; }
void execute_return (instruction* instr) { assert(0); return; }