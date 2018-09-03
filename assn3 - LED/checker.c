#include <stdio.h>

int inputStringLength(char string[])
{
	int idx=0;
	while (string[idx] != '\0')
		idx++;//to calculate the length of string

	return idx;
}

int inputStringChecker(char string[], int len)
{
	int idx;
	int check_result=3;

	if (len <= 20)//to check the case which string length is under 20
	{
		for (idx=0; idx < len; idx++)
		{
			if(string[idx] != '\n' && string[idx] != ' ' && string[idx] != '0' && string[idx] != '1' && string[idx] != '2' && string[idx] != '3' && string[idx] != '4' && string[idx] != '5' && string[idx] != '6' && string[idx] != '7' && string[idx] != '8' && string[idx] != '9' && string[idx] != 'a' && string[idx] != 'b' && string[idx] != 'c' && string[idx] != 'd' && string[idx] != 'e' && string[idx] != 'f' && string[idx] != 'g' && string[idx] != 'h' && string[idx] != 'i' && string[idx] != 'j' && string[idx] != 'k' && string[idx] != 'l' && string[idx] != 'm' && string[idx] != 'n' && string[idx] != 'o' && string[idx] != 'p' && string[idx] != 'q' && string[idx] != 'r' && string[idx] != 's' && string[idx] != 't' && string[idx] != 'u' && string[idx] != 'v' && string[idx] != 'w' && string[idx] != 'x' && string[idx] != 'y' && string[idx] != 'z')

				return check_result = 1;//the case which is that user input incorrect string

			else
				continue;//go back to the roop
		}

		return check_result = 2;//the case which is that user input correct string
	}
	else//to check the case which string length is over 20
	{
		for (idx=0; idx < len; idx++)
		{
			if(string[idx] != '\n' && string[idx] != ' ' && string[idx] != '0' && string[idx] != '1' && string[idx] != '2' && string[idx] != '3' && string[idx] != '4' && string[idx] != '5' && string[idx] != '6' && string[idx] != '7' && string[idx] != '8' && string[idx] != '9' && string[idx] != 'a' && string[idx] != 'b' && string[idx] != 'c' && string[idx] != 'd' && string[idx] != 'e' && string[idx] != 'f' && string[idx] != 'g' && string[idx] != 'h' && string[idx] != 'i' && string[idx] != 'j' && string[idx] != 'k' && string[idx] != 'l' && string[idx] != 'm' && string[idx] != 'n' && string[idx] != 'o' && string[idx] != 'p' && string[idx] != 'q' && string[idx] != 'r' && string[idx] != 's' && string[idx] != 't' && string[idx] != 'u' && string[idx] != 'v' && string[idx] != 'w' && string[idx] != 'x' && string[idx] != 'y' && string[idx] != 'z')

				return check_result = -1;//the case which is that user input incorrect string
			else
				continue;//go back to the roop
		}
		return check_result = 0;//the case which is that user input correct string
	}
}


