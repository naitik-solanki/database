#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include"libsys.h"

// Define the global variable of libsys
struct LibsysInfo repo_handle;
//ATTENTION
//Error codes and success codes that have been returned are wrt the driver file.
//Some error codes have been returned by their general menaing

// Open the data file and index file in "wb" mode
// Initialize index file by store "0" to indicate there are zero entries in index file

int libsys_create( char *repo_name)
{
	char* data_file;
	char* ind_file;
	data_file=malloc(sizeof(repo_name)+4);
	ind_file=malloc(sizeof(repo_name)+4);
	strcpy(data_file, repo_name);
	strcpy(ind_file, repo_name);
	strcat(data_file, ".dat");
	strcat(ind_file, ".ndx");
	FILE *fp1 = fopen(data_file, "wb");
	FILE *fp2 = fopen(ind_file, "wb");
	if(fp1 == NULL || fp2 == NULL)
	{
		return(LIB_FILE_ERROR);
	}
	int i =0;
	fwrite(&i, sizeof(int), 1, fp2);
	fclose(fp1);fclose(fp2);
	return(LIB_SUCCESS);
}

// Open the data file and index file in rb+ mode
// Update the fields of LIB_RepoInfo appropriately
// Read number of index entries from index file
// Load index_entries array by reading index entries from the index file
// Close only the index file
int libsys_open( char *repo_name )
{
	char* data_file;
	char* ind_file;
	data_file=malloc(sizeof(repo_name)+4);
	ind_file=malloc(sizeof(repo_name)+4);
	strcpy(data_file, repo_name);
	strcpy(ind_file, repo_name);
	strcat(data_file, ".dat");
	strcat(ind_file, ".ndx");
	
	if(repo_handle.repo_status == LIB_REPO_OPEN || repo_handle.repo_status == LIB_REPO_ALREADY_OPEN)
	{
		return(LIB_REPO_ALREADY_OPEN);
	}
	FILE *fp1 = fopen(data_file, "rb+");
	FILE *fp2 = fopen(ind_file, "rb+");
	if(fp1 == NULL || fp2 == NULL)
	{
		return(LIB_FILE_ERROR);
	}
	repo_handle.libsys_data_fp = fp1;
	repo_handle.libsys_ndx_fp = fp2;
	strcpy(repo_handle.libsys_name, repo_name);
	repo_handle.repo_status = LIB_REPO_OPEN;

	int index_count;
	//Reading the total number of index entries
	fread(&repo_handle.index_count, sizeof(int), 1, repo_handle.libsys_ndx_fp);

	//Reading the index entries and storing them in an array
	struct LIB_NdxInfo entry;
	int p;
	for(int i=0;i<repo_handle.index_count;i++)
	{
		p=fread(&entry, sizeof(entry), 1, repo_handle.libsys_ndx_fp);
		if(p!=1)	return(LIB_FILE_ERROR);
		repo_handle.index_entries[i] = entry;
	}
	fclose(repo_handle.libsys_ndx_fp);
	return(LIB_SUCCESS);
}

// put_rec_by_key
// Seek to the end of the data file
// Create an index entry with the current data file location using ftell
// Add index entry to array using offset returned by ftell
// Write the key at the current data file location
// Write the record after writing the key
int put_book_by_isbn( int key, struct Book *rec )
{
	if(repo_handle.repo_status == LIB_REPO_CLOSED)
	{
		return(LIB_REPO_NOT_OPEN);
	}

	fseek(repo_handle.libsys_data_fp, 0, SEEK_END);
	int p, q;
	struct LIB_NdxInfo Index_entry;
	for(int j=0;j<repo_handle.index_count;j++)
	{
		if(repo_handle.index_entries[j].key == key)
		{
			return(BOOK_FAILURE);
		}
	}
	
	//Noting down the offset and key
	Index_entry.key = key;
	Index_entry.offset = ftell(repo_handle.libsys_data_fp);
	//fwrite returns the number of elements it correctly wrote
	p = fwrite(&key, sizeof(int), 1 , repo_handle.libsys_data_fp);
	q = fwrite(rec, sizeof(struct Book), 1, repo_handle.libsys_data_fp);
	if(p!=1 || q!=1)
	{
		return(LIB_ADD_FAILED);
	}

	//Adding to the array
	repo_handle.index_entries[repo_handle.index_count] = Index_entry;
	repo_handle.index_count++;
	return(BOOK_SUCCESS);
}

//Utility function
int search_IndexArray(int key)
{
	int book_offset = -1;
	for(int i=0;i<repo_handle.index_count;i++)
	{
		if(repo_handle.index_entries[i].key == key)
		{
			book_offset = repo_handle.index_entries[i].offset;
		}
	}
	return(book_offset);
}

// get_rec_by_key
// Search for index entry in index_entries array
// Seek to the file location based on offset in index entry
// Read the key at the current file location 
// Read the record after reading the key
int get_book_by_isbn( int key, struct Book *rec )
{
	if(repo_handle.repo_status == LIB_REPO_CLOSED)
	{
		return(LIB_REPO_NOT_OPEN);
	}
	int book_offset =  search_IndexArray(key);
	if(book_offset < 0)		return(LIB_REC_NOT_FOUND);
	fseek(repo_handle.libsys_data_fp, book_offset, SEEK_SET);
	int isbn;
	fread(&isbn, sizeof(int), 1, repo_handle.libsys_data_fp);
	
	//Security check on key
	int p;
	if(key == isbn)
	{
		p=fread(rec, sizeof(struct Book), 1, repo_handle.libsys_data_fp);
		if(p!=1)	return(LIB_REC_NOT_FOUND);
		return(BOOK_SUCCESS); 
	}
	return(LIB_REC_NOT_FOUND);
}

// libsys_close
// Open the index file in wb mode (write mode, not append mode)
// Write number of index entries at the beginning of index file
// Unload the index array into the index file (overwrite the entire index file)
// Close the index file and data file
int libsys_close()
{
	if(repo_handle.repo_status == LIB_REPO_CLOSED)
	{
		return(LIB_REPO_NOT_OPEN);
	}
	FILE* fp3 = fopen(strncat(repo_handle.libsys_name, ".ndx", sizeof(repo_handle.libsys_name) - strlen(repo_handle.libsys_name)),"wb");
	if(repo_handle.libsys_ndx_fp == NULL)	return(LIB_FILE_ERROR);
	fwrite(&repo_handle.index_count, sizeof(int), 1, fp3);
	
	int p;
	for(int i=0;i<repo_handle.index_count;i++)
	{
		p = fwrite(&repo_handle.index_entries[i], sizeof(repo_handle.index_entries[i]), 1, fp3);
		if(p != 1)
		{
			return(LIB_NDX_SAVE_FAILED);
		}
	}

	fclose(repo_handle.libsys_data_fp);
	fclose(fp3);
	strcpy(repo_handle.libsys_name, "");
	repo_handle.repo_status = LIB_REPO_CLOSED;
	return LIB_SUCCESS;
}

