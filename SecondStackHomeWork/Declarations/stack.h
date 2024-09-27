#define STACK_MAX_SIZE 100

enum { FALSE, TRUE };
typedef unsigned char Boolean;
typedef int stack_item;
typedef struct {
	int top;
	stack_item data[STACK_MAX_SIZE];
} stack;

//======= PROTOTYPE ======================
void stack_init(stack*);
Boolean  stack_empty(stack*);
Boolean  stack_full(stack*);
stack_item stack_pop(stack*);
void stack_push(stack*, stack_item);
stack_item stack_top(stack*);
