#include<stdio.h>
#include<unistd.h>
#include"keyboard.h"

void textMenu(char string[], int stringsize)
{
	int check_result;
	int len;

	while(1)
	{
		printf("***** Enter String *****\n(less than 20 letters with 0-9 and a-z)\n: ");
		fgets(string, stringsize, stdin);//get the user input by using fgets
		__fpurge(stdin);//clear the buffer
		len = inputStringLength(string);//calculate the length of inputstring
		string[len - 1] = '\0';//clear the '\n'
		len--;

		//printf("string: --%s--\n", string);
		//printf("length: --%d--\n", len);
		check_result = inputStringChecker(string, len);//check the string whether it is proper or not
		//printf("check result: ==%d==\n", check_result);

		switch (check_result)
		{
			case -1://the case that user input unproper string which is over 20 characters
				printf("please, put a string with 0-9 and a-z");
				break;

			case 0://the case that user input over 20 letters
				printf("please, put less than 20 letters");
				break;

			case 1://the case that user input unproper string
				printf("please, put a string with 0-9 and a-z");
				break;

			case 2://correct input
				return;

			default:
				break;
		}
		printf(" (Enter any key to continue)\n");

		while(!kbhit())
		{ }
		getchar();
		system("clear");
	}
}

int patternMenu()
{
	int pattern=0;
	while(1)
	{
		system("clear");
		printf("***** Pattern Selection *****\n1. Move leftward\n2. Move rightward\n3. Move upward\n4. Move downward\n(number) : ");
		scanf("%d", &pattern);
		__fpurge(stdin);

		if(pattern <= 4 && 1 <= pattern)
			break;
		else
		{
			printf("please, put a number between 1 and 4 (enter any key to continue)");
			while(!kbhit())
			{}
			getchar();
			__fpurge(stdin);
		}
	}

	return pattern;
}

int moveSpeed()
{
	int speed=0;
	int time=0;
	while(1)
	{
		system("clear");
		printf("***** Move Speed *****\n1. every 1 second\n2. every 0.5 second\n3. every 0.33 second\n(number) : ");
		scanf("%d", &speed);
		__fpurge(stdin);

		if(speed <= 3 && 1 <= speed)
			break;
		else
		{
			printf("please, put a number between 1 and 3 (enter any key to continue)");
			while(!kbhit())
			{}
			getchar();
			__fpurge(stdin);
		}
	}

	switch(speed)
	{
	case 1:
		time = 1000000;
		break;
	case 2:
		time = 500000;
		break;
	case 3:
		time = 333333;
		break;
	default:
		break;
	}

	return time;
}

int ledColor()
{
	int number;
	int color;
	while(1)
	{
		system("clear");
		printf("***** LED Color *****\n1. RED\n2. YELLOW\n3. GREEN\n4. BLUE\n(number) : ");
		scanf("%d", &number);
		__fpurge(stdin);

		if(number <= 4 && 1 <= number)
			break;
		else
		{
			printf("please, put a number between 1 and 4 (enter any key to continue)");
			while(!kbhit())
			{}
			getchar();
			__fpurge(stdin);
		}
	}

	switch(number)
	{
	case 1:
		color = 91;
		break;
	case 2:
		color = 93;
		break;
	case 3:
		color = 92;
		break;
	case 4:
		color = 94;
		break;
	default:
		break;
	}

	return color;
}




