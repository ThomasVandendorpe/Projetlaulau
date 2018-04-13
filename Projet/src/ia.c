#include "ia.h"
#include "board.h"
#include <stdlib.h>

/**
* \file    ia.c
* \brief   Gestion de l'IA
*/

/**
*\brief    IA mode facile
*\detail   renvoit le numéro de colonne que l'ia va jouer, en l'occurence, un nombre aléatoire
*\param    b la grille de jeu
*\return   -1 si erreur, le numero de la colonne sinon
*/
int Easy(Board b)
{
  int i, j, flag, l;
  l = rand() % b.width;
  for(i=(b.height-1); i>=0; i--)
    {
      if(b.tab[i][l]=='\0')
        {
	  return l+1;
        }
      flag = 0;
      while(i==0 && b.tab[i][l]!='\0')
        {
	  l = rand() % b.width;
	  flag = 1;
        }
      for(j=(b.height-1); flag==1; j--)
        {
	  if(b.tab[j][l]=='\0')
            {
	      return l+1;
            }
        }
    }
  return -1;
}

/**
*\brief    check si vide
*\detail   Indique si la case à la ligne numOfrow et colonne num sera la prochaine case remplie par l'insertion d'un charactère dans le board
*\param    b la grille de jeu
*\param    num la collone
*\param    num0frow la ligne
*\return   1 si la case à la ligne numOfrow et colonne num sera la prochaine case remplie par l'insertion d'un charactère dans le board, 0 sinon
*/
int checkEmpty1(Board b,int num,int numOfrow)
{
  assert(num>=0 && num<b.width);
  assert(numOfrow>=0 && numOfrow<b.height);
  if(numOfrow==(b.height-1) && b.tab[numOfrow][num]==VIDE){return 1;}
  else if(numOfrow+1<b.height && b.tab[numOfrow+1][num]!=VIDE && b.tab[numOfrow][num]==VIDE){return 1;}
  return 0;
}

/**
*\brief    IA mode moyen
*\detail   Indique le numéro de colonne à jouer pour empécher une suite de 4 caractères identiques à la suite (sur ligne,colonne, ou diagonale)
*\param    b la grille de jeu
*\param    character les caractères dont il faut empécher la suite
*\return   Le numéro de colonne à jouer pour empécher une suite de 4 caractères identiques à la suite (sur ligne,colonne, ou diagonale)
*/
int Medium(Board b, char character/*, int *num*/)
{
  int i, j;
  for(i=b.height-1; i>=3; i--)
    {
      for(j=0; j<b.width; j++)
        {
	  if(b.tab[i][j] == character && b.tab[i-1][j] == character && b.tab[i-2][j] == character && b.tab[i-3][j]=='\0')
            {
	      return j+1;
	      /*b.tab[i-3][j] = 'O';
	      *num = j+1;
	      return 1;*/
            }
        }
    }
  for(i=0;i<b.height;i++)
    {
      for(j=0;j<(b.width-3);j++)
        {
	  if(b.tab[i][j] == character && b.tab[i][j+1] == character && b.tab[i][j+2] == character && checkEmpty1(b,j+3,i)){
	    return j+4;
	    /* b.tab[i][j+3] = 'O';
	    *num = j+3+1;
	    return 1;*/
	  }
	  if(b.tab[i][j+1] == character && b.tab[i][j+2] == character && b.tab[i][j+3] == character && checkEmpty1(b,j,i)){
	    return j+1;
	    /*b.tab[i][j] = 'O';
	    *num = j+1;
	    return 1;*/
	  }
	  if(b.tab[i][j] == character && b.tab[i][j+2] == character && b.tab[i][j+3] == character && checkEmpty1(b,j+1,i)){
	    return j+2;
	    /* b.tab[i][j+1] = 'O';
	    *num = j+1+1;
	    return 1;*/
	  }
	  if(b.tab[i][j] == character && b.tab[i][j+1] == character && b.tab[i][j+3] == character && checkEmpty1(b,j+2,i)){
	    return j+3;
	    /*b.tab[i][j+2] = 'O';
	    *num = j+2+1;
	    return 1;*/
	  }
        }
    }
  for(i=b.height-1; i>=3; i--)
    {
      for(j=0;j<(b.width-3);j++)
        {
	  if(b.tab[i][j] == character && b.tab[i-1][j+1] == character && b.tab[i-2][j+2] == character && checkEmpty1(b,j+3,i-3)){
	    return j+4;
	    /*b.tab[i-3][j+3] = 'O';
	    *num = j+3+1;
	    return 1;*/
	  }
	  if(b.tab[i-1][j+1] == character && b.tab[i-2][j+2] == character && b.tab[i-3][j+3] == character && checkEmpty1(b,j,i)){
	    return j+1;
	    /* b.tab[i][j] = 'O';
	    *num = j+1;
	    return 1;*/
	  }
	  if(b.tab[i][j] == character && b.tab[i-2][j+2] == character && b.tab[i-3][j+3] == character && checkEmpty1(b,j+1,i-1)){
	    return j+2;
	    /* b.tab[i-1][j+1] = 'O';
	    *num = j+1+1;
	    return 1;*/
	  }
	  if(b.tab[i][j] == character && b.tab[i-1][j+1] == character && b.tab[i-3][j+3] == character && checkEmpty1(b,j+2,i-2)){
	    return j+3;
	    /* b.tab[i-2][j+2] = 'O';
	    *num = j+2+1;
	    return 1;*/
	  }
        }
    }
  for(i=b.height-1; i>=3; i--)
    {
      for(j=b.width-1; j>=3; j--)
        {
	  if(b.tab[i][j] == character && b.tab[i-1][j-1] == character && b.tab[i-2][j-2] == character && checkEmpty1(b,j-3,i-3)){
	    return j-2;
	    /*b.tab[i-3][j-3] = 'O';
	    *num = j-3+1;
	    return 1;*/
	  }
	  if(b.tab[i-1][j-1] == character && b.tab[i-2][j-2] == character && b.tab[i-3][j-3] == character && checkEmpty1(b,j,i)){
	    return j+1;
	    /*b.tab[i][j] = 'O';
	    *num = j+1;
	    return 1;*/
	  }
	  if(b.tab[i][j] == character && b.tab[i-2][j-2] == character && b.tab[i-3][j-3] == character && checkEmpty1(b,j-1,i-1)){
	    return j;
	    /*b.tab[i-1][j-1] = 'O';
	    *num = j-1+1;
	    return 1;*/
	  }
	  if(b.tab[i][j] == character && b.tab[i-1][j-1] == character && b.tab[i-3][j-3] == character && checkEmpty1(b,j-2,i-2)){
	    return j-1;
	    /*b.tab[i-2][j-2] = 'O';
	    *num = j-2+1;
	    return 1;*/
	  }
        }
    }
  return -1;
}

