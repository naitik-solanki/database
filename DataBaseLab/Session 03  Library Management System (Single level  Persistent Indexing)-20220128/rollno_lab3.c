#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include"libsys.h"

// Define the global variable of libsys
struct LibsysInfo repo_handle;

// Open the data file and index file in "wb" mode
// Initialize index file by store "0" to indicate there are zero entries in index file

int libsys_create( char *repo_name)
{
}

// Open the data file and index file in rb+ mode
// Update the fields of LIB_RepoInfo appropriately
// Read number of index entries from index file
// Load index_entries array by reading index entries from the index file
// Close only the index file
int libsys_open( char *repo_name )
{
}

// put_rec_by_key
// Seek to the end of the data file
// Create an index entry with the current data file location using ftell
// Add index entry to array using offset returned by ftell
// Write the key at the current data file location
// Write the record after writing the key
int put_book_by_isbn( int key, struct Book *rec )
{
}

// get_rec_by_key
// Search for index entry in index_entries array
// Seek to the file location based on offset in index entry
// Read the key at the current file location 
// Read the record after reading the key
int get_book_by_isbn( int key, struct Book *rec )
{
}

// libsys_close
// Open the index file in wb mode (write mode, not append mode)
// Write number of index entries at the beginning of index file
// Unload the index array into the index file (overwrite the entire index file)
// Close the index file and data file
int libsys_close()
{
}

