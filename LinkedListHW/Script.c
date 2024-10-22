//Ithamar Baron
#pragma warning(disable : 4996)
#include <stdio.h>
#include "List.h"

typedef char String[256];

#define GRN  "\x1B[32m"
#define WHT  "\x1B[37m"
#define CYN  "\x1B[36m"
#define MAG  "\x1B[35m"
#define RED  "\x1B[31m"
#define YEL  "\x1B[33m"

//QUESTION 1 (1-6)

// Function to print the linked list
void PrintList(NodePtr head)
{
    if (IsEmpty(head))
    {
        printf(RED"null\n"WHT);
        return;
    }

    NodePtr current = head;
    while (current != NULL)
    {
        printf(CYN"[%d]"WHT, current->info);
        if (current->next != NULL)
            printf(" -> "WHT);
        current = current->next;
    }
    printf(WHT" -> ");
    printf(CYN"null\n"WHT);
}

//Function to revurse and print the list
void RevurseList(NodePtr head)
{
    NodePtr newHead;
    Init(&newHead);

    NodePtr current = head;
    while (current != NULL) 
    {
        InsertToHead(&newHead, current->info);
        current = current->next;
    }
        
    PrintList(newHead);
}

//Function that takes X and prints if X is in the list
void FindX(NodePtr head, int x)
{
    NodePtr current = head;
    while (current != NULL)
    {
        if (current->info == x)
        {
            printf("%d Is in the list!\n",x);
            return;
        }
        current = current->next;
    }
    printf("%d Is not in the list\n", x);
}

//returns the number of nodes
int CountNodes(NodePtr head)
{
    if (head == NULL)
        return 0;
    return CountNodes(head->next) + 1;
}

//finds the max diffenace
void MaxDifferance(NodePtr head)
{
    NodePtr current = head->next;
    int max = head->info;
    int min = max;
    while (current != NULL)
    {
        if (current->info > max)
            max = current->info;
        else if (current->info < min)
            min = current->info;
        current = current->next;
    }
    int diff = max - min;
    printf("The max differance is %d\n", diff);
}

//seperates the list to odd and even numbers (if i currectly understood the question...?)
void SeperateList(NodePtr head)
{
    NodePtr current = head;

    while (current != NULL)
    {
        if (current->info % 2 !=0)
        {
            InsertToHead(&head,current->info);
            NodePtr temp = current;
            current = current->next;
            Delete(&head, temp);
        }
        else
            current = current->next;
    }
}


//QUESTION 2 (A-B)

//  helper function to insert a value into 2 lisst in sorted order
void InsertSorted(NodePtr* pHead, int value)
{
    NodePtr newNode;
    GetNode(&newNode, value);
    if (newNode == NULL)
        return;

    if (IsEmpty(*pHead) || (*pHead)->info >= value)
    {
        newNode->next = *pHead;
        *pHead = newNode;
    }
    else
    {
        NodePtr current = *pHead;
        // Find the correct position to insert
        while (current->next != NULL && current->next->info < value)
            current = current->next;
        newNode->next = current->next;
        current->next = newNode;
    }

}

//method requested in question 2 input 2 sorted lists.
void Input2Lists()
{
    NodePtr list1, list2;
    Init(&list1);
    Init(&list2);

    int value;
    char choice;

        printf("Enter integers (type 'q' to finish):\n");
        while (1) 
        {
            printf("Enter an integer: ");
            if (scanf("%d", &value) != 1) 
            {
                scanf("%c", &choice);
                if (choice == 'q')
                    break;
                printf("Invalid input. Please enter an integer or 'q' to quit.\n");
                continue;
            }
            InsertSorted(&list1, value); // Insert in sorted order
        }
        PrintList(list1);

        printf("Enter integers (type 'q' finish):\n");
        while (1) 
        {
            printf("Enter an integer: ");
            if (scanf("%d", &value) != 1) 
            {
                scanf("%c", &choice);
                if (choice == 'q')
                    break;
                printf("Invalid input. Please enter an integer or 'q' to quit.\n");
                continue;
            }
            InsertSorted(&list2, value); // Insert in sorted order
        }
        PrintList(list2);

    
}

//checks if both lists are eqal (question 2 A)
int AreListsEqual(NodePtr head1, NodePtr head2) 
{
    if (head1 == NULL && head2 == NULL)
        return 1;
    
    if (head1 == NULL || head2 == NULL)
        return 0;

    NodePtr current1 = head1;
    NodePtr current2 = head2;

    while (current1 != NULL && current2 != NULL)
    {
        if (current1->info != current2->info)
            return 0;
        current1 = current1->next;
        current2 = current2->next;
    }
    return current1 == NULL && current2 == NULL;
}

//adds list 2 to the end of list 1.
//(dont use same list, ull create an infinate loop)
int MergeAndPrint(NodePtr head1, NodePtr head2) 
{
    NodePtr pos = head1;

    while (pos->next != NULL)
        pos = pos->next;
    pos->next = head2;

    PrintList(head1); 
}

