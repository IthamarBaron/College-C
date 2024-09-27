#pragma warning(disable : 4996)

#include <stdio.h>
#include "stack.h"
//used colores to help debug in question 10
#define GRN  "\x1B[32m"
#define WHT  "\x1B[37m"
#define CYN  "\x1B[36m"
#define MAG  "\x1B[35m"
#define RED  "\x1B[31m"
#define YEL  "\x1B[33m"

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

//((5+7)-((1+9)/2)) -> 7 
//NOTE!!! wanted to make it usable for floats but Stack_item is int. 
int Question7(string str)
{
    stack parentheses;
    stack operands;
    stack operators;
    stack_init(&parentheses);
    stack_init(&operands);
    stack_init(&operators);


    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '(')
            stack_push(&parentheses, '(');
        else if (str[i] == '+' || str[i] == '-' || str[i] == '/' || str[i] == '*')
            stack_push(&operators, str[i]);
        else if (str[i] != ')')
            stack_push(&operands, (int)(str[i] - '0'));

        if (str[i] == ')')
        {
            stack_pop(&parentheses);
            int B = (int)stack_pop(&operands);
            int A = (int)stack_pop(&operands);

            char c = stack_pop(&operators);
            int result = 0;
            switch (c)
            {
            case '+':
                result = A + B;
                printf("%d + %d = %d", A, B , result);
                printf("\n");

                break;
            case '-':
                result = A - B;
                printf("%d - %d = %d", A, B, result);
                printf("\n");

                break;
            case '/':
                result = A / B;
                printf("%d / %d = %d", A, B, result);
                printf("\n");

                break;
            case '*':
                result = A * B;
                printf("%d * %d = %d", A, B, result);
                printf("\n");
                break;
            default:
                break;
            }

            stack_push(&operands, result);
        }
    }
    int ret = stack_pop(&operands);
    return(ret);
}

//23+4*56*+ ->50
int Question8(string str) 
{
    stack operands; 
    stack_init(&operands);
    for (int i = 0; str[i] != '\0'; i++)
    {   
        if (!(str[i] == '+' || str[i] == '-' || str[i] == '/' || str[i] == '*')) 
        {
            stack_push(&operands, (int)(str[i] - '0'));
        }
        else 
        {
            int B = (int)stack_pop(&operands);
            int A = (int)stack_pop(&operands);

            char c = str[i];
            int result = 0;
            switch (c)
            {
            case '+':
                result = A + B;
                printf("%d + %d = %d", A, B, result);
                printf("\n");

                break;
            case '-':
                result = A - B;
                printf("%d - %d = %d", A, B, result);
                printf("\n");

                break;
            case '/':
                result = A / B;
                printf("%d / %d = %d", A, B, result);
                printf("\n");

                break;
            case '*':
                result = A * B;
                printf("%d * %d = %d", A, B, result);
                printf("\n");
                break;
            default:
                break;
            }

            stack_push(&operands, result);
        }  
    }
    int ret = stack_pop(&operands);
    return(ret);
}

//infix->postfix + result
int Question9(string str) {
    stack operators;
    stack_init(&operators);

    string postfix;
    int postfix_index = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= '0' && str[i] <= '9') 
            postfix[postfix_index++] = str[i];
        else if (str[i] == '(') 
            stack_push(&operators, '('); 

        else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') 
        {
            // While the precedence of the current operator is less than or equal to the top of the stack

            while (!stack_empty(&operators) && (stack_top(&operators) != '(') && ((str[i] == '+' || str[i] == '-') ? 1 : 0) <= ((stack_top(&operators) == '+' || stack_top(&operators) == '-') ? 1 : ((stack_top(&operators) == '*' || stack_top(&operators) == '/') ? 2 : 0)))
                        postfix[postfix_index++] = (char)stack_pop(&operators);
            stack_push(&operators, str[i]);
        }
        else if (str[i] == ')') 
        {
            while (!stack_empty(&operators) && stack_top(&operators) != '(') 
                postfix[postfix_index++] = (char)stack_pop(&operators); // Pop until '('
            stack_pop(&operators); // Remove '(' from stack
        }
    }

    // Pop all remaining operators
    while (!stack_empty(&operators))
        postfix[postfix_index++] = (char)stack_pop(&operators);

    postfix[postfix_index] = '\0'; 
    int result = Question8(postfix);
    printf("Postfix expression: %s  and is equal to: %d \n", postfix, result); // Print the postfix expression & the result
    return result;// as requested in the question for some reason... 
}

