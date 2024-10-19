#include <stdio.h>

int FindMissing(unsigned int a[], unsigned int n)
{
	//O(N)..... efficent? idk you tell me
	int arrSum = 0;
	int sumToN = n;
	for (int i = 1; i < n; i++)
	{
		arrSum += a[i - 1];
		sumToN += i;
	}
	return(sumToN - arrSum);
}

int main()
{
	int a[] = { 2, 6, 5, 3, 4 };
	int n = 6;
	int result = FindMissing(a, n);
	printf("Missing %d",result);
	return 0;
}