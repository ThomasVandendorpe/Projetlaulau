#include <stdio.h>
#include "score.h"
#include "board.h"

int horizontalScore(Board board, char character){
  int u, v, j;
  int score1=0;
  v = board_lastPlayCol(board);
  // for(u=0;u<board.height && board.tab[u][v]==VIDE ;u++);
  u=board_lastPlayRow(board);
  for(j=v-3;j<=v;j++){
    if(j>=0 && j+3<board.width && board.tab[u][j] == character && board.tab[u][j+1] == character && board.tab[u][j+2] == character && board.tab[u][j+3] == character){
      score1++;
    }
  }
  return score1;
}
int verticalScore(Board board, char character){
  int u, v, i;
  int score1=0;
  v = board_lastPlayCol(board);
  //for(u=0;u<board.height && board.tab[u][v]==VIDE ;u++);
  u=board_lastPlayRow(board);
  for(i=u-3;i<=u;i++)
    {
      if(i>=0 && i+3<board.height && board.tab[i][v] == character && board.tab[i+1][v] == character && board.tab[i+2][v] == character && board.tab[i+3][v] == character){
	score1++;
      }
    }
  return score1;
}

/*
\v
 */
int diagonal(Board board, char character){
  int u, v, a;
  int score1=0;
  v = board_lastPlayCol(board);
  //for(u=0;u<board.height && board.tab[u][v]==VIDE ;u++);
  u=board_lastPlayRow(board);
  for(a=-3;a<=0;a++)
    {
	if(v+a>=0 && v+a+3<board.width && u+a>=0 && u+a+3<board.height && board.tab[u+a][v+a] == character && board.tab[u+a+1][v+a+1] == character && board.tab[u+a+2][v+a+2] == character && board.tab[u+a+3][v+a+3] == character){
	  score1++;
	}
    }
  return score1;
}

/*
/^
 */
int diagonal1(Board board, char character){
  int u, v, a;
  int score1=0;
  v = board_lastPlayCol(board);
  //  for(u=0;u<board.height && board.tab[u][v]==VIDE ;u++);
  u=board_lastPlayRow(board);
  for(a=-3;a<=0;a++)
    {
	if(v+a>=0 && v+a+3<board.width && u-a<board.height && u-a-3>=0 && board.tab[u-a][v+a] == character && board.tab[u-a-1][v+a+1] == character && board.tab[u-a-2][v+a+2] == character && board.tab[u-a-3][v+a+3] == character){
	  score1++;
	}
    }
  return score1;
}

void print_scores(int scores[2]){
  printf("\n***************************************************");
  printf("\n***************************************************");
  printf("\n**                      **                       **");
  printf("\n** player1 score : %d    **   player2 score  : %d  **", scores[0], scores[1]);
  printf("\n**                      **                       **");
  printf("\n***************************************************");
  printf("\n***************************************************");
}
