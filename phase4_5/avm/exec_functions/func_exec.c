#include"../avm.h"
#include"../read_binary/read_binary.h"
#include<math.h>
#include<ctype.h>

void execute_call(instruction* instr){
    avm_memcell* func = avm_translate_operand(instr->result, &ax);
    assert(func);
    avm_callsaveenvironment();

    switch(func->type){

        case userfunc_m: {
            pc = userfuncs[func->data.funcVal].address;
            //pc = func->data.funcVal; // sto funcVal apothikeuoume pu prepei na ginei to jump
            assert(pc < AVM_ENDING_PC);
            //printf("pc = %d\n", pc);
            assert(code[pc].opcode == enterfunc_v);
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
            printf("kane edo to avm_error!top = %d, topsp = %d\n",top,topsp);
            free(s);
            executionFinished = 1;
        }
    }
}

void execute_funcenter(instruction* instr){
    avm_memcell* func = avm_translate_operand(instr->result, &ax);
    assert(func);
    assert(pc == userfuncs[func->data.funcVal].address);

    totalActuals = 0;
    userfunc* funcInfo = avm_getfuncinfo(pc);
    topsp = top;
    top = top - funcInfo->localSize;
}


unsigned avm_get_envvalue(unsigned i){  
    assert(avm_stack[i].type == number_m); 
    unsigned val = (unsigned)avm_stack[i].data.numVal;
    assert(avm_stack[i].data.numVal == ((double)val));
    return val;
}

void execute_funcexit(instruction* unused){
    unsigned oldTop = top;
    top = avm_get_envvalue(topsp+ AVM_SAVEDTOP_OFFSET);
    pc = avm_get_envvalue(topsp+ AVM_SAVEDPC_OFFSET);
    topsp = avm_get_envvalue(topsp+ AVM_SAVEDTOPSP_OFFSET);
    while(++oldTop < top){
        avm_memcellclear(&avm_stack[oldTop]);
    }
}




void avm_calllibfunc(char* id){
    library_func_t f = avm_getlibraryfunc(id);
    if(!f){
        char tmp[1024];
        sprintf(tmp, "unsupported lib func '%s' called!", id);
        avm_error(tmp);
        executionFinished = 1;
    }
    else{
        topsp = top;
        totalActuals = 0;
        (*f)();
        if(!executionFinished){
            execute_funcexit((instruction*)0);
        }
    }
}

unsigned avm_totalactuals(void){
    return avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET);
}

avm_memcell* avm_getactual(unsigned i){
    assert(i < avm_totalactuals());
    return &avm_stack[topsp + AVM_STACKENV_SIZE + i +1];
}

void avm_registerlibfunc(char* id, library_func_t addr);

void execute_pusharg(instruction* instr){
    avm_memcell* arg = avm_translate_operand(instr->result, &ax);
    assert(arg);
    //assert(top > 0);
    //avm_stack_push(&avm_stack[top],arg);
    avm_assign(&avm_stack[top],arg);
    ++totalActuals;
    avm_dec_top();
}

//libfuncs

void libfunc_print(void){
    unsigned n = avm_totalactuals();
    for(unsigned i = 0; i < n ; i++){
        avm_memcell *arg = avm_getactual(i);
        char* s = avm_tostring(arg);
        switch(arg->type){
            case userfunc_m:
                printf("userfunction: %d", userfuncs[arg->data.funcVal].address);
                break;
            case libfunc_m:
                printf("library function: %s",s);
                break;
            case table_m:
                printf("tables not yet supported");  //TODO na ektipwnw ta content tu
                break;
            case number_m:
                printf("%.3f", arg->data.numVal);
                break;
            default:
                printf("%s", s);
                break;
        }
        
        free(s);
    }
    printf("\n");
}

void libfunc_typeof(void){
    unsigned n = avm_totalactuals();
    if(n != 1){
        char tmp[1024];
        sprintf(tmp, "one argument (not %d) expected in 'typeof'!", n);
        avm_error(tmp);
        retval.type=nil_m;
    }else{
        avm_memcellclear(&retval);
        retval.type = string_m;
        retval.data.strVal = strdup(typeStrings[avm_getactual(0)->type]);
    }
}

void libfunc_totalarguments(void){
    unsigned p_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
    avm_memcellclear(&retval);
    if(!p_topsp){
        avm_error("'totalarguments' called outside a function!");
        retval.type = nil_m;
    }else{
        retval.type = number_m;
        retval.data.numVal = avm_get_envvalue(p_topsp + AVM_NUMACTUALS_OFFSET);
    }
}


void libfunc_sqrt(void){
    unsigned n = avm_totalactuals();
    if(n != 1){
        char tmp[1024];
        sprintf(tmp, "one argument (not %d) expected in 'sqrt'!", n);
        avm_error(tmp);
        retval.type=nil_m;
    }else if (avm_getactual(0)->type != number_m){
        avm_error("'sqrt' requires a number as parameter!");
        retval.type=nil_m;
    }else if(avm_getactual(0)->data.numVal < 0){
        avm_error("'sqrt' requires a non-negative number as parameter!");
        retval.type=nil_m;
    }else{
        avm_memcellclear(&retval);
        retval.type = number_m;
        double tmp = avm_getactual(0)->data.numVal;
        retval.data.numVal = sqrt(tmp);
    }
}




#define PI 3.14159265358979323846
void libfunc_cos(void){
    unsigned n = avm_totalactuals();
    if(n != 1){
        char tmp[1024];
        sprintf(tmp, "one argument (not %d) expected in 'cos'!", n);
        avm_error(tmp);
        retval.type=nil_m;
    }
    else if(avm_getactual(0)->type != number_m){
        avm_error("library function cos accepts only numbers as parameter!");
        retval.type=nil_m;
    }
    else{
        avm_memcellclear(&retval);
        retval.type = number_m;
        double tmp = avm_getactual(0)->data.numVal;
        
        retval.data.numVal = cos((tmp*PI)/180);
    }    
}

void libfunc_sin(void){
    unsigned n = avm_totalactuals();
    if(n != 1){
        char tmp[1024];
        sprintf(tmp, "one argument (not %d) expected in 'sin'!", n);
        avm_error(tmp);
        retval.type=nil_m;
    }
    else if(avm_getactual(0)->type != number_m){
        avm_error("library function sin accepts only numbers as parameter!");
        retval.type=nil_m;
    }
    else{
        avm_memcellclear(&retval);
        retval.type = number_m;
        double tmp = avm_getactual(0)->data.numVal;
        retval.data.numVal = sin((tmp*PI)/180);
    }    
}

void libfunc_strtonum(void){
    unsigned n = avm_totalactuals();
    if(n != 1){
        char tmp[1024];
        sprintf(tmp, "one argument (not %d) expected in 'strtonum'!", n);
        avm_error(tmp);
        retval.type=nil_m;
    }
    else if(avm_getactual(0)->type != string_m){
        avm_error("library function strtonum accepts only strings as parameter!");
        retval.type=nil_m;
    }
    else{
        avm_memcellclear(&retval);
        retval.type = number_m;
        char* tmp = avm_getactual(0)->data.strVal;
        int flag = 0;
        for(int i = 0 ; i < strlen(tmp) ; i++){
            if(tmp[i]=='.'){
                flag ++;
            }else if(!isdigit(tmp[i])){
                avm_error("library function strtonum accepts only numbers as parameter!");
                retval.type=nil_m;
                return;
            }
            if(flag==2){
                avm_error("strtonum error found more than one '.' in the string!");
                retval.type=nil_m;
                return;
            }
        }
        retval.data.numVal = atof(tmp);
    }    
}

int is_number(char * str){
    int flag = 0;
    for(int i = 0 ; i < strlen(str) ; i++){
        if(str[i]=='.'){
            flag ++;
        }else if(!isdigit(str[i])){
            return 0;
        }
        if(flag==2){
            return 0;
        }
    }
    return 1;
}

void libfunc_input(void){
    unsigned n = avm_totalactuals();
    if(n != 0){
        char tmp[1024];
        sprintf(tmp, "%d arguments ignored , no arguments needed in 'input'!", n);
        avm_warning(tmp);
    }
    char *s = malloc(sizeof(char)*1024);
    size_t i = 0;
    while(i!=1024){
        s[i]=getc(stdin);
        if(s[i]=='\n'){
            s[i]='\0';
            break;
        }
        i++;
    }
    if(i == 1024){
        avm_error("input error: string is too long!");
        retval.type=nil_m;
        return;
    }
    avm_memcellclear(&retval);
    if(strcmp(s, "true")==0){
        retval.type = bool_m;
        retval.data.boolVal = 1;
    }else if(strcmp(s, "false")==0){
        retval.type = bool_m;
        retval.data.boolVal = 0;
    }else if(strcmp(s,"nil")==0){
        retval.type = nil_m;
    }else if (is_number(s)){
        retval.type = number_m;
        retval.data.numVal = atof(s);
    }else{
        retval.type = string_m;
        retval.data.strVal = strdup(s);
    }
    
}


// DOESNT WORK
void libfunc_argument(void){
    unsigned n = avm_totalactuals();
    unsigned p_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
    if(n != 1){
        char tmp[1024];
        sprintf(tmp, "one argument (not %d) expected in 'argument'!", n);
        avm_error(tmp);
        retval.type=nil_m;
    }
    else if (avm_getactual(0)->type != number_m){
        avm_error("library function argument accepts only numbers as parameter!");
        retval.type=nil_m;
    }
    else{
        //avm_memcell* test = avm_getactual(0);
        //printf("%f\n", test->data.numVal);
        
        unsigned arg = avm_getactual(0)->data.numVal;
        if(avm_get_envvalue(top + AVM_SAVEDTOP_OFFSET) - arg > p_topsp){
            avm_error("library function argument error: argument out of range!");
            retval.type=nil_m;
            return;
        }
        avm_memcell* test1 = &avm_stack[p_topsp + AVM_STACKENV_SIZE + arg];
        
        avm_memcellclear(&retval);
        
        retval = *test1;
        //retval.data.numVal = avm_get_envvalue(p_topsp + AVM_STACKENV_SIZE + arg);
        
    }
}