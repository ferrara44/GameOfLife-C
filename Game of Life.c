#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <unistd.h>

//Conway's Game of Life, C implementation by Facundo Ferrara github.com/ferrara44
int turn;
int life;
int fertility;
char world1[70][20];
char world2[70][20];
char menu;

void seed(){ //Sets the seed for the world based on the chosen fertility level
	for (int j=0;j<20;j++){
		for(int i=0;i<70;i++){
			life=(rand()%10);
			if (life<fertility) world1[i][j]='o';
			else world1[i][j]=' ';
		}
	}
}

void printWorld1(){
		for (int j=0;j<20;j++){
			for(int i=0;i<70;i++){
				printf("%c", world1[i][j]);
				if (i==69) printf("\n");
			}
		}

}

void printWorld2(){
	for (int j=0;j<20;j++){
		for(int i=0;i<70;i++){
			printf("%c", world2[i][j]);
			if (i==69) printf("\n");
		}
	}
	
}

void evaluar(int a,int b,int c){ //checks how many living neighbors this tile has in world1, and determines the outcome as per the rules of the game.
	int alive=a;
	int neighbors=0;
	if (world1	[b-1]	[c]		=='o') neighbors++;
	if (world1	[b+1]	[c]		=='o') neighbors++;
	if (world1	[b-1]	[c+1]	=='o') neighbors++;
	if (world1	[b]		[c+1]	=='o') neighbors++;
	if (world1	[b+1]	[c+1]	=='o') neighbors++;
	if (world1	[b-1]	[c-1]	=='o') neighbors++;
	if (world1	[b]		[c-1]	=='o') neighbors++;
	if (world1	[b+1]	[c-1]	=='o') neighbors++;
	
	if 		(alive==1 && neighbors<2) world2[b][c]=' '; /*dies of loneliness*/
	else if (alive==1 && neighbors>3) world2[b][c]=' '; /*overpopulation*/
	else if (alive==1 && (neighbors==2 || neighbors==3)) world2[b][c]='o'; /*stable*/
	else if (alive==0 && neighbors==3) world2[b][c]='o'; /*birth*/
	else world2[b][c]=' '; /*barren*/
}



void evaluar2(int a,int b,int c){ //checks how many living neighbors this tile has in world2, and determines the outcome as per the rules of the game.
	int alive=a;
	int neighbors=0;
	if (world2	[b-1]	[c]		=='o') neighbors++;
	if (world2	[b+1]	[c]		=='o') neighbors++;
	if (world2	[b-1]	[c+1]	=='o') neighbors++;
	if (world2	[b]		[c+1]	=='o') neighbors++;
	if (world2	[b+1]	[c+1]	=='o') neighbors++;
	if (world2	[b-1]	[c-1]	=='o') neighbors++;
	if (world2	[b]		[c-1]	=='o') neighbors++;
	if (world2	[b+1]	[c-1]	=='o') neighbors++;
	
	if 		(alive==1 && neighbors<2) world1[b][c]=' '; 
	else if (alive==1 && neighbors>3) world1[b][c]=' '; 
	else if (alive==1 && (neighbors==2 || neighbors==3)) world1[b][c]='o'; 
	else if (alive==0 && neighbors==3) world1[b][c]='o';
	else world1[b][c]=' ';
}

void step1(){
	int alive;
	
	for (int j=0;j<20;j++){
		for (int i=0;i<70;i++){
			if (world1[i][j]=='o'){
				alive=1;
			}
			else alive=0;
			evaluar(alive,i,j);
		}
	}
	}
	
void step2(){
	int alive;
	
	for (int j=0;j<20;j++){
		for (int i=0;i<70;i++){
			if (world2[i][j]=='o'){
				alive=1;
			}
			else alive=0;
			evaluar2(alive,i,j);
		}
	}
}

int main(){
	srand(time(NULL));
	
	printf("Conway's Game of Life");
	printf("Select a starting fertility level from 1 to 10:\n");
	do{
	scanf("%d",&fertility);
	
	if (fertility <1 || fertility > 10) printf("\n Please set a starting fertility in ranges 1 to 10.\n");}while (fertility<1||fertility>10);
	
	seed();
	printWorld1();
	
	printf("\n\n Generated World.\n");
	printf("\n\n Type 'Y' to play this world.\n Type 'S' to perform a step \n Type any other value to exit.\n");
	
	scanf("\n%c",&menu);
	
	do{switch (menu){
	case ('Y'): case ('y'):
		for(int turno=0;turno<150;turno++){
		if (turn==0){
			system("cls");
			printWorld1();
			step1();
			Sleep(50);
			system("cls");
			printWorld2();
			step2();
			Sleep(50);
		}
		else if (turn==1){
			system("cls");
			printWorld1();
			step2();
			Sleep(50);
			turn=0;
		}
		
		}
		break;
		
	case ('S'): case ('s'):
		if(turn==0){
			system("cls");
			printWorld1();
			step1();
			Sleep(50);
			turn=1;
		}
		else if(turn==1){
			system("cls");
			printWorld2();
			step2();
			Sleep(50);
			turn=0;
		}
		break;
	}
	printf("\n\n Type 'Y' to play this world.\n Type 'S' to perform a step \n Type any other value to exit.\n");
	
	scanf("\n%c",&menu);
	}while (menu=='S' || menu=='s' || menu=='Y' || menu=='y');
}
