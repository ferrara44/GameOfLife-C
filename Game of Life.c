#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#ifdef WINDOWS
#include <windows.h>
#endif
#include <unistd.h>

#define ROWS 20
#define COLS 70

#ifdef WINDOWS
	#define SLEEP Sleep(100)
	#define CLS system("cls")
#else
	#define SLEEP usleep(100000)
	#define CLS printf("\033[%dA", ROWS)
#endif

//Conway's Game of Life, C implementation by Facundo Ferrara github.com/ferrara44
int turn;
int life;
int fertility;
char world1[COLS][ROWS];
char world2[COLS][ROWS];
char menu;

void seed(){ //Sets the seed for the world based on the chosen fertility level
	for (int j=0;j<ROWS;j++){
		for(int i=0;i<COLS;i++){
			life=(rand()%10);
			if (life<fertility) world1[i][j]='o';
			else world1[i][j]=' ';
		}
	}
}

void printWorld(char world[COLS][ROWS]){
		for (int j = 0; j < ROWS; j++){
			for(int i = 0 ;i < COLS; i++){
				printf("%c", world[i][j]);
			}
			printf("\n");
		}
}

void evaluar(int b, int c, char world_a[COLS][ROWS], char world_b[COLS][ROWS]){ //checks how many living neighbors this tile has in world1, and determines the outcome as per the rules of the game.
	int neighbors = 0;
	int alive = (world_a[b][c] == 'o');
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (i == j) {
				continue;
			}
			neighbors += (world_a[b + i][c + j] == 'o');
		}
	}
	
	if (neighbors == 3 || (alive && (neighbors == 2))) {
		world_b[b][c] = 'o';
	} else {
		world_b[b][c] = ' ';
	}
}

void step(char world_a[COLS][ROWS], char world_b[COLS][ROWS]){
	for (int j = 0; j < ROWS; j++){
		for (int i = 0; i < COLS; i++){
			evaluar(i, j, world_a, world_b);
		}
	}
}

int main(){
	srand(time(NULL));
	fertility = 0;
	
	printf("Conway's Game of Life");
	printf("Select a starting fertility level from 1 to 10:\n");
	char buffer[100] = "";
	do{
		fgets(buffer, sizeof(buffer), stdin);
		if (sscanf(buffer, "%d", &fertility) != 1) {
			fertility = 0;
		}
		if (fertility >= 1 && fertility <= 10) {
			break;
		}
		printf("Please set a starting fertility in ranges 1 to 10.\n");
	} while (true);
	
	seed();
	printWorld(world1);
	
	printf("\n\n Generated World.\n");
	printf("\n\n Type 'Y' to play this world.\n Type 'S' to perform a step \n Type any other value to exit.\n");
	
	scanf("\n%c", &menu);
	printf("\033[2J\033[H");
	
	do{
	switch (menu){
	case ('Y'): case ('y'):
		for(int turno = 0; turno < 150; turno++) {
			CLS;
			printWorld(world1);
			if (turn == 0){
				step(world1, world2);
				SLEEP;
				CLS;
				printWorld(world2);
				step(world2, world1);
			} else if (turn == 1){
				step(world2, world1);
				turn = 0;
			}
			SLEEP;
		}
		break;
		
	case ('S'): case ('s'):
		CLS;
		if(turn == 0){
			printWorld(world1);
			step(world1, world2);
			turn = 1;
		}
		else if(turn == 1){
			printWorld(world2);
			step(world2, world1);
			turn = 0;
		}
		SLEEP;
		break;
	}
	printf("\n\n Type 'Y' to play this world.\n Type 'S' to perform a step \n Type any other value to exit.\n\033[6A");
	
	scanf("\n%c", &menu);
	} while (menu =='S' || menu =='s' || menu =='Y' || menu == 'y');

	printf("\033[6B");
}
