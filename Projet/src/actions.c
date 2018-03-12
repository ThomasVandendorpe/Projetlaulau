#include <stdio.h>
#include "actions.h"
#include "board.h"
#include "score.h"
#include "ia.h"
#include "assert.h"

int play_ia(Board* board,int difficulty){
  switch(difficulty)
    {
    case 1:{
      int res=-1;
      res = Easy(*board);
      assert(res!=-1);
      board_put(board,res);
      break;
    }
    case 2: {
      int res=-1;
      res = Medium(*board,SYM_PLAYER_1);
      if(res==-1) res = Easy(*board);
      assert(res!=-1);
      board_put(board,res);
      break;
    }
    case 3:{
      int res=-1;
      res = Hard(*board);
      assert(res!=-1);
      board_put(board,res);
      break;
    }
    }
  return 0;
}

int play_player(Board* board,int currentPlayer,int mode){
  int num;
  board_print(*board);
  printf("\nif you want to undo, press 0\n");
  printf("if you want to redo, press -3, to load, press -1, to save, press -2\n");
  printf("\nplayer %d enter number of the column:",currentPlayer);
  num=-100;
  scanf("%d",&num);
  while(!checknum(num,*board)){
    getc(stdin);
    board_print(*board);
    printf("\nPlease enter a number between 1 and %d :", board->width);
    scanf("%d",&num);
  }
  switch(num){
  case -1:
  case -2:
    saveLoad(&num,*board);
    break;
  case -3:
    board_redo(board,mode);
    break;
  case 0:
    if(board_undo(board,mode)==-1)
      printf("\ncannot undo! play again");
    break;
  default:
    {
      if (!board_colIsFull(*board,num)){
	board_put(board,num);
	return 1;
      }
      else{
	printf("Invalid input. Do another move : ");
      }
	  
      break;
    }
  }
  return 0;
}


void player(Board board, int num, char character)
{
	int i;
	for(i=(board.height-1); i>=0;i--)
	{
		if(num>0 && board.tab[i][num-1]==VIDE)
		{
			board.tab[i][num-1] = character;
			break;
		}
	}
	board_print(board);
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
		board.tab[undoRow[(*q-1)]][undoCol[(*q-1)]] = VIDE;
		board_print(board);
		*q-=1;
		*z-=1;
	}
	else if(num == -3){
		dcounter += 1;
		if((dcounter <= ccounter)){
			board.tab[redoRow[*z]][redoCol[*z]] = *x;
			board_print(board);
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
		board_print(board);
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

