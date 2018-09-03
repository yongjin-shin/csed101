#include "studentList.h"

//����ü �ʱ�ȭ
void set_default(LIST* plist, SET* pset) {
	plist->head = NULL;
	plist->count = 0;
	plist->tail = NULL;

	pset->head = NULL;
	pset->count = 0;
	pset->tail = NULL;
}

//�л� ��� �ҷ�����
void insert_stu(FILE* infile, SET* pSet) {

	STUDENT* temp;
	int num = 0, level, sub_num = 0;
	char id[9], name[11], dept[7], sub_code[8], grade[3];


	while (fscanf(infile, "%s ", id) != EOF) {//ù��° ���ڿ��� �о����
		num = atoi(id) / 10000000;//���� ������ ġȯ�Ͽ��� ��

		if (0 < num && num <= 9) {//0�� 9���̿� �ִٸ�
			temp = (STUDENT*)malloc(sizeof(STUDENT));//�����Ҵ��� �ϰ� �޸𸮸� ����
			temp->next = NULL;
			temp->sub_num = 0;
			sub_num = 0;

			if (pSet->count == 0) {//���� count�� 0�϶����� �Ӹ��� ������ temp�� ���̱�
				pSet->head = temp;
				pSet->tail = temp;
			}
			else//����Ʈ�� ����Ǿ� �ִٸ�, �� ������ �̾� ���̱�
			{
				pSet->tail->next = temp;
				pSet->tail = temp;
			}

			pSet->count++;//����Ʈ�� ����� ���ķ� count 1�� ����

			temp->id = atoi(id);//�׸��� �̸�, �а�, �г��� �Է¹޾� ����
			fscanf(infile, "%s %s %d\n", name, dept, &level);
			strcpy(temp->name, name);
			strcpy(temp->dept, dept);
			temp->level = level;
		}
		else {//���� ù��° ���ڿ��� �������� �ƴ϶�� �Ѵٸ�
			strcpy(temp->subject[sub_num].sub_code, id);//�ش� ���ڿ��� �����ڵ�� �Է�
			fscanf(infile, "%s\n", grade);//���� ���ڿ��� ���� �������� �Է�
			strcpy(temp->subject[sub_num].grade, grade);
			sub_num++;//�� �������� �ӹ��� ������ ������� ������Ŵ
			temp->sub_num = sub_num;
		}
	}
}

//���� �޴� ���
void print_menu() {
	printf("### ���� ���� ���α׷� ###\n");
	printf("1. �л��� ����\n");
	printf("2. ���� ����\n");
	printf("0. ����\n");
	printf(">> ");
}

//�л��� ���� ���
void by_student(LIST* plist, SET* pset) {
	SUBJECT* pCur;
	STUDENT* sCur;
	int i = 0, tot_credit = 0;
	float  tot_grade = 0.00;

	printf("\n �й�\t |�̸�\t  |�а�(�г�)|");

	for (pCur = plist->head; pCur != NULL; pCur = pCur->next) {
		printf(" %-8s|", pCur->sub_code);
	}
	printf(" �������\t\n");

	for (sCur = pset->head; sCur != NULL; sCur = sCur->next) {//������ ���� ��� from ���� ��ũ�� ����Ʈ����
		printf(" %-8d|%-8s|%s(%d)   |", sCur->id, sCur->name, sCur->dept, sCur->level);
		for (pCur = plist->head; pCur != NULL; pCur = pCur->next) {//������ ��¥�� ������� ������
			for (i = 0; i <= sCur->sub_num; i++) {//������� �ҷ����鼭, �ű⿡ �´� �л����� ������ �ҷ���
				if (strcmp(sCur->subject[i].sub_code, pCur->sub_code) == 0) {
					printf(" %-8s|", sCur->subject[i].grade);
					tot_credit += pCur->credit;//�� ������ �Է��� �Ǹ�, ������ ����ϰ�
					tot_grade += pCur->credit * convert(sCur->subject[i].grade);//������ ����Ѵ�.
					break;
				}
				else if (i == sCur->sub_num) {//������ ���� ���� ��� �ǳʶڴ�.
					printf(" -       |");
				}
			}
		}
		printf(" %-8.2f\n", tot_grade / tot_credit);//�տ��� ���� ������ ������ �̿��� ����� ����
		tot_grade = 0;//������ �������� �ʱ�ȭ
		tot_credit = 0;
	}
	printf("\n");
}

