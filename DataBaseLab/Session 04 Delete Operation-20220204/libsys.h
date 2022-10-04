#ifndef LIBSYS_H
#define LIBSYS_H

// Error codes
#define LIB_SUCCESS 0
#define LIB_FILE_ERROR 1
#define LIB_ADD_FAILED 2
#define LIB_REC_NOT_FOUND 3
#define LIB_REPO_ALREADY_OPEN 12
#define LIB_NDX_SAVE_FAILED 13
#define LIB_REPO_NOT_OPEN 14
#define BOOK_SUCCESS 0
#define BOOK_FAILURE 1

#define RECORD_DELETED 0
#define RECORD_PRESENT 1

// Repository status values
#define LIB_REPO_OPEN 10
#define LIB_REPO_CLOSED 11
#define LIB_MAX_INDEX_ENTRIES 10000

struct Book
{
	int isbn;
	char title[40];
	char author[40];
	float price;
};

struct LIB_NdxInfo{
	int key;
	int offset;
	int flag; 
};

struct LibsysInfo{
	char libsys_name[30];
	FILE *libsys_data_fp;
	FILE *libsys_ndx_fp;
	int repo_status; 
	struct LIB_NdxInfo index_entries[LIB_MAX_INDEX_ENTRIES];
	int index_count;
};

extern struct LibsysInfo repo_handle;

// libsys_create
// Open the data file and index file in "wb" mode
// Initialize index file by store "0" to indicate there are zero entries in index file

int libsys_create( char *repo_name); // fopen, fclose

// libsys_open
// Open the data file and index file in rb+ mode
// Update the fields of LIB_RepoInfo appropriately
// Read number of index entries from index file
// Load index_entries array by reading index entries from the index file
// Close only the index file
int libsys_open( char *repo_name );

// put_rec_by_key
//-----check index file for key
//-----if key already present check for flag 
//-----if key is present but flag is RECORD_DELETED then just add entry at same index i.e update only offset and update flag; return status
//-----if key is present but flag is RECORD_PRSENT return failure as data is already present
//-----if key is not prsent then proceed with following steps:

// Seek to the end of the data file
// Create an index entry with the current data file location using ftell
// Add index entry to array using offset returned by ftell
// Write the key at the current data file location
// Write the record after writing the key
// return status
int put_book_by_isbn( int key, struct Book *rec );

// get_rec_by_key
//check repo status
// Search for index entry in index_entries array
//-----use flag : RECORD_PRSENT to read valid entries
// Seek to the file location based on offset in index entry
// Read the key at the current file location 
// Read the record after reading the key
int get_book_by_isbn( int key, struct Book *rec );

//-----delete_rec_by_key
//-----check repo status
//-----Search for index entry in index_entries array
//-----if key matches and flag is RECORD_PRSENT then reset flag to RECORD_DELETED
//-----if key matches but flag is RECORD_DELETED  return status LIB_REC_NOT_FOUND
int delete_book_by_isbn( int key );

// libsys_close
// Open the index file in wb mode (write mode, not append mode)
// Write number of index entries at the beginning of index file
// Unload the index array into the index file (overwrite the entire index file)
// Close the index file and data file
int libsys_close();


#endif
