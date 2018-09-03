#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ledGet.h"
#include "menu.h"
#include "checker.h"
#include "led.h"

int main()
{
	int i, j, k;
	const int stringsize=50;
	int len=0;
	char string[stringsize];
	char led[21][220];//define led array which consists of 21 rows and 220 columns
	char col[21][1];//the array cosists of 21 rows and 1 column for using copy the information when the led characters move right and ledward
	int pattern=0;
	int time=0;
	int color=0;
	
	for(i=0; i<21; i++)//led array is set by ' '
		for(j=0; j<220; j++)
			led[i][j] = ' ';

	for(i=0; i<21; i++)
		col[i][1] = ' ';
	
	system("clear");//clear the display
	textMenu(string, stringsize);//call textMenu function from menu.c
	pattern=patternMenu();//call patterMenu from menu.c
	time=moveSpeed();//call moveSpeed from menu.c
	color=ledColor();//call ledColor from menu.c
	system("clear");//clear the display
	len=inputStringLength(string);//calculate the length of stirng user input
	//printf("length = %d\n", len);length
	ledGet(string, len, led);
	
	switch(pattern)//call the proper move patter function based upon the user input
	{
		case 1:
			moveLEDleft(led, col, len, time, color);
			break;
		case 2:
			moveLEDright(led,col, len, time, color);
			break;
		case 3:
			moveLEDup(led, time, color);
			break;
		case 4:
			moveLEDdown(led, time, color);
			break;
		default:
			break;
	}
		return 0;
}
