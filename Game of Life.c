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

//Conway's Game of Life, C implementation. github.com/ferrara44
int life;
int fertility;
char world1[COLS][ROWS];
char world2[COLS][ROWS];
char menu;

void seed(){ //Generates the world based on the selected fertility level
	for (int j=0;j<ROWS;j++){
		for(int i=0;i<COLS;i++){
			life=(rand()%10);
			if (life<fertility) world1[i][j]='o';
			else world1[i][j]=' ';
		}
	}
}

void printWorld(char world[COLS][ROWS]){ //Prints the next world on screen
		for (int j = 0; j < ROWS; j++){
			for(int i = 0 ;i < COLS; i++){
				printf("%c", world[i][j]);
			}
			printf("\n");
		}
}

void evaluate(int b, int c, char world_a[COLS][ROWS], char world_b[COLS][ROWS]){ //checks how many living neighbors this tilr currently has, and determines the outcome as per the rules of the game.
	int neighbors = 0;
	// These nested for loops iterate through the nine squares around the current cell, where X is the current cell.
	// ----------------------------------------------
	// |(b - 1, c - 1)|(b + 0, c - 1)|(b + 1, c - 1)|
	// ----------------------------------------------
	// |(b - 1, c + 0)|(b + 0, c + 0)|(b + 1, c + 0)|
	// ----------------------------------------------
	// |(b - 1, c + 1)|(b + 0, c + 1)|(b + 1, c + 1)|
	// ----------------------------------------------
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			// This line was originally incorrect, my bad. I had i == j, which skips the diagonal.
			if ((i == 0 && j == 0)				// If we're looking at the current cell

				|| b + i >= COLS				// or the cell we're looking at is outside of the world
				|| b + i < 0
				|| c + j >= ROWS
				|| c + j < 0) 
			{
				continue;						// Skip it
			}

			// If the cell is alive, (world_a[b + i][c + j] == 'o') will return 1,
			// otherwise the expression will return 0.
			// You could also write it as
			// if (world_a[b + i][c + j] == 'o') neighbors++;
			if (world_a[b + i][c + j] == 'o') neighbors++;
		}
	}

	// I'm going to do some Boolean logic to show that this is equivalent to
	// the rules of Game of Life

	// Let x = three neighbors, y = two neighbors, z = alive, and !z = dead.	(definition of variables and not alive == dead)
	// The rules are therefore a cell is alive if and only if
	// (three neighbors and dead) or (alive and (two or three neighbors))		(definition of the rules of Game of Life)
	// (x && !z) || (z && (x || y))												(just rewrote it using variables)
	// == (x && !z) || (x && z) || (y && z)										(distributive property of and/or)
	// == (x && (!z || z)) || (y && z)											(distributive property of and/or)
	// == x || (y && z)															(!z || z) == true and x && true == x
	// == three neighbors || (two neighbors && alive)
	if (neighbors == 3 || (neighbors == 2 && world_a[b][c] == 'o')) {
		world_b[b][c] = 'o';
	} else {
		world_b[b][c] = ' ';
	}
}

void step(char world_a[COLS][ROWS], char world_b[COLS][ROWS]){
	for (int j = 0; j < ROWS; j++){
		for (int i = 0; i < COLS; i++){
			evaluate(i, j, world_a, world_b);
		}
	}
}

int main(){
	srand(time(NULL));
	fertility = 0;
	
	printf("Conway's Game of Life");
	printf("Select a starting fertility level from 1 to 10:\n");
	char buffer[100] = "";
	for(;;){
		fgets(buffer, sizeof(buffer), stdin);
		if (sscanf(buffer, "%d", &fertility) != 1) {
			fertility = 0;
		}
		if (fertility >= 1 && fertility <= 10) {
			break;
		}
		printf("Please set a starting fertility in ranges 1 to 10.\n");
	}
	
	seed();
	printWorld(world1);
	
	printf("\n\n Generated World.\n");
	printf("\n\n Type 'Y' to play this world.\n Type 'S' to perform a step \n Type any other value to exit.\n");
	
	scanf("\n%c", &menu);
	printf("\033[2J\033[H");

	int turn = 0;
	
	do{
	switch (menu){
	case ('Y'): case ('y'):
		for(turn = 0; turn < 150; turn++) {
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
