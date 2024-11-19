/* main.c */
#include <stdio.h>
#include <stdlib.h>
#include "bookarr.h"  /* for using the book array types and functions */
#include "book.h"		/* for using the book types and functions */


//typedef unsigned int size_t
/* debug memory leaks in Visual C++ */
#ifdef _DEBUG
//#include <crtdbg.h>
//#define CHECK_MEM    _CrtSetDbgFlag( _CRTDBG_LEAK_CHECK_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG)) 
#define CHECK_MEM
#else
#define CHECK_MEM
#endif

/* display menu to the user */;
void menu()
{
	printf("\n\n\n\n\n");
	puts("Book program main menu");
	puts("------------------------");
	puts("a. Add a book to the array");
	puts("d. Delete a book from the array");
	puts("i. Find a book by ID");
	puts("n. Find a book by name");
	puts("s. Sort the book array by ID");
	puts("b. Sort the book array by name");
	puts("p. Print all books");
	puts("x. Exit");
	puts("\n\n\n\n\n\n\n\n");
}

/* pause - wait for user confirmation */
void pause()
{
	puts("\nHit Enter to continue");
	getchar();
}

int main()
{
	int c;
	int  num;
	Array  array;
	Book  *pbook;
	String name, temp;
	array_init(&array);
	for(;;)  /* forever */
	{
		/* display menu */
		menu();

		c = getchar(); 
		gets(temp); /* read up to the newline character */
		switch(c)
		{
		case 'a': /* add Book */
			pbook = malloc(sizeof(Book));
			book_input(pbook);
			array_add_book(&array, pbook);
			pause();
			break;
		case 'd': /* delete Book */
			printf("Enter an ID of book to delete: ");
			if(scanf("%d", &num) == 1)  /* successfull read */
				array_del_book(&array, num);
			pause();
			break;
		case 'i': /* find a book by ID */
			printf("Enter a Book ID:");
			scanf("%d",&num);
			pbook = array_find_by_ID(&array, num);
			if(pbook)
				book_output(pbook);
			pause();
			break;
		case 'n': /* find a book by name */
			printf("Enter a Book name:");
			gets(name);
			pbook = array_find_by_name(&array, name);
			if(pbook)
				book_output(pbook);
			pause();
			break;
		case 's': /* sort the book array */
			array_sort(&array);
			pause();
			break;
		case 'p': /* print the book array */
			array_print(&array);
			pause();
			break;
		case 'b': /* sort */
			array_sort_by_bname(&array);
			pause();
			break;
		case 'x': /* Exit */
			array_clear(&array);
			return 0;
		default:
			break;
		}
	}
	return 0;
	CHECK_MEM;    
}
