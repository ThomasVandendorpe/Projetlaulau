#include <stdio.h>
#include "actions.h"
#include "board.h"
#include "score.h"
#include "ia.h"
#include "assert.h"

/**
* \file    actions.c
* \brief   Gestion du mode de jeu : JcJ ou JvIA
*/

/**
 * \brief      L'IA joue un jeton celon la difficultée
 * \param      board une table de jeu
 * \param      difficulty difficulté de l'IA
 * \return     0
 */
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

/**
 * \brief      Le joueur fait une action
 * \detail     Propose au joueur de sauvegarder / charger / retourner en arriere / ou jouer un jeton
 * \param      board une table de jeu
 * \param      currentPlayer joueur courant
 * \param      mode undo redo
 * \return     return 1 si le joueur a jouer (+ joue le coup dans le board)
               0 s'il veut undo
	       -1 ou -2 s'il veut  save ou load
	       -3 s'il veut redo
	       -4 si l'entrée n'était pas valide (colonne pleine)
 */
int play_player(Board* board,int currentPlayer,int mode){
  int num;
  board_print(*board);
  printf("\nif you want to undo, press 0\n");
  printf("if you want to redo, press -3, to load, press -1, to save, press -2\n");
  printf("\nplayer %d enter number of the column:",currentPlayer);
  num=-100;
  scanf("%d",&num);
  char ch;
  while(!checknum(num,*board)){
    while((ch = getchar()) != '\n' && ch!=EOF);
    board_print(*board);
    printf("\nPlease enter a number between 1 and %d :", board->width);
    scanf("%d",&num);
  }
  assert(num>=-3 && num<=board->width);
  if(num<=0){
    return num;
  }
  if (!board_colIsFull(*board,num)){
    board_put(board,num);
    return 1;
  }
  else{
    printf("Invalid input. Do another move : ");
  }
  return -4;
  
}

