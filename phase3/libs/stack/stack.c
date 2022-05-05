#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "stack.h"


alpha_stack* alpha_stack_init(){
    alpha_stack* new_stack;
    new_stack = (alpha_stack*)malloc(sizeof(alpha_stack));

    if(new_stack == NULL){
        return NULL;
    }

    new_stack->size = 0;
    new_stack->top = NULL;
    return new_stack;
}

int stack_is_empty(alpha_stack* stack){
    assert(stack != NULL);
    return (stack->size == 0);
}

int stack_push(alpha_stack* stack, void* value){
    stack_node* new_node;

    assert(stack != NULL);

    new_node = (stack_node*) malloc(sizeof(stack_node));
    if(new_node == NULL){
        return -1;
    }

    new_node->value = value;
    new_node->next = stack->top;

    stack->top = new_node;
    stack->size++;

    return 0;
}

void* stack_pop(alpha_stack* stack){
    void* tmp_val;
    stack_node* tmp_node;

    assert(stack != NULL);

    if(stack_is_empty(stack)){
        exit(-1);
    }

    tmp_val = stack->top->value;
    tmp_node = stack->top;

    stack->top = stack->top->next;
    stack->size--;

    tmp_node->next = NULL;
    free(tmp_node);

    return tmp_val;
}

void* stack_top(alpha_stack* stack){
    assert(stack != NULL);

    if(stack_is_empty(stack)){
        exit(-1);
    }

    return (stack->top->value);
}

void stack_free(alpha_stack* stack){
    assert(stack != NULL);

    stack->top = NULL;

    free(stack);
}

unsigned int stack_get_size(alpha_stack* stack){
    assert(stack);

    return stack->size;
}

void stack_apply(alpha_stack* stack, void (*apply)(void*)){
    assert(stack);

    stack_node *iter = stack->top;

    while(iter){
        apply(iter->value);
        iter = iter->next;
    }
}

/* Isos xreiastei na valoume kai to isFreeable se periptosi poy exoume kapoio string os value */
void stack_clear(alpha_stack* stack){
    assert(stack);

    stack_node *iter = stack->top, *tmp;
    
    while(iter){
        tmp = iter;
        iter = iter->next;
        free(tmp);
    }

    stack->top = NULL;
    stack->size = 0;
}