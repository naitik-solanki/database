#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include"libsys.h"

// Define the global variable of libsys
struct LibsysInfo repo_handle;

//--------------------------------create()---------------------------------
int libsys_create( char *repo_name1,char *repo_name2,char *repo_name3)
{
    	// create booksys file pointer to open a file in 'wb' mode
 	// handle file pointer error if value is NULL return appropriate error code referring to the error codes 
    	// close file pointer
	char * booksys = malloc(sizeof(repo_name1)+4);
    strcpy(booksys,repo_name1);
    strcat(booksys,".dat");
    FILE * Booksys = fopen(booksys,"wb");
    if(Booksys==NULL)
    {
        return LIB_FILE_ERROR;
    }
	fclose(Booksys);

    	// create studsys file pointer to open a file in 'wb' mode
 	// handle file pointer error if value is NULL return appropriate error code referring to the error codes 
    	// close file pointer
    char * studsys = malloc(sizeof(repo_name2)+4);
    strcpy(studsys,repo_name2);
    strcat(studsys,".dat");
    FILE * Studsys = fopen(studsys,"wb");
    if(Studsys==NULL)
    {
        return LIB_FILE_ERROR;
    }
	fclose(Studsys);
    	// create issuesys file pointer to open a file in 'wb' mode
 	// handle file pointer error if value is NULL return appropriate error code referring to the error codes 
// close file pointer
	char * issuesys = malloc(sizeof(repo_name3)+4);
    strcpy(issuesys,repo_name3);
    strcat(issuesys,".dat");
    FILE * Issuesys = fopen(issuesys,"wb");
    if(Issuesys==NULL)
    {
        return LIB_FILE_ERROR;
    }
	fclose(Issuesys);

// Open the index file in "wb" mode
// Initialize index file by store "0" to indicate there are zero entries in index file

    	// return success 
	char * bookindsys = malloc(sizeof(repo_name1)+4);
    strcpy(bookindsys,repo_name1);
    strcat(bookindsys,".ndx");
    FILE * BookIndsys = fopen(bookindsys,"wb");
    if(BookIndsys==NULL)
    {
        return LIB_FILE_ERROR;
    }
	int a=0;
	fwrite(&a,sizeof(a),1,BookIndsys);
	fclose(BookIndsys);

	char * Studindsys = malloc(sizeof(repo_name2)+4);
    strcpy(Studindsys,repo_name2);
    strcat(Studindsys,".ndx");
    FILE * StudIndsys = fopen(Studindsys,"wb");
    if(StudIndsys==NULL)
    {
        return LIB_FILE_ERROR;
    }
	a=0;
	fwrite(&a,sizeof(a),1,StudIndsys);
	fclose(StudIndsys);

	return LIB_SUCCESS;
}
//--------------------------------open()---------------------------------
int libsys_open(char *book_name,char *stud_name,char *issue_name)
{


	//call booksys_open()
	//call studsys_open()
	//call issuesys_open()
	int a,b,c;
	a=booksys_open(book_name);
	b=studsys_open(stud_name);
	c=issuesys_open(issue_name);


	char * bookindsys = malloc(sizeof(book_name)+4);
	strcpy(bookindsys,book_name);
	strcat(bookindsys,".ndx");
	FILE* BookIndsys = fopen(bookindsys,"rb+");
	if(BookIndsys==NULL)
	{
		return LIB_FILE_ERROR;
	}
	repo_handle.libsys_ndx_fp=BookIndsys;


	// Read number of index entries from index file
	fread(&repo_handle.index_count,sizeof(repo_handle.index_count),1,BookIndsys);
	struct LIB_NdxInfo new_entry;
	int p;
	// Load index_entries array by reading index entries from the index 	file
	if(repo_handle.index_count>0)
	{
		fread(repo_handle.index_entries,sizeof(struct LIB_NdxInfo),repo_handle.index_count,repo_handle.libsys_ndx_fp);
	}
	// Close only the index file
	fclose(BookIndsys);




	char * studindsys = malloc(sizeof(stud_name)+4);
	strcpy(studindsys,stud_name);
	strcat(studindsys,".ndx");
	FILE* StudIndsys = fopen(studindsys,"rb+");
	if(StudIndsys==NULL)
	{
		return LIB_FILE_ERROR;
	}
	repo_handle.stud_ndx_fp=StudIndsys;
	fread(&repo_handle.stud_index_count,sizeof(int),1,StudIndsys);
	struct STUD_NdxInfo newEntry;
	if(repo_handle.stud_index_count>0)
	{
		fread(repo_handle.stud_index_entries,sizeof(struct STUD_NdxInfo),repo_handle.stud_index_count,repo_handle.stud_ndx_fp);
	}
	fclose(StudIndsys);



	//check status of above functions
	// if all of them return success then return SUCCESS else return ERROR
	if(a || b || c)
	{
		return LIB_FILE_ERROR;
	}
	else
	{
		return LIB_SUCCESS;
	}
}

