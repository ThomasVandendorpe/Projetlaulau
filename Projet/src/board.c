#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include <assert.h>


/**
* \file  board.c
* \brief Gestion de la grille de jeu ainsi que des scores 
*/

/**
 * \brief      Cree une table de jeu
 * \details    initialisation de la grille de jeu ainsi que des scores
 * \param      width         largeure de la grille
 * \param      heigh         longueure de la grille
 * \param      highscores    table des highscores
 * \return     une grille de jeu selon les paramètres donnés
 */
Board board_new(int width,int height,int highScores){
  Board b;
  int i,j;
  b.tab = (char **)malloc(height*sizeof(char *));
  b.width = width;
  b.height = height;
  b.highScores = highScores;
  for(i=0; i<height; i++)
    {
      b.tab[i] = (char*)malloc(width*sizeof(char));
      for(j=0; j<width; j++)
	{
	  b.tab[i][j]= VIDE;
	}
    }
  b.last = malloc(width*height*sizeof(char));
  b.n_last = 0;
  b.undoRedoIndex = 0;
  return b;
}

/**
 * \brief      vide une table de jeu
 * \param      board une table de jeu
 */
void board_free(Board board){
  int i;
  for(i=0; i<board.height; i++)
    {
      free(board.tab[i]);
    }
  free(board.last);
  free(board.tab);
}

/**
 * \brief      affiche la grille
 * \param      board une table de jeu
 */
void board_print(Board board)
{
  int i, j;
  //printf("\033[31m");
  char color[]="\033[34m";
  printf("%s",color);
  for(i=0; i<board.height; i++)
    {
      printf("\n+");
      for(j=0; j<board.width; j++)
	{
	  printf("---+");
	}
      printf("\n|");
      for(j=0; j<board.width; j++)
	{
	  if(board.tab[i][j]!=VIDE){
	    printf("\033[0m");
	    if(board.tab[i][j]==SYM_PLAYER_1)
	      printf("\033[43m");
	    else
	      printf("\033[41m");
	    printf(" %c ", board.tab[i][j]);
	    printf("\033[0m");
	    printf("%s|",color);
	  }
	  else{
	    printf("   |");
	  }
	}
    }
  printf("\n+");
  for(i=0; i<board.width; i++)
    {
      printf("---+");
    }
  printf("\n");
  for(i=1;i<=board.width;i++){
    printf("   %d",i);
  }
  printf("\n\n\n");
  printf("\033[0m");
}

char board_currentPlayerSymbole(Board b){
  if((b.undoRedoIndex&1)==0)
    return SYM_PLAYER_1;
  return SYM_PLAYER_2;
}

/**
 * \brief      ajoute un jeton dans la grille
 * \param      board une table de jeu
 * \param      col la collone où il faut ajouter le jeton
 * \param      symPlayer la couleur / symbole du jeton
 * \return     -1 si il y a une erreur
 */
int board_put(Board* board,int col){
  int i;
  assert(col>0 && col<=board->width);
  for(i=board->height-1;i>=0;i--)
    {
      if(board->tab[i][col-1]==VIDE)
	{
	  board->tab[i][col-1] = board_currentPlayerSymbole(*board);
	  board->last[board->undoRedoIndex]=col-1;
	  board->undoRedoIndex++;
	  board->n_last = board->undoRedoIndex;
	  return i;
	}
    }
  return -1;
}

/**
 * \brief      verifie que la colonne soit pleinne
 * \param      board une table de jeu
 * \param      col la colonne où il faut ajouter le jeton
 * \return     -1 si la colonne n'est pas pleine
 */
int board_colIsFull(Board board,int col){
  assert(col>0 && col <= board.width);
  return board.tab[0][col-1]!=VIDE;
}

/*
  Renvoie la dernière colonne jouée, sinon -1
 */
int board_lastPlayCol(Board board){
  if(board.undoRedoIndex<=0) return -1;
  return board.last[board.undoRedoIndex-1];
}

/*
  Renvoie la dernière ligne jouée, sinon -1
 */
