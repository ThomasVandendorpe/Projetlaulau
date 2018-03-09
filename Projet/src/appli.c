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
    int flag, choose;

    //lancement du jeu
    printf("\n\n                     **** WELCOME TO THE GAME ****\n\n");
    printf("Player1 vs Player2: press 1 \n\nPlayer vs Computer: press 2 \n\n");
    scanf("%d", &choose);
    while((choose!=1 && choose!=2) || isalpha(choose))
      {
	printf("Enter 1 or 2\n");
	printf("Player1 vs Player2: press 1 \n\nPlayer vs Computer: press 2 \n\n");
	scanf("%d", &choose);
      }
    if(choose == 1){//PLAYER VS PLAYER
      int scores[2] = {0,0};
      int currentPlayer;
      char symPlayer;
      do{
	currentPlayer=board.undoRedoIndex%2+1;
	if (currentPlayer==1) symPlayer=SYM_PLAYER_1;
	else symPlayer=SYM_PLAYER_2;
  	if(play_player(&board,currentPlayer,symPlayer,1)){
	  scores[currentPlayer-1]=horizontalScore(board,symPlayer)+verticalScore(board,symPlayer)+diagonal(board,symPlayer)+diagonal1(board,symPlayer);
	  print_scores(scores);	  
	}
      }while(checkfull(board));
      board_print(board);
      print_scores(scores);	  
      if(scores[1]>scores[0]){
	//high=scores[1];
	printf("\nPLAYER 2 WINS");
      }
      else if(scores[0]==scores[1]){
	//high=scores[0];
	printf("\nDRAW");
      }
      else{
	//high=scores[0];
	printf("\nPLAYER 1 WINS");
      }

    }
    else
      {
      	printf("\nEasy (press 1), Medium (press 2), Hard (press 3)\n");
	choose=0;
      	scanf("%d", &choose);
      	while(choose!=1 && choose!=2 && choose!=3)
	  {
	    getc(stdin);
	    printf("Enter 1 , 2 or 3\n");
	    printf("\nEasy (press 1), Medium (press 2), Hard (press 3)\n");
	    scanf("%d", &choose);
	  }

	int scores[2] = {0,0};
	int currentPlayer;
	char symPlayer;
	do{
	  currentPlayer=board.undoRedoIndex%2+1;
	  if (currentPlayer==1) {
	    symPlayer=SYM_PLAYER_1;
	    if(play_player(&board,currentPlayer,symPlayer,2)){
	      scores[currentPlayer-1]=horizontalScore(board,symPlayer)+verticalScore(board,symPlayer)+diagonal(board,symPlayer)+diagonal1(board,symPlayer);
	      print_scores(scores);	  
	    }
	  }
	  else{
	    symPlayer=SYM_PLAYER_2;
	    play_ia(&board,symPlayer,choose);
	    scores[currentPlayer-1]=horizontalScore(board,symPlayer)+verticalScore(board,symPlayer)+diagonal(board,symPlayer)+diagonal1(board,symPlayer);
	  }
	}while(checkfull(board));
	board_print(board);
	print_scores(scores);	  
	if(scores[1]>scores[0]){
	  //high=scores[1];
	  printf("\nComputer WINS");
	}
	else if(scores[0]==scores[1]){
	  //high=scores[0];
	  printf("\nDRAW");
	}
	else{
	  //high=scores[0];
	  printf("\nUser WINS");
	}
      }
    highscore(high,board);
    printf("\nif you you want to play again press y, else press any key\n");
    board_free(board);
    scanf("\n%c",&playAgain);
  }while(playAgain == 'y');
  return 0;
}