//QUESTION 3
//takes a list (min length = 4)
//returns a sublist (of length =4) with the max value;
//NOTE! requested to return 2 values (ptr, int) we did not yet learn how to do that so im printing the int and returning the ptr
NodePtr MaxSubList(NodePtr head)
{
    NodePtr current = head;
    NodePtr retPtr = NULL;
    int maxSum = 0;
    while (current != NULL)
    {
        int sum = current->info;
        if (current->next != NULL)
        {
            sum += current->next->info;
            if (current->next->next != NULL)
            {
                sum += current->next->next->info;
                if (current->next->next->next != NULL)
                    sum += current->next->next->next->info;
            }
        }
        if (sum > maxSum)
        {
            maxSum = sum;
            retPtr = current;
        }
        current = current->next;
    }

    printf("MAX SUM IS %d\n", maxSum);
    return retPtr;
}

//prints palinoms as requested in the question

void printPolinom(NodePtr head1, NodePtr head2)
{
    NodePtr current1 = head1;
    NodePtr current2 = head2;
    String str, str2, addStr, multStr;
    int i = 0;
    int exp = 0;
    for (i; current1 != NULL && current2 != NULL && i < 250; i+=4)
    {
        str[i] = current1->info;
        str[i + 1] = '>';
        str[i + 2] = exp;
        str[i + 3] = '+';
        str2[i] = current2->info;
        str2[i + 1] = '>';
        str2[i + 2] = exp;
        str2[i + 3] = '+';
        addStr[i] = current2->info + current1->info;
        addStr[i + 1] = '>';
        addStr[i + 2] = exp;
        addStr[i + 3] = '+';
        multStr[i] = current2->info * current1->info;
        multStr[i + 1] = '>';
        multStr[i + 2] = exp;
        multStr[i + 3] = '+';
        exp++;
        current1 = current1->next;
        current2 = current2->next;
    }


    NodePtr current;
    if (current1 != NULL) 
    {
        current = current1;
        while (current != NULL) 
        {
            str[i] = current->info;
            str[i + 1] = '>';
            str[i + 2] = exp;
            str[i + 3] = '+';
            addStr[i] = current->info;
            addStr[i + 1] = '>';
            addStr[i + 2] = exp;
            addStr[i + 3] = '+';
            multStr[i] = current->info;
            multStr[i + 1] = '>';
            multStr[i + 2] = exp;
            multStr[i + 3] = '+';
            i += 4;
            exp++;
            current = current->next;
        }
    }
    else
    {
        current = current2;
        while (current != NULL)
        {
            str2[i] = current->info;
            str2[i + 1] = '>';
            str2[i + 2] = exp;
            str2[i + 3] = '+';
            addStr[i] = current->info;
            addStr[i + 1] = '>';
            addStr[i + 2] = exp;
            addStr[i + 3] = '+';
            multStr[i] = current->info;
            multStr[i + 1] = '>';
            multStr[i + 2] = exp;
            multStr[i + 3] = '+';
            i += 4;
            exp++;
            current = current->next;
        }
    }

}



//PAGE 5 QUESTION 1

// Function to create a circular linked list with the given number of soldiers
void CreateCircularList(NodePtr* pHead, int numOfSoldiers)
{
    Init(pHead);

    for (int i = 1; i <= numOfSoldiers; i++) 
    {
        if (IsEmpty(*pHead))
            InsertToHead(pHead, i); 
        else 
            InsertToEnd(*pHead, i);
    }
    NodePtr last = *pHead;
    while (last->next != NULL) 
    {
        last = last->next;
    }
    last->next = *pHead;
}

// Function to eliminate every N-th soldier
void EliminateSoldiers(int numOfSoldiers, int N) 
{
    NodePtr head = NULL; 
    CreateCircularList(&head, numOfSoldiers);

    NodePtr current = head, prev = NULL;
    while (current->next != current) 
    {
        for (int i = 1; i < N; i++) 
        {
            prev = current;
            current = current->next;
        }
        // Delete the N-th node
        prev->next = current->next;
        printf("Soldier %d is eliminated.\n", current->info);
        free(current);
        current = prev->next;
    }

    printf("The last remaining soldier is %d.\n", current->info);
    free(current);
}

//PAGE 5 QUESTION 2

void PrintLongsSum(long num1, long num2)
{
    long long sum = num1 + num2;

    NodePtr head1 = NULL;
    NodePtr head2 = NULL;

    Init(&head1);
    Init(&head2);

    while (num1 > 0)
    {
        int digit = num1 % 10;
        num1 /= 10;
        InsertToHead(&head1, digit);
    }

    while (num2 > 0)
    {
        int digit2 = num2 % 10;
        num2 /= 10;
        InsertToHead(&head2, digit2);
    }
    PrintList(head1);
    PrintList(head2);

    printf("The sum is: %lld\n", sum);
}



int main() 
{
    int numOfSoldiers, N;

    printf("Enter the number of soldiers: ");
    scanf("%d", &numOfSoldiers);
    printf("Enter the step N: ");
    scanf("%d", &N);

    EliminateSoldiers(numOfSoldiers, N);

    PrintLongsSum(12345678, 8764321);

    return 0;
}

