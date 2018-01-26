#include "score.h"

int horizontalScore(char **board, char character){
  int u, v;
  int score1=0;
  for(u=0;u<height;u++)
    {
      for(v=0;v<(width-3);v++)
        {
	  if(board[u][v] == character && board[u][v+1] == character && board[u][v+2] == character && board[u][v+3] == character){
	    score1++;
	  }
        }
    }
  return score1;
}
int verticalScore(char **board, char character){
  int u, v;
  int score1=0;
  for(v=0;v<width;v++)
    {
      for(u=0;u<(height-3);u++)
        {
	  if(board[u][v] == character && board[u+1][v] == character && board[u+2][v] == character && board[u+3][v] == character){
	    score1++;
	  }
        }
    }
  return score1;
}
int diagonal(char **board, char character){
  int u, v;
  int score1=0;
  for(u=(height-1);u>=3;u--)
    {
      for(v=0;v<(width-3);v++)
        {
	  if(board[u][v] == character && board[u-1][v+1] == character && board[u-2][v+2] == character && board[u-3][v+3] == character){
	    score1++;
	  }
        }
    }
  return score1;
}
int diagonal1(char **board, char character){
  int u, v;
  int score1=0;
  for(u=(height-1);u>=3;u--)
    {
      for(v=(width-1);v>=3;v--)
        {
	  if(board[u][v] == character && board[u-1][v-1] == character && board[u-2][v-2] == character && board[u-3][v-3] == character){
	    score1++;
	  }
        }
    }
  return score1;
}