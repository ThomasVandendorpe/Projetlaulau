#ifndef _BOARD_H_
#define _BOARD_H_

#define VIDE '\0'

typedef struct Board {
	char** tab;
	int width;
	int height;
	int highScores;
} Board;

Board board_new(int width,int height,int highScores);

void board_free(Board b);

void board_print(Board board);

int checknum(int num, Board board);

int checkfull(Board board);

int rowNum(int num, Board board);

int checkEmpty(Board board);

int checkCol(int num, Board board);

void XMLformating(char* filename,int* w,int* h,int* hs);

void saveLoad(int *num, Board board);

void highscore(int high,Board board);

#endif
