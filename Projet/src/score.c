#include <stdio.h>
#include "score.h"
#include "board.h"

/**
* \file    score.c
* \brief   Gestion des scores de la partie en cours
*/

/**
*\brief    compte les points horizontaux
*\param    board la table de jeu
*\param    character le symbol du joueur
*\return   le score
*/
int horizontalScore(Board board, char character){
  int u, v, j;
  int score1=0;
  v = board_lastPlayCol(board);
  // for(u=0;u<board.height && board.tab[u][v]==VIDE ;u++);
  u=board_lastPlayRow(board);
  if(u==-1 || v==-1) return 0;
  for(j=v-3;j<=v;j++){
    if(j>=0 && j+3<board.width && board.tab[u][j] == character && board.tab[u][j+1] == character && board.tab[u][j+2] == character && board.tab[u][j+3] == character){
      score1++;
    }
  }
  return score1;
}

/**
*\brief    compte les points verticaux
*\param    board la table de jeu
*\param    character le symbol du joueur
*\return   le score
*/
int verticalScore(Board board, char character){
  int u, v, i;
  int score1=0;
  v = board_lastPlayCol(board);
  //for(u=0;u<board.height && board.tab[u][v]==VIDE ;u++);
  u=board_lastPlayRow(board);
  if(u==-1 || v==-1) return 0;
  for(i=u-3;i<=u;i++)
    {
      if(i>=0 && i+3<board.height && board.tab[i][v] == character && board.tab[i+1][v] == character && board.tab[i+2][v] == character && board.tab[i+3][v] == character){
	score1++;
      }
    }
  return score1;
}


/**
*\brief    compte les points diagonaux (haut gauche vers bas droite)
*\param    board la table de jeu
*\param    character le symbol du joueur
*\return   le score
*/
int diagonal(Board board, char character){
  int u, v, a;
  int score1=0;
  v = board_lastPlayCol(board);
  //for(u=0;u<board.height && board.tab[u][v]==VIDE ;u++);
  u=board_lastPlayRow(board);
  if(u==-1 || v==-1) return 0;
  for(a=-3;a<=0;a++)
    {
	if(v+a>=0 && v+a+3<board.width && u+a>=0 && u+a+3<board.height && board.tab[u+a][v+a] == character && board.tab[u+a+1][v+a+1] == character && board.tab[u+a+2][v+a+2] == character && board.tab[u+a+3][v+a+3] == character){
	  score1++;
	}
    }
  return score1;
}

/**
*\brief    compte les points diagonaux (bas gauche vers haut droite)
*\param    board la table de jeu
*\param    character le symbol du joueur
*\return   le score
*/
int diagonal1(Board board, char character){
  int u, v, a;
  int score1=0;
  v = board_lastPlayCol(board);
  //  for(u=0;u<board.height && board.tab[u][v]==VIDE ;u++);
  u=board_lastPlayRow(board);
  if(u==-1 || v==-1) return 0;
  for(a=-3;a<=0;a++)
    {
	if(v+a>=0 && v+a+3<board.width && u-a<board.height && u-a-3>=0 && board.tab[u-a][v+a] == character && board.tab[u-a-1][v+a+1] == character && board.tab[u-a-2][v+a+2] == character && board.tab[u-a-3][v+a+3] == character){
	  score1++;
	}
    }
  return score1;
}


/**
 *\brief    Affiche les scores
 *\param    scores[] les scores des joueurs
 */
void print_scores(int scores[2]){
  printf("\n***************************************************");
  printf("\n***************************************************");
  printf("\n**                      **                       **");
  printf("\n** player1 score : %d    **   player2 score  : %d  **", scores[0], scores[1]);
  printf("\n**                      **                       **");
  printf("\n***************************************************");
  printf("\n***************************************************");
}