int booksys_open( char *repo_name )
{


    	//1. assign repo handle a file pointer by opening file in 'rb+' mode
    	//2. handle file pointer error if value is NULL return appropriate error code referring to the error codes in libsys.h
	//3. assign values (repo_name) to booksys_repo_handle
      	//4. assign value to repo_handle.book_repo_status=LIB_REPO_OPEN;
	//5. return booksys_success 
	char * booksys = malloc(sizeof(repo_name)+4);
    strcpy(booksys,repo_name);
    strcat(booksys,".dat");
	if(repo_handle.book_repo_status==LIB_REPO_OPEN)
	{
		return LIB_REPO_ALREADY_OPEN;
	}
    FILE * Booksys = fopen(booksys,"rb+");
    if(Booksys==NULL)
    {
        return LIB_FILE_ERROR;
    }
	repo_handle.booksys_data_fp=Booksys;
	strcpy(repo_handle.booksys_name,repo_name);
	repo_handle.book_repo_status=LIB_REPO_OPEN;
	return LIB_SUCCESS;
}

int issuesys_open( char *repo_name )
{


    	//1. assign repo handle a file pointer by opening file in 'rb+' mode
    	//2. handle file pointer error if value is NULL return appropriate error code referring to the error codes in libsys.h
	//3. assign values (repo_name) to issuesys_repo_handle
      	//4. assign value to repo_handle.issue_repo_status=LIB_REPO_OPEN;
	//5. return issuesys_success 
	char * issuesys = malloc(sizeof(repo_name)+4);
    strcpy(issuesys,repo_name);
    strcat(issuesys,".dat");
	if(repo_handle.issue_repo_status==LIB_REPO_OPEN)
	{
		return LIB_REPO_ALREADY_OPEN;
	}
    FILE * Issuesys = fopen(issuesys,"rb+");
    if(Issuesys==NULL)
    {
        return LIB_FILE_ERROR;
    }
	repo_handle.issue_repo_status=LIB_REPO_OPEN;
	repo_handle.issuesys_data_fp=Issuesys;
	strcpy(repo_handle.issuesys_name,repo_name);
	return LIB_SUCCESS;

}

int studsys_open( char *repo_name )
{

	
    	//1. assign repo handle a file pointer by opening file in 'rb+' mode
    	//2. handle file pointer error if value is NULL return appropriate error code referring to the error codes 
	//3. assign values (repo_name) to studsys_repo_handle
      	//4. assign value to repo_handle.stud_repo_status=LIB_REPO_OPEN;
	//5. return studsys_success 
	char * studentsys = malloc(sizeof(repo_name)+4);
    strcpy(studentsys,repo_name);
    strcat(studentsys,".dat");
	if(repo_handle.stud_repo_status==LIB_REPO_OPEN)
	{
		return LIB_REPO_ALREADY_OPEN;
	}
    FILE * Studentsys= fopen(studentsys,"rb+");
    if(Studentsys==NULL)
    {
        return LIB_FILE_ERROR;
    }
	repo_handle.stud_repo_status=LIB_REPO_OPEN;
	repo_handle.studsys_data_fp=Studentsys;
	strcpy(repo_handle.studsys_name,repo_name);
	return LIB_SUCCESS;

}
	

