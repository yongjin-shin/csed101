#include <stdio.h>

//함수 선언
void getData(int*); //입력부
void divide(int*, int*, int*, int*, int*, int*); //처리부 - 자릿수 나누기
void cal_func(int, int, int, int, int*); //처리부 - 10진수로 계산
void print_result(int, int); //10진수 숫자 출력

int main()
{
	int num, num_copy, a1, a2, a3, a4, cal_result;

    //각 함수 호출
	getData(&num);
	divide(&num, &num_copy, &a1, &a2, &a3, &a4);
	cal_func(a1, a2, a3, a4, &cal_result);
	print_result(num_copy, cal_result);

	return 0;
}

//사용자에 의해 입력된 데이터는 num변수의 주소를 타고 곧바로 메모리에 저장됨.
void getData(int* num){
	printf("Input a 4-bit binary number: ");
	scanf("%d", num);
	return;
}

//변수 num에 저장되어 있는 값을 불러와 각 자릿 수에 할당된 변수 a1, a2, a3, a4에 나누어 저장함.
void divide(int* num, int* num_copy, int* a1, int* a2, int* a3, int* a4){
	*num_copy = *num; //num에 저장되어 있는 원본 값을 복사해둠.
	*a1 = *num / 1000; // 첫째자리 수는 10^3으로 나눈 몫임
	*num = (*num - *a1*1000); //첫째자리를 제외한 값을 새로운 num의 값으로 저장
	*a2 = *num / 100; //이하 동일한 과정들임.
	*num = (*num - *a2*100);
	*a3 = *num / 10;
	*num = (*num - *a3*10);
	*a4 = *num;
	return;
}

//위에서 나누어진 각 자리수들을 2^n을 곱해준 이후에, 합산하여 계산함.
void cal_func(int a1, int a2, int a3, int a4, int* cal_result){
	int result = 0;
	result = a1*2*2*2+a2*2*2+a3*2+a4*1;
	*cal_result = result;
	return;
}

//printf만으로 구성된 함수. 원본값의 복사본인 num_copy와 계산 결과를 불러들임. 이름은 ASCII code를 이용해 나타냄.
void print_result(int num_copy, int cal_result){
	printf("The binary number %d is a decimal number %d\n", num_copy, cal_result);
	printf("Written by %c%c%c%c%c%c%c%c%c%c%c%c.\n", 89,79,78,71,74,73,78,32,83,72,73,78);
	return;
}
