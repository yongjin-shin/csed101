#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>

void drawLine(void);
int ShowMenu(void);
int levelSetting(void);
int startGame(int);
void display(int, int, int, int, int, char, char);
void showState(int, int, int);
void showTime(int, int);
void showLife(int);
char getInstruction(void);
void showInstruction(char);
char getUserKey(void);
int judge(char, char, int);
void showFlag(char);
int com_score(int, int);
int last_answer(void);


int main(){
    int choose, yesno, level;
    int max_score=0;
    int score=0;
        
    while (1)
    {
    
		choose = ShowMenu(); //showMenu 함수에서 선택값 반환해서 choose 변수에 지정.

		switch (choose)
        {
            case 1://게임 시작
                level = levelSetting(); //level 값 설정
                score = startGame(level); //startGame에서 score값 반환 후 score 변수에 저장.
                continue; //반복문으로 다시 시작.
                
            case 2://최고 점수 확인
                max_score = com_score(max_score, score); // score 점수 비교를 하고 더 크거나 같은 값을 반환.
                printf("\n최고 점수는 %d점 입니다! \n\n", max_score);
                continue;
                
            case 3://게임 종료.
            {
                yesno = last_answer(); //lastAnswer 함수에서 yes or no question. 받아온 값이 yes인 경우 (리턴값 1) 프로그램 종료, 그외의 경우에는 처음으로.
                if (yesno == 1)
                    break;
                else
                {
                    printf("\n");
                    continue;
                }
            }

            default://잘못 입력시 반목문 다시 시작.
                printf("\n잘못된 값을 입력하셨습니다. 다시 입력해 주세요.\n\n");
                continue;
        }
		break;
    }
    
    return 0;
}


void drawLine(void)//라인 그리기
{
    int i;
    for(i=0; i<64; i++)
        printf("=");
    printf("\n");
}

int ShowMenu(void)//초기 메뉴화면 구성
{
    int choose;
    
    drawLine();
    printf("청기 백기 게임\n");
    drawLine();
    printf("1. 게임 시작\n");
    printf("2. 최고 점수 확인\n");
    printf("3. 게임 종료\n");
    drawLine();
    printf("번호 입력 : ");
    scanf("%d", &choose);
    
    return choose;//리턴 값은 정수형으로 반환.
}

int levelSetting(void) //게임 레벨 설정.
{
    int level;
    printf("난이도 선택 (1~3) : ");
    scanf("%d", &level);
    
    while(1)
    {
        switch (level)
        {
            case 1:
            case 2:
            case 3:
                break;
                
            default:// 1,2,3 이외의 값 입력시 다시 도출하고, 반복문 처음으로 돌아가기.
                printf("난이도 선택 (1~3) : ");
                scanf("%d", &level);
                continue;
        }
        break;
    }
    return level;//난이도 정수형으로 반환
}

int startGame(int level)
{

	int score = 0;
	int life = 5;
	int lim_time = 3;
	int cur_time;
	int rem_time;
	char direction = 0;
	char userInput = 0;
	int processing;


	for (cur_time = 0; cur_time < lim_time; cur_time++) // 본 게임 시작 전 카운트다운.
	{
		system("cls"); //메뉴화면 삭제 후 게임화면 불러오기.
		direction = 's'; //지시상태 대신에 시간을 표시하기 위함.
		display(level, life, score, cur_time, lim_time, direction, userInput); //게임화면 출력.
		Sleep(1000);//매 화면 출력마다 1초씩 딜레이.
	}
	system("cls");

	switch (level)//난이도 설정에서 받아온 값을 switch 함수에 적용. 난이도에 따른 제한시간 반환.
	{
	case 1:
		lim_time = 3;
		break;
	case 2:
		lim_time = 2;
		break;
	case 3:
		lim_time = 1;
		break;
	default:
		break;
	}

	while (1) //무한루프 시작. 본격 게임.
	{
		int i;
		direction = getInstruction();// getInstruction에서 받아온 컴퓨터의 지시사항을 direction 변수에 지정. 이를 display에 적용.
		for (cur_time = 0; cur_time <= lim_time; cur_time++)//진행시간은 0부터 시작하여 제한시간과 같아질때까지 반복됨.
		{
			display(level, life, score, cur_time, lim_time, direction, userInput);
			Sleep(1000);//화면 출력 이후 잠깐 정지.
			userInput = getUserKey();//그동안 사용자에게 입력키를 받음.
			system("cls");//기존이 화면 출력 삭제
			display(level, life, score, cur_time, lim_time, direction, userInput);//사용자에 의해 입력된 결과를 출력하기 위해 display함수를 다시 불러옴.
			rem_time = lim_time - cur_time;//남은시간 = 제한시간 - 진행시간
			processing = judge(direction, userInput, rem_time);//judge함수에서 반환되는 값을 진행사항 변수에 저장.

			i = cur_time;//두번째 for문에 쓰일 값 i. 이제까지 진행했던 시간을 잠깐 저장해둠.

			switch (processing)// judge함수에서 반환된 값을 이용해, 사용자가 키 입력 이후의 작업을 결정.
			{
			case 0://아무런 입력이 이루어지지 않을 경우, 반복문 계속 시행.
				system("cls");
				continue;
			case 1:
				printf("틀렸습니다!!\n");//오답일 경우. 2초동안 보여주고, 반복문에서 벗어남.
				life--;
				Sleep(2000);
				system("cls");
				break;
			case 2:
				printf("정답입니다!!\n"); //정답일 경우, 결과를 2초 동안 보여주고, 반복문에서 벗어남.
				score++;
				Sleep(2000);
				system("cls");
				break;
			case 3:
				printf("시간 초과!!\n"); //시간 초과일 경우, 결과를 2초 동안 보여주고, 다시 반목문으로 돌아감.
				life--;
				Sleep(2000);
				system("cls");
				continue;
			default:
				break;
			}
			
			for (cur_time = i+1; cur_time <= lim_time; cur_time++) //judge 이후 정답, 오답일 경우. 진행시간을 앞보다 1을 더 증가시켜야 게임의 시간이 바로 흐르게 됨. 그렇지 않다면 입력 이후 총 3초간 쉬게 됨.
			{
				system("cls");
				userInput = NULL;
				display(level, life, score, cur_time, lim_time, direction, userInput);
				Sleep(1000);
				system("cls");
			}
		}
		if (life == 0)
			break;
	}
	system("cls");
	printf("GAME OVER\n");
	printf("%d 점으로 끝났습니다.\n\n", score);
	return score;//점수 반환.
}