//same as Question7, only this time we looped over each number's digits and constracted a number fom it 
int Question10(string(str)) {
    //Spaghetti!!
    stack parentheses;
    stack operands;
    stack operators;
    stack_init(&parentheses);
    stack_init(&operands);
    stack_init(&operators);


    for (int i = 0; str[i] != '\0'; i++)
    {
       //DEBUG printf(GRN"Itteration [%d] Current char [%c]\n"WHT, i, str[i]); 
        if (str[i] == '(')
            stack_push(&parentheses, '(');
        else if (!(str[i] == '+' || str[i] == '-' || str[i] == '/' || str[i] == '*') && str[i] != '\0' && str[i] != ')')
        {
            int num = 0;
            while (!(str[i] == '+' || str[i] == '-' || str[i] == '/' || str[i] == '*') && str[i] != '\0' && str[i] != ')')
            {
                //DEBUGprintf("gotten into the loop with Char [%c]\n", str[i]);
                int digit = (int)(str[i] - '0');
                num += digit;
                num *= 10;
                i++;
                //DEBUG printf("num inside the loop = %d\n", num);
            }
            //DEBUGprintf("num outside (/10) the loop = %d\n", num / 10);
            stack_push(&operands, (num / 10));
            //DEBUGprintf(YEL"Itteration[%d] Pushing[%d] into the OPERANDS stack\n"WHT, i, num/10);
            //DEBUGprintf(YEL"Itteration[%d] Pushing[%c] into the OPERANDS stack\n"WHT, i, num / 10);
            //DEBUGprintf(CYN"Itteration [%d] Current char [%c]\n"WHT, i, str[i]);

        }
        if (str[i] == '+' || str[i] == '-' || str[i] == '/' || str[i] == '*')
        {
            //DEBUGprintf(RED"Itteration[%d] Pushing[% c] into the operators stack\n"WHT, i, str[i]);
            stack_push(&operators, str[i]);

        }

        //DEBUGprintf(MAG"Itteration [%d] Current char [%c]\n"WHT, i, str[i]);

        if (str[i] == ')')
        {

            stack_pop(&parentheses);
            int B = (int)stack_pop(&operands);
            int A = (int)stack_pop(&operands);

            char c = stack_pop(&operators);
            int result = 0;
            //DEBUGprintf("C = [%c]\n", c);
            switch (c)
            {
            case '+':
                result = A + B;
                printf("%d + %d = %d", A, B, result);
                printf("\n");

                break;
            case '-':
                result = A - B;
                printf("%d - %d = %d", A, B, result);
                printf("\n");

                break;
            case '/':
                result = A / B;
                printf("%d / %d = %d", A, B, result);
                printf("\n");

                break;
            case '*':
                result = A * B;
                printf("%d * %d = %d", A, B, result);
                printf("\n");
                break;
            default:
                break;
            }
            //DEBUGprintf(YEL "Itteration[%d] Pushing RESULT [%d] into the operators stack\n"WHT, i, result);
            stack_push(&operands, result);
            //DEBUGprintf(YEL);
            //DEBUGstack_print(&operands);
            //DEBUGprintf(WHT);

        }
    }
    int ret = stack_pop(&operands);
    return(ret);
}

int main()
{
    //Question 7:
    int a = Question7("((5+7)-((1+9)/2))");
    printf("result =  %d\n", a);
    //question 8:
    int c = Question8("23+4*56*+");
    printf("result =  %d", c);
    //Question 9:
    int result = Question9("((2+3)-(4*5))");
    //question10
    int b = Question10("((579-429)+(51/(7-4)))");
    printf("result =  %d\n", b);
    return 0;
}
