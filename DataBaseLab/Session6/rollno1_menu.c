#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "libsys.h"

// Your code must support menu-driven functionality.
// Function calls rollno_libsys.h

void menu()
{
    printf( "---------LIBRARY MANAGEMENT SYSTEM--------" );
    printf( "\n CHOOSE THE OPTION" );
    printf("\n 1) Add Book");
    printf("\n 2) Add Student");
    printf("\n 3) Delete Book");
    printf("\n 4) Delete Student");
    printf("\n 5) Issue Book");
    printf("\n 6) Search Book By isbn");
    printf("\n 7) Search Book by title");
    printf("\n 8) Search Student by roll no");
    printf("\n 9) Search Student by name");
    printf("\n 10) Exit \n");

    libsys_open("book_data.dat", "stud_data.dat", "issue.dat");

    while (1)
    {
        int n;
        printf("\n\nYour Choice :- ");
        scanf("%d", &n);

        if (n == 1)
        {
            int isbn;
            char title[40];
            char author[40];
            float price;

            printf("\nEnter ISBN :- ");
            scanf("%d", &isbn);
            printf("Enter Title :- ");
            scanf("%s", title);
            printf("Enter Author :- ");
            scanf("%s", author);
            printf("Enter Price :- ");
            scanf("%f", &price);

            struct Book *rec = (struct Book *)malloc(sizeof(struct Book));
            strncpy(rec->author, author, 40);
            strncpy(rec->title, title, 40);
            rec->price = price;
            rec->isbn = isbn;

            int res = put_book_by_isbn(isbn, rec);
            if (res == BOOK_SUCCESS)
            {
                printf("\nSUCCESS\n");
            }
            else
            {
                printf("FAILED" );
            }
        }

        else if (n == 2)
        {
            struct Student *st = (struct Student *)malloc(sizeof(struct Student));

            printf("\nEnter Roll No :- ");
            scanf("%d", &st->rollno);
            printf("Enter Name :- ");
            scanf("%s", st->name);
            printf("Enter Address :- ");
            scanf("%s", st->address);
            printf("Enter CGPA :- " );
            scanf("%f", &st->cgpa);

            int res = put_student_by_rollno(st->rollno, st);
            if (res == BOOK_SUCCESS)
            {
                printf("\nSUCCESS\n" );
            }
            else
            {
                printf("FAILED" );
            }
        }

        else if (n == 3)
        {
            int isbn;
            printf("\nEnter ISBN :- ");
            scanf("%d", &isbn);

            int res = delete_book_by_isbn(isbn);
            if (res == LIB_SUCCESS)
            {
                printf( "\nSUCCESS\n" );
            }
            else
            {
                printf( "FAILED" );
            }
        }

        else if (n == 4)
        {
            int rollno;
            printf( "\nEnter ROLL_NO :- ");
            scanf("%d", &rollno);

            int res = delete_student_by_rollno(rollno);
            if (res == LIB_SUCCESS)
            {
                printf( "\nSUCCESS\n" );
            }
            else
            {
                printf( "FAILED" );
            }
        }

        else if (n == 5)
        {
            int isbn;
            printf( "\nEnter ISBN :- ");
            scanf("%d", &isbn);

            int rollno;
            printf( "\nEnter ROLL_NO :- ");
            scanf("%d", &rollno);

            int res = issue(rollno, isbn);
            if (res == LIB_SUCCESS)
            {
                printf( "\nSUCCESS\n" );
            }
            else
            {
                printf( "FAILED" );
            }
        }

        else if (n == 6)
        {
            int isbn;
            printf( "\nEnter ISBN :- ");
            scanf("%d", &isbn);

            struct Book *rec = (struct Book *)malloc(sizeof(struct Book));

            int res = get_book_by_isbn(isbn, rec);
            if (res == LIB_SUCCESS)
            {
                printf( "Title :- %s\nAuthor :- %s\nPrice :- %f" , rec->title, rec->author, rec->price);
            }
            else
            {
                printf( "FAILED" );
            }
        }

        else if (n == 7)
        {
            char title[40];
            printf( "\nEnter Title :- ");
            scanf("%s", title);

            struct Book *rec = (struct Book *)malloc(sizeof(struct Book));

            int res = get_book_by_title(title, rec);
            if (res == LIB_SUCCESS)
            {
                printf( "Title :- %s\nAuthor :- %s\nPrice :- %f" , rec->title, rec->author, rec->price);
            }
            else
            {
                printf( "FAILED" );
            }
        }

        else if (n == 8)
        {
            int rollno;
            printf( "\nEnter Roll No :- ");
            scanf("%d", &rollno);

            struct Student *rec = (struct Student *)malloc(sizeof(struct Student));

            int res = get_student_by_rollno(rollno, rec);
            if (res == LIB_SUCCESS)
            {
                printf( "Name :- %s\nAddress :- %s\nCGPA :- %f" , rec->name, rec->address, rec->cgpa);
            }
            else
            {
                printf( "FAILED" );
            }
        }

        else if (n == 9)
        {
            char name[40];
            printf( "\nEnter Name :- ");
            scanf("%s", name);

            struct Student *rec = (struct Student *)malloc(sizeof(struct Student));

            int res = get_student_by_name(name, rec);
            if (res == LIB_SUCCESS)
            {
                printf( "Name :- %s\nAddress :- %s\nCGPA :- %f" , rec->name, rec->address, rec->cgpa);
            }
            else
            {
                printf( "FAILED");
            }
        }

        else if (n == 10)
        {
            libsys_close();
            break;
        }
    }
}

int main()
{
    int a = libsys_create("book_data.dat", "stud_data.dat", "issue.dat");
    if (a != LIB_SUCCESS)
    {
        printf( "FAILED TO OPEN FILES" );
    }
    menu();
}