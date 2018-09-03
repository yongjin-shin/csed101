#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct subject {
	char sub_code[8];
	char sub_name[41];
	int credit;
	struct subject* next;
} SUBJECT;

typedef struct {
	SUBJECT* head;
	int count;
	SUBJECT* tail;
} LIST;

void insert_sub(FILE* infile, LIST* plist);
void print_sub(LIST* plist);
void find_pos(LIST* plist, SUBJECT* temp);
void delete_sub(LIST* plist);
void add_sub(LIST* plist);
void quit_sub(FILE* outifle, LIST* plist);
