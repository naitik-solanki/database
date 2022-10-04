#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include"libsys.h"

//Your code must support menu-driven functionality.
//Function calls rollno_libsys.h
int main()
{
    printf("press 1 to add a book\n");
    printf("press 2 to add student\n");
    printf("press 3 to delete a book\n");
    printf("press 4 to delete a studet\n");
    printf("press 5 to add issue of a book\n");
    printf("press 6 to  seach a book by isbn\n");
    printf("press 7 to  seach a book by title\n");
    printf("press 8 to  seach a student by roll no.\n");
    printf("press 9 to  seach a student by name\n");
    printf("press 10 to exit\n");
    int status;
	struct Book testContact;
	char *test_case_id;
    testContact.isbn=1000;
    int n;
    scanf("%d",&n);
    switch (n)
    {
    case 1:
        printf("enter key\n");
        int key;
        scanf("%d",&key);
        
        break;
    
    default:
        break;
    }


    
}
