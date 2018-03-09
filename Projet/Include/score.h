#ifndef _SCORE_H_
#define _SCORE_H_

#include "board.h"

int horizontalScore(Board board, char character);
int verticalScore(Board board, char character);
int diagonal(Board board, char character);
int diagonal1(Board board, char character);
void print_scores(int scores[2]);

#endif
