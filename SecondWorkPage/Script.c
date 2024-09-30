#pragma warning(disable : 4996)
#include <stdio.h>
#include <ctype.h> // For isdigit()

typedef char string[255];

int main3() {
    // A
    for (int i = 6; i > 0; i--) {
        for (int j = 0; j < i; j++)
            putchar('*');
        putchar('\n');
    }

    puts("");

    // B
    for (int i = 1; i <= 5; i++) {
        for (int j = 0; j < i; j++)
            putchar('*');
        putchar('\n');
    }

    puts("");

    // C
    int spaces = 0;
    for (int i = 11; i > 0; i -= 2) {
        for (int j = 0; j < spaces; j++)
            putchar(' ');
        for (int j = 0; j < i; j++)
            putchar('*');
        putchar('\n');
        spaces++;
    }

    for (int i = 3; i <= 11; i += 2)
    {
        for (int j = 0; j < (11 - i) / 2; j++)
            putchar(' ');
        for (int j = 0; j < i; j++)
            putchar('*');
        putchar('\n');
    }
    return 0;
}

int main2()
{
    string str;
    printf("Enter a string: ");
    gets(str);
    int alphaCounter = 0;
    for (int i = 0; str[i] != '\0'; i++)
        if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z'))
            alphaCounter++;

    printf("The String \"%s\"\nContains [%d] Alphabetic Chars\n ", str, alphaCounter);

    return 0;
}

int main1()
{
    char ch;

    printf("Enter characters (input stops at whitespace): ");
    int firstCharFlag = 1;
    int toggleNegFlag = 0;
    int num = 0;
    while ((ch = getchar()) != EOF) {
        if (ch == ' ' || ch == '\t' || ch == '\n') {
            break;
        }
        if (isdigit(ch)) {
            int digit = ch - '0'; // Convert character to integer (ASSCI)
            num += digit;
            num *= 10;
            firstCharFlag = 0;
        }
        else if (ch == '-' && firstCharFlag)
        {
            firstCharFlag = 0;
            toggleNegFlag = 1;
        }
        else if (ch == '+' && firstCharFlag)
            firstCharFlag = 0;
        else
        {
            printf("%c is not a digit. please enter a legal input.\n", ch);
            return;
        }
    }
    num /= 10;

    if (toggleNegFlag)
        num *= -1;
    printf("The number you buit is [%d]", num);
    return 0;
}