int board_lastPlayRow(Board board){
  int i,j,n;
  int v;
  i=0;
  j=board.height-1;
  if((v = board_lastPlayCol(board))==-1) return -1;
  n = (i+j)/2;
  while(i<j){
    if(board.tab[n][v]!=VIDE){
      if(n==0 || board.tab[n-1][v]==VIDE) return n;
      else {
	j=n-1;
	n=(i+j)/2;
      }
    }
    else{
      i=n+1;
      n=(i+j)/2;
    }
  }
  return i;
}

/**
 * \brief      défait le dernière "board_undo" exécuté
 * \details    remet le dernier jeton supprimé. 
 * \param      board une table de jeu
 * \param      n nombre de undo disponible
 * \return     res
 */
int board_redo(Board* board,int n){
  int i,j,k,res;
  res=-1;
  if(board->undoRedoIndex+n>board->n_last) return -1;
  for(k=0;k<n;k++){
    j = board->last[board->undoRedoIndex];
    for(i=board->height-1;i>=0;i--)
      {
	if(board->tab[i][j]==VIDE)
	  {
	    if(board->undoRedoIndex&1==1)
	      board->tab[i][j]=SYM_PLAYER_2;
	    else
	      board->tab[i][j]=SYM_PLAYER_1;
	    board->undoRedoIndex++;
	    res=i;
	    break;
	  }
      }
  }
  return res;
}

/**
 * \brief      défait le dernière "board_put" exécuté
 * \details    enlève le dernier jeton ajouté. 
 * \param      board une table de jeu
 * \param      n nombre de undo disponible
 * \return     res
 */
int board_undo(Board* board,int n){
  int i,j,k,res;
  res=-1;
  if(board->undoRedoIndex-n<0) return -1;
  for(k=0;k<n;k++){
    j = board->last[board->undoRedoIndex-1];
    for(i=0;i<board->height;i++){
      if(board->tab[i][j]!=VIDE){
	board->tab[i][j]=VIDE;
	board->undoRedoIndex--;
        res=i;
	break;
      }
    }
  }
  return res;
}

/**
 * \brief      verifie que l'action faite par l'utilisateur soit reconnue
 * \details    si le nombre entré est compri entre -3 et la taille max de la largeur du tableau, alors la commande est exécutable
 * \param      num chiffre entré par l'utilisateur
 * \param      board une table de jeu
 * \return     1 si la commande n'est pas reconnue, 0 sinon
 */
int checknum(int num, Board board)
{
  if (num<-3 || num>board.width)
    return 0;
  return 1;
}

/**
 * \brief      verifie que la grille soit pleine
 * \param      board une table de jeu
 * \return     0 si la grille est pleine, 1 sinon
 */
int checkfull(Board board)
{
  int i, j;
  for(i=0; i<board.height; i++)
    {
      for(j=0; j<board.width; j++)
	{
	  if(board.tab[i][j] == '\0')
	    {
	      return 1;
	    }
	}

    }
  return 0;
}


/**
 * \brief      lit un fichier au forma XML qui contient les informations de la partie 
 * \param      filename le nom du fichier
 * \param      w la largeur de la grille
 * \param      h la hauteur de la grille
 * \param      hs le highscore
 */
