/* bookarr.h - an interface to the book array */

#ifndef BOOK_ARR_H
#define BOOK_ARR_H

#include "book.h"

/************** CONSTANTS ******************************/
#define ARR_SIZE 1000

/**************** TYPES *******************************/
typedef enum { FALSE = 0, TRUE = 1 } Boolean;

/* array structure */
typedef struct
{
	BookPtr* array;	/* pointer to the bookPtr array */
	int			size;	/*length of the array*/
	int			count;		/* number of elements in the array */
	Boolean changed_fl; /* array change flag */
} Array;

/************** FUNCTION PROTOTYPES *******************/

void	array_init(Array* parray);
void	array_clear(Array* parray);
Boolean	array_is_full(Array* parray);
void	array_add_book(Array* parray, BookPtr pbook);
void	array_del_book(Array* parray, int num);
BookPtr array_find_by_ID(Array* parray, int ID);
BookPtr array_find_by_name(Array* parray, String name);
void	array_sort(Array* parray);
void	array_print(Array* parray);
void array_sort_by_bname(Array* parray);
void array_save_to_file(Array* parray, char* file_name);
void array_load_from_file(Array* parray, char* file_name);
void array_check_for_save(Array* plist, char* file_name);
#endif