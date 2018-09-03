#include"studentList.h"

int main(int argc, char* argv[]) {
	FILE* infile_subject;
	FILE* infile_student;
	char file_subject[20];
	char file_student[20];
	LIST list_subject;
	SET list_student;
	int comm;

	set_default(&list_subject, &list_student);//��ũ�帮��Ʈ �ʱ�ȭ

	strcpy(file_subject, argv[1]);//ù��° ���ϰ� �̸� ����
	strcpy(file_student, argv[2]);//�ι�° ���ϰ� �̸� ����
	
	infile_subject = fopen(file_subject, "r");
	if (infile_subject == NULL) {
		printf("������ �о�� �� �����ϴ�.");//���� ���� ��� ���� �޼���
		return 100;
	}

	infile_student = fopen(file_student, "r");
	if (infile_student == NULL) {
		printf("������ �о�� �� �����ϴ�.");//���� ���� ��� ���� �޼���
		return 200;
	}

	insert_sub(infile_subject, &list_subject);//ù��° ���Ͽ��� ���� ��� �ҷ�����
	insert_stu(infile_student, &list_student);//�ι�° ���Ͽ��� �л� ���� �ҷ�����
	
	while (1) {
		print_menu();
		scanf("%d", &comm);//������� �Է¿� ���� ����

		switch (comm) {
		case 1:
			by_student(&list_subject, &list_student);//�л��� ���� ���
			continue;

		case 2:
			by_subject(&list_subject, &list_student);//���� ���� ���
			continue;

		case 0:
			break;

		default:
			break;
		}

		free_mem(&list_subject, &list_student);//�����Ҵ� �޸� ����
		fclose(infile_subject);//���ϴݱ�
		fclose(infile_student);
		break;
	}

	return 0;
}
