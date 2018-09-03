#include <stdio.h>
#include <math.h> //sqrt 함수를 사용하기 위해 <math.h> 헤더파일을 호출.

//필요한 함수들 선언함
void getData(signed int*, signed int*, signed int*, signed int*, signed int*, signed int*);
void cal_peri(signed int, signed int, signed int, signed int, signed int, signed int, float*, float*, float*, float*);
void cal_area(float, float, float, float, float*);
void print_result(float, float);

int main(){
	signed int x1, y1, x2, y2, x3, y3; //음수값 표시
	float a, b, c, s, area;

    //함수 호출
	getData(&x1, &y1, &x2, &y2, &x3, &y3);
	cal_peri(x1, y1, x2, y2, x3, y3, &a, &b, &c, &s);
	cal_area(a, b, c, s, &area);
	print_result(s, area);

	return 0;
}

//입력되는 값들은 모두 포인터 변수에 의해 주소를 따라 바로 할당된 메모리에 저장됨. Call by address이기 때문에 따로 return되는 결과값은 없음.
void getData(signed int* x1, signed int* y1, signed int* x2, signed int* y2, signed int* x3, signed int* y3){
	printf("Enter P1(x1, y1) : ");
	scanf("%d %d", x1, y1); //첫 번째 좌표
	fflush(stdin); //buffer clear
	printf("Enter P2(x2, y2) : ");
	scanf(" %d %d", x2, y2); //두 번째 좌표
	fflush(stdin); // buffer clear
	printf("Enter P3(x3, y3) : ");
	scanf(" %d %d", x3, y3); //세 번째 좌표
}

//단순 계산. sqrt 함수를 이용하여 제곱근 값을 구해낸다. 이때도 역시나 포인터 변수를 이용하여 return값 없이 바로 변수에 저장을 함.
void cal_peri(signed int x1, signed int y1, signed int x2, signed int y2, signed int x3, signed int y3, float* a, float* b, float* c, float* s){
	*a = sqrt(((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2)));
	*b = sqrt(((x2-x3)*(x2-x3))+((y2-y3)*(y2-y3)));
	*c = sqrt(((x1-x3)*(x1-x3))+((y1-y3)*(y1-y3)));
	*s = (*a+*b+*c)/2;
}

//앞서 도출해내었던 값들을 불러내어 삼각형의 면적을 구하고, area값을 변수에 저장함.
void cal_area(float a, float b, float c, float s, float* area){
	*area = sqrt(s * (s-a) * (s-b) * (s-c));
}

// 결과를 도출함.
void print_result(float s, float area){
	printf("The perimeter of triangle is : %.3f\n", s*2); //perimeter = 2*s
	printf("The area of triangle is : %.3f\n", area);
}
