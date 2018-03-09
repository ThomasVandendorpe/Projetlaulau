#ifndef _ACTIONS_H_
#define _ACTIONS_H_

#include "board.h"

/*
Joue un coup sur la colonne num avec le symbole character
 */
void player(Board board, int num, char character);

void undoRedo(char *x, Board board, int num, int *undoCol,
	int *undoRow, int *k, int *l, int *z,
	int *redoCol, int *redoRow, int *q);

/*
??
 */
void undoRedoLimit(int num, int *undoCounter, int *redoCounter);

/*
retourne 1 si player a jouer un coup dans le board, 0 sinon
 */
int play_player(Board* board,int currentPlayer,char symPlayer,int mode);

int play_ia(Board* board,char sym,int difficulty);


#endif