void display(int level, int life, int score, int cur_time, int lim_time, char direction, char userInput)
{
    drawLine(); //첫째줄 시작. 처음 정보 제시.
    showState(level, score, life);
    printf("\n");
 
    drawLine(); //둘째줄 시작. 시간 표시.
    showTime(cur_time, lim_time);
    
    drawLine(); //세째줄 시작. 시간 및 지시문
	switch (direction)
	{
	case 'e':
	case 'd':
	case 'i':
	case 'k':
	case NULL://e,d,i,k 일 경우를 제외하면 지시문 함수 불러옴. showInsturction.
		showInstruction(direction);
		break;
	default:
		printf("%d초 후 시작합니다\n", (lim_time - cur_time));
	}
    
    drawLine(); //네째줄 시작. 깃발 표시.
	showFlag(userInput);

	drawLine(); //5th line to start. Show the flag.
}

void showState(int level, int score, int life)
{
    printf("LEVEL : %d        ", level);
    printf("SCORE : %d        ", score);
    showLife(life);//life는 showLife 함수를 통해 구현.
}

void showLife(int life)
{
	int i, j;
    printf("LIFE : ");
 
	for (i = 0; i < life; i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		printf("♥");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
	for (j = 0; j < 5-life; j++)//life가 감소하였을 경우, 5개에서 현재 life만큼의 값을 빼준 뒤, 남은 값들을 빈하트 모양으로 출력.
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		printf("♡");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}

}

void showTime(int cur_time, int lim_time)
{
	int i, r;
	r = 30 / lim_time;//제한시간에 따라, 감소되는 사각형의 비율을 나타내는 값.

	for (i = 0; i < 30-(cur_time*r); i++)//전체 30개에서 진행시간에 따라 r의 값에 따라 출력값이 바뀜.
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		printf("■");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
	printf("\n");
}

char getInstruction(void) //To solve when there is no input.
{
	int desig;
	char direction;

	srand(time(NULL));//난수 생성
	desig = rand() % 5;
	
	switch(desig)
	{
		case 0:
			direction = 'e';
			break;

		case 1:
			 direction = 'd';
			break;
		
		case 2:
			 direction = 'i';
			break;
	
		case 3:
			 direction = 'k';
			break;
		
		default://5개의 난수 중 반드시 1개는 default값으로 배정됨. null값으로 도출.
			direction = NULL;
			break;
	}

	return direction;

}

void showInstruction(char direction) //getInstruction에서 반환된 값을 읽고, 지시문 출력.
{
		switch(direction)
	{
		case 'e':
			printf("청기 올려\n");
			break;

		case 'd':
			printf("청기 내려\n");
			break;
		
		case 'i':
			printf("백기 올려\n");
			break;
	
		case 'k':
			printf("백기 내려\n");
			break;

		case NULL:
			printf("청기 올리지마\n");
			break;
		
		default:
			break;
		}
}

char getUserKey(void)
{
	char userInput=0;

	if (kbhit() != 0)//입력이 되었을 경우에는
	{
		userInput = getch();//입력된 값을 반환.
	}
	else
		userInput = NULL;//입력이 안되었을 경우에는 null로 반환.
	
	return userInput;
}

