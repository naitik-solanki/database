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
    char * DataFile = malloc(sizeof(repo_name)+4);
    char * IndexFile = malloc(sizeof(repo_name)+4);
    strcpy(DataFile,repo_name);
    strcpy(IndexFile,repo_name);
    strcat(DataFile,".dat");
    strcat(IndexFile,".ndx");
    FILE * dataFile = fopen(DataFile,"wb");
    FILE * indexFile = fopen(IndexFile,"wb");
    if(dataFile==NULL || indexFile==NULL)
    {
        return LIB_FILE_ERROR;
    }
    int a=0;
    fwrite(&a,sizeof(a),1,indexFile);
    fclose(dataFile);
    fclose(indexFile);
    return LIB_SUCCESS;
}

// Open the data file and index file in rb+ mode
// Update the fields of LIB_RepoInfo appropriately
// Read number of index entries from index file
// Load index_entries array by reading index entries from the index file
// Close only the index file
int libsys_open( char *repo_name )
{
    char *DataFileName= malloc(sizeof(repo_name)+4);
    char *IndexFileName= malloc(sizeof(repo_name)+4);
    strcpy(DataFileName,repo_name);
    strcpy(IndexFileName,repo_name);
    strcat(DataFileName,".dat");
    strcat(IndexFileName,".ndx");
    if(repo_handle.repo_status==LIB_REPO_OPEN )
    {
        return LIB_REPO_ALREADY_OPEN;
    }
    FILE *DataFile =fopen(DataFileName,"rb+");
    FILE *IndexFile = fopen(IndexFileName,"rb+");
    // if(DataFile==NULL || IndexFile==NULL)
    // {
    //     return LIB_FILE_ERROR;
    // }
    repo_handle.libsys_data_fp = DataFile;
    repo_handle.libsys_ndx_fp=IndexFile;
    strcpy(repo_handle.libsys_name,repo_name);
    repo_handle.repo_status=LIB_REPO_OPEN;
    
    fread(&repo_handle.index_count,sizeof(repo_handle.index_count),1,IndexFile);
    struct LIB_NdxInfo new_entry;
    int p;
    for(int i=0;i<repo_handle.index_count;i++)
    {
        p=fread(&new_entry,sizeof(new_entry),1,IndexFile);
        if(p!=1)
        {
            return LIB_FILE_ERROR;
        }
        repo_handle.index_entries[i]=new_entry;
    }
    fclose(repo_handle.libsys_ndx_fp);
}

// put_rec_by_key
// Seek to the end of the data file
// Create an index entry with the current data file location using ftell
// Add index entry to array using offset returned by ftell
// Write the key at the current data file location
// Write the record after writing the key
int put_book_by_isbn( int key, struct Book *rec )
{
    if(repo_handle.repo_status==LIB_REPO_CLOSED)
    {
        return LIB_REPO_NOT_OPEN;
    }
    fseek(repo_handle.libsys_data_fp,0,SEEK_END);
    struct LIB_NdxInfo entry;
    for(int i=0;i<repo_handle.index_count;i++)
    {
        if(repo_handle.index_entries[i].key==key)
        {
            return BOOK_FAILURE;
        }
    }
    int p,q;
    entry.key=key;
    entry.offset= ftell(repo_handle.libsys_data_fp);
    p = fwrite(&key,sizeof(key),1,repo_handle.libsys_data_fp);
    q = fwrite(rec,sizeof(struct Book),1,repo_handle.libsys_data_fp);
    if(p!=1 || q!=1)
    {
        return LIB_ADD_FAILED;
    }
    repo_handle.index_entries[repo_handle.index_count]=entry;
    repo_handle.index_count++;
    return BOOK_SUCCESS;
}

// get_rec_by_key
// Search for index entry in index_entries array
// Seek to the file location based on offset in index entry
// Read the key at the current file location 
// Read the record after reading the key
int get_book_by_isbn( int key, struct Book *rec )
{
    if(repo_handle.repo_status==LIB_REPO_CLOSED)
    {
        return LIB_REPO_NOT_OPEN;
    }
    int offset =-1;
    for(int i=0; i<repo_handle.index_count;i++)
    {
        if(repo_handle.index_entries[i].key==key)
        {
            offset= repo_handle.index_entries[i].offset;
            break;
        }
    }
    if(offset==-1)
    {
        return LIB_REC_NOT_FOUND;
    }
    fseek(repo_handle.libsys_data_fp,offset,SEEK_SET);
    int isbn ;
    fread(&isbn,sizeof(int),1,repo_handle.libsys_data_fp);
    int p;
    if(key!=isbn)
    {
        return LIB_REC_NOT_FOUND;
    }
    
    p=fread(rec ,sizeof(*rec),1,repo_handle.libsys_data_fp);
    if(p!=1)
    {
        return LIB_REC_NOT_FOUND;
    }
    return LIB_SUCCESS;
}

// libsys_close
// Open the index file in wb mode (write mode, not append mode)
// Write number of index entries at the beginning of index file
// Unload the index array into the index file (overwrite the entire index file)
// Close the index file and data file
int libsys_close()
{
    char * INdexFileName = repo_handle.libsys_name;
    strcat(INdexFileName,".ndx");
    FILE * indexFile = fopen(INdexFileName,"wb");
    if(indexFile==NULL)
    {
        return LIB_FILE_ERROR;
    }
    fwrite(&repo_handle.index_count,sizeof(int ),1,indexFile);
    int p;
    for(int i=0;i<repo_handle.index_count;i++)
    {
        p=fwrite(&repo_handle.index_entries[i],sizeof(repo_handle.index_entries[i]),1,indexFile);
        if(p!=1)
        {
            return LIB_NDX_SAVE_FAILED;
        }
    }
    fclose(repo_handle.libsys_data_fp);
    fclose(indexFile);
    strcpy(repo_handle.libsys_name,"");
    repo_handle.repo_status=LIB_REPO_CLOSED;
    return LIB_SUCCESS;
}

