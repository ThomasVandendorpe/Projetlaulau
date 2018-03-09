#include <stdio.h>
#include "score.h"
#include "board.h"

int horizontalScore(Board board, char character){
  int u, v;
  int score1=0;
  for(u=0;u<board.height;u++)
    {
      for(v=0;v<(board.width-3);v++)
        {
	  if(board.tab[u][v] == character && board.tab[u][v+1] == character && board.tab[u][v+2] == character && board.tab[u][v+3] == character){
	    score1++;
	  }
        }
    }
  return score1;
}
int verticalScore(Board board, char character){
  int u, v;
  int score1=0;
  for(v=0;v<board.width;v++)
    {
      for(u=0;u<(board.height-3);u++)
        {
	  if(board.tab[u][v] == character && board.tab[u+1][v] == character && board.tab[u+2][v] == character && board.tab[u+3][v] == character){
	    score1++;
	  }
        }
    }
  return score1;
}
int diagonal(Board board, char character){
  int u, v;
  int score1=0;
  for(u=(board.height-1);u>=3;u--)
    {
      for(v=0;v<(board.width-3);v++)
        {
	  if(board.tab[u][v] == character && board.tab[u-1][v+1] == character && board.tab[u-2][v+2] == character && board.tab[u-3][v+3] == character){
	    score1++;
	  }
        }
    }
  return score1;
}
int diagonal1(Board board, char character){
  int u, v;
  int score1=0;
  for(u=(board.height-1);u>=3;u--)
    {
      for(v=(board.width-1);v>=3;v--)
        {
	  if(board.tab[u][v] == character && board.tab[u-1][v-1] == character && board.tab[u-2][v-2] == character && board.tab[u-3][v-3] == character){
	    score1++;
	  }
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
