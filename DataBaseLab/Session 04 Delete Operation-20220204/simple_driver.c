#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "libsys.h"


// You can use the following macro to report test result
// Do NOT put a semicolon after calling the macro (see examples below)

#define TREPORT(tid,result) { printf("Test-case-id %s:%s\n",tid,result); fflush(stdout); }

int main()
{
	char *repo_name = "demo";
	libsys_create(repo_name);
	int status;
	struct Book testContact;
	char *test_case_id;

	testContact.isbn = 10000;
	strcpy(testContact.title, "dummy name");
	strcpy(testContact.author, "dummy author");

	test_case_id = "01";
	status = libsys_open( repo_name );
	if( status == LIB_SUCCESS ){
		TREPORT(test_case_id,"SUCCESS")
	}
	else{
		TREPORT(test_case_id,"FAIL")
		exit(status);
	}

	test_case_id = "02";
	testContact.isbn = 10000;
	status = put_book_by_isbn(testContact.isbn, &testContact );
	if( status == BOOK_SUCCESS )
		TREPORT(test_case_id,"SUCCESS")
	else
		TREPORT(test_case_id,"FAIL")


	test_case_id = "03";
	status = get_book_by_isbn( 10000, &testContact );
	if( status == BOOK_SUCCESS )
		TREPORT(test_case_id,"SUCCESS")
	else
		TREPORT(test_case_id,"FAIL")

	test_case_id = "04";
	if( testContact.isbn == 10000  && 
		strcmp(testContact.title,"dummy name") == 0 &&
		strcmp(testContact.author,"dummy author") == 0 )
	{

		TREPORT(test_case_id,"SUCCESS")
	}
	else
		TREPORT(test_case_id,"FAIL")

	test_case_id = "05";
	status = libsys_close();
	if( status == BOOK_SUCCESS ){
		TREPORT(test_case_id,"SUCCESS")
	}
	else{
		TREPORT(test_case_id,"FAIL")
		exit(status);
	}

	test_case_id = "06";
	status = libsys_open( repo_name );
	if( status == LIB_SUCCESS ){
		TREPORT(test_case_id,"SUCCESS")
	}
	else{
		TREPORT(test_case_id,"FAIL")
		exit(status);
	}

	test_case_id = "07";
	status = get_book_by_isbn( 10000, &testContact );
	if( status == BOOK_SUCCESS )
		TREPORT(test_case_id,"SUCCESS")
	else
		TREPORT(test_case_id,"FAIL")

	test_case_id = "08";
	if( testContact.isbn == 10000  && 
		strcmp(testContact.title,"dummy name") == 0 &&
		strcmp(testContact.author,"dummy author") == 0 )

		TREPORT(test_case_id,"SUCCESS")
	else
		TREPORT(test_case_id,"FAIL")

	test_case_id = "09";
	status = delete_book_by_isbn( 10000 );
	if( status == BOOK_SUCCESS )
		TREPORT(test_case_id,"SUCCESS")
	else
		TREPORT(test_case_id,"FAIL")

	test_case_id = "09";
	status = delete_book_by_isbn( 10000 );
	if( status == BOOK_SUCCESS )
		TREPORT(test_case_id,"SUCCESS")
	else
		TREPORT(test_case_id,"FAIL")

	testContact.isbn = 10000;
	strcpy(testContact.title, "dummy name");
	strcpy(testContact.author, "dummy author");

	test_case_id = "10";
	testContact.isbn = 10000;
	status = put_book_by_isbn(testContact.isbn, &testContact );
	if( status == BOOK_SUCCESS )
		TREPORT(test_case_id,"SUCCESS")
	else
		TREPORT(test_case_id,"FAIL")


	test_case_id = "11";
	status = get_book_by_isbn( 10000, &testContact );
	if( status == BOOK_SUCCESS )
		TREPORT(test_case_id,"SUCCESS")
	else
		TREPORT(test_case_id,"FAIL")

	test_case_id = "12";
	if( testContact.isbn == 10000  && 
		strcmp(testContact.title,"dummy name") == 0 &&
		strcmp(testContact.author,"dummy author") == 0 )
	{

		TREPORT(test_case_id,"SUCCESS")
	}
	else
		TREPORT(test_case_id,"FAIL")



	test_case_id = "13";
	status = libsys_close();
	if( status == LIB_SUCCESS ){
		TREPORT(test_case_id,"SUCCESS")
	}
	else{
		TREPORT(test_case_id,"FAIL")
		exit(status);
	}
	return 0;
}


