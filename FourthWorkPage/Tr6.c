#include <stdio.h>

int MidMax(float a, float b, float c)
{
	return (a < b&& c < b);
}

int CountPeaks(int hights[], int size)
{
	int peaks = 0;
	for (int i = 1; i < size - 1; i++)
		peaks += MidMax(hights[i - 1], hights[i], hights[i + 1]);
	return peaks;
}

int main()
{
	int arr[] = { 206, 350 ,300 ,167 ,406 ,310 ,328 ,250 ,200, 120 ,400 ,380 ,435, 200, 337 ,200 };
	int peaks = CountPeaks(arr, 16);
	printf("peaks %d", peaks);

	return 0;
}