//------------------------------book:NO change ----------------------------
void PrintIssue(int key)
{
	fseek(repo_handle.issuesys_data_fp,0,SEEK_SET);
	while(!feof(repo_handle.issuesys_data_fp))
	{
		struct Issue myRec;
		fread(&myRec,sizeof(struct Issue),1,repo_handle.issuesys_data_fp);
		if(myRec.isbn==key)
		{
			struct Student s;
			get_student_by_rollno(myRec.rollno,&s);
			printf("Roll no: %d\n",s.rollno);
			printf("Name : %s\n",s.name);
			printf("Address : %s\n",s.address);
			printf("CGPA : %lf\n",s.cgpa);
			return;
		}
	}
}

int get_book_by_isbn( int key, struct Book *rec )
{

// get_rec_by_key
//check repo status
// Search for index entry in index_entries array
//-----use flag to read valid entries
// Seek to the file location based on offset in index entry
// Read the key at the current file location 
// Read the record after reading the key
	if(repo_handle.book_repo_status==LIB_REPO_CLOSED)
	{
		return LIB_REPO_NOT_OPEN;
	}
		int offset=-1;
		for(int i=0;i<repo_handle.index_count;i++)
		{
			if(repo_handle.index_entries[i].flag==RECORD_ISSUED && repo_handle.index_entries[i].key == key)
			{
				PrintIssue(key);
				return LIB_REC_NOT_FOUND;
			}
			if(repo_handle.index_entries[i].flag==RECORD_PRESENT && repo_handle.index_entries[i].key==key)
			{
				fseek(repo_handle.booksys_data_fp,repo_handle.index_entries[i].offset,SEEK_SET);
				fread(&key,sizeof(key),1,repo_handle.booksys_data_fp);
				fread(rec,sizeof(*rec),1,repo_handle.booksys_data_fp);
				return LIB_SUCCESS;
			}
		}
	return LIB_REC_NOT_FOUND;
}



int put_book_by_isbn(int key,struct Book *rec)
{

//-----check index file for key
//-----if key already present check for flag [flag=1 : entry is valid]
//-----if key is present but flag is 0 then just add entry at same index i.e update only offset and update flag; return status
//-----if key is present but flag is 1 return failure as data is already present
//-----if key is not prsent then proceed with following steps:

// Seek to the end of the data file
// Create an index entry with the current data file location using ftell
// Add index entry to array using offset returned by ftell
// Write the key at the current data file location
// Write the record after writing the key
// return status
if(repo_handle.book_repo_status==LIB_REPO_CLOSED)
  {
    return LIB_REPO_NOT_OPEN;
  }
  int p,q;
  
  for(int i=0;i<repo_handle.index_count;i++)
  {
    if(repo_handle.index_entries[i].key==key)
    {
      if(repo_handle.index_entries[i].flag==RECORD_PRESENT)
      {
        BOOK_FAILURE;
      }
      else
      {
        repo_handle.index_entries[i].offset=ftell(repo_handle.booksys_data_fp);
        repo_handle.index_entries[i].flag=RECORD_PRESENT;
        p = fwrite(&key,sizeof(key),1,repo_handle.booksys_data_fp);
        q = fwrite(rec,sizeof(*rec),1,repo_handle.booksys_data_fp);
        if(p!=1 || q!=1)
        {
          return LIB_ADD_FAILED;
        }
        return BOOK_SUCCESS;
      }
    }
  }
  fseek(repo_handle.booksys_data_fp,0,SEEK_END);
  struct LIB_NdxInfo entry;

  entry.offset= ftell(repo_handle.booksys_data_fp);
  entry.flag=RECORD_PRESENT;
  entry.key=key;
  strcpy(entry.title,rec->title);
  repo_handle.index_entries[repo_handle.index_count]=entry;
  repo_handle.index_count++;
  p = fwrite(&key,sizeof(key),1,repo_handle.booksys_data_fp);
  q= fwrite(rec,sizeof( *rec),1,repo_handle.booksys_data_fp);
  if(p!=1 || q!=1)
  {
    return LIB_ADD_FAILED;
  }
  return BOOK_SUCCESS;
}




