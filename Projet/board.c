#include "board.h"

Board board_new(int width,int height,int highScores){
	Board b;
	int i;
	b.tab = (char **)malloc(height*sizeof(char *));
	b.width = width;
	b.height = height;
	b.highScores = highScores;
	for(i=0; i<height; i++)
	{
		board[i] = (char*)malloc(width*sizeof(char));
		for(j=0; j<width; j++)
		{
			board[i][j]= VIDE;
		}
	}
	return b;
}


void board_print(Board board)
{
	int i, j;
	for(i=0; i<board.height; i++)
	{
		printf("\n+");
		for(j=0; j<board.board.width; j++)
		{
			printf("---+");
		}
		printf("\n|");
		for(j=0; j<board.width; j++)
		{
			if(board.tab[i][j]!=VIDE){
				printf(" %c |", board.tab[i][j]);
			}
			else{
				printf("   |");
			}
		}
	}
	printf("\n+");
	for(i=0; i<board.width; i++)
	{
		printf("---+");
	}
	printf("\n");
	for(i=1;i<=board.width;i++){
		printf("   %d",i);
	}
	printf("\n\n\n");
}

int checknum(int num, Board board)
{
	while((num<-3) || (num>board.width))
	{
		print(board);
		printf("\nPlease enter a number between 1 and %d :", board.width);
		scanf("%d", &num);
	}
	return num;
}
int checkfull(Board board)
{
	int i, j;
	for(i=0; i<height; i++)
	{
		for(j=0; j<board.width; j++)
		{
			if(board[i][j] == '\0')
			{
				return 1;
			}
		}

	}
	return 0;
}

int rowNum(int num, Board board){
	int i=0;
	for(i=0;i<board.height;i++){
		if(num == 0){return 0;}
    if(board[i][num-1]!='\0'){break;}//TODO \0 -> VIDE ??
}
return i-1;
}
int checkEmpty(Board board){
	int n, m;
	for(n=0;n<board.height;n++){
		for(m=0;m<board.width;m++){
      if(board[n][m] != '\0'){return 0;}//TODO \0 -> VIDE ??
  }
}
return 1;
}
int checkCol(int num, Board board){
	int i, counter=0;
	for(i=board.height-1;i>=0;i--){
		if(board[i][num-1] == '\0'){
			counter = 0;
			break;
		}
		else{
			counter = 1;
		}
	}
	return counter;
}