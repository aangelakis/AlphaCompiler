#include"avm.h"

//UNCOMMENT THIS TO RUN THE TEST MAIN FUNCTION
//#define TEST_MAIN
#ifdef TEST_MAIN
#define TEST_MAIN_START int main(void)
#else
#define TEST_MAIN_START int definitely_not_main(void)
#endif

#include <stdio.h>

avm_memcell avm_stack[AVM_STACKSIZE];
static int curr_index = AVM_STACKSIZE-1;

avm_memcell avm_stack_pop(){
    if(curr_index == -1){
        printf("Fatal error: stack underflow\n");
        exit(1);
    }
    avm_memcell ret = avm_stack[curr_index];
    AVM_WIPEOUT(avm_stack[curr_index]);
    --curr_index;
    return ret;
}

void avm_stack_push(avm_memcell item){
  if(curr_index == AVM_STACKSIZE-1){
    printf("Fatal error: stack Overflow\n");
    exit(1);
  }
  avm_stack[++curr_index] = item;
}

void avm_initstack(void){
    for(unsigned i = 0; i < AVM_STACKSIZE; ++i){
        AVM_WIPEOUT(avm_stack[i]);
        avm_stack[i].type = undef_m;
    }
}

TEST_MAIN_START{
    avm_initstack();
    return 0;

}