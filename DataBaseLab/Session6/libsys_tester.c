#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "libsys.h"

#define TREPORT(a1,a2) printf("Status %s: %s\n\n",a1,a2); fflush(stdout);

void process_line( char *test_case );

int main(int argc, char *argv[])
{
	FILE *cfptr;
	char test_case[50];

	if( argc != 2 ){
		fprintf(stderr, "Usage: %s testcasefile\n", argv[0]);
		exit(1);
	}

	cfptr = (FILE *) fopen(argv[1], "r");
	while(fgets(test_case, sizeof(test_case)-1, cfptr)){
		// printf("line:%s",test_case);
		if( !strcmp(test_case,"\n") || !strcmp(test_case,"") )
			continue;
		process_line( test_case );
	}
	return 0;
}


void process_line( char *test_case )
{

	char book_repo_name[30],stud_repo_name[30],issue_repo_name[30],temp[30];
	char command[30], param1[10], param2[10], info[1000],param3[10];
	int isbn, status, book_rec_size, expected_status;
	char title[30],name[30];
	int rollno, stud_rec_size;

	struct Book testBook;
	struct Student testStudent;

	book_rec_size = sizeof(struct Book);
	stud_rec_size = sizeof(struct Student);

	sscanf(test_case, "%s %s %s %s", command, param1, param2,param3);
	
	printf("Test case: %s", test_case); fflush(stdout);
	if( !strcmp(command,"CREATE") ){

		strcpy(temp, param1);
		strcat(temp, "Book");
		strcpy(book_repo_name, temp);

		strcpy(temp, param1);
		strcat(temp, "Student");
		strcpy(stud_repo_name, temp);

		strcpy(temp, param1);
		strcat(temp, "Issue");
		strcpy(issue_repo_name, temp);

		if( !strcmp(param2,"0") )
			expected_status = BOOK_SUCCESS;
		else
			expected_status = BOOK_FAILURE;
		
		status = libsys_create( book_repo_name,stud_repo_name,issue_repo_name );
		if( status == expected_status ){
			TREPORT("PASS", "");
		}
		else{
			sprintf(info,"libsys_open returned status %d",status);
			TREPORT("FAIL", info);
		}
	}

	strcpy(testBook.title, "YOGI");
	strcpy(testBook.author, "yoganand");

	strcpy(testStudent.name, "ABC");
	strcpy(testStudent.address, "#219");
	
	testBook.price = 120;
	testStudent.cgpa = 3.2;

	
	if( !strcmp(command,"OPEN") ){
		strcpy(temp, param1);
		strcat(temp, "Book");
		strcpy(book_repo_name, temp);

		strcpy(temp, param1);
		strcat(temp, "Student");
		strcpy(stud_repo_name, temp);

		strcpy(temp, param1);
		strcat(temp, "Issue");
		strcpy(issue_repo_name, temp);

		if( !strcmp(param2,"0") )
			expected_status = BOOK_SUCCESS;
		else
			expected_status = BOOK_FAILURE;

		status = libsys_open( book_repo_name,stud_repo_name,issue_repo_name  );
		if(status == LIB_SUCCESS)
			status = BOOK_SUCCESS;
		else
			status = BOOK_FAILURE;
		if( status == expected_status ){
			TREPORT("PASS", "");
		}
		else{
			sprintf(info,"libsys_open returned status %d",status);
			TREPORT("FAIL", info);
		}
	}


	else if( !strcmp(command,"ADD_BOOK") ){
		if( !strcmp(param2,"0") )
			expected_status = BOOK_SUCCESS;
		else
			expected_status = BOOK_FAILURE;

		sscanf(param1, "%d", &isbn);
		testBook.isbn = isbn;
		status = put_book_by_isbn( isbn, &testBook );
		if(status == LIB_SUCCESS)
			status = BOOK_SUCCESS;
		else
			status = BOOK_FAILURE;
		if( status == expected_status ){
			TREPORT("PASS", "");
		}
		else{
			sprintf(info,"put_book_by_isbn returned status %d",status);
			TREPORT("FAIL", info);
		}
	}

	else if(!strcmp(command,"ADD_STUDENT") ){
		if( !strcmp(param2,"0") )
			expected_status = BOOK_SUCCESS;
		else
			expected_status = BOOK_FAILURE;

		sscanf(param1, "%d", &rollno);
		testStudent.rollno = rollno;
		status = put_student_by_rollno( rollno, &testStudent );
		if(status == LIB_SUCCESS)
			status = BOOK_SUCCESS;
		else
			status = BOOK_FAILURE;
		if( status == expected_status ){
			TREPORT("PASS", "");
		}
		else{
			sprintf(info,"put_student_by_rollno returned status %d",status);
			TREPORT("FAIL", info);
		}
	}

	else if( !strcmp(command,"SEARCH_BOOK_ISBN") ){
		if( !strcmp(param2,"0") )
			expected_status = BOOK_SUCCESS;
		else
			expected_status = BOOK_FAILURE;

		sscanf(param1, "%d", &isbn);
		testBook.isbn = -1;
		status = get_book_by_isbn( isbn, &testBook );
		if(status == LIB_SUCCESS)
			status = BOOK_SUCCESS;
		else
			status = BOOK_FAILURE;
		if( status != expected_status ){
			sprintf(info,"search key: %d; Got status %d",isbn, status);
			TREPORT("FAIL", info);
		}
		else{
			if( expected_status == 0 )
			{
				if (testBook.isbn == isbn && strcmp(testBook.title,"YOGI") == 0 && strcmp(testBook.author,"yoganand") == 0 && testBook.price == 120)
				{
						TREPORT("PASS", "");
				}
				else
				{
					sprintf(info,"data doesn't match Expected:{%d,%s,%s,%f} Got:{%d,%s,%s,%f}\n",
						isbn, "YOGI", "yoganand",120, 
						testBook.isbn, testBook.title, testBook.author, testBook.price
					);
					TREPORT("FAIL", info);
				}
			}
			else
			{
				TREPORT("PASS", "");
			}
		}
	}

	else if( !strcmp(command,"SEARCH_BOOK_TITLE") ){
		if( !strcmp(param2,"0") )
			expected_status = BOOK_SUCCESS;
		else
			expected_status = BOOK_FAILURE;

		sscanf(param1, "%s", title);
		strcpy(testBook.title,"");
		status = get_book_by_title( title, &testBook );
		if(status == LIB_SUCCESS)
			status = BOOK_SUCCESS;
		else
			status = BOOK_FAILURE;
		if( status != expected_status ){
			sprintf(info,"search key: %s; Got status %d",title, status);
			TREPORT("FAIL", info);
		}
		else{
			if( expected_status == 0 )
			{
				if (testBook.isbn == 10000 && strcmp(testBook.title, title) == 0 && strcmp(testBook.author,"yoganand") == 0 &&testBook.price == 120)
				{
						TREPORT("PASS", "");
				}
				else
				{
					sprintf(info,"Data not matching... Expected:{%d,%s,%s,%f} Got:{%d,%s,%s,%f}\n",
						isbn, "YOGI", "yoganand",120, 
						testBook.isbn, testBook.title, testBook.author, testBook.price
					);
					TREPORT("FAIL", info);
				}
			}
			else
				TREPORT("PASS", "");
		}
	}

	else if( !strcmp(command,"SEARCH_STUDENT_NAME") )
	{
		if( !strcmp(param2,"0") )
			expected_status = BOOK_SUCCESS;
		else
			expected_status = BOOK_FAILURE;

		sscanf(param1, "%s", name);
		strcpy(testStudent.name,"");
		status = get_student_by_name( name, &testStudent );
		if(status == LIB_SUCCESS)
			status = BOOK_SUCCESS;
		else
			status = BOOK_FAILURE;
		if( status != expected_status )
		{
			sprintf(info,"searched key: %s; Got status %d",name, status);
			TREPORT("FAIL", info);
		}
		else{
			// Check if the retrieved values match with what was stored earlier
			if( expected_status == 0 ){
				if (testStudent.rollno == 1 && strcmp(testStudent.name, name) == 0 &&strcmp(testStudent.address,"#219") == 0 && testStudent.cgpa == 3.2)
				{
						TREPORT("PASS", "");
				}
				else
				{
					sprintf(info,"Data doesn't match Expected:{%d,%s,%s,%f} Got:{%d,%s,%s,%f}\n",
						rollno, "ABC", "#219",3.2, 
						testStudent.rollno, testStudent.name, testStudent.address, testStudent.cgpa
					);
					TREPORT("FAIL", info);
				}
			}
			else
				TREPORT("PASS", "");
		}
	}

	else if( !strcmp(command,"DELETE_BOOK") ){
		if( !strcmp(param2,"0") )
			expected_status = BOOK_SUCCESS;
		else
			expected_status = BOOK_FAILURE;

		sscanf(param1, "%d", &isbn);
		testBook.isbn = isbn;
		status = delete_book_by_isbn( isbn );
		if(status == LIB_SUCCESS)
			status = BOOK_SUCCESS;
		else
			status = BOOK_FAILURE;
		if( status == expected_status ){
			TREPORT("PASS", "");
		}
		else{
			sprintf(info,"delete_book_by_isbn returned status %d",status);
			TREPORT("FAIL", info);
		}
	}

	else if( !strcmp(command,"DELETE_STUDENT") ){
		if( !strcmp(param2,"0") )
			expected_status = BOOK_SUCCESS;
		else
			expected_status = BOOK_FAILURE;

		sscanf(param1, "%d", &rollno);
		testStudent.rollno = rollno;
		status = delete_student_by_rollno( rollno );
		if(status == LIB_SUCCESS)
			status = BOOK_SUCCESS;
		else
			status = BOOK_FAILURE;
		if( status == expected_status ){
			TREPORT("PASS", "");
		}
		else{
			sprintf(info,"delete_student_by_rollno returned status %d",status);
			TREPORT("FAIL", info);
		}
	}

	else if( !strcmp(command,"ISSUE") ){
		if( !strcmp(param3,"0") )
			expected_status = BOOK_SUCCESS;
		else
			expected_status = BOOK_FAILURE;

		sscanf(param2, "%d", &rollno);
		sscanf(param1, "%d", &isbn);

		testStudent.rollno = rollno;
		testBook.isbn = isbn;

		status = issue( rollno, isbn );
		if(status == LIB_SUCCESS)
			status = BOOK_SUCCESS;
		else
			status = BOOK_FAILURE;
		if( status == expected_status ){
			TREPORT("PASS", "");
		}
		else{
			sprintf(info,"issue returned status %d",status);
			TREPORT("FAIL", info);
		}


	}

	else if( !strcmp(command,"CLOSE") ){
		if( !strcmp(param1,"0") )
			expected_status = BOOK_SUCCESS;
		else
			expected_status = BOOK_FAILURE;

		status = libsys_close();
		if(status == LIB_SUCCESS)
			status = BOOK_SUCCESS;
		else
			status = BOOK_FAILURE;
		if( status == expected_status ){
			TREPORT("PASS", "");
		}
		else{
			sprintf(info,"libsys_close returned status %d",status);
			TREPORT("FAIL", info);
		}
	}

}


