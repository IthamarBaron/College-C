#pragma warning (disable:4996)
#include <stdio.h>

//Helper func. takes 2 ints _component & _exponent 
//returns _component^_exponent
int power(int _component, int _exponent)
{
	if (!_exponent) return !_exponent;
	int result = _component;
	for (_exponent; _exponent > 1 ; _exponent--)
		result *= _component;
	return result;
}

int f_targil1()
{
	int a, n;
	printf("Enter A:");
	scanf("%d", &a);
	printf("Enter N:");
	scanf("%d", &n);
	int sum = 0;
	for (n;  n>0; n--)
		sum += n * (power(a,(2*n)));
	return sum;
}

void f_targil2()
{
	for (int i = 1; i < 10E6; i++)
	{
		int sumOfDeviders = 0;
		for (int j = 1; j < (i-1); j++)
		{
			if (i % j == 0)
				sumOfDeviders += j;
		}
		if (sumOfDeviders == i)
			printf("[%d] Is a perfect number\n" ,i);
	}
}

void f_targil4()
{
	for (int i = 1000; i < 9901; i++)
		if (power((i % 100) + (i / 100), 2) == i)
			printf("[%d] is of the special type!\n",i);
}

//cant submit as requested "void f_targil5" 
//since for it to be recursive it needs to return a value
long long f_targil5(int n)
{
	if (n == 1)
		return 6;
	long long previous = f_targil5(n - 1);
	return (long long)(n - 1) * previous + (long long)(n - 1) * (n - 1);
}

int main() {
	
	//the non recursive part of Question 5:
	int n;
	printf("enter n (1 to 50): ");
	scanf("%d", &n);
	if (n >= 1 && n <= 50) {
		long long result = f_targil5(n);
		printf("The value of a_%d is: %lld\n", n, result);
	}
	else
		printf("n must be between 1 and 50.\n");
	return 0;
}