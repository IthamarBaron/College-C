/* book.c - An implementation file for the Book */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book.h"

/************** FUNCTION BODIES ************************/

/* print one book data to the standard output */
void book_output(BookPtr pbook)
{
	printf("book %s:\n", pbook->name);
	printf("\twriter=%s\n", pbook->writer);
	printf("\tpublisher=%s\n", pbook->publisher);
	printf("\tyear=%d\n", pbook->year);
	printf("\tcost=%.2f\n", pbook->cost);
	printf("\tID=%d\n", pbook->ID);
}

/* read and initialize book data from the standard input */
void book_input(BookPtr pbook)
{
	String temp;
	puts("Enter book name, writer, and publisher separated by newlines:");
	gets(temp);
	pbook->name = _strdup(temp);
	gets(temp);
	pbook->writer = _strdup(temp);
	gets(temp);
	pbook->publisher = _strdup(temp);

	printf("Enter publishing year:");
	scanf("%d", &pbook->year);
	printf("Enter cost:");
	scanf("%f", &pbook->cost);
	printf("Enter ID:");
	scanf("%d", &pbook->ID);
	gets(temp); /* to read up to the end of line */
}

/* free the book allocated memory */
void book_clear(BookPtr pbook)
{
	free(pbook->name);
	free(pbook->writer);
	free(pbook->publisher);
	free(pbook);
}

/* compare 2 books and return:*/
/*		value > 0		if book1 > book2
		value < 0		if book1 < book2
		value = 0		if book1== book2
*/
int book_compare(const void* ppbook1, const void* ppbook2)
{
	BookPtr pbook1 = *(BookPtr*)ppbook1;
	BookPtr pbook2 = *(BookPtr*)ppbook2;

	return pbook1->ID - pbook2->ID;
}

void book_save_to_file(FILE* fp, BookPtr pbook)
{
	fprintf(fp, "\n%s\n%s\n%s\n%d\n%f\n%d",
	pbook->name, pbook->writer, pbook->publisher, pbook->year, pbook->cost, pbook->ID);
}
char* getline(FILE* fp)
{

	String temp;
	fgets(temp, MAX_STR_LEN, fp);
	temp[strlen(temp) - 1] = '\0'; /* instead of the '\n' inserted by fgets */
	return strdup(temp);

}
void book_read_from_file(FILE* fp, BookPtr pbook)
{
	String temp;
	pbook->name = getline(fp);
	pbook->writer = getline(fp);
	pbook->publisher = getline(fp);
	fscanf(fp, "%d", &pbook->year);
	fscanf(fp, "%f", &pbook->cost);
	fscanf(fp, "%d", &pbook->ID);
	fgets(temp, MAX_STR_LEN, fp); /* to read up to the end of line */
}
