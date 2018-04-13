#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "board.h"
#include "actions.h"
#include "score.h"
#include "ia.h"


/**
* \file     appli.c
* \brief    Exécution du puissance 4.
*/


/**
 * \brief      exécution d'une partie
 * \param      argc argument qui est le nom du fichier XML contenant les informations de la partie
 * \return     0
 */

int main(int argc,char* argv[])
{
  int width,height,highScores;
  int high=0;
  if(argc<2){
    fprintf(stderr,"Il faut un nom de fichier en argument.\n");
    exit(1);
  }
  XMLformating(argv[1],&width,&height,&highScores);
  char playAgain='n';
  do{
    Board board = board_new(width,height,highScores);
    //initialisation tableaux
    int flag, choose=0;

    //lancement du jeu
    printf("\n\n                     **** WELCOME TO THE GAME ****\n\n");
    printf("Player1 vs Player2: press 1 \n\nPlayer vs Computer: press 2 \n\n");
    scanf("%d", &choose);
    while((choose!=1 && choose!=2))
      {
	while(getc(stdin)!='\n');
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
	symPlayer=board_currentPlayerSymbole(board);
	switch(play_player(&board,currentPlayer,1)){
	case -3://REDO
	  board_redo(&board,1);
	  scores[currentPlayer-1]+=horizontalScore(board,symPlayer)+verticalScore(board,symPlayer)+diagonal(board,symPlayer)+diagonal1(board,symPlayer);

	  break;
	case -2:
	  saveLoad(-2,&board);
	  break;
	case -1://Save Load
	  saveLoad(-1,&board);
	  break;
	case 0://UNDO
	  {
	    int otherPlayer = (currentPlayer)%2;
	    int symOtherPlayer = SYM_PLAYER_1+SYM_PLAYER_2-symPlayer;
	  scores[otherPlayer]-=horizontalScore(board,symOtherPlayer)+verticalScore(board,symOtherPlayer)+diagonal(board,symOtherPlayer)+diagonal1(board,symOtherPlayer);
	  if(board_undo(&board,1)==-1)
	     printf("\ncannot undo! play again");
	  break;
	  }
	case 1://coup valide
	  scores[currentPlayer-1]+=horizontalScore(board,symPlayer)+verticalScore(board,symPlayer)+diagonal(board,symPlayer)+diagonal1(board,symPlayer);
	  print_scores(scores);
	  break;
	default://coup invalide
	  printf("Invalid input. Do another move : ");
	  break;
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
	  symPlayer = board_currentPlayerSymbole(board);
	  if (currentPlayer==1) {
	    switch(play_player(&board,currentPlayer,1)){
	    case -3://REDO
	      board_redo(&board,1);
	      scores[0]+=horizontalScore(board,SYM_PLAYER_1)+verticalScore(board,SYM_PLAYER_1)+diagonal(board,SYM_PLAYER_1)+diagonal1(board,SYM_PLAYER_1);
	      board_redo(&board,1);
	      scores[1]+=horizontalScore(board,SYM_PLAYER_2)+verticalScore(board,SYM_PLAYER_2)+diagonal(board,SYM_PLAYER_2)+diagonal1(board,SYM_PLAYER_2);
	      break;
	    case -2:
	      saveLoad(-2,&board);
	      break;
	    case -1://Save Load
	      saveLoad(-1,&board);
	      break;
	    case 0://UNDO
	      {
		scores[1]-=horizontalScore(board,SYM_PLAYER_2)+verticalScore(board,SYM_PLAYER_2)+diagonal(board,SYM_PLAYER_2)+diagonal1(board,SYM_PLAYER_2);
		board_undo(&board,1);
		scores[0]-=horizontalScore(board,SYM_PLAYER_1)+verticalScore(board,SYM_PLAYER_1)+diagonal(board,SYM_PLAYER_1)+diagonal1(board,SYM_PLAYER_1);
		board_undo(&board,1);
		  /*if(board_undo(&board,1)==-1)
		  printf("\ncannot undo! play again");
		  break;*/
	      }
	    case 1://coup valide
	      scores[currentPlayer-1]+=horizontalScore(board,symPlayer)+verticalScore(board,symPlayer)+diagonal(board,symPlayer)+diagonal1(board,symPlayer);
	      print_scores(scores);
	      break;
	    default://coup invalide
	      printf("Invalid input. Do another move : ");
	      break;
	    }
	    /*if(play_player(&board,currentPlayer,2)){
	      scores[currentPlayer-1]+=horizontalScore(board,symPlayer)+verticalScore(board,symPlayer)+diagonal(board,symPlayer)+diagonal1(board,symPlayer);
	      print_scores(scores);	  
	      }*/
	  }
	  else{
	    board_print(board);
	    play_ia(&board,choose);
	    scores[currentPlayer-1]+=horizontalScore(board,symPlayer)+verticalScore(board,symPlayer)+diagonal(board,symPlayer)+diagonal1(board,symPlayer);
	    print_scores(scores);
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