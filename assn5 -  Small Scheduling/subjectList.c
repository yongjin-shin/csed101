#include"subjectList.h"

//파일에서 정보 긁어오기
void insert_sub(FILE* infile, LIST* plist) {

	SUBJECT* temp;
	char sub_code[8], sub_name[41];
	int credit;

	while (fscanf(infile, "%s %s %d\n", sub_code, sub_name, &credit) != EOF)//과목코드, 이름, 학점순으로 읽기
	{
		temp = (SUBJECT*)malloc(sizeof(SUBJECT));//동적메모리 할당하기

		strcpy(temp->sub_code, sub_code);
		strcpy(temp->sub_name, sub_name);
		temp->credit = credit;
		temp->next = NULL;

		find_pos(plist, temp);//위치 찾아서 저장
	}
}

//과목 목록 출력
void print_sub(LIST* plist) {
	SUBJECT* pCur;
	int num = 1;

	printf("과목 목록\n");
	for (pCur = plist->head; pCur != NULL; pCur = pCur->next) {
		printf(" %d %s %s (%d학점)\n", num, pCur->sub_code, pCur->sub_name, pCur->credit);
		num++;
	}
}

//리스트에서 위치 찾기
void find_pos(LIST* plist, SUBJECT* temp) {

	SUBJECT* pCur;

	if (plist->count == 0) {//빈 리스트에서는 헤드와 테일에 읽은 파일 내용 넣기
		plist->head = temp;
		plist->tail = temp;
	}
	else {//빈 리스트가 아닐 경우에는, 
		for (pCur = plist->head; pCur != NULL; pCur = pCur->next)
		{
			if (strcmp(pCur->sub_code, temp->sub_code) > 0) {//과목코드의 문자열 값을 비교하여, 긁어온 값이 존재하는 값보다 작을 경우
				temp->next = plist->head;//앞에 갖다 붙임
				plist->head = temp;
				break;
			}
			else if (pCur->next == NULL) {//처음도 아니고, 중간일 경우: 마지막에 붙임.
				temp->next = pCur->next;//마지막에 가져다 붙이기
				pCur->next = temp;
				plist->tail = temp;
				break;
			}
			else if (strcmp(pCur->sub_code, temp->sub_code) < 0 && 0 < strcmp(pCur->next->sub_code, temp->sub_code)) {//중간일 경우
				temp->next = pCur->next;
				pCur->next = temp;
				break;
			}
		}
	}
	plist->count++;//리스트의 개수 업데이트
}

void delete_sub(LIST* plist) {
	SUBJECT* pCur;
	SUBJECT* pNext;
	char del_code[8];

	printf("과목코드: ");
	scanf("%s", del_code);//과목 코드를 입력 받음
	getchar();

	for (pCur = plist->head; pCur != NULL; pCur = pCur->next) {//순서대로 읽어가면서
		if (strcmp(pCur->sub_code, del_code) == 0 && pCur == plist->head) {//만약 일치하는 것이 있는 경우, 그리고 제일 처음일 때
			plist->head = pCur->next;
			free(pCur);
			plist->count--;
			return;
		}

		else if (pCur->next != NULL && strcmp(pCur->next->sub_code, del_code) == 0 && pCur->next == plist->tail) {//일치하고, 마지막일 때
			plist->tail = pCur;
			pCur->next = NULL;
			pNext = pCur->next;
			free(pNext);
			plist->count--;
			return;
		}

		else if (pCur->next != NULL && strcmp(pCur->next->sub_code, del_code) == 0 && pCur->next != plist->tail) {//일치하고, 중간일 때
			pNext = pCur->next;
			pCur->next = pCur->next->next;
			plist->count--;
			free(pNext);
			return;
		}
	}
	printf("Not Found\n");//없는 경우에는 not found 출력
	return;
}

void add_sub(LIST* plist) {
	SUBJECT* pCur;
	SUBJECT* temp;
	char input_code[8];
	char input_name[41];
	int input_credit;

	printf("과목코드: ");
	scanf("%s", input_code);//사용자 입력 코드
	getchar();

	for (pCur = plist->head; pCur != NULL; pCur = pCur->next) {
		if (strcmp(pCur->sub_code, input_code) == 0) { return; }//만약 일치하는 경우가 있다면, 종료
	}

	//일치하는 경우가 없다면, 다음을 출력
	printf("과목명: ");
	scanf("%s", input_name);
	getchar();
	printf("학점: ");
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

	//종료전 outfile 에 출력
	for (pCur = plist->head; pCur != NULL; pCur = pCur->next) {
		fprintf(outfile, "%s %s %d\n", pCur->sub_code, pCur->sub_name, pCur->credit);
	}

	//동적할당 메모리 해제
	pCur = plist->head;

	while (plist->count != 0) {
		pNext = pCur->next;
		free(pCur);
		pCur = pNext;
		plist->count--;
	}

	printf("Outfile Name: new_subject.txt\n");
}