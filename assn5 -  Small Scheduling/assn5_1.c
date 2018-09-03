#include"subjectList.h"

int main(int argc, char* argv[]){
	FILE* infile;
	FILE* outfile;
	char infile_name[20];
	SUBJECT sub;
	LIST list;
	char comm[20];

	//set list default
	list.head = NULL;
	list.count = 0;
	list.tail = NULL;

	if (argc == 1) { //�Է��� ���� ���, subject.txt ���Ϸ� �ޱ�
		infile = fopen("subject.txt", "r");
		if (infile == NULL) {
			printf("Something wrong with it\n");
			return 100;
		}
	}
	else
	{
		strcpy(infile_name, argv[1]);//�Է°��� �������, �Է°���� ���� ����
		infile = fopen(infile_name, "r");
		if (infile == NULL) {
			printf("������ �о�� �� �����ϴ�.");
			return 200;
		}
	}

	outfile = fopen("new_subject.txt", "w");//out���� new_subject�̸����� ����
	if (outfile == NULL) {
		printf("Outfile has something wrong\n");
		return 300;
	}

	insert_sub(infile, &list);
	print_sub(&list);
	
	while (1) {
		printf("\n>>");
		scanf("%s", comm);//����� �Է¹ޱ�
		getchar();

		if (strcmp(comm, "show") == 0) {
			print_sub(&list);
			continue;
		}
		else if (strcmp(comm, "quit") == 0) {
			quit_sub(outfile, &list);
			fclose(infile);
			fclose(outfile);
			break;
		}
		else if (strcmp(comm, "delete") == 0) {
			delete_sub(&list);
			continue;
		}
		else if (strcmp(comm, "add") == 0) {
			add_sub(&list);
			continue;
		}
	}

	return 0;
}
