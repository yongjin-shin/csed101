#include"studentList.h"

int main(int argc, char* argv[]) {
	FILE* infile_subject;
	FILE* infile_student;
	char file_subject[20];
	char file_student[20];
	LIST list_subject;
	SET list_student;
	int comm;

	set_default(&list_subject, &list_student);//링크드리스트 초기화

	strcpy(file_subject, argv[1]);//첫번째 파일값 이름 복사
	strcpy(file_student, argv[2]);//두번째 파일값 이름 복사
	
	infile_subject = fopen(file_subject, "r");
	if (infile_subject == NULL) {
		printf("파일을 읽어올 수 없습니다.");//파일 없을 경우 오류 메세지
		return 100;
	}

	infile_student = fopen(file_student, "r");
	if (infile_student == NULL) {
		printf("파일을 읽어올 수 없습니다.");//파일 없을 경우 오류 메세지
		return 200;
	}

	insert_sub(infile_subject, &list_subject);//첫번째 파일에서 과목 목록 불러오기
	insert_stu(infile_student, &list_student);//두번째 파일에서 학생 정보 불러오기
	
	while (1) {
		print_menu();
		scanf("%d", &comm);//사용자의 입력에 따라 실행

		switch (comm) {
		case 1:
			by_student(&list_subject, &list_student);//학생별 성적 출력
			continue;

		case 2:
			by_subject(&list_subject, &list_student);//과목별 성적 출력
			continue;

		case 0:
			break;

		default:
			break;
		}

		free_mem(&list_subject, &list_student);//동적할당 메모리 해제
		fclose(infile_subject);//파일닫기
		fclose(infile_student);
		break;
	}

	return 0;
}
