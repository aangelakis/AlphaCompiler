#ifndef ALPHA_STACK_HEADER
#define ALPHA_STACK_HEADER

typedef struct stack_node{
    void* value;
    struct stack_node* next;
} stack_node;


typedef struct alpha_stack{
    unsigned int size;
    struct stack_node* top;
} alpha_stack;

/* Initializes the stack. */
alpha_stack* alpha_stack_init();

/* Checks if stack is empty. */
int stack_is_empty(alpha_stack*);

/* Pushes a stack_node in the stack. */
int stack_push(alpha_stack*, void*);

/* Returns the current size of the stack. */
unsigned int stack_get_size(alpha_stack*);

/* Pops the top node of the stack. */
void* stack_pop(alpha_stack*);

/* Returns the value of the stack's top node. */
void* stack_top(alpha_stack*);

/* Frees the stack */
void stack_free(alpha_stack*);

/* Applies function 'apply(void*)' to the value of each stack_node of the stack */
void stack_apply(alpha_stack*, void (*apply)(void*));

/* Clears the stack */
void stack_clear(alpha_stack*);

#endif