//grade�� ���������� ��ȯ
float convert(char* grade) {
	if (strcmp(grade, "A+") == 0)
		return 4.3;
	else if (strcmp(grade, "A0") == 0)
		return 4.0;
	else if (strcmp(grade, "A-") == 0)
		return 3.7;
	else if (strcmp(grade, "B+") == 0)
		return 3.3;
	else if (strcmp(grade, "B0") == 0)
		return 3.0;
	else if (strcmp(grade, "B-") == 0)
		return 2.7;
	else if (strcmp(grade, "C+") == 0)
		return 2.3;
	else if (strcmp(grade, "C0") == 0)
		return 2.0;
	else if (strcmp(grade, "C-") == 0)
		return 1.7;
	else if (strcmp(grade, "D+") == 0)
		return 1.3;
	else if (strcmp(grade, "D0") == 0)
		return 1.0;
	else if (strcmp(grade, "D-") == 0)
		return 0.7;
	else if (strcmp(grade, "F") == 0)
		return 0.0;
}

//���� ����
void by_subject(LIST* plist, SET* pset) {
	SUBJECT* pCur;
	STUDENT* sCur;

	//���� �ʱ�ȭ
	int comm = 0;
	int a = plist->count;
	int i = 0, j = 0, stu_num = 0;
	float tot_sub = 0.00;

	while (1) {
		printf("\n");
		print_sub(plist);//������� �����.

		while (1) {
			printf("������(0) >> ");
			scanf("%d", &comm);//������� �Է��� ���� ����
			if (1 <= comm && comm <= a)//�Է��� �����̿� ������ ����������
				break;
			else if (comm == 0)//0�� �Է����� ���
				break;
			else {
				printf("�ùٸ� �Է��� �ƴմϴ�.\n");//�̿��� �Է¿� ���ؼ��� ��� ����
				continue;
			}
		}

		if (comm == 0) {//���� �Էµ� ���� 0�̶�� ���ѷ��� ����������
			printf("\n");
			break;
		}

		for (pCur = plist->head; pCur != NULL; pCur = pCur->next) {//�ùٸ� �Է��̶��
			i++;
			if (i == comm) {//�Էµ� ���ڿ� ���� �ش��ϴ� ������ ��Ī�ؼ� ���
				printf("\n�����: %s(%s),  ����: %d����\n\n", pCur->sub_code, pCur->sub_name, pCur->credit);
				i = 0;
				break;
			}
		}

		printf(" �й�\t | �̸�\t   | �а�(�г�) | ����\t\n");
		for (sCur = pset->head; sCur != NULL; sCur = sCur->next) {//�л����� ������ ���ʴ�� �ҷ�����
			for (j = 0; j <= sCur->sub_num; j++) {
				if (strcmp(sCur->subject[j].sub_code, pCur->sub_code) == 0) {//������� ��ġ�ϴ� ����
					printf(" %-8d| %-8s| %s(%d)\t|", sCur->id, sCur->name, sCur->dept, sCur->level);//����Ѵ�
					printf(" %s(%.2f)\n", sCur->subject[j].grade, convert(sCur->subject[j].grade));//������ �����
					tot_sub += convert(sCur->subject[j].grade);//������ ����ϰ�
					stu_num++;
					break;
				}
			}
		}
		printf("\n** �������: %.2f\n\n", tot_sub / stu_num);//�̸� �̿��� ����� ���Ѵ�
		stu_num = 0;
		tot_sub = 0.0;
	}
}

void free_mem(LIST* plist, SET* pset) {
	SUBJECT* pCur;
	SUBJECT* pNext;
	STUDENT* sCur;
	STUDENT* sNext;

	pCur = plist->head;

	while (plist->count != 0) {//���� �޸��Ҵ� ����
		pNext = pCur->next;
		free(pCur);
		pCur = pNext;
		plist->count--;
	}

	sCur = pset->head;

	while (pset->count != 0) {//�л� �޸��Ҵ� ����
		sNext = sCur->next;
		free(sCur);
		sCur = sNext;
		pset->count--;
	}
}