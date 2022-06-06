#include"../avm.h"

execute_func_t executeFuncs[] = {
    execute_assign,         //0
    execute_add,            //1
    execute_sub,            //2
    execute_mul,            //3
    execute_div,            //4
    execute_mod,            //5
    execute_uminus,         //6
    execute_and,            //7
    execute_or,             //8
    execute_not,            //9
    execute_jeq,            //10
    execute_jne,            //11
    execute_jle,            //12
    execute_jge,            //13
    execute_jlt,            //14
    execute_jgt,            //15
    execute_call,           //16
    execute_pusharg,        //17
    execute_return,         //18
    execute_getretval,      //19
    execute_funcenter,      //20
    execute_funcexit,       //21
    execute_newtable,       //22
    execute_tablegetelem,   //23
    execute_tablesetelem,   //24
    execute_jump,           //25
    execute_nop             //26
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
        //printf("instr opcode = %d\n", instr->opcode);
        //printf("top : %d , topsp : %d\n",top,topsp);
        CHECK_TOP_STACK //checks for stack over flow or under flow
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