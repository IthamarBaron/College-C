/* bookarr.c - An implementation file for the book array */
#include <stdio.h>
#include <string.h>  /* for strcmp() */
#include <stdlib.h>  

#include "bookarr.h"
#include "book.h"
#define ARR_INIT_SIZE 3

/************** FUNCTION BODIES ************************/
int compare(const void* element1, const void* element2)
{
	BookPtr pbook1 = *(BookPtr*)element1;
	BookPtr pbook2 = *(BookPtr*)element2;
	return strcmp(pbook1->name, pbook2->name);
}
void array_sort_by_bname(Array* parray)
{
	qsort((void*)parray->array, parray->count, sizeof(BookPtr), compare);
}


/*realoc the book array to twice its size*/
void array_realloc(Array* parray)
{
	int length = parray->size;
	parray->array = (BookPtr*)realloc(parray->array, sizeof(BookPtr)*2*length);
	if (parray != NULL)
		parray->size *= 2;
}

/* initialize the book array */
void array_init(Array *parray)
{
	parray->count = 0;
	parray->array = (BookPtr*)malloc(ARR_INIT_SIZE*sizeof(BookPtr));
	parray->size = ARR_INIT_SIZE;
}

/* is the array full? */
Boolean array_is_full(Array *parray)
{
	return parray->count == ARR_SIZE;
}

/* clear and free the array nodes */
void array_clear(Array *parray)
{
	int i;
	for(i=0; i < parray->count; i++)
		book_clear(parray->array[i]); /* free allocated memory in the book struct */
	parray->count = 0;
}

/* add a new book to the array */
void array_add_book(Array *parray, BookPtr pbook)
{
	if (array_is_full(parray))
		array_realloc(parray); //updates `size` inside of the realloc method
	parray->array[parray->count] = pbook;
	parray->count++;
}

/* delete a book from the array */
void array_del_book(Array *parray, int num)
{
	int i,j;
	for(i=0; i < parray->count; i++)
	{
		if(parray->array[i]->ID == num)
		{
			book_clear(parray->array[i]); /* clear the book allocated memory */
			/* move the following books one place backward */
			for(j=i; j < parray->count-1; j++) 
				parray->array[j] = parray->array[j+1];
			parray->count--;
			return;
		}
	}
}

/* find a book according to it's name */
BookPtr array_find_by_name(Array *parray, String name)
{
	int i;
	for(i=0; i < parray->count; i++)
		if(strcmp(parray->array[i]->name, name)==0)
			return parray->array[i];
	return NULL;  /* not found */
}

/* find a book according to it's ID */
BookPtr array_find_by_ID(Array *parray, int ID)
{
	int i;
	for(i=0; i < parray->count; i++)
		if(parray->array[i]->ID == ID)
			return parray->array[i];
	return NULL;  /* not found */
}

/*
void swap(BookPtr *ppbook1, BookPtr *ppbook2)
{
	BookPtr temp = *ppbook1;
	*ppbook1 = *ppbook2;
	*ppbook2 = temp;

}
*/

/* sort the array by the book ID in an ascending order */
void array_sort(Array *parray)
{
/*
	int i,j;
	for(i=0; i < parray->count - 1; i++) 
		for(j=0; j < parray->count- 1 - i; j++) 
			if(parray->array[j]->ID > parray->array[j+1]->ID) 
				swap(&parray->array[j], &parray->array[j+1]);
*/
	qsort((void *)parray->array, (size_t)parray->count, sizeof(BookPtr), book_compare);
}

/* output book array  */
void array_print(Array *parray)
{
	int i;
	printf("\nBooks:\n");
	for(i=0; i < parray->count; i++)
		book_output(parray->array[i]);
}
