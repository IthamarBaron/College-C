/* book.h - an interface for the book */

#ifndef BOOK_H
#define BOOK_H

/************** CONSTANTS ****************************/
#define MAX_STR_LEN		256
#pragma warning(disable:4996)

/************** TYPES ********************************/
typedef char String[MAX_STR_LEN];

/* Book type */
typedef struct
{
	char* name;
	char* writer;
	char* publisher;
	float	cost;
	int		year;
	int		ID;
} Book;

typedef Book* BookPtr; /* a pointer to Book struct */

/************** FUNCTION PROTOTYPES ********************/
void	book_input(BookPtr pbook);
void	book_output(BookPtr pbook);
void	book_clear(BookPtr pbook);
int		book_compare(const void* ppbook1, const void* ppbook2);
void	book_save_to_file(FILE* fp, BookPtr pbook);
char* getline(FILE* fp);
void book_read_from_file(FILE* fp, BookPtr pbook);

#endif