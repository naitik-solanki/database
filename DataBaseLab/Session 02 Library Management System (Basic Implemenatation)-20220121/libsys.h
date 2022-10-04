#ifndef LIBSYS_H
#define LIBSYS_H

#define BOOK_SUCCESS 0
#define BOOK_FAILURE 1

// Error codes
#define LIB_SUCCESS 0
#define LIB_FILE_ERROR 1
#define LIB_ADD_FAILED 2
#define LIB_REC_NOT_FOUND 3

// Repository status values
#define LIB_REPO_OPEN 10
#define LIB_REPO_CLOSED 11
#define LIB_REPO_ALREADY_OPEN 12

struct LibsysInfo{
	char libsys_name[30];
	FILE *libsys_data_fp;
	int repo_status; 
};

struct Book
{
	int isbn;
	char title[40];
	char author[40];
	float price;
};


int libsys_create( char *repo_name);

int libsys_open( char *repo_name );

int put_book_by_isbn( int isbn, struct Book *rec );

int get_book_by_isbn( int isbn, struct Book *rec );

int libsys_close();
#endif
