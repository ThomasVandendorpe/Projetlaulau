#ifndef _ACTIONS_H_
#define _ACTIONS_H_
void player(Board board, int num, char character);

void undoRedo(char *x, Board board, int num, int *undoCol,
	int *undoRow, int *k, int *l, int *z,
	int *redoCol, int *redoRow, int *q);

void undoRedoLimit(int num, int *undoCounter, int *redoCounter);

int numX(Board board);
int numO(Board board);

#endif