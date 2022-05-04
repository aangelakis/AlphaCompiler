typedef struct stack_node{
    void* value;
    struct stack_node* next;
} stack_node;


typedef struct stack_t{
    unsigned int size;
    struct stack_node* top;
} stack_t;

/* Initializes the stack. */
stack_t* stack_t_init();

/* Checks if stack is empty. */
int stack_is_empty(stack_t*);

/* Pushes a stack_node in the stack. */
int stack_push(stack_t*, void*);

/* Returns the current size of the stack. */
unsigned int stack_get_size(stack_t*);

/* Pops the top node of the stack. */
void* stack_pop(stack_t*);

/* Returns the value of the stack's top node. */
void* stack_top(stack_t*);

/* Frees the stack */
void stack_free(stack_t*);

/* Applies function 'apply(void*)' to the value of each stack_node of the stack */
void stack_apply(stack_t*, void (*apply)(void*));

/* Clears the stack */
void stack_clear(stack_t*);