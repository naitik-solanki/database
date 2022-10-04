#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include"libsys.h"

// Define the global variable of libsys
struct LibsysInfo repo_handle;
int libsys_create( char *repo_name)
{ 
	FILE *myfile = fopen(repo_name,"wb");// creates file pointer
	if(myfile==NULL) // checks for errors
	{
		LIB_FILE_ERROR;
	}
	fclose(myfile); //close the file
	return LIB_SUCCESS; // return success of the process
}

int libsys_open( char *repo_name )
{
	if(repo_handle.repo_status==LIB_REPO_OPEN)//if the file is already open, just return lib_repo_already_open
	{
		return LIB_REPO_ALREADY_OPEN;
	}
	FILE *myfile = fopen(repo_name,"rb+");//if file is not open, open it and save the pointer to global struct
	if(myfile==NULL) // chekc for errors with file
	{
		return LIB_FILE_ERROR;
	}
	strcpy(repo_handle.libsys_name,repo_name);//assign name
	repo_handle.libsys_data_fp=myfile; // assign file pointer
	repo_handle.repo_status=LIB_REPO_OPEN; // assign open status
	return LIB_SUCCESS; //return success


}

int put_book_by_isbn( int isbn_to_write, struct Book *rec )
{
    if(repo_handle.repo_status==LIB_REPO_CLOSED) //if file is closed, we cannot write so return error
	{
		return BOOK_FAILURE;
	}
	fseek(repo_handle.libsys_data_fp,0,SEEK_END); // move pointer to the end of the file
	int n=fwrite(&isbn_to_write,4,1,repo_handle.libsys_data_fp); // write the isbn
	if(n!=1) //return error if isbn is not written
	{
		return LIB_ADD_FAILED;
	}
	int m=fwrite(&rec,sizeof(struct Book),1,repo_handle.libsys_data_fp);//write the data
	if(m!=1) //return error if data is not written properly
	{
		return LIB_ADD_FAILED;
	}
	return LIB_SUCCESS;//if everything goes well ,return success
}


int get_book_by_isbn( int isbn_to_read, struct Book *rec )
{
    if(repo_handle.repo_status==LIB_REPO_CLOSED) // if file is closed, we cannot read so return error
	{
		return LIB_FILE_ERROR;
	}
	fseek(repo_handle.libsys_data_fp,0,SEEK_SET); // move the file pointer
	while(!feof(repo_handle.libsys_data_fp))
	{
		int num;
		fread(&num,4,1,repo_handle.libsys_data_fp);//read the isbn
		if(num==isbn_to_read) //check if this the the isbn number that we want if yes ,read the data
		{
			fread(&rec,sizeof(rec),1,repo_handle.libsys_data_fp);
			//printf("%d %s %s %f",rec->isbn,rec->title,rec->author,rec->price);
			return BOOK_SUCCESS;//since we found out book, return success
		}
		else fseek(repo_handle.libsys_data_fp,sizeof(struct Book),SEEK_CUR); // if no, move to the location of the next isbn number
	}
	return BOOK_FAILURE;// if we dont find the isbn, return failure
}

int libsys_close()
{
	if(repo_handle.repo_status==LIB_REPO_CLOSED)// if file is already closed, return error
	{
		return LIB_FILE_ERROR;
	}	
	fclose(repo_handle.libsys_data_fp);// close the file
	strcpy(repo_handle.libsys_name,""); // re initilize the file name in the global struct
	repo_handle.repo_status=LIB_REPO_CLOSED;// reinitilize the repo status
	return LIB_SUCCESS;//return success on closing successfully
	
}

