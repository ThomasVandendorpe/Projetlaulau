#ifndef _BOARD_H_
#define _BOARD_H_

#define VIDE '\0'

#define SYM_PLAYER_1 'X'
#define SYM_PLAYER_2 'O'

typedef struct Board {
  char** tab;
  int width;
  int height;
  int highScores;
  char* last;//derniers coups joués
  int n_last;//nombre de coups joués
  int undoRedoIndex;
} Board;

/*
Renvoie un nouveau boardu de largeur width et de hauteur height
 */
Board board_new(int width,int height,int highScores);

/*
Libère un board
 */
void board_free(Board board);

/*
Affiche un board
 */
void board_print(Board board);

/*
Renvoie 0 si le board est plein, 1 sinon
 */
int checkfull(Board board);

/*
Renvoie le nombre de 'O' dans le board
 */
int numO(Board board);

/*
Renvoie le nombre de 'X' dans le board
 */
int numX(Board board);

/*
Renvoie 1 si la colonne num du board est pleine, sinon 0
 */
int checkCol(int num, Board board);

/*
Renvoie le symbole de joueur courant
 */
char board_currentPlayerSymbole(Board b);

/*
Insere le symbol du joueur courant dans le board à la colonne col (numéroté de 1 à board.width)
Met à jour le système undo/redo
Renvoie le numero de la ligne (de 0 à board.height-1) si succès, sinon -1
 */
int board_put(Board* board,int col);


/*renvoie 1 si le colonne col est pleine, sinon 0*/
int board_colIsFull(Board board,int col);

/*
Effectue n undo
Renvoie la dernière colonne undo si réussi, sinon -1
 */
int board_undo(Board* board,int n);

/*
Effectue n redo
Renvoie la dernière colonne redo si réussi, sinon -1
 */
int board_redo(Board* board,int n);

/*
Renvoie la dernière colonne jouée num de 0 à board.width-1
 */
int board_lastPlayCol(Board board);

/*
Renvoie la dernière ligne jouée num de 0 à board.height-1
 */
int board_lastPlayRow(Board board);


int checknum(int num, Board board);


int rowNum(int num, Board board);

int checkEmpty(Board board);

void XMLformating(char* filename,int* w,int* h,int* hs);

void saveLoad(int num, Board board);

void highscore(int high,Board board);

#endif
