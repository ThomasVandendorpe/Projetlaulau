#include "actions.h"

void player(Board board, int num, char character)
{
	int i;
	for(i=(board.height-1); i>=0;i--)
	{
		if(board[i][num-1]==VIDE)
		{
			board[i][num-1] = character;
			break;
		}
	}
	print(board);
}

void undoRedo(char *x, Board board, int num, int *undoCol,
	int *undoRow, int *k, int *l, int *z,
	int *redoCol, int *redoRow, int *q){
	static int ccounter = 0, dcounter = 0;
	if(num != 0 && !checkCol(num, board) && num != -3 && !(num<-3) && !(num>board.width) && !(num == -2)){
		undoCol[*q] = num-1;
		*k = rowNum(num, board);
		undoRow[*q] = *k;
	}
	if(num != 0 && !checkCol(num, board) && num != -3 && !(num<-3) && !(num>board.width) && !(num == -2)){
		redoCol[*z] = num-1;
		*l = rowNum(num, board);
		redoRow[*z] = *l;
		*z+=1;
	}
	if(num == 0){
		ccounter +=1;
		board[undoRow[(*q-1)]][undoCol[(*q-1)]] = VIDE;
		print(board);
		*q-=1;
		*z-=1;
	}
	else if(num == -3){
		dcounter += 1;
		if((dcounter <= ccounter)){
			board[redoRow[*z]][redoCol[*z]] = *x;
			print(board);
			*q+=1;
			undoCol[*q] = redoCol[*z+1];
			undoRow[*q] = redoRow[*z+1];
			*z+=1;
		}
	}
	else if(num == -1){
		printf("Game Loaded Successfully");
	}
	else if(num == -2){
		printf("Game saved Successfully");
		print(board);
	}
	else{
		*q+=1;
		player(board,num,*x);
		ccounter = 0;
		dcounter = 0;
	}
}

void undoRedoLimit(int num, int *undoCounter, int *redoCounter){
	if(num == 0){
		*undoCounter += 1;
	}
	else if(num == -3){
		*redoCounter += 1;
	}
	else{
		*undoCounter = 0;
		*redoCounter = 0;
	}
}

int numX(Board board){
	int i, j, counter=0;
	for(i=board.height-1;i>=0;i--){
		for(j=board.width-1;j>=0;j--){
			if(board[i][j] == 'X'){;
				counter+=1;
			}
		}
	}
	return counter;
}
int numO(Board board){
	int i, j, counter=0;
	for(i=board.height-1;i>=0;i--){
		for(j=board.width-1;j>=0;j--){
			if(board[i][j] == 'O'){;
				counter+=1;
			}
		}
	}
	return counter;
}