void XMLformating(char* filename,int* w,int* h,int* hs)
{
  int width,height,highScores;

  char c, c1, c2, c3, c4, c5, c6, c7, widthTag, heightTag, highscoresTag; //correction TP1
  int start=0, End=0, flag1=0, flag2=0, widthflag=0, heightflag=0, highscoresflag=0;
  FILE *file=NULL;
  file = fopen(filename, "r");
  if(file==NULL){
    fprintf(stderr,"Impossible d'ouvrir le fichier %s.\n",filename);
    exit(1);
  }
  fscanf(file,"< Configurations %c", &c);
  if(c=='>'){
    flag1=1;
    start=ftell(file);
  }
  else{
    while(fscanf(file,"%c", &c1)!=EOF){
      fscanf(file,"< Configurations %c", &c2);
      if(c2=='>'){
	flag1=1;
	start=ftell(file);
	break;
      }
    }
  }
  c4='0';
  while(fscanf(file,"%c", &c3)!=EOF){
    fscanf(file,"< / Configurations %c", &c4);
    if(c4=='>'){
      flag2=1;
      End=ftell(file);
      break;
    }
  }
  if(flag1==1 && flag2==1)
    {
      fseek(file,start,SEEK_SET);
      width=0;
      widthTag='0';
      while(fscanf(file,"%c", &c5)!=EOF){
	fscanf(file,"< Width >%d < / Width %c", &width, &widthTag);
	if( (widthTag=='>') && (width>=4) && ftell(file)<End )
	  {
	    widthflag=1;
	    break;
	  }
      }
      fseek(file,start,SEEK_SET);
      height=0;
      heightTag='0';
      while(fscanf(file,"%c", &c6)!=EOF){
	fscanf(file,"< Height >%d < / Height %c", &height, &heightTag);
	if( (heightTag=='>') && (height>=4) && ftell(file)<End ) {
	  heightflag=1;
	  break;
	}
      }
      fseek(file,start,SEEK_SET);
      highscoresTag='0';
      highScores=0;
      while(fscanf(file,"%c", &c7)!=EOF){
	fscanf(file,"< Highscores >%d < / Highscores %c", &highScores, &highscoresTag);
	if( (highscoresTag=='>') && (highScores>=4) && ftell(file)<End ) {highscoresflag=1; break;}
      }
    }
  if(width==0 || widthflag==0){
    width=7;
    printf("Incorrect file format, default value of width (7) is loaded\n");
  }
  if(height==0 || heightflag==0){
    height=6;
    printf("Incorrect file format, default value of height (6) is loaded\n");
  }
  if(highScores==0 || highscoresflag==0){
    highScores=5;
    printf("Incorrect file format, default value of highscore list (5) is loaded\n");
  }
  fclose(file);
  (*w) = width;
  (*h) = height;
  (*hs) = highScores;
}

/**
 * \brief      lit un fichier contenant les highscores et le met à jour celon le score de la partie
 * \param      high le score courant
 * \param      board la grille de jeu
 */
void highscore(int high,Board board)
{
  int i=0, n=0, temp;
  int* highs=malloc(board.highScores*sizeof(int));
  FILE *highsc = NULL;
  highsc = fopen("highscores.text", "r");
  if(highsc!=NULL){
    fscanf(highsc, "%d", &highs[i]);
    do
      {
	i++;
	if(fscanf(highsc, "%d", &n)!=EOF){highs[i]=n;}
	else {break;}
      }while(i<board.highScores);
    while(board.highScores>i){highs[i]=0;i++;}
    i--;
    if(high>highs[i])
      {
	highs[i] = high;
      }
    while(highs[i]>highs[i-1] && i>0)
      {
	temp = highs[i-1];
	highs[i-1] = highs[i];
	highs[i] = temp;
	i--;
      }
    fclose(highsc);
  }
  highsc = fopen("highscores.text", "w");
  printf("\n\t      High Scores\n\t\t*****");
  for(i=0; i<board.highScores; i++)
    {
      fprintf(highsc,"%d ", highs[i]);
      printf("\n\t\t* %d *", highs[i]);
    }
  printf("\n\t\t*****");
  fclose(highsc);
  free(highs);
}

/**
 * \brief      sauvegarde ou enregistre une partie
 * \param      num -2 pour save -1 pour enregistrer
 * \param      board la grille de jeu
 */
void saveLoad(int num, Board* board){
  FILE *pfile;
  int i;
  pfile = NULL;
  if(num == -2){
    printf("Game Saved Successfully");
    pfile = fopen("save.txt", "w");
    for(i=0;i<board->undoRedoIndex;i++){
      fprintf(pfile,"%d ",board->last[i]);
    }
    fclose(pfile);
  }
  if(num == -1){
    pfile = fopen("save.txt", "r");
    if(pfile==NULL){
      fprintf(stderr,"Pas de fichier de sauvegarde.\n");
      return;
    }
    int j;
    for(i=0;i<board->height;i++){
      for(j=0;j<board->width;j++){
	board->tab[i][j] = VIDE;
      }
    }
    board->undoRedoIndex=0;
    board->n_last=0;
    while(fscanf(pfile, "%d", &i)!=EOF){
      board_put(board,i+1);
    }
    
    fclose(pfile);
    board_print(*board);
  }
}
