#include <stdio.h>
typedef enum { A, B, C } tower;


void hanoi(int disks, tower from, tower to)
{
	tower other = (A + B + C) - to - from;
	if (disks == 1)
	{
		printf("%C -> %C\n", 'A' + from, 'A' + to);
	}
	else
	{
		hanoi(disks-1, from, other);
		printf("% C -> % C\n", 'A' + from, 'A' + to);
		hanoi(disks-1, other, to);

	}
}

void constrained_hanoi(int n, tower from, tower to)
{
	tower other = (A + B + C) - to - from;
	if (n == 0) return;
	if (other != B)/* to & from הם שני מגדלים סמוכים */
	{
		constrained_hanoi(n-1,from,other);
		printf("%C -> %C\n", 'A' + from, 'A' + to);
		constrained_hanoi(n-1, other, to);
	}
	else /* to & from הם שני המגדלים שבקצוות */
	{
    (3)
    (4)
		printf("%C -> %C\n", 'A' + from, 'A' + other);
		printf("%C -> %C\n", 'A' + other, 'A' + to);
		//(6)
	}
}

int main()
{

	return 0;

}
