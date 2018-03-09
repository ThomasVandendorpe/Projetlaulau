#include "ia.h"
#include "board.h"
#include <stdlib.h>

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
int checkEmpty1(Board b,int num,int numOfrow)
{
  if(numOfrow==(b.height-1) && b.tab[numOfrow][num]=='\0'){return 1;}
  else if(b.tab[numOfrow+1][num]!='\0' && b.tab[numOfrow][num]=='\0'){return 1;}//TODO: ERREUR DE SEGEMENTATION CF.VALGRIND
  return 0;
}
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
