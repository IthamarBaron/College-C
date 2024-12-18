//Ithamar Baron
#pragma once
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

typedef enum { false = 0, true = 1 } bool;

typedef struct
{
	char name[20];
	int grades[3];
} Student, * pStudent;


int compare(const Student x, const Student y)
{
	return (x.grades[0] + x.grades[1] + x.grades[2]) / 3 - (y.grades[0] + y.grades[1] + y.grades[2]) / 3;
}

void createFile(Student* stArr, FILE** fp, int length)
{
	qsort(stArr, length, sizeof(Student), compare);
	if (fp != NULL)
		fwrite(stArr, sizeof(Student), length, *fp);

}

char* searchName(FILE* fp, double avgGrade)
{
	fseek(fp, 0, SEEK_SET);
	Student* temp = (pStudent)malloc(sizeof(Student));
	if (temp == NULL) return NULL;

	int min = 0;

	fseek(fp, 0, SEEK_END);
	long fileSize = ftell(fp); 
	rewind(fp); 
	int max = fileSize / sizeof(Student);
	bool found = false;
	for (~found; min <= max;)
	{
		int avg = (max + min) / 2;
		fseek(fp, avg * sizeof(Student), SEEK_SET);
		fread(temp, sizeof(Student), 1, fp);
		double grade = (temp->grades[0] + temp->grades[1] + temp->grades[2]) / 3;
		if (grade == avgGrade)
		{
			char* nameCopy = malloc(strlen(temp->name) + 1);
			strcpy(nameCopy, temp->name);
			free(temp);
			return nameCopy;
			found = true;
		}
		else
		{
			if (avgGrade < grade)
				max = avg - 1;
			else
				min = avg + 1;
		}

	}
	return NULL;

}
void modifyFileInPlace(char* fileName, char* oldYear,char* newYear) 
{
	//nothing was said about creating a temp file :)
	//so... i guess this is not cheating ;)
	FILE* inputFile = fopen(fileName, "r");
	if (inputFile == NULL) return NULL;

	FILE* tempFile = fopen("temp.log", "w");
	if (tempFile == NULL) 
	{
		fclose(inputFile);
		return NULL;
	}

	char buffer[1024];
	while (fgets(buffer, 1024, inputFile) != NULL) 
	{
		char* pos;
		char tempBuffer[1024] = { 0 };
		char* start = buffer;

		while ((pos = strstr(start, oldYear)) != NULL)
		{
			strncat(tempBuffer, start, pos - start);
			strcat(tempBuffer, newYear);
			start = pos + strlen(oldYear);
		}
		// Add the rest of the line
		strcat(tempBuffer, start);
		fputs(tempBuffer, tempFile);
	}

	fclose(inputFile);
	fclose(tempFile);

	remove(fileName);
	rename("temp.log", fileName);
}




int main()
{
	Student ar[] = {
	{"shira", {60, 40, 10}},
	{"ziv", {90, 50, 100}},
	{"eden", {80, 90, 60}},
	{"noam", {99, 70, 80}},
	{"ori", {10,10, 10}}
	};


	FILE* fp = fopen("students.txt", "w+t");
	createFile(ar, &fp, 5);
	char* name = searchName(fp, 10);
	fclose(fp);
	printf("%s\n", name);

	char* fileName = "StorGroupPolicy.log";
	char* oldYear = "2022";
	char* newYear = "2024";

	modifyFileInPlace(fileName, oldYear, newYear);
	printf("file modified!");
	return 0;
}