int judge(char direction, char userInput, int rem_time)
{
	int processing;
	if (rem_time == 0)//남은시간이 0초일 경우,
	{
		if (direction != NULL)
			processing = 3;//지시문이 청기 올리지마가 아니었을 경우, 시간초과 출력
		else
			processing = 2;//지시문이 청기 올리지마 였을 경우, 정답 출력
	}
	else//남은시간이 남아있을 경우,
	{
		if (direction == NULL)
		{
			if (userInput != NULL)
				processing = 1;//지시문은 없지만, 키를 입력했을 경우, 오답 출력
			else
				processing = 0;//지시문도 없고, 키도 입력하지 않았을 경우, 계속 진행
		}
		else
		{
			if (userInput == NULL)
				processing = 0;//지시문이 있고, 입력이 이루어지지 않았을 경우, 계속 진행
			else
			{
				if (userInput == direction)
					processing = 2;//지시문도 있고, 입력이 이루어지고, 이때 둘의 값이 같은 경우, 정답 출력.
				else
					processing = 1;//지시문도 있고, 입력도 이루어졌지만, 둘의 값이 다른 경우, 오답 출력.
			}
		}
	}
	return processing; //진행사항 값 정수형으로 반환
}

void showFlag(char userInput)
{
	int i, j, k, r;

	switch (userInput)//사용자가 입력한 값에 따라 깃발의 모양을 다르게 출력.
	{
	case 'e':
		for (i = 0; i < 5; i++)//왼쪽 상단 푸른 깃발
		{
			for (j = 0; j < 8; j++)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
				printf("■");
			}
			printf("\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		for (k = 0; k < 32; k++)//중간 막대
		{
			if (k < 15)
				printf("■");
			else
				if (14 < k && k < 17)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
					printf("■");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				}
				else
					printf("■");
		}
		for (r = 0; r < 6; r++)//왼쪽 상단 공간
			printf("\n");
		break;

	case 'd':
		for (r = 0; r < 5; r++)//왼쪽 상단 공간
			printf("\n");
		for (k = 0; k < 32; k++)//중간 막대
		{
			if (k < 15)
				printf("■");
			else
				if (14 < k && k < 17)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
					printf("■");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				}
				else
					printf("■");
		}
		printf("\n");
		for (i = 0; i < 5; i++)//왼쪽 하단 푸른 깃발
		{
			for (j = 0; j < 8; j++)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
				printf("■");
			}
			printf("\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}

		break;

	case 'i':
		for (i = 0; i < 5; i++)//오른쪽 상단 하얀 깃발
		{
			for (j = 0; j < 32; j++)
			{
				if (j < 24)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
					printf("■");
				}
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					printf("■");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				}
			}
			printf("\n");
		}
		for (k = 0; k < 32; k++)//중간 막대
		{
			if (k < 15)
				printf("■");
			else
				if (14 < k && k < 17)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
					printf("■");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				}
				else
					printf("■");
		}
		for (r = 0; r < 6; r++)//오른쪽 하단 공간
			printf("\n");
		break;

	case 'k'://오른쪽 상단 공간
		for (r = 0; r < 5; r++)
			printf("\n");
		for (k = 0; k < 32; k++)//중간 막대
		{
			if (k < 15)
				printf("■");
			else
				if (14 < k && k < 17)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
					printf("■");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				}
				else
					printf("■");
		}
		printf("\n");
		for (i = 0; i < 5; i++)//오른쪽 하단 하얀 깃발
		{
			for (j = 0; j < 32; j++)
			{
				if (j < 24)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
					printf("■");
				}
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					printf("■");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				}
			}
			printf("\n");
		}
		break;

	default:
		for (r = 0; r < 5; r++)//위쪽 공간
			printf("\n");
		for (k = 0; k < 32; k++)//중간 막대
		{
			if (k < 15)
				printf("■");
			else
				if (14 < k && k < 17)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
					printf("■");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				}
				else
					printf("■");
		}
		for (r = 0; r < 6; r++)//아래쪽 공간
			printf("\n");
		break;
	}
}

int com_score(int max_score, int score)//현재 점수와 최고 점수 비교. 현재 점수는 '게임시작'의 함수에서 받아옴.
{
    if(max_score >= score)
        return max_score;
    else
        return score;
}



int last_answer(void)// 마지막 yes or no 질문의 값을 yes이면 1로 반환. no인 경우 0으로 반환.
{
    char answer;
    int answer_result;
    printf("게임을 종료하시겠습니까? (y/n) ");
    scanf(" %c", &answer);
    
    switch (answer)
    {
        case 'Y':
        case 'y':
            answer_result = 1;
            break;
            
        case 'N':
        case 'n':
            answer_result = 0;
            break;
            
        default:
            break;
    }
    return answer_result;
}
