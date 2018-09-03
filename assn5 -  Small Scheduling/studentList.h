#include"subjectList.h"

typedef struct {
	char sub_code[8];
	char grade[3];
}TAKING_SUBJECTS;

typedef struct student {
	int id;
	char name[11];
	char dept[7];
	int level;
	int sub_num;
	TAKING_SUBJECTS subject[8];
	struct student* next;
}STUDENT;

typedef struct {
	STUDENT* head;
	int count;
	STUDENT* tail;
} SET;

void set_default(LIST* plist, SET* pset);
void insert_stu(FILE* infile, SET* pSet);
void print_menu();
void by_student(LIST* plist, SET* pset);
float convert(char* grade);
void by_subject(LIST* plist, SET* pset);
void free_mem(LIST* plist, SET* pset);