int delete_book_by_isbn( int key )
{


//-----delete_rec_by_key
//-----check repo status
//-----Search for index entry in index_entries array
//-----if key matches and flag is 1 then reset flag
//-----if key matches but flag is already reset return status
//-----if key doesn't match then return status
if(repo_handle.book_repo_status==LIB_REPO_CLOSED)
  {
    return LIB_REPO_NOT_OPEN;
  }
  for(int i=0;i<repo_handle.index_count;i++)
  {
    if(repo_handle.index_entries[i].flag==RECORD_PRESENT && repo_handle.index_entries[i].key==key)
    {
      repo_handle.index_entries[i].flag=RECORD_DELETED;
      return LIB_SUCCESS;
    }
  }
  return LIB_REC_NOT_FOUND;
}



//-----------------------------student: additional code---------------------------
int put_student_by_rollno( int rollno_to_write, struct Student *rec )

{

	//1. check if repo status is closed then return return appropriate error code referring to the error codes 
	//2. else continue with following action sequence
	//3. set the file pointer to end
	//4. write rollno_to_write 
	//5. write Student record
	//6. if both actions are successful then return studsys_success 
	//7. else return studsys_add_failed
	if(repo_handle.stud_repo_status==LIB_REPO_CLOSED)
  	{
    	return LIB_REPO_NOT_OPEN;
  	}
  	int p,q;
  
  	for(int i=0;i<repo_handle.stud_index_count;i++)
  	{
    	if(repo_handle.stud_index_entries[i].roll_no==rollno_to_write)
    	{
      		if(repo_handle.stud_index_entries[i].flag==RECORD_PRESENT)
      		{
        		return BOOK_FAILURE;
      		}
		else
		{
			fseek(repo_handle.studsys_data_fp,0,SEEK_END);
			repo_handle.stud_index_entries[i].offset=ftell(repo_handle.studsys_data_fp);
			repo_handle.stud_index_entries[i].flag=RECORD_PRESENT;
			p = fwrite(&rollno_to_write,sizeof(int),1,repo_handle.studsys_data_fp);
			q = fwrite(rec,sizeof(*rec),1,repo_handle.studsys_data_fp);
			if(p!=1 || q!=1)
			{
				return LIB_ADD_FAILED;
			}
			return BOOK_SUCCESS;
		}
    }
  }
  fseek(repo_handle.studsys_data_fp,0,SEEK_END);
  struct STUD_NdxInfo entry;

  entry.offset= ftell(repo_handle.studsys_data_fp);
  entry.flag=RECORD_PRESENT;
  entry.roll_no=rollno_to_write;
  strcpy(entry.name,rec->name);
  repo_handle.stud_index_entries[repo_handle.stud_index_count]=entry;
  repo_handle.stud_index_count++;
  p = fwrite(&rollno_to_write,sizeof(int),1,repo_handle.studsys_data_fp);
  q= fwrite(rec,sizeof( *rec),1,repo_handle.studsys_data_fp);
  if(p!=1 || q!=1)
  {
    return LIB_ADD_FAILED;
  }
  return BOOK_SUCCESS;
}



int get_student_by_rollno( int rollno_to_read, struct Student *rec )
{


	//1. check if repo status is closed then  return appropriate error code referring to the error codes 
	//2. else continue with following action sequence
	
	//3.1 read rollno
	//3.2 check if rollno is equal to the rollno_to_read 
 	//3.3 if yes then read entire record of a Student and return studsys_success
	//3.4 else skip the record and read next rollno of the Student
	//4. Repeat step 4.1 to 4.4 till end of file 
	//5. Return record not found : appropriate error code referring to the error codes 
	if(repo_handle.stud_repo_status==LIB_REPO_CLOSED)
  	{
    	return LIB_REPO_NOT_OPEN;
  	}
  	int offset=-1;
	int roll_no;
  	for(int i=0;i<repo_handle.stud_index_count;i++)
  	{
    	if(repo_handle.stud_index_entries[i].flag==RECORD_PRESENT && repo_handle.stud_index_entries[i].roll_no==rollno_to_read)
    	{
      		fseek(repo_handle.studsys_data_fp,repo_handle.stud_index_entries[i].offset,SEEK_SET);
      		fread(&roll_no,sizeof(int),1,repo_handle.studsys_data_fp);
			if(roll_no==rollno_to_read)
			{
      			fread(rec,sizeof(*rec),1,repo_handle.studsys_data_fp);
      			return LIB_SUCCESS;
			}
    	}
  	}
  	return LIB_REC_NOT_FOUND;
}


