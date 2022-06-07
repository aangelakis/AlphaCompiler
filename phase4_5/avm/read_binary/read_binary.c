#include "read_binary.h"


//UNCOMMENT THIS TO SEE DEBUG PRINTS
//#define DEBUG_PRINTS_ON
#ifdef DEBUG_PRINTS_ON
#define DEBUG_PRINT(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...) do {} while (0)
#endif

//reads the next string from the file inbetween the quotes
char* make_string(){ 
    char tmp[1024];
    char* new_string = (char*) 0; 
    char c = fgetc(binary);
    if(c == '\n')
        c = fgetc(binary);
    
    int i = 0;
    for(; c; ++i) {
        //putchar(c);
        tmp[i] = c;
        c = fgetc(binary);
    }
    tmp[i] = (char) 0; 

    new_string = malloc(i);

    int j = 0;
    for( ;tmp[j]; ++j)
        new_string[j] = tmp[j];
    new_string[j] = tmp[j];
    assert(i == j);
    return new_string;
}

//reads the magic number and checks it
void get_magic_number(){
    long int magic_number;
    fread(&magic_number, sizeof(long int), 1, binary);
    DEBUG_PRINT("Magic number: %ld\n", magic_number);
    assert(magic_number == MAGIC_NUMBER_OFFSET);
}

//reads the number of constants
int get_size_of_consts(){
    int num;
    fread(&num, sizeof(int), 1, binary);
    DEBUG_PRINT("%d\n", num);
    return num;
}

//reads the whole number constant table
double * get_number_consts(int size){
    if(size == 0){return NULL;}
    double * consts = malloc(sizeof(double) * size);
    for(int i = 0; i < size; i++){
        fread(&consts[i], sizeof(double), 1, binary);
        DEBUG_PRINT("%lf\n", consts[i]);
    }
    return consts;
}

//reads the whole string constant table (strings/libfuncs/userfuncs)
char ** get_string_consts(int size){
    if(size == 0){return NULL;}

    char ** consts = malloc(sizeof(char*)*size);
    for(int i = 0; i < size; i++){
        consts[i] = make_string();
        DEBUG_PRINT("%s\n", consts[i]);
    }
    return consts;

}

//reads the userfunc consts
userfunc * get_userfunc_consts(int size){
    if(size==0){return NULL;}

    userfunc* consts = calloc(size ,sizeof(userfunc));
    for(int i = 0; i < size; i++){
        fread(&consts[i].address, sizeof(unsigned), 1, binary);
        DEBUG_PRINT("%u ", consts[i].address);
        fread(&consts[i].localSize, sizeof(unsigned), 1, binary);
        DEBUG_PRINT("%u ", consts[i].localSize);
        consts[i].id = make_string();
        DEBUG_PRINT("%s\n",  consts[i].id);
    }

    return consts;
}

//reads the instructions
instruction * get_instructions(int size){
    instruction * instructions = calloc(size+1, sizeof(instruction));
    for(int i = 1 ; i < size+1 ; i++){
        instructions[i].result = calloc(1, sizeof(vmarg));
        instructions[i].arg1 = calloc(1, sizeof(vmarg));
        instructions[i].arg2 = calloc(1, sizeof(vmarg));

        fread(&instructions[i].opcode, sizeof(int), 1, binary);
        DEBUG_PRINT("%d ", instructions[i].opcode);

        fread(&instructions[i].result->type, sizeof(int), 1, binary);
        fread(&instructions[i].result->val, sizeof(int), 1, binary);
        DEBUG_PRINT("%d %d ", instructions[i].result->type, instructions[i].result->val);

        fread(&instructions[i].arg1->type, sizeof(int), 1, binary);
        fread(&instructions[i].arg1->val, sizeof(int), 1, binary);
        DEBUG_PRINT("%d %d ", instructions[i].arg1->type, instructions[i].arg1->val);

        fread(&instructions[i].arg2->type, sizeof(int), 1, binary);
        fread(&instructions[i].arg2->val, sizeof(int), 1, binary);
        DEBUG_PRINT("%d %d ", instructions[i].arg2->type, instructions[i].arg2->val);

        fread(&instructions[i].srcLine, sizeof(int), 1, binary);
        DEBUG_PRINT("%d\n", instructions[i].srcLine);

        //ean opoiodipote kommati einai userfunc bazw tin thesi pu antistoixei apo ton pinaka ws val    
        // if(instructions[i].result->type == userfunc_a ){
        //     instructions[i].result->val = userfuncs[instructions[i].result->val].address;
        // }
        // if(instructions[i].arg1->type == userfunc_a ){
        //     instructions[i].arg1->val = userfuncs[instructions[i].arg1->val].address;
        // }
        // if(instructions[i].arg2->type == userfunc_a ){
        //     instructions[i].arg2->val = userfuncs[instructions[i].arg2->val].address;
        // }
    }
    return instructions;
}

//reads binary and inits the globals needed to save it
void read_binary(){
    binary = fopen("../binary.abc", "r");
    //get the magic number assertion check inside the get function
    get_magic_number();

    //get the size of the global variables
    DEBUG_PRINT("%s","Total global variables : ");
    total_global_var = get_size_of_consts();

    //get the size of the array for constants for the numbers and also the array
    DEBUG_PRINT("%s","Total number consts : "); 
    number_constsNum = get_size_of_consts();
    number_consts = get_number_consts(number_constsNum);

    //get the number of strings and the array of strings
    DEBUG_PRINT("%s","Total string consts : "); 
    string_constsNum = get_size_of_consts();
    string_consts = get_string_consts(string_constsNum);
    
    //get the number of libfunctions and the array of libfunctions
    DEBUG_PRINT("%s","Total libfunctions consts : ");
    libfuncsNum = get_size_of_consts();
    libfuncs = get_string_consts(libfuncsNum);

    //get the number of user functions and the array of user functions
    DEBUG_PRINT("%s","Total user functions consts : ");
    userfuncsNum = get_size_of_consts();
    userfuncs = get_userfunc_consts(userfuncsNum);

    //get the number of instructions
    DEBUG_PRINT("%s","Total instructions : ");
    codeSize = get_size_of_consts() ;
    code = get_instructions(codeSize);

    fclose(binary);
}





