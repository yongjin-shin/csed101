#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int row;
	int col;
	char dir;
}POSITION;

typedef struct {
	int row;
	int col;
}POSITION_F;

void print_map(FILE* outfile, char** map, int map_row, int map_col);
void position_cal(char** map, int map_row, int map_col, POSITION_F* flowers, int flower_num, POSITION* wolves, int wolf_num, int sh_row, int sh_col);
int check_final(int life, int sh_row, int sh_col, int map_row, int map_col, int score, int* comm);
void move_sheep(char comm, int* sh_row, int* sh_col, int map_row, int map_col);
void move_flower(int flower_num, int sh_col, int sh_row, int map_col, int map_row, POSITION_F* flowers, char** map, int* score);
void move_wolf(int wolf_num, POSITION* wolves, int flower_num, POSITION_F* flowers, int map_col, int map_row, int sh_col, int sh_row, int* life);


int main()
{
	FILE* infile;
	FILE* outfile;
	POSITION* wolves;
	POSITION_F* flowers;
	char ch[10], outfile_name[11], infile_name[11], comm;
	char** map;
	int i, j, wolf_num = 0, flower_num = 0, map_row = 0, map_col = 0, life = 5, sh_row = 0, sh_col = 0, score, final_result;

	printf("Input the out file name: ");
	scanf("%s", outfile_name);	//get the name of out file ex)out1.txt
	getchar();

	printf("Input the map file name: ");
	scanf("%s", infile_name);	//get the name of in file ex)map3.txt
	getchar();

	infile = fopen(infile_name, "r");	//open the input file with read mode
	if (infile == NULL) {
		printf("Could not open %s file\n", infile_name);
		return(200);
	}

	outfile = fopen(outfile_name, "a");	//oepn the output file with the append mode
	if (outfile == NULL)
		return(200);

	while (fscanf(infile, "%s", ch) != EOF) {
		if (strcmp(ch, "#MAP") == 0) {	//compare the string with #map
			fscanf(infile, "%d %d", &map_row, &map_col);	//if it is '#map', then collect the info of the size of map 
			map = (char**)calloc(map_row, sizeof(char*));
			for (i = 0; i < map_row; i++)
				*(map + i) = (char*)calloc(map_col, sizeof(char));
		}

		else if (strcmp(ch, "#WOLF") == 0) {	//if it is '#wolf'
			fscanf(infile, "%d", &wolf_num);	//then collect the # of wolf
			wolves = (POSITION*)calloc(wolf_num, sizeof(POSITION));	//and set the dynamic allocation for wolves
			for (i = 0; i < wolf_num; i++)
				fscanf(infile, "%d %d %c", &(wolves[i].row), &(wolves[i].col), &(wolves[i].dir));	//collect the info of the location of wolves
		}

		else if (strcmp(ch, "#FLOWER") == 0) {	//if it is '#flower'
			fscanf(infile, "%d", &flower_num);	//then collect the # of flower
			score = flower_num;		//score will be shown on the display as the remaining number of flowers
			flowers = (POSITION_F*)calloc(flower_num, sizeof(POSITION_F));	//set the dynamic allocation for flowers
			for (i = 0; i < flower_num; i++)
				fscanf(infile, "%d %d", &(flowers[i].row), &(flowers[i].col));	//collect the info of the location of flowers
		}
	}

	do { 
		position_cal(map, map_row, map_col, flowers, flower_num, wolves, wolf_num, sh_row, sh_col);		//update the map based on the location of each players
		system("cls");		//delete the previous display
		printf("LIFE:\t%d\n", life);
		printf("FLOWER:\t%d\n", score);
		print_map(outfile, map, map_row, map_col);		//print the new map by the information of position_cal funtion
		final_result=check_final(life, sh_row, sh_col, map_row, map_col, score, &comm);		//checking whether it is time to end the game or not

		if (final_result == 0 || final_result == 1)		//if the resut shows the proper situation to end
			break;										//then break the infinite roop

		move_sheep(comm, &sh_row, &sh_col, map_row, map_col);		//move the location of sheep by the input from the prompt user			
		move_flower(flower_num, sh_col, sh_row, map_col, map_row, flowers, map, &score);		//decide the existence of flowers
		move_wolf(wolf_num, wolves, flower_num, flowers, map_col, map_row, sh_col, sh_row, &life);		//decide the existence of wolves
	} while (1);

	free(wolves);
	free(flowers);
	for (int i = 0; i < map_row; i++) {
		free(*(map + i));
	}
	free(map);

	fclose(outfile);
	fclose(infile);

	return 0;
}

void print_map(FILE* outfile, char** map, int map_row, int map_col) {
	int i, j;
	for (i = 0; i < map_row; i++) {
		for (j = 0; j < map_col; j++) {
			printf("%c ", map[i][j]);
			fprintf(outfile, "%c ", map[i][j]);
		}
		printf("\n");
		fprintf(outfile, "\n");
	}
	fprintf(outfile, "\n");
}

