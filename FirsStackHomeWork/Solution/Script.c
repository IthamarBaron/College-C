//Ithamar Bar On 24/9/24
#pragma warning(disable : 4996)
#include <stdio.h>
#include "stack.h"

typedef char string[100];

//=======\\Helper methods//=======
stack stack_reverse(stack s) {
    stack reversed;
    stack_init(&reversed);
    stack temp = s;

    while (!stack_empty(&temp)) {
        stack_item item = stack_pop(&temp);
        stack_push(&reversed, item);
    }

    return reversed;
}

void stack_print(stack* sptr) {
    if (stack_empty(sptr)) {
        printf("Stack is empty.\n");
        return;
    }

    printf("Top\n");  // Print the top label
    for (int i = sptr->top; i >= 0; i--) {  // Iterate from top to bottom
        printf("%d\n", sptr->data[i]);  // Print each element
    }
    printf("Bottom\n");  // Print the bottom label
}
//=======//Helper methods\\=======



//IsPalindrom()
int Question1(string str)
{
    stack original;
    stack_init(&original);
    for (int i = 0; str[i] != '\0'; i++)
        stack_push(&original, str[i]);
    stack reversed = stack_reverse(original);
    //both stacks are the same size so we can only check on one of them:
    while (!stack_empty(&original))
    {
        stack_item A = stack_pop(&original);
        stack_item B = stack_pop(&reversed);
        if (A != B)
            return 0;
    }
    return 1;
}

//XXX.XXX -> 1 | XXX.YYY -> 0
int Question2(string str) 
{
    //making 2 strings from the first string (could have skipped this part but wanted to expirament with strings :D )
    string beforeDig = "";
    string afterDig = "";
    short foundDig = 0;

    int beforeIndex = 0;
    int afterIndex = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '.')
            foundDig = 1; 
        else //tried to do string1 += string2 but in c... idk if that how you do it but it works
        {
            if (!foundDig)
            {
                beforeDig[beforeIndex] = str[i];  
                beforeIndex++;                   
                beforeDig[beforeIndex] = '\0';    
            }
            else
            {
                afterDig[afterIndex] = str[i];    
                afterIndex++;                     
                afterDig[afterIndex] = '\0';      
            }
        }
    }

    //making 2 stacks from the 2 strings
    stack beforeDigStack;
    stack afterDigStack;

    stack_init(&beforeDigStack);
    stack_init(&afterDigStack);

    for (int i = 0; beforeDig[i] != '\0'; i++)
        stack_push(&beforeDigStack, beforeDig[i]);
    for (int i = 0; afterDig[i] != '\0'; i++)
        stack_push(&afterDigStack, afterDig[i]);


    //comparing the stacks to get our results
    while (!stack_empty(&beforeDigStack) && !stack_empty(&afterDigStack))
    {
        stack_item A = stack_pop(&beforeDigStack);
        stack_item B = stack_pop(&afterDigStack);
        if (A != B)
            return 0;
    }
    return (stack_empty(&beforeDigStack) && stack_empty(&afterDigStack));
}

//Sorted stack input
stack Question3(int n) 
{
    stack input;
    stack temp;
    stack_init(&input);
    stack_init(&temp);

    for (int i = 0; i < n; i++)// input loop
    {
        stack_item var = 0;
        scanf("%d", &var);

        if (stack_empty(&input))
            stack_push(&input,var);
        else if (stack_top(&input) <= var)
            stack_push(&input, var);
        else
        {
            while (stack_top(&input) > var)
            {
                stack_item tempItem = stack_pop(&input);
                stack_push(&temp, tempItem);
            }
            stack_push(&input, var);
            while (!stack_empty(&temp))
            {
                stack_item tempItem = stack_pop(&temp);
                stack_push(&input, tempItem);
            }
        }
        //stack_print(&input); DEBUG
    }
    return input;
}

//merge sorted stacks
stack Question4(stack s1, stack s2)
{
    stack s3;
    stack revS3;
    stack_init(&revS3);
    //pushing untill one of them is empty,
    while (!stack_empty(&s1) && !stack_empty(&s2))
    {
        stack_item item1 = stack_pop(&s1);
        stack_item item2 = stack_pop(&s2);

        if (item1 > item2)
        {
            stack_push(&revS3, item1);
            stack_push(&revS3, item2);
        }
        else
        {
            stack_push(&revS3, item2);
            stack_push(&revS3, item1);
        }
    }
    // pushing the ramaining items from one of the stacks (the larger one)
    while (!stack_empty(&s1))
    {
        stack_item item = stack_pop(&s1);
        stack_push(&revS3, item);
    }
    while (!stack_empty(&s2))
    {
        stack_item item = stack_pop(&s2);
        stack_push(&revS3, item);
    }

    s3 = stack_reverse(revS3);
    return s3;
}

// L1 = {A^nB^n | n>=0}
int Question5(string str)
{
    stack s;
    stack_init(&s);
    int i = 0;//we use the same <i> for both loops.
    for (i; str[i] != '\0' && str[i] != 'B'; i++)
    {
        if (str[i] != 'A')
            return 0;
        stack_push(&s, str[i]);

    }
    for (i; str[i] != '\0'; i++) 
    {
        if (str[i] != 'B')
            return 0;
        stack_pop(&s);
    }


    return stack_empty(&s);
}

//L2={xCy | x E { A,B }+ and y E { A,B }+ and y=xr}
int Question6(string str)
{
    stack s;
    stack_init(&s);
    int i = 0;//we use the same <i> for both loops.
    for (i; str[i] != '\0' && str[i] != 'C'; i++)
    {
        if (str[i] != 'A' && str[i] != 'B')
            return 0;
        stack_push(&s, str[i]);
    }
    for (++i; str[i] != '\0'; i++)
    {
        if (stack_empty(&s))
            return 0;
        stack_item item = stack_pop(&s);
        if (item != str[i])
            return 0;
    }
    return stack_empty(&s);

}
//modified Q6 to fit demands on Q7 (L3)
int Question7(string str)
{
    stack s;
    stack_init(&s);
    stack s1;
    stack_init(&s1);
    int i = 0;//we use the same <i> for both loops.
    for (i; str[i] != '\0' && str[i] != 'C'; i++)
    {
        if (str[i] != 'A' && str[i] != 'B')
            return 0;
        stack_push(&s, str[i]);
    }
    for (++i; str[i] != '\0' && str[i] != 'C'; i++)
    {
        if (stack_empty(&s))
            return 0;
        stack_item item = stack_pop(&s);
        //this time we will re use the values to see if they match our next X
        stack_push(&s1, item);
        if (item != str[i])
            return 0;
    }
    if (!stack_empty(&s))
        return 0;
    for (++i; str[i] != '\0'; i++)
    {
        if (stack_empty(&s1))
            return 0;
        stack_item item = stack_pop(&s1);
        if (item != str[i])
            return 0;
    }
    return stack_empty(&s1);
}


int main()
{
    /* TEST QUESTION 4
    stack s = Question3(5);
    stack_print(&s);
    stack s2 = Question3(5);
    stack_print(&s2);
    stack s3 = Question4(s, s2);
    stack_print(&s3);*/


}