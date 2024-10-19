//Ithamar Baron
#pragma warning(disable : 4996)
#include <stdio.h>

void SolveCypher()
{
    //note all numbers are single digits so no need to build numbers in a fancy way ;)

    int numericInfo[4] = { 0,0,0,0 };
    char str[256];
    int counter = 0;
    while (scanf("%s", str) != EOF)
    {
        for (int i = 0; str[i] != '\0'; i++)
        {
            if (isdigit(str[i]))
            {
                numericInfo[counter] = (int)(str[i] - '0');
                counter++;
                break;
            }
        }
        if (counter > 3)
        {
            break;
        }
    }
    printf("We shall meet on the %d.%d on the %dth avenue, building number %d\n", numericInfo[0], numericInfo[1], numericInfo[2], numericInfo[3]);
}

int main()
{
    SolveCypher();
    return 0;
}