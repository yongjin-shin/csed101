#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include"keyboard.h"

void moveLEDleft(char led[][220], char col[][1], int len, int time, int color)
{
	int i, j;
	printf("\033[%dm", color);//to print the characters with using the color which user input
	
		for(i=0; i<20; i++)//75X20 LED print
		{
			for(j=0; j<75; j++)
				printf("%c", led[i][j]);
			printf("\n");
		}
	
		usleep(time);//to delay for the time user want
		system("clear");// to clear the display

	while(1)
	{
		while(!kbhit())//to check the keyboard hit
		{
		if(len<7)//the case which length is under 7 as the display shows only 6.8 characters
			for(i=0; i<20; i++)
			{
				for(j=0; j<=75; j++)
					if(j == 0)
						led[i][75] = led[i][j];//copy the first column information to the last column
					else
						led[i][j-1] = led[i][j];
			}

		else//the case which length is over 7
			for(i=0; i<20; i++)
			{
				for(j=0; j<len*11; j++)
				{
					if(j == 0)
						col[i][j] = led[i][j];//copy the first colum into the col arrary temporalily
					else
						led[i][j-1] = led[i][j];
				}
				led[i][len*11-1] = col[i][0];
			}

		for(i=0; i<20; i++)//print the led array
		{
			for(j=0; j<75; j++)
				printf("%c", led[i][j]);
			printf("\n");
		}
	
		usleep(time);
		system("clear");
		}

		if(getchar()=='q')//if the input key is 'q', the program is terminated
		{
			printf("\033[0m");//color of led go back to normal as black
			break;
		}
	}
}

void moveLEDright(char led[][220], char col[][1], int len, int time, int color)
{
	int i, j;
	printf("\033[%dm", color);
	
	do
	{
	while(!kbhit())
	{
		for(i=0; i<20; i++)
		{
			for(j=0; j<75; j++)
				printf("%c", led[i][j]);
			printf("\n");
		}
	
		usleep(time);
		system("clear");

		if(len<7)
			for(i=0; i<20; i++)
			{
				for(j=74; 0<=j; j--)
				{
					if(j == 74)
						col[i][0] = led[i][j];
					else
						led[i][j+1] = led[i][j];
				}
				led[i][0] = col[i][0];
			}

		else
			for(i=0; i<20; i++)
			{
				for(j=len*11-1; 0<=j; j--)
				{
					if(j == len*11-1)
						col[i][0] = led[i][j];
					else
						led[i][j+1] = led[i][j];
				}
				led[i][0] = col[i][0];
			}
	}

	if(getchar() == 'q')
	{
		printf("\033[0m");
		break;
	}
	
	}while(1);
}

void moveLEDup(char led[][220], int time, int color)
{

	int i, j;
	printf("\033[%dm", color);
	
	do
	{		
	while(!kbhit())
	{
		for(i=0; i<20; i++)
		{
			for(j=0; j<75; j++)
				printf("%c", led[i][j]);
			printf("\n");
		}
		usleep(time);
		system("clear");
	
		for(i=0; i<21; i++)
		{
			if(i == 0)
				for(j=0; j<220; j++)
					led[20][j] = led[0][j];//the first row of information is copied to the 21st row
			else
				for(j=0; j<220; j++)
					led[i-1][j]=led[i][j];
		}
	}

	if(getchar() == 'q')
	{
	printf("\033[0m");
	break;
	}
	
	}while(1);
}

void moveLEDdown(char led[][220], int time, int color)
{
	int i,j;
	printf("\033[%dm", color);
	
	do
	{
		while(!kbhit())
		{

		for(i=0; i<20; i++)
		{
			for(j=0; j<75; j++)
				printf("%c", led[i][j]);
			printf("\n");
		}
		usleep(time);
		system("clear");

		for(i=19; -1<=i; i--)
		{
			if( 0<=i)
				for(j=0; j<220; j++)
					led[i+1][j]=led[i][j];
			else
				for(j=0; j<220; j++)
					led[0][j] = led[20][j];
		}
		}

		if(getchar() == 'q')
		{
			printf("\033[0m");
			break;
		}
	}while(1);

}

