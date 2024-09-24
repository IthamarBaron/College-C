// my_stack.c
#include <stdio.h>
#include "stack.h"


/*********************** Function bodies **************/

void stack_init(stack* sptr)
{
	sptr->top = -1;
}

void stack_push(stack* sptr, stack_item x)
{
	sptr->top++;
	sptr->data[sptr->top] = x;

}
Boolean stack_empty(stack* sptr)    // if the stack empty return 1
{
	return sptr->top == -1;
}
Boolean stack_full(stack* sptr)    // if the stack full return 1
{
	return sptr->top == STACK_MAX_SIZE - 1;
}
stack_item stack_pop(stack* sptr)
{
	stack_item  x;
	x = sptr->data[sptr->top];
	sptr->top--;
	return(x);
}

stack_item stack_top(stack* sptr)
{
	if (stack_empty(sptr))
	{
		printf("Stack empty \n");
		return (stack_item)NULL;
	}
	return (sptr->data[sptr->top]);
}
