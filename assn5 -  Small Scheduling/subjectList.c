#include"subjectList.h"

//���Ͽ��� ���� �ܾ����
void insert_sub(FILE* infile, LIST* plist) {

	SUBJECT* temp;
	char sub_code[8], sub_name[41];
	int credit;

	while (fscanf(infile, "%s %s %d\n", sub_code, sub_name, &credit) != EOF)//�����ڵ�, �̸�, ���������� �б�
	{
		temp = (SUBJECT*)malloc(sizeof(SUBJECT));//�����޸� �Ҵ��ϱ�

		strcpy(temp->sub_code, sub_code);
		strcpy(temp->sub_name, sub_name);
		temp->credit = credit;
		temp->next = NULL;

		find_pos(plist, temp);//��ġ ã�Ƽ� ����
	}
}

//���� ��� ���
void print_sub(LIST* plist) {
	SUBJECT* pCur;
	int num = 1;

	printf("���� ���\n");
	for (pCur = plist->head; pCur != NULL; pCur = pCur->next) {
		printf(" %d %s %s (%d����)\n", num, pCur->sub_code, pCur->sub_name, pCur->credit);
		num++;
	}
}

//����Ʈ���� ��ġ ã��
void find_pos(LIST* plist, SUBJECT* temp) {

	SUBJECT* pCur;

	if (plist->count == 0) {//�� ����Ʈ������ ���� ���Ͽ� ���� ���� ���� �ֱ�
		plist->head = temp;
		plist->tail = temp;
	}
	else {//�� ����Ʈ�� �ƴ� ��쿡��, 
		for (pCur = plist->head; pCur != NULL; pCur = pCur->next)
		{
			if (strcmp(pCur->sub_code, temp->sub_code) > 0) {//�����ڵ��� ���ڿ� ���� ���Ͽ�, �ܾ�� ���� �����ϴ� ������ ���� ���
				temp->next = plist->head;//�տ� ���� ����
				plist->head = temp;
				break;
			}
			else if (pCur->next == NULL) {//ó���� �ƴϰ�, �߰��� ���: �������� ����.
				temp->next = pCur->next;//�������� ������ ���̱�
				pCur->next = temp;
				plist->tail = temp;
				break;
			}
			else if (strcmp(pCur->sub_code, temp->sub_code) < 0 && 0 < strcmp(pCur->next->sub_code, temp->sub_code)) {//�߰��� ���
				temp->next = pCur->next;
				pCur->next = temp;
				break;
			}
		}
	}
	plist->count++;//����Ʈ�� ���� ������Ʈ
}

void delete_sub(LIST* plist) {
	SUBJECT* pCur;
	SUBJECT* pNext;
	char del_code[8];

	printf("�����ڵ�: ");
	scanf("%s", del_code);//���� �ڵ带 �Է� ����
	getchar();

	for (pCur = plist->head; pCur != NULL; pCur = pCur->next) {//������� �о�鼭
		if (strcmp(pCur->sub_code, del_code) == 0 && pCur == plist->head) {//���� ��ġ�ϴ� ���� �ִ� ���, �׸��� ���� ó���� ��
			plist->head = pCur->next;
			free(pCur);
			plist->count--;
			return;
		}

		else if (pCur->next != NULL && strcmp(pCur->next->sub_code, del_code) == 0 && pCur->next == plist->tail) {//��ġ�ϰ�, �������� ��
			plist->tail = pCur;
			pCur->next = NULL;
			pNext = pCur->next;
			free(pNext);
			plist->count--;
			return;
		}

		else if (pCur->next != NULL && strcmp(pCur->next->sub_code, del_code) == 0 && pCur->next != plist->tail) {//��ġ�ϰ�, �߰��� ��
			pNext = pCur->next;
			pCur->next = pCur->next->next;
			plist->count--;
			free(pNext);
			return;
		}
	}
	printf("Not Found\n");//���� ��쿡�� not found ���
	return;
}

void add_sub(LIST* plist) {
	SUBJECT* pCur;
	SUBJECT* temp;
	char input_code[8];
	char input_name[41];
	int input_credit;

	printf("�����ڵ�: ");
	scanf("%s", input_code);//����� �Է� �ڵ�
	getchar();

	for (pCur = plist->head; pCur != NULL; pCur = pCur->next) {
		if (strcmp(pCur->sub_code, input_code) == 0) { return; }//���� ��ġ�ϴ� ��찡 �ִٸ�, ����
	}

	//��ġ�ϴ� ��찡 ���ٸ�, ������ ���
	printf("�����: ");
	scanf("%s", input_name);
	getchar();
	printf("����: ");
	scanf("%d", &input_credit);

	temp = (SUBJECT*)malloc(sizeof(SUBJECT));

	strcpy(temp->sub_code, input_code);
	strcpy(temp->sub_name, input_name);
	temp->credit = input_credit;
	temp->next = NULL;

	find_pos(plist, temp);
}

void quit_sub(FILE* outfile, LIST* plist) {
	SUBJECT* pCur;
	SUBJECT* pNext;

	//������ outfile �� ���
	for (pCur = plist->head; pCur != NULL; pCur = pCur->next) {
		fprintf(outfile, "%s %s %d\n", pCur->sub_code, pCur->sub_name, pCur->credit);
	}

	//�����Ҵ� �޸� ����
	pCur = plist->head;

	while (plist->count != 0) {
		pNext = pCur->next;
		free(pCur);
		pCur = pNext;
		plist->count--;
	}

	printf("Outfile Name: new_subject.txt\n");
}