/**
*\brief    IA mode moyen
*\detail   revoit le numéro de colonne que l'ia va jouer, en fonction des disponibilitées
*\param    b la grille de jeu
*\return   e numero de la colonne sinon, ou Easy en dernier recourt
*/
int Hard(Board b/*, int *num*/)
{
  int i, j;
  char x='X',o='O';
  
  /*
  if(Medium(b,x,num)==1)return;
  if(Medium(b,o,num)==1)return;
  */
  int r;
  r=Medium(b,SYM_PLAYER_1);
  if (r!=-1) return r;
  r=Medium(b,SYM_PLAYER_2);
  if (r!=-1) return r;
  
  for(i=b.height-1; i>=2; i--)
    {
      for(j=0; j<b.width; j++)
        {

	  if(b.tab[i][j] == 'O' && b.tab[i-1][j] == 'O' && b.tab[i-2][j]=='\0')
            {
	      return j+1;
	      /*b.tab[i-2][j] = 'O';
	      *num = j+1;
	      return;
	      */
            }
        }
    }
  for(i=0;i<b.height;i++)
    {
      for(j=0;j<(b.width-2);j++)
        {
	  if(b.tab[i][j] == 'O' && b.tab[i][j+1] == 'O' && checkEmpty1(b,j+2,i)){
	    return j+3;
	    /*b.tab[i][j+2] = 'O';
	    *num = j+2+1;
	    return;
	    */
	  }
	  if(b.tab[i][j+1] == 'O' && b.tab[i][j+2] == 'O' && checkEmpty1(b,j,i)){
	    return j+1;
	    /*b.tab[i][j] = 'O';
	    *num = j+1;
	    return;*/
	  }
        }
    }
  for(i=b.height-1; i>=2; i--)
    {
      for(j=0;j<(b.width-2);j++)
        {
	  if(b.tab[i][j] == 'O' && b.tab[i-1][j+1] == 'O' && checkEmpty1(b,j+2,i-2)){
	    return j+3;
	    /*b.tab[i-2][j+2] = 'O';
	    *num = j+2+1;
	    return;*/
	  }
	  if(b.tab[i-1][j+1] == 'O' && b.tab[i-2][j+2] == 'O' && checkEmpty1(b,j,i)){
	    return j+1;
	    /*b.tab[i][j] = 'O';
	    *num = j+1;
	    return;*/
	  }
        }
    }
  for(i=b.height-1; i>=2; i--)
    {
      for(j=b.width-1; j>=2; j--)
        {
	  if(b.tab[i][j] == 'O' && b.tab[i-1][j-1] == 'O' && checkEmpty1(b,j-2,i-2)){
	    return j-1;
	    /*b.tab[i-2][j-2] = 'O';
	    *num = j-2+1;
	    return;*/
	  }
	  if(b.tab[i-1][j-1] == 'O' && b.tab[i-2][j-2] == 'O' && checkEmpty1(b,j,i)){
	    return j+1;
	    /*b.tab[i][j] = 'O';
	    *num = j+1;
	    return;*/
	  }
        }
    }
  return Easy(b);
}
