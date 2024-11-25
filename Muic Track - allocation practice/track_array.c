/* Track_array2.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  /* for strcmp() */
#include "track_def.h"
#pragma warning(disable : 4996)



void output_one_Track(Track *Track)
{
    printf("\nTrack %d:\n", (Track->num));
    printf("\tname=%s\n", (Track->name));
    printf("\tartist=%s\n", Track->artist);
    printf("\tcategory=%s\n", Track->category);
    printf("\tlength=%.2f\n", Track->length);
    if (Track->album)
        printf("\tFrom album=%s\n", Track->album);
}

void input_one_Track(Track* Track)
{
	char temp[80]; // Temporary buffer for input

	printf("Enter Track name: ");
	gets(temp);
	Track->name = (char*) malloc(strlen(temp) + 1); 
	strcpy(Track->name, temp);             

	printf("Enter Artist name: ");
	gets(temp);
	Track->artist = (char*)malloc(strlen(temp) + 1);
	strcpy(Track->artist, temp);

	printf("Enter Category: ");
	gets(temp);
	Track->category = (char*)malloc(strlen(temp) + 1);
	strcpy(Track->category, temp);

	printf("Enter length: ");
	scanf_s("%f", &Track->length);
	gets(temp); 

	printf("Enter Album name: ");
	gets(temp);
	Track->album = (char*)malloc(strlen(temp) + 1);
	strcpy(Track->album, temp);
}




/* initialize the array by input from the user */
void input_Track_array(Track arr[], int array_size)
{
	int i;
	for (i=0; i<array_size; i++)
	{
		input_one_Track(&arr[i]);
		arr[i].num = i+1;
	}
}


/* output array elements  */
void output_Track_array(Track arr[], int array_size)
{
	int i;

	printf("\nArray elements:\n");
	for (i=0; i<array_size; i++)
		output_one_Track(&arr[i]);
}


/* find a Track according to it's name */
int find_Track_by_name(Track arr[], int array_size, char name[])
{
	int i;

	for(i=0; i<array_size; i++)
		if(strcmp(arr[i].name, name)==0)
			return i;
	return NOT_FOUND;
}

/* find the longest Track and return it's index in the array */
int find_longest_Track(Track arr[], int array_size)
{
	int i;
	int   index = 0;
	float max = arr[0].length;
	for(i=1; i<array_size; i++)
	{
		if(arr[i].length > max)
		{
			max = arr[i].length;
			index = i;
		}
	}
	return index;
}



/* is a given serial num exist in the array */
int exist(Track arr[], int array_size, int num)
{
	int i;
	for(i=0; i<array_size; i++)
		if(arr[i].num == num)
			return 1; /* exist */
	return 0;	/* does not exist */
}

/* swap between 2 Track's in the array */
void swap(Track *pTrack1, Track *pTrack2)
{
	Track temp = *pTrack1;
	*pTrack1 = *pTrack2;
	*pTrack2 = temp;
}


/* sort the array by the Track's names in ascending order */
void sort_by_name(Track arr[], int array_size)
{
	int i,j;

	for(i=0; i<array_size - 1; i++) 
		for(j=0; j<array_size - 1 - i; j++) 
			if(strcmp(arr[j].name, arr[j+1].name) >0) 
				swap(&arr[j], &arr[j+1]);
}


int main()
{
	enum {ARRAY_SIZE=1};
	int num,index;
	Track  track_array[ARRAY_SIZE];

	/* initialize the array */
	input_Track_array(track_array, ARRAY_SIZE);
	
	/* find most expensive Track in the array */
	printf("\nThe longest Track index is:");
	index = find_longest_Track(track_array, ARRAY_SIZE);
	output_one_Track(&track_array[index]);
	
	
	/* is a given num exist in the array */
	printf("\nEnter a serial num to find in the Track array:");
	scanf_s("%d",&num);
	if(exist(track_array, ARRAY_SIZE, num))
		printf("\nTrack num %d exist in the array", num);
	else
		printf("\nThe Track does not exist in the array");
	printf("\nHit any key");
	getchar();

	/* sort the array by length */
	printf("\nSorting the array by name...");
	sort_by_name(track_array, ARRAY_SIZE);
	output_Track_array(track_array, ARRAY_SIZE);

	return 0;
}
