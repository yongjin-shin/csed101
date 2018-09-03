#include "studentList.h"

//구조체 초기화
void set_default(LIST* plist, SET* pset) {
	plist->head = NULL;
	plist->count = 0;
	plist->tail = NULL;

	pset->head = NULL;
	pset->count = 0;
	pset->tail = NULL;
}

//학생 목록 불러오기
void insert_stu(FILE* infile, SET* pSet) {

	STUDENT* temp;
	int num = 0, level, sub_num = 0;
	char id[9], name[11], dept[7], sub_code[8], grade[3];


	while (fscanf(infile, "%s ", id) != EOF) {//첫번째 문자열을 읽어들임
		num = atoi(id) / 10000000;//만약 정수로 치환하였을 때

		if (0 < num && num <= 9) {//0과 9사이에 있다면
			temp = (STUDENT*)malloc(sizeof(STUDENT));//동적할당을 하고 메모리를 잡음
			temp->next = NULL;
			temp->sub_num = 0;
			sub_num = 0;

			if (pSet->count == 0) {//만약 count가 0일때에는 머리와 꼬리를 temp에 붙이기
				pSet->head = temp;
				pSet->tail = temp;
			}
			else//리스트가 연결되어 있다면, 그 다음에 이어 붙이기
			{
				pSet->tail->next = temp;
				pSet->tail = temp;
			}

			pSet->count++;//리스트에 연결된 이후로 count 1씩 증가

			temp->id = atoi(id);//그리고 이름, 학과, 학년을 입력받아 저장
			fscanf(infile, "%s %s %d\n", name, dept, &level);
			strcpy(temp->name, name);
			strcpy(temp->dept, dept);
			temp->level = level;
		}
		else {//만약 첫번째 문자열이 정수형이 아니라고 한다면
			strcpy(temp->subject[sub_num].sub_code, id);//해당 문자열을 과목코드로 입력
			fscanf(infile, "%s\n", grade);//다음 문자열을 과목 성적으로 입력
			strcpy(temp->subject[sub_num].grade, grade);
			sub_num++;//이 루프에서 머무를 동안은 과목수를 증가시킴
			temp->sub_num = sub_num;
		}
	}
}

//메인 메뉴 출력
void print_menu() {
	printf("### 성적 관리 프로그램 ###\n");
	printf("1. 학생별 성적\n");
	printf("2. 과목별 성적\n");
	printf("0. 종료\n");
	printf(">> ");
}

//학생별 성적 출력
void by_student(LIST* plist, SET* pset) {
	SUBJECT* pCur;
	STUDENT* sCur;
	int i = 0, tot_credit = 0;
	float  tot_grade = 0.00;

	printf("\n 학번\t |이름\t  |학과(학년)|");

	for (pCur = plist->head; pCur != NULL; pCur = pCur->next) {
		printf(" %-8s|", pCur->sub_code);
	}
	printf(" 평점평균\t\n");

	for (sCur = pset->head; sCur != NULL; sCur = sCur->next) {//과목을 먼저 출력 from 과목 링크드 리스트에서
		printf(" %-8d|%-8s|%s(%d)   |", sCur->id, sCur->name, sCur->dept, sCur->level);
		for (pCur = plist->head; pCur != NULL; pCur = pCur->next) {//과목이 어짜피 순서대로 있으니
			for (i = 0; i <= sCur->sub_num; i++) {//순서대로 불러오면서, 거기에 맞는 학생들의 성적을 불러옴
				if (strcmp(sCur->subject[i].sub_code, pCur->sub_code) == 0) {
					printf(" %-8s|", sCur->subject[i].grade);
					tot_credit += pCur->credit;//한 과목이 입력이 되면, 학점을 계산하고
					tot_grade += pCur->credit * convert(sCur->subject[i].grade);//성적을 계산한다.
					break;
				}
				else if (i == sCur->sub_num) {//수업을 듣지 않을 경우 건너뛴다.
					printf(" -       |");
				}
			}
		}
		printf(" %-8.2f\n", tot_grade / tot_credit);//앞에서 구한 학점과 성적을 이용해 평균을 구함
		tot_grade = 0;//루프가 끝났으니 초기화
		tot_credit = 0;
	}
	printf("\n");
}

//grade를 정수형으로 변환
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

//과목별 성적
void by_subject(LIST* plist, SET* pset) {
	SUBJECT* pCur;
	STUDENT* sCur;

	//변수 초기화
	int comm = 0;
	int a = plist->count;
	int i = 0, j = 0, stu_num = 0;
	float tot_sub = 0.00;

	while (1) {
		printf("\n");
		print_sub(plist);//과목명을 출력함.

		while (1) {
			printf("나가기(0) >> ");
			scanf("%d", &comm);//사용자의 입력을 먼저 받음
			if (1 <= comm && comm <= a)//입력한 값사이에 있으면 빠져나가고
				break;
			else if (comm == 0)//0을 입력했을 경우
				break;
			else {
				printf("올바른 입력이 아닙니다.\n");//이외의 입력에 대해서는 계속 시행
				continue;
			}
		}

		if (comm == 0) {//만약 입력된 값이 0이라면 무한루프 빠져나가기
			printf("\n");
			break;
		}

		for (pCur = plist->head; pCur != NULL; pCur = pCur->next) {//올바른 입력이라면
			i++;
			if (i == comm) {//입력된 숫자와 과목에 해당하는 순서를 매칭해서 출력
				printf("\n과목명: %s(%s),  학점: %d학점\n\n", pCur->sub_code, pCur->sub_name, pCur->credit);
				i = 0;
				break;
			}
		}

		printf(" 학번\t | 이름\t   | 학과(학년) | 학점\t\n");
		for (sCur = pset->head; sCur != NULL; sCur = sCur->next) {//학생들의 과목을 차례대로 불러들임
			for (j = 0; j <= sCur->sub_num; j++) {
				if (strcmp(sCur->subject[j].sub_code, pCur->sub_code) == 0) {//과목명이 일치하는 것을
					printf(" %-8d| %-8s| %s(%d)\t|", sCur->id, sCur->name, sCur->dept, sCur->level);//출력한다
					printf(" %s(%.2f)\n", sCur->subject[j].grade, convert(sCur->subject[j].grade));//성적을 출력함
					tot_sub += convert(sCur->subject[j].grade);//총합을 계산하고
					stu_num++;
					break;
				}
			}
		}
		printf("\n** 과목평균: %.2f\n\n", tot_sub / stu_num);//이를 이용해 평균을 구한다
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

	while (plist->count != 0) {//과목 메모리할당 해제
		pNext = pCur->next;
		free(pCur);
		pCur = pNext;
		plist->count--;
	}

	sCur = pset->head;

	while (pset->count != 0) {//학생 메모리할당 해제
		sNext = sCur->next;
		free(sCur);
		sCur = sNext;
		pset->count--;
	}
}