#include "libs/scopelist/scopelists.h"
#include "libs/SymTableEntry/SymTableEntry.h"
#include "libs/symtable/symtable.h"
#include "libs/zarkList/zarkList.h"
#include "expression.h"
#include "parser.h"
#include "libs/stack/stack.h"
#include "libs/Vektor/Vektor.h"
#include "expression.h" 
#include "instruction.h"
#include "quads.h"
#include "scanner.h"

SymTable_T symTable;
scopeArray* scpArr;
Vektor* instructions;
Vektor* quads;
FILE* quads_out;
FILE* instructions_out;
FILE* binary;
alpha_stack* anon_func_names_stack; 
alpha_stack* invalid_funcname_number_stack;
alpha_stack* loopcounter_stack;
alpha_stack* func_init_jump_stack;
Vektor*     numConsts;
Vektor*     stringConsts;
Vektor*     namedLibfuncs;
Vektor*     userFuncs;

//gia offset
alpha_stack* function_local_offset_stack;
alpha_stack* funcstart_label_stack;

extern int programvar_offset;

scopeArray* globalScopeArr;

char libraryFunctions[12][24]={
    "print",
    "input",
    "objectmemberkeys",
    "objecttotalmembers",
    "objectcopy",
    "totalarguments",
    "argument",
    "typeof",
    "strtonum",
    "sqrt",
    "cos",
    "sin"
};

void print_string(void * void_str, int i) {
    char* s = (char*) void_str, nl = '\n';
    fprintf(instructions_out, "%d: \"%s\"\n", i, s);
    fwrite(s, sizeof(char), strlen(s)+1, binary);
    //fwrite(&nl, sizeof(char), 1, binary);
    //fprintf(binary, "\"%s\"", s);
    //fputc('\0', binary);
    //fputc('\n', binary);
}

void print_double(void* void_double, int i){
    double* num = (double*) void_double;
    char nl = '\n';
    fprintf(instructions_out, "%d: %lf\n", i, *num);
    fwrite(num, sizeof(double), 1, binary);
    //fwrite(&nl, sizeof(char), 1, binary);
    //fprintf(binary, "%lf\n", *num);
}

void print_userfunc(void* void_func, int i) {
    userfunc* uf = (userfunc*) void_func;
    char nl = '\n';
    fprintf(instructions_out, "%d: address %d, local size %d, id \"%s\"\n", i, uf->address, uf->localSize, uf->id);
    //fprintf(binary, "%d %d \"%s\"\n", uf->address, uf->localSize, uf->id);
    fwrite(&uf->address, sizeof(unsigned), 1, binary);
    fwrite(&uf->localSize, sizeof(unsigned), 1, binary);
    fwrite(uf->id, sizeof(char), strlen(uf->id)+1, binary);
    //fwrite(&nl, sizeof(char), 1, binary);
}

int main(int argc, char *argv[]){
    quads_out = fopen("quads_output.txt", "w"); 

    // initialize necessary global structures
	symTable = SymTable_new();
	scpArr = scope_initialize();
	globalScopeArr = scope_initialize();
    quads = vektor_initialize();
    instructions = vektor_initialize();
    numConsts = vektor_initialize();
    stringConsts = vektor_initialize();
    namedLibfuncs = vektor_initialize();
    userFuncs = vektor_initialize();
    anon_func_names_stack = alpha_stack_init();
    invalid_funcname_number_stack = alpha_stack_init();
    loopcounter_stack= alpha_stack_init();
    func_init_jump_stack = alpha_stack_init();
    function_local_offset_stack = alpha_stack_init();
    funcstart_label_stack = alpha_stack_init();
    SymTableEntry* tmp;
    
    if (argc > 1)
    {
        if (!(yyin = fopen(argv[1], "r")))
        {
            fprintf(stderr, "Cannot read file: %s\n", argv[1]);
            return 1;
        }
    }
    else
    {
        yyin = stdin;
    }

    /* Putting all the library functions in the SymTable */
    for (int i = 0; i < 12; i++){
        //char *key = strdup(libraryFunctions[i]);
        tmp = makeSymTableEntry(libraryFunctions[i], NULL, 0, 0, LIBFUNC, 0, 0);
        SymTable_put(symTable, libraryFunctions[i], (void*)tmp);
        insert_to_scopeArr(&scpArr,0,tmp);
    }

    yyparse();
    puts("----------------Symbol Table Entries-------------------------");
    //SymTable_quickApply(symTable, printSymTableEntry);
    int len = globalScopeArr->size;
    for(int i = 0; i < len; i++) {
        if(globalScopeArr->scopes[i]->size != 0) {
            char scopeStr[1024];
            sprintf(scopeStr, "\n-----------\tScope #%d\t-----------", i);
            puts(scopeStr);
            zarklist_apply(globalScopeArr->scopes[i], printSymTableEntry);
        }
    }
    
    fprintf(quads_out,"Number of quads -> %d\n", quads->cur_size-1);
    //quads_out = stdout;
    //puts("quad#\t\topcode\t\t\t\t\t  result\t\targ1\t\targ2\t\tlabel");
    fprintf(quads_out,"quad#\t\topcode\t\t\t\t\t  result\t\targ1\t\targ2\t\tlabel\n");
    vektor_apply(quads, print_quad);
    fclose(quads_out);

    vektor_apply(quads, quad_to_instruction);
    printf("sizes:\n");
    printf("%d\n", quads->max_size);
    printf("%d\n",instructions->max_size);
    printf("%d\n",numConsts->max_size);
    printf("%d\n",stringConsts->max_size);
    printf("%d\n",namedLibfuncs->max_size);
    printf("%d\n",userFuncs->max_size);
    printf("totalQuads=%d\n", quads->cur_size-1);
    printf("totalInsts=%d\n", instructions->cur_size-1);

    instructions_out = fopen("instructions_output.txt", "w");
    binary = fopen("binary.abc", "w");
    fprintf(instructions_out, "magicnumber: %ld\n", (long int) 133780085); // magicnumber
    //fprintf(binary, "%ld\n", (long int) 133780085); // magicnumber
    long int magic_number = 133780085;
    fwrite(&magic_number, sizeof(long int), 1, binary);
    fwrite(&programvar_offset, sizeof(int), 1, binary);
    // printf("PROGRAM_VAR_OFFSET:%d\n", programvar_offset);

    fprintf(instructions_out, "*********** NUMCONSTS ***********\n");
    fprintf(instructions_out, "numConsts: %d\n", numConsts->cur_size);
    //fprintf(binary, "%d\n", numConsts->cur_size);
    fwrite(&numConsts->cur_size, sizeof(int), 1, binary);
    vektor_apply2(numConsts, print_double);
    
    fprintf(instructions_out, "*********** STRCONSTS ***********\n");
    fprintf(instructions_out, "stringConsts: %d\n", stringConsts->cur_size);
    //fprintf(binary, "%d\n", stringConsts->cur_size);
    fwrite(&stringConsts->cur_size, sizeof(int), 1, binary);
    vektor_apply2(stringConsts, print_string);
    
    fprintf(instructions_out, "*********** LIBFUNCS ***********\n");
    fprintf(instructions_out, "namedLibFuncs: %d\n", namedLibfuncs->cur_size);
    //fprintf(binary, "%d\n", namedLibfuncs->cur_size);
    fwrite(&namedLibfuncs->cur_size, sizeof(int), 1, binary);
    vektor_apply2(namedLibfuncs, print_string);
    
    fprintf(instructions_out, "*********** USERFUNCS ***********\n");
    fprintf(instructions_out, "userFuncs: %d\n", userFuncs->cur_size);
    //fprintf(binary, "%d\n", userFuncs->cur_size);
    fwrite(&userFuncs->cur_size, sizeof(int), 1, binary);
    vektor_apply2(userFuncs, print_userfunc);
    fprintf(instructions_out, "*********************************\n\n");

    fprintf(instructions_out, "############### INSTRUCTIONS #################\n");
    fprintf(instructions_out, "totalInsts=%d\n", instructions->cur_size-1);
    vektor_apply2(instructions, print_instruction);
    //fprintf(binary, "%d\n", instructions->cur_size-1);
    int tmp_tmp = instructions->cur_size-1;
    fwrite(&tmp_tmp, sizeof(int), 1, binary);
    vektor_apply(instructions, instruction_to_binary);

    fclose(instructions_out);
    fclose(binary);

    SymTable_free(symTable);
    free_scopeArr(scpArr);
    free_scopeArr(globalScopeArr);
    return 24;
}