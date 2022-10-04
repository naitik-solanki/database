#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "libsys.h"


// You can use the following macro to report test result
// Do NOT put a semicolon after calling the macro (see examples below)

#define TREPORT(tid,result) { printf("Test-case-id %s:%s\n",tid,result); fflush(stdout); }

int main()
{
	char *stud_repo_name = "stud_demo.dat";
	char *book_repo_name = "book_demo.dat";
	char *issue_repo_name= "issue.dat";

	

	int status;
	struct Book testContact;
	char *test_case_id;


	test_case_id = "01";
	status = libsys_create(book_repo_name,stud_repo_name,issue_repo_name);
	if( status == LIB_SUCCESS ){
		TREPORT(test_case_id,"SUCCESS")
	}
	else{
		TREPORT(test_case_id,"FAIL")
		exit(status);
	}
	testContact.isbn = 10000;
	strcpy(testContact.title, "dummy name");
	strcpy(testContact.author, "dummy author");

	test_case_id = "02";
	status = libsys_open(book_repo_name,stud_repo_name,issue_repo_name);
	if( status == LIB_SUCCESS ){
		TREPORT(test_case_id,"SUCCESS")
	}
	else{
		TREPORT(test_case_id,"FAIL")
		exit(status);
	}

	test_case_id = "03";
	testContact.isbn = 10000;
	status = put_book_by_isbn(testContact.isbn, &testContact );
	if( status == BOOK_SUCCESS )
		TREPORT(test_case_id,"SUCCESS")
	else
		TREPORT(test_case_id,"FAIL")


	test_case_id = "04";
	status = get_book_by_isbn( 10000, &testContact );
	if( status == BOOK_SUCCESS )
		TREPORT(test_case_id,"SUCCESS")
	else
		TREPORT(test_case_id,"FAIL")

	test_case_id = "05";
	if( testContact.isbn == 10000  && 
		strcmp(testContact.title,"dummy name") == 0 &&
		strcmp(testContact.author,"dummy author") == 0 )
	{

		TREPORT(test_case_id,"SUCCESS")
	}
	else
		TREPORT(test_case_id,"FAIL")



	test_case_id = "06";
	status = get_book_by_isbn( 10000, &testContact );
	if( status == BOOK_SUCCESS )
		TREPORT(test_case_id,"SUCCESS")
	else
		TREPORT(test_case_id,"FAIL")

	test_case_id = "07";
	if( testContact.isbn == 10000  && 
		strcmp(testContact.title,"dummy name") == 0 &&
		strcmp(testContact.author,"dummy author") == 0 )

		TREPORT(test_case_id,"SUCCESS")
	else
		TREPORT(test_case_id,"FAIL")


	
	struct Student testStudent;
	

	testStudent.rollno = 10000;
	strcpy(testStudent.name, "dummy name");
	strcpy(testStudent.address, "dummy address");



	test_case_id = "8";
	testStudent.rollno = 10000;
	status = put_student_by_rollno(testStudent.rollno, &testStudent );
	if( status == BOOK_SUCCESS )
		TREPORT(test_case_id,"SUCCESS")
	else
		TREPORT(test_case_id,"FAIL")


	test_case_id = "9";
	status = get_student_by_rollno( 10000, &testStudent );
	if( status == BOOK_SUCCESS )
		TREPORT(test_case_id,"SUCCESS")
	else
		TREPORT(test_case_id,"FAIL")

	test_case_id = "10";
	if( testStudent.rollno == 10000  && 
		strcmp(testStudent.name,"dummy name") == 0 &&
		strcmp(testStudent.address,"dummy address") == 0 )
	{

		TREPORT(test_case_id,"SUCCESS")
	}
	else
		TREPORT(test_case_id,"FAIL")



	test_case_id = "11";
	status = get_student_by_rollno( 10000, &testStudent );
	if( status == BOOK_SUCCESS )
		TREPORT(test_case_id,"SUCCESS")
	else
		TREPORT(test_case_id,"FAIL")

	test_case_id = "12";
	if( testStudent.rollno == 10000  && 
		strcmp(testStudent.name,"dummy name") == 0 &&
		strcmp(testStudent.address,"dummy address") == 0 )
		{
		TREPORT(test_case_id,"SUCCESS")
		}
	else
		TREPORT(test_case_id,"FAIL")
	
	//printf("yo\n");
	test_case_id = "13";
	status = issue( 10000, 10000 );
	if( status==LIB_SUCCESS )

		TREPORT(test_case_id,"SUCCESS")
	else
		TREPORT(test_case_id,"FAIL")

	test_case_id = "14";
	status = issue( 10080, 10050 );
	if( status==LIB_SUCCESS )

		TREPORT(test_case_id,"SUCCESS")
	else
		TREPORT(test_case_id,"FAIL")

	

	test_case_id = "15";
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


