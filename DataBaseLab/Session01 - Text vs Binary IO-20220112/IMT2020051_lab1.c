# include <stdio.h> 
#include<string.h>
struct student {
  int rollnum;
  char name[30];
  int age;
};

int save_num_text( char *filename ) {
  FILE *my_file = fopen(filename,"w");
  for(int i=0;i<20;i++)
  {
    fprintf(my_file,"%d\n",i);
  }
  fclose(my_file);
}

int read_num_text( char *filename ) {
  FILE *my_file = fopen(filename,"r");
  int num;
  while(fscanf(my_file,"%d",&num))
  {
    printf("%d\n",num);
  }
  fclose(my_file);
}

int save_struct_text( char *filename ) {
  struct student student_list[5];
  char names[5][30] ={"naitik","arin","kaushik","vaibhav","vatsal"}; 
  for(int i=0;i<5;i++)
  {
    student_list[i].rollnum=i+1;
    strcpy(student_list[i].name,names[i]);
    student_list[i].age=25-2*i;
  }
  FILE *my_file = fopen(filename,"w");
  for(int i=0;i<5;i++)
  {
    fprintf(my_file,"%d %s %d\n",student_list[i].rollnum,student_list[i].name,student_list[i].age);
  }
  fclose(my_file);
}

int read_struct_text( char *filename ) {
  FILE * my_file = fopen(filename,"r");
  int roll_num;
  char name[30];
  int age;
  while(!feof(my_file))
  {
    fscanf(my_file,"%d %s %d\n",&roll_num,&name,&age);
    printf("rollno:%d,name:%s,age:%d\n",roll_num,name,age);
  }
  fclose(my_file);
}


int save_num_binary( char *filename) {
  FILE *my_file = fopen(filename,"wb");         
  for(int i= 0;i<20;i++)
  {
    fwrite(&i,4,1,my_file);
  }
  fclose(my_file);
}

int read_num_binary( char *filename ) {
 FILE *my_file = fopen(filename,"rb");
 int num;
 while(fread(&num,4,1,my_file))
 {
   printf("%d\n",num);
 }
 fclose(my_file);
}

int save_struct_binary( char *filename ) {
  FILE* my_file = fopen(filename,"wb");
  struct student student_list[5];
  char names[5][30] ={"naitik","arin","kaushik","vaibhav","vatsal"}; 
  for(int i=0;i<5;i++)
  {
    student_list[i].rollnum=i+1;
    strcpy(student_list[i].name,names[i]);
    student_list[i].age=25-2*i;
  }
  for(int i=0;i<5;i++)
  {
    fwrite(&student_list[i],sizeof(student_list[i]),1,my_file);
  }
  fclose(my_file);
}

int read_struct_binary( char *filename ) {
 FILE* my_file = fopen(filename,"rb");
 struct student student_list[5];
 int i=0;
 while(fread(&student_list[i],sizeof(student_list[i]),1,my_file))
 {
   printf("rollno:%d,name:%s,age:%d\n",student_list[i].rollnum,student_list[i].name,student_list[i].age);
   i++;
 }
 fclose(my_file);
}

