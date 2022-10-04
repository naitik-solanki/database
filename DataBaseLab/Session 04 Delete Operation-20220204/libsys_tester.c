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
	char repo_name[30];
	char command[10], param1[10], param2[10], info[1000];
	int isbn, status, rec_size, expected_status;
	struct Book testBook;

	strcpy(testBook.title, "dummy name");
	strcpy(testBook.author, "dummy author");
	testBook.price = 100.50;

	rec_size = sizeof(struct Book);

	sscanf(test_case, "%s%s%s", command, param1, param2);
	printf("Test case: %s", test_case); fflush(stdout);
	if( !strcmp(command,"CREATE") ){
		strcpy(repo_name, param1);
		if( !strcmp(param2,"0") )
			expected_status = BOOK_SUCCESS;
		else
			expected_status = BOOK_FAILURE;
		
		status = libsys_create( repo_name );
		if( status == expected_status ){
			TREPORT("PASS", "");
		}
		else{
			sprintf(info,"libsys_open returned status %d",status);
			TREPORT("FAIL", info);
		}
	}

	if( !strcmp(command,"OPEN") ){
		strcpy(repo_name, param1);
		if( !strcmp(param2,"0") )
			expected_status = BOOK_SUCCESS;
		else
			expected_status = BOOK_FAILURE;

		status = libsys_open( repo_name );
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
	else if( !strcmp(command,"STORE") ){
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
	else if( !strcmp(command,"SEARCH") ){
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
			// Check if the retrieved values match with what was stored earlier
			if( expected_status == 0 ){
				if (testBook.isbn == isbn && 
					strcmp(testBook.title,"dummy name") == 0 &&
					strcmp(testBook.author,"dummy author") == 0 &&
					testBook.price == 100.50)
				{
						TREPORT("PASS", "");
				}
				else{
					sprintf(info,"Book data not matching... Expected:{%d,%s,%s,%f} Got:{%d,%s,%s,%f}\n",
						isbn, "dummy_name", "dummy number",100.50, 
						testBook.isbn, testBook.title, testBook.author, testBook.price
					);
					TREPORT("FAIL", info);
				}
			}
			else
				TREPORT("PASS", "");
		}
	}

else if( !strcmp(command,"DELETE") ){
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