//--------------------------------issue()---------------------------------
int issue(int rollno, int isbn)
{


	// check if book repo status is closed then return return appropriate error code referring to the error codes 
	// else continue with following action sequence


	// check if student repo status is closed then return return appropriate error code referring to the error codes 
	// else continue with following action sequence

	
	// check if issue repo status is closed then return return appropriate error code referring to the error codes 
	// else continue with following action sequence


	//declare student and book variables 

	//get book by isbn and store status in status1
	//get student by rollno and store status in status1
	
	
	// if status1 and status2 are successful then continue with following action sequence else return error
		
	// create Issue object and assign rollno and isbn 
	// set the file pointer to end
	// write issue record
	
	// if both actions are successful then return success 
	// else return failed		
	if(repo_handle.book_repo_status==LIB_REPO_CLOSED)
	{
		return LIB_REPO_NOT_OPEN;
	}		
	if(repo_handle.issue_repo_status==LIB_REPO_CLOSED)
	{
		return LIB_REPO_NOT_OPEN;
	}
	if(repo_handle.stud_repo_status==LIB_REPO_CLOSED)
	{
		return LIB_REPO_NOT_OPEN;
	}
	int p,q;
	struct Book rec;
	struct Student stud_rec;
	p = get_book_by_isbn(isbn,&rec);
	q= get_student_by_rollno(rollno,&stud_rec);
	if(p || q)
	{
		return LIB_ADD_FAILED;
	}
	struct Issue record;
	record.isbn=isbn;
	record.rollno=rollno;
	for(int i=0;i<repo_handle.index_count;i++)
	{
		if(repo_handle.index_entries[i].key==isbn)
		{
			repo_handle.index_entries[i].flag=RECORD_ISSUED;    
		}
	}

	fseek(repo_handle.issuesys_data_fp,0,SEEK_END);
	p=fwrite(&record,sizeof(struct Issue),1,repo_handle.issuesys_data_fp);
	if(p!=1)
	{
		return LIB_ADD_FAILED;
	}
	return BOOK_SUCCESS;

}

//----------------------------------close()---------------------------------
int libsys_close()
{
	int a,b,c;
	//call booksys_close()
	//call studsys_close()
	//call issuesys_close()
	a=booksys_close();
	b=studsys_close();
	c=issuesys_close();

	if(a!= LIB_SUCCESS || b!=LIB_SUCCESS || c!= LIB_SUCCESS)
	{
		return LIB_NDX_SAVE_FAILED;
	}

	// Open the index file in wb mode (write mode, not append mode)
	// Write number of index entries at the beginning of index file
	// Unload the index array into the index file (overwrite the entire index file)
	// Close the index file and data file
	char INdexFileName[sizeof(repo_handle.booksys_name)+4];
	strcpy(INdexFileName,repo_handle.booksys_name);
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
    strcpy(repo_handle.booksys_name,"");
    repo_handle.book_repo_status=LIB_REPO_CLOSED;
    fclose(indexFile);

	





	char * STUD_NdxFileName=repo_handle.studsys_name;
	strcat(STUD_NdxFileName,".ndx");
    FILE * StudindexFile = fopen(INdexFileName,"wb");
    if(StudindexFile==NULL)
    {
        return LIB_FILE_ERROR;
    }
    fwrite(&repo_handle.stud_index_count,sizeof(int ),1,StudindexFile);
	p=0;
    for(int i=0;i<repo_handle.stud_index_count;i++)
    {
        p=fwrite(&repo_handle.stud_index_entries[i],sizeof(repo_handle.stud_index_entries[i]),1,StudindexFile);
        if(p!=1)
        {
            return LIB_NDX_SAVE_FAILED;
        }
    }
    fclose(StudindexFile);
    strcpy(repo_handle.booksys_name,"");
    repo_handle.book_repo_status=LIB_REPO_CLOSED;
	//check status of above functions
	// if all of them return success then return SUCCESS else return ERROR


	return LIB_SUCCESS;
}

int booksys_close()
{
	//1. check if repo status is closed then  return appropriate error code referring to the error codes in libsys.h
	//2. else continue with following action sequence
	//3. close file pointer
	//4. set booksys_name as "" 
	//5. set book_repo_status=LIB_REPO_CLOSED
    //6. return LIB_SUCCESS;
	if(repo_handle.book_repo_status==LIB_REPO_CLOSED)
	{
		return LIB_REPO_NOT_OPEN;
	}
	fclose(repo_handle.booksys_data_fp);
	strcpy(repo_handle.booksys_name,"");
	repo_handle.book_repo_status=LIB_REPO_CLOSED;
	return LIB_SUCCESS;

}



int studsys_close()
{


	//1. check if repo status is closed then  return appropriate error code referring to the error codes 
	//2. else continue with following action sequence
	//3. close file pointer
	//4. set studsys_name as "" 
	//5. set stud_repo_status=LIB_REPO_CLOSED
	//6. return LIB_SUCCESS;
	if(repo_handle.stud_repo_status==LIB_REPO_CLOSED)
	{
		return LIB_REPO_NOT_OPEN;
	}
	fclose(repo_handle.studsys_data_fp);
	strcpy(repo_handle.studsys_name,"");
	repo_handle.stud_repo_status=LIB_REPO_CLOSED;
	return LIB_SUCCESS;


}
int issuesys_close()
{


	//1. check if repo status is closed then  return appropriate error code referring to the error codes 
	//2. else continue with following action sequence
	//3. close file pointer
	//4. set issuesys_name as "" 
	//5. set issue_repo_status=LIB_REPO_CLOSED
	//6. return LIB_SUCCESS;
	if(repo_handle.issue_repo_status==LIB_REPO_CLOSED)
	{
		return LIB_REPO_NOT_OPEN;
	}
	fclose(repo_handle.issuesys_data_fp);
	strcpy(repo_handle.issuesys_name,"");
	repo_handle.issue_repo_status=LIB_REPO_CLOSED;
	return LIB_SUCCESS;
}
//---------------------------------------------------Additional Functions -----------------------
int get_book_by_title(char *title, struct Book *rec)
{
	if(repo_handle.book_repo_status==LIB_REPO_CLOSED)
	{
		return LIB_REPO_NOT_OPEN;
	}
	int offset=-1;
	int key;
	for(int i=0;i<repo_handle.index_count;i++)
	{
		if(repo_handle.index_entries[i].flag==RECORD_PRESENT && strcmp(repo_handle.index_entries[i].title,title)==0)
		{
			fseek(repo_handle.booksys_data_fp,repo_handle.index_entries[i].offset,SEEK_SET);
			fread(&key,sizeof(key),1,repo_handle.booksys_data_fp);
			fread(rec,sizeof(*rec),1,repo_handle.booksys_data_fp);
			return LIB_SUCCESS;
		}
	}
	return LIB_REC_NOT_FOUND;
}
int get_student_by_name(char *name, struct Student *rec)
{
	if(repo_handle.stud_repo_status==LIB_REPO_CLOSED)
  	{
    	return LIB_REPO_NOT_OPEN;
  	}
  	int offset=-1;
	int roll_no;
  	for(int i=0;i<repo_handle.stud_index_count;i++)
  	{
    	if(repo_handle.stud_index_entries[i].flag==RECORD_PRESENT && !strcmp(repo_handle.stud_index_entries[i].name,name))
    	{
      		fseek(repo_handle.studsys_data_fp,repo_handle.stud_index_entries[i].offset,SEEK_SET);
      		fread(&roll_no,sizeof(int),1,repo_handle.studsys_data_fp);
      		fread(rec,sizeof(*rec),1,repo_handle.studsys_data_fp);
      		return LIB_SUCCESS;
    	}
  	}
  	return LIB_REC_NOT_FOUND;	
}
int delete_student_by_rollno(int rollno)
{
	if(repo_handle.stud_repo_status==LIB_REPO_CLOSED)
  	{
    	return LIB_REPO_NOT_OPEN;
  	}
  	for(int i=0;i<repo_handle.stud_index_count;i++)
  	{
    	if(repo_handle.stud_index_entries[i].flag==RECORD_PRESENT && (repo_handle.stud_index_entries[i].roll_no==rollno))
    	{
      		repo_handle.stud_index_entries[i].flag=RECORD_DELETED;
      		return LIB_SUCCESS;
    	}
  	}
  	return LIB_REC_NOT_FOUND;
}