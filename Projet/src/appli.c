#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "board.h"
#include "actions.h"
#include "score.h"
#include "ia.h"

int main(int argc,char* argv[])
{
  int width,height,highScores;
  int high=0;
  if(argc<2){
    fprintf(stderr,"Il faut un nom de fichier en argument.\n");
    exit(1);
  }
  XMLformating(argv[1],&width,&height,&highScores);
  char playAgain;
  do{
    Board board = board_new(width,height,highScores);
    //initialisation tableaux
    int flag, score1=0, score2=0, *compUndoCol, undoCounter=0,
      redoCounter=0, compUndoCounter =0, choose;
    int i, num=0, *undoCol, k, *undoRow,
      *redoCol, *redoRow, l, *compUndoRow;
    static int q=0, z=0, d=0, c=0;
    char x='X', o='O';

    undoCol = (int *)malloc(height*width*sizeof(int));
    for(i=0;i<height*width;i++){
      undoCol[i] = 0;
    }
    redoCol = (int *)malloc(height*width*sizeof(int));
    for(i=0;i<height*width;i++){
      redoCol[i] = 0;
    }
    undoRow = (int *)malloc(height*width*sizeof(int));
    for(i=0;i<height*width;i++){
      undoRow[i] = 0;
    }
    redoRow = (int *)malloc(height*width*sizeof(int));
    for(i=0;i<height*width;i++){
      redoRow[i] = 0;
    }
    compUndoCol = (int *)malloc(height*width*sizeof(int));
    for(i=0;i<height*width;i++){
      compUndoCol[i] = 0;
    }
    compUndoRow = (int *)malloc(height*width*sizeof(int));
    for(i=0;i<height*width;i++){
      compUndoRow[i] = 0;
    }


    //lancement du jeu
    printf("\n\n                     **** WELCOME TO THE GAME ****\n\n");
    printf("Player1 vs Player2: press 1 \n\nPlayer vs Computer: press 2 \n\n");
    scanf("%d", &choose);
    while((choose!=1 && choose!=2) || isalpha(choose))
      {
	printf("Enter 1 or 2\n");
	printf("Player1 vs Player2: press 1 \n\nPlayer vs Computer: press 2 \n\n");
	scanf("%d", &choose);
      }//TODO: boucle infinie
    if(choose == 1){
      board_print(board);
      do{
	printf("\nif you want to undo, press 0\n");
	printf("if you want to redo, press -3, to load, press -1, to save, press -2\n");
	if(numX(board) <= numO(board)){
	  printf("\nplayer 1 enter number of the column:");
	  scanf("%d", &num);
	  saveLoad(&num, board);
	  num = checknum(num,board);
	  if(checkCol(num,board)){
	    while(board.tab[0][num-1]!=VIDE)
	      {
		board_print(board);
		printf("Invalid input. Do another move : ");
		scanf("%d", &num);
		saveLoad(&num, board);
		if(num == 0 || num == -3){
		  break;
		}
	      }
	  }
	  if(redoCounter >= undoCounter){
	    while(num == -3){
	      board_print(board);
	      printf("\ncannot redo!! play again");
	      scanf("%d", &num);
	      saveLoad(&num, board);
	      if(num == 0){
		break;
	      }
	    }
	  }
	  while(num == 0 && checkEmpty(board)){
	    board_print(board);
	    printf("\ncannot undo! play again");
	    scanf("%d", &num);
	    saveLoad(&num, board);
	    if(num == -3){
	      if(redoCounter >= undoCounter){
		while(num == -3){
		  board_print(board);
		  printf("\ncannot redo!! play again");
		  scanf("%d", &num);
		  if(num == 0){
		    break;
		  }
		}
	      }
	    }
	  }
	  undoRedoLimit(num,&undoCounter,&redoCounter);
	  undoRedo(&x,board,num,undoCol,undoRow,&k,&l,&z,redoCol,redoRow,&q);
	  score1=horizontalScore(board,x)+verticalScore(board,x)+diagonal(board,x)+diagonal1(board,x);
	  printf("\n***************************************************");
	  printf("\n***************************************************");
	  printf("\n**                      **                       **");
	  printf("\n** player1 score : %d    **   player2 score  : %d  **", score1, score2);
	  printf("\n**                      **                       **");
	  printf("\n***************************************************");
	  printf("\n***************************************************");
	}
	printf("\nif you want to undo, press 0\n");
	printf("if you want to redo, press -3, to load, press -1, to save, press -2\n");
	if(numO(board) < numX(board)){
	  printf("\nplayer 2 enter number of the column:");
	  scanf("%d", &num);
	  saveLoad(&num, board);
	  num = checknum(num,board);
	  if(checkCol(num,board)){
	    while(board.tab[0][num-1]!=VIDE)
	      {
		board_print(board);
		printf("Invalid input. Do another move : ");
		scanf("%d", &num);
		saveLoad(&num, board);
		if(num == 0 || num == -3){
		  break;
		}
	      }
	  }
	  if(redoCounter >= undoCounter){
	    while(num == -3){
	      board_print(board);
	      printf("\ncannot redo!! play again");
	      scanf("%d", &num);
	      saveLoad(&num, board);
	      if(num == 0){
		break;
	      }
	    }
	  }
	  while(num == 0 && checkEmpty(board)){
	    board_print(board);
	    printf("\ncannot undo! play again");
	    scanf("%d", &num);
	    saveLoad(&num, board);
	    if(num == -3){
	      if(redoCounter >= undoCounter){
		while(num == -3){
		  board_print(board);
		  printf("\ncannot redo!! play again");
		  scanf("%d", &num);
		  saveLoad(&num, board);
		  if(num == 0){break;}
		}
	      }
	    }
	  }
	  undoRedoLimit(num,&undoCounter,&redoCounter);
	  undoRedo(&o,board,num,undoCol,undoRow,&k,&l,&z,redoCol,redoRow,&q);
	  score2=horizontalScore(board,o)+verticalScore(board,o)+diagonal(board,o)+diagonal1(board,o);
	  printf("\n***************************************************");
	  printf("\n***************************************************");
	  printf("\n**                      **                       **");
	  printf("\n** player1 score : %d    **   player2 score  : %d  **", score1, score2);
	  printf("\n**                      **                       **");
	  printf("\n***************************************************");
	  printf("\n***************************************************");
	}
      }while(checkfull(board));

      if(score2>score1){
	high=score2;
	printf("\nPLAYER 2 WINS");
      }
      else if(score1==score2){
	high=score1;
	printf("\nDRAW");
      }
      else{
	high=score1;
	printf("\nPLAYER 1 WINS");
      }
    }
    else
      {
      	printf("\nEasy (press 1), Medium (press 2), Hard (press 3)\n");
      	scanf("%d", &choose);
      	while(choose!=1 && choose!=2 && choose!=3)
	  {
	    printf("Enter 1 , 2 or 3\n");
	    printf("\nEasy (press 1), Medium (press 2), Hard (press 3)\n");
	    scanf("%d", &choose);
	  }
      	board_print(board);
      	do{
	  printf("\nif you want to undo, press 0\n");
	  printf("if you want to redo, press -3, to load, press -1, to save, press -2\n");
	  printf("\nenter number of the column:");
	  scanf("%d", &num);
	  saveLoad(&num, board);
	  num = checknum(num,board);
	  if(checkCol(num,board)){
	    while(board.tab[0][num-1]!=VIDE)
	      {
		board_print(board);
		printf("Invalid input. Do another move : ");
		scanf("%d", &num);
		saveLoad(&num, board);
		if(num == 0 || num == -3){
		  break;
		}
	      }
	  }
	  if(redoCounter >= compUndoCounter){
	    while(num == -3){
	      board_print(board);
	      printf("\ncannot redo!! play again");
	      scanf("%d", &num);
	      saveLoad(&num, board);
	      if(num == 0){
		break;
	      }
	    }
	  }
	  while(num == 0 && checkEmpty(board)){
	    board_print(board);
	    printf("\ncannot undo! play again");
	    scanf("%d", &num);
	    saveLoad(&num, board);
	    if(num == -3){
	      if(redoCounter >= compUndoCounter){
		while(num == -3){
		  board_print(board);
		  printf("\ncannot redo!! play again");
		  scanf("%d", &num);
		  saveLoad(&num, board);
		  if(num == 0){
		    break;
		  }
		}
	      }
	    }
	  }
	  undoRedoLimit(num,&undoCounter,&redoCounter);
	  undoRedo(&x,board,num,undoCol,undoRow,&k,&l,&z,redoCol,redoRow,&q);
	  score1=horizontalScore(board,x)+verticalScore(board,x)+diagonal(board,x)+diagonal1(board,x);
	  printf("\n***************************************************");
	  printf("\n***************************************************");
	  printf("\n**                      **                       **");
	  printf("\n**   User  score : %d    **  Computer score  : %d  **", score1, score2);
	  printf("\n**                      **                       **");
	  printf("\n***************************************************");
	  printf("\n***************************************************");
	  switch(choose)
	    {
	    case 1:{
	      if(num != 0 && num != -1 && num != -2){
		Easy(board, &num);
		compUndoCol[d++] = num-1 ;
		compUndoRow[c++] = rowNum(num,board)+1;
		compUndoCounter = 0;
	      }
	      if(num == 0){
		compUndoCounter += 1;
		c--;
		d--;
		board.tab[compUndoRow[c]][compUndoCol[d]] = VIDE;
	      }
	      break;
	    }
	    case 2: {
	      if(num != 0 && num != -1 && num != -2){
		flag=0;
		if(Medium(board,x,&num)==1){flag=1;}
		if(flag!=1){Easy(board, &num);}
		compUndoCol[d++] = num-1 ;
		compUndoRow[c++] = rowNum(num,board)+1;
		compUndoCounter = 0;
	      }
	      if(num == 0){
		compUndoCounter += 1;
		c--;
		d--;
		board.tab[compUndoRow[c]][compUndoCol[d]] = VIDE;
	      }
	      break;
	    }
	    case 3:{
	      if(num != 0 && num != -1 && num != -2){
		Hard(board,&num);
		compUndoCol[d++] = num-1 ;
		compUndoRow[c++] = rowNum(num,board)+1;
		compUndoCounter = 0;
	      }
	      if(num == 0){
		compUndoCounter += 1;
		c--;
		d--;
		board.tab[compUndoRow[c]][compUndoCol[d]] = VIDE;
	      }
	      break;
	    }
	    }
	  board_print(board);
	  score2=horizontalScore(board,o)+verticalScore(board,o)+diagonal(board,o)+diagonal1(board,o);
	  printf("\n***************************************************");
	  printf("\n***************************************************");
	  printf("\n**                      **                       **");
	  printf("\n**   User  score : %d    **  Computer score  : %d  **", score1, score2);
	  printf("\n**                      **                       **");
	  printf("\n***************************************************");
	  printf("\n***************************************************");
      	}while(checkfull(board));
      	if(score2>score1){
	  high=score2;
	  printf("\nComputer WINS\n");
      	}
      	else if(score1==score2){
	  high=score1;
	  printf("\nDRAW\n");
      	}
      	else{
	  high=score1;
	  printf("\nUser WINS\n");
      	}
      }
    highscore(high,board);
    printf("\nif you you want to play again press y, else press any key\n");
    board_free(board);
    scanf("\n%c",&playAgain);
  }while(playAgain == 'y');
  return 0;
}









