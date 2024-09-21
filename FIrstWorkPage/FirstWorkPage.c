//Questions 1-2 open comment
/*
Question 1A: num will be 0, it will start with 100 then 99 then NOT 99, 99 is true, therefor NOT TRUE is FALSE, false is 0

Question 1B:
	leftover = 1 (the remainder when amount (11) is divided by 10).
	price = 5 (initially incremented to 6, then decremented back to 5).
	to_pay = 55 (price (5) multiplied by amount (11) before the decrement).
	total = 55 (price (5) multiplied by amount (11) before the post-decrement, which reduces amount to 10 after the calculation).

Question 2:
	int a,b,c;
	a = 10;
	a += a++;
	// a = 20
	//******************
	a = 10;
	a += ++a;
	// a = 21
	//******************
	a = 10;
	a *= a + a;
	// a = 200
	//******************
	a = 10;
	a *= a++;
	// a = 100
	//******************
	a = 10;
	b = 9;
	a = 5 + (c *= b + c++);
	// a = ERROR, C WAS NEVER DEFINED
	//******************
	a = 10;
	b = 9;
	a *= (a + b) + (a + b);
	// a = 380

*/


#pragma warning(disable : 4996)
#include <stdio.h>

void Question3() {
	int totalSeconds, hours, minutes, seconds;

	printf("Enter time in seconds: ");
	scanf("%d", &totalSeconds);
	hours = totalSeconds / 3600;
	totalSeconds %= 3600;
	minutes = totalSeconds / 60;
	seconds = totalSeconds % 60;

	printf("%02d:%02d:%02d\n", hours, minutes, seconds);
}


void Question4() {

	float A, B, C, MAX;

	printf("Enter the first number (A): ");
	scanf("%f", &A);
	printf("Enter the second number (B): ");
	scanf("%f", &B);
	printf("Enter the third number (C): ");
	scanf("%f", &C);

	float max = A; // Assume A is the maximum
	if (B > max) {
		max = B; 
	}
	if (C > max) {
		max = C; 
	}
	printf("MAX NUMBER IS %.2f\n", max);
}



void Question5() {

	float A, B, C;

	printf("Enter the first number (A): ");
	scanf("%f", &A);
	printf("Enter the second number (B): ");
	scanf("%f", &B);
	printf("Enter the third number (C): ");
	scanf("%f", &C);

	if ((A + B > C) && (A + C > B) && (B + C > A))
	{
		int isIsosceles = (A == B) || (A == C) || (B == C);

		// Calculate the squares of the sides
		float a2 = A * A;
		float b2 = B * B;
		float c2 = C * C;

		if (a2 + b2 > c2 && a2 + c2 > b2 && b2 + c2 > a2)//חד
			printf("The triangle is acute.\n");
		else if (a2 + b2 == c2 || a2 + c2 == b2 || b2 + c2 == a2) //ישר
			printf("The triangle is right.\n");
		else
			printf("The triangle is obtuse.\n");//קהה

		if (isIsosceles)
			printf("The triangle is isosceles.\n");//משוש
		else
			printf("The triangle is not isosceles.\n");
	}

}

void Question6() {

	//IDEA: compare A and D, swap if needed. Compare b and c, swap if needed.
	float A, B, C, D;

	printf("Enter four real numbers:\n");
	scanf("%f %f %f %f", &A, &B, &C, &D);

	// Find the minimum and maximum values
	float min = A;
	float max = A;

	if (B < min) min = B;
	if (C < min) min = C;
	if (D < min) min = D;

	if (B > max) max = B;
	if (C > max) max = C;
	if (D > max) max = D;

	// Assign the minimum and maximum to A and D
	A = min;
	D = max;

	// Use a temporary variable to sort B and C
	float temp;
	if (B > C) {
		temp = B;
		B = C;
		C = temp;
	}

	// Print the sorted values
	printf("A (min): %.2f\n", A);
	printf("B: %.2f\n", B);
	printf("C: %.2f\n", C);
	printf("D (max): %.2f\n", D);
}


int main() {

	//Question3 test
	Question3();

	//Question 4 test
	Question4();

	//Question 5 test
	Question5();

	//Question 6 test
	Question6();


	return 0;
}
