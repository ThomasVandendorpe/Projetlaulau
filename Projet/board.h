#ifndef _BOARD_H_
#define _BOARD_H_

#define VIDE '\0'

typedef struct Board {
	char** tab;
	int width;
	int height;
	int hightScores;
} Board;

#endif
void board_print(Board board);

int checknum(int num, Board board);

int checkfull(Board board);

int rowNum(int num, Board board);

int checkEmpty(Board board);

int checkCol(int num, Board board);