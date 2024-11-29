#pragma once
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

typedef struct 
{
	char* name;
	int faculty;
	float scores[3];
	float avg;

} student, *studentPtr;

studentPtr Innit_Student()
{
	studentPtr s = (studentPtr)malloc(sizeof(student));
	if (s==NULL) return NULL;
	s->name = (char*)malloc(sizeof(char) * 8);// avg name length is 7
	if (s->name == NULL) return NULL;
	s->name[7] = '\0';
	s->faculty = -1;
	for (int i = 0; i < 3; i++)
		s->scores[i] = -1;
	s->avg = 0;
}

void InputStudent(studentPtr s)
{
	char temp[15];
	printf("====Enter Stats====\n");
	printf("Enter name:");
	scanf("%14s", temp);
	if (s->name != NULL)
		free(s->name);
	s->name = (char*)malloc(sizeof(char) * strlen(temp) + 1);
	if (s->name == NULL)
	{
		printf("ALLOCATION FAILED!!!\n");
		return NULL;
	}
	strcpy(s->name, temp);
	printf("Enter Faculty: ");
	scanf("%d", &s->faculty);
	
	for (int i = 0; i < 3; i++)
	{
		printf("Enter score [%d/3]: ", i + 1);
		scanf("%f", &s->scores[i]);
	}

	s->avg = (s->scores[0] + s->scores[1] + s->scores[2]) / 3.0f;
}

void PrintStudent(studentPtr s) 
{
	puts("Student Info:");
	printf("Name %s: ",s->name);
	printf("\nFaculty: %d", s->faculty);
	puts("\n     Scores:\n------------------");
	printf("%.2f\t%.2f\t%.2f", s->scores[0], s->scores[1], s->scores[2]);
	printf("\nAverage: %f \n", s->avg);
	printf("\n\n\n");
}

void AvgGrade(studentPtr students[],int length)
{
	//average is already calculated at input
	float max = 0;
	for (int i = 0; i < length; i++)
		max = max < students[i]->avg ? students[i]->avg : max;

	printf("Students With Highest Average:\n");
	for (int i = 0; i < length; i++)
	{
		if (students[i]->avg == max)
			PrintStudent(students[i]);
	}
}

void DeptStats(studentPtr students[], int length, int facultyID)
{
	int amountInFaculty = 0;
	float sumOfAvgs = 0;
	float avg = 0;
	for (int i = 0; i < length; i++)
	{
		if (students[i]->faculty == facultyID)
		{
			amountInFaculty++;
			sumOfAvgs += students[i]->avg;
		}
	}
	avg = sumOfAvgs / amountInFaculty;
	printf("====Faculty %d====", facultyID);
	printf("\nStudents in faculty: %d", amountInFaculty);
	printf("\nFaculty grade average: %f\n", avg);
}

int main()
{
	studentPtr students[10];
	for (int i = 0; i < 10; i++)
	{
		students[i] = Innit_Student();
		InputStudent(students[i]);
		PrintStudent(students[i]);
	}
	AvgGrade(students, 10);
	DeptStats(students, 10, 1);

	return 0;
}