void position_cal(char** map, int map_row, int map_col, POSITION_F* flowers, int flower_num, POSITION* wolves, int wolf_num, int sh_row, int sh_col) {
	int i,j;

	for (i = 0; i < map_row; i++)
		for (j = 0; j < map_col; j++)
			map[i][j] = '.';		//print map with '.' at first

	for (i = 0; i < flower_num; i++) {		
		if ( flowers[i].row >= map_row )
			map[flowers[i].row - map_row][flowers[i].col - map_col] = '.';		//if the location of flowers is out the map, then print that location with '.'
		else
			map[flowers[i].row][flowers[i].col] = '*';		//otherwise, print the flower as '*'
	}

	for (i = 0; i < wolf_num; i++) {		
		if (wolves[i].dir == 'L')		
			map[wolves[i].row][wolves[i].col] = '<';
		else if (wolves[i].dir == 'R')
			map[wolves[i].row][wolves[i].col] = '>';
		else if (wolves[i].dir == 'D')		//if the direction of wolves is 'D' as dead, then
			map[wolves[i].row][wolves[i].col] = '.';		//print the location of that place as '.'
	}

	map[sh_row][sh_col] = '@';		//at the last step, print the location of sheep
}

int check_final(int life, int sh_row, int sh_col, int map_row, int map_col, int score, int* comm) {

	if (life == 0) {
		printf("You are dead\n");
		return 0;
	}
	else if (sh_row == map_row - 1 && sh_col == map_col - 1 && score == 0) {
		printf("Congratulation! You made it!!\n");
		return 1;
	}
	else {
		printf("Input the command: ");
		scanf(" %c", comm);		//get the user input
		return 2;
	}
}

void move_sheep(char comm, int* sh_row, int* sh_col, int map_row, int map_col) {

	switch (comm) {		//with the user input
	case 'w':
		if (0 < *sh_row)		//if the sheep is under the line
			*sh_row = *sh_row-1;	
		break;
	case 's':
		if (*sh_row < map_row - 1)		//if the sheep is above the line
			*sh_row = *sh_row+1;
		break;
	case 'a':
		if (0 < *sh_col)		//if the sheep is inside the map
			*sh_col = *sh_col-1;
		break;
	case 'd':
		if (*sh_col < map_col - 1)
			*sh_col = *sh_col+1;
		break;
	default:
		break;
	}
}

void move_flower(int flower_num, int sh_col, int sh_row, int map_col, int map_row, POSITION_F* flowers, char** map, int* score) {
	int i;

	for (i = 0; i < flower_num; i++)
		if (sh_col == flowers[i].col && sh_row == flowers[i].row && map[flowers[i].row][flowers[i].col] != '.') {		//if the location of sheep is same with the flower which is printed only '.'
			flowers[i].col = map_col + i, flowers[i].row = map_row + i;		//put that flower outside of the map
			*score = *score-1;		//and minus one out of the score
		}
}

void move_wolf(int wolf_num, POSITION* wolves, int flower_num, POSITION_F* flowers, int map_col, int map_row, int sh_col, int sh_row, int* life) {
	int i, j;

	for (i = 0; i < wolf_num; i++) {
		if (wolves[i].dir == 'L') {		//for the case of L direction of wolf
			if (0 < wolves[i].col) {	//when the wolf is insde of the map
				wolves[i].col--;		//move left
				for (j = 0; j < flower_num; j++) {
					if (wolves[i].col == flowers[j].col && wolves[i].row == flowers[j].row) {	//if the wolf faces into the flower
						wolves[i].col++;		//then go back the previous location and 
						wolves[i].dir = 'R';	//change the direction
					}
				}
			}
			else {
				wolves[i].col += (map_col - 1);		//if the wolfe is on the lsft side of edge, then move it on the right side of edge
				for (j = 0; j < flower_num; j++) {	
					if (wolves[i].col == flowers[j].col && wolves[i].row == flowers[j].row) {	//when the wolf faces into the flower
						wolves[i].col = 0;
						wolves[i].dir = 'R';
					}
				}
			}
		}
		else if (wolves[i].dir == 'R') {		//for the case of R direction of wolf
			if (wolves[i].col < map_col - 1) {
				wolves[i].col++;
				for (j = 0; j < flower_num; j++) {
					if (wolves[i].col == flowers[j].col && wolves[i].row == flowers[j].row) {
						wolves[i].col--;
						wolves[i].dir = 'L';
					}
				}
			}
			else {
				wolves[i].col = 0;
				for (j = 0; j < flower_num; j++) {
					if (wolves[i].col == flowers[j].col && wolves[i].row == flowers[j].row) {
						wolves[i].col = map_col - 1;
						wolves[i].dir = 'L';
					}
				}
			}
		}
	}

	for (i = 0; i < wolf_num; i++)
		if (sh_col == wolves[i].col && sh_row == wolves[i].row && (wolves[i].dir == 'L' || wolves[i].dir == 'R')) {		//only the case of 'L' and 'R' direction of wolf facing the sheep
			wolves[i].dir = 'D';	//change the direction of wolf as 'D' which means dead
			*life = *life-1;		//and minus one out of the life
		}
}
