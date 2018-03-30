#include <stdio.h>
#include "CuTest.h"
#include "actions.h"
#include "board.h"
#include "score.h"
#include "ia.h"

Board boardVide (int w,int h){
  return board_new(w,h,1);
}

Board boardCol3Full(){
  Board b;
  int i;
  b = board_new(10,7,1);
  for(i=0;i<7;i++){
    b.tab[i][2] = SYM_PLAYER_1;
  }
  return b;
}

/*
 *
 * board.c
 *
 */

void Test_board_currentPlayerSymbole(CuTest *tc){
  char expectedsym,actualsym;
  Board b1;
  b1 = boardVide(10,7);

  actualsym = board_currentPlayerSymbole(b1);
  expectedsym = SYM_PLAYER_1;
  CuAssertIntEquals(tc, expectedsym, actualsym);

  board_put(&b1,2);
  actualsym = board_currentPlayerSymbole(b1);
  expectedsym = SYM_PLAYER_2;
  CuAssertIntEquals(tc, expectedsym, actualsym);

  board_put(&b1,2);
  actualsym = board_currentPlayerSymbole(b1);
  expectedsym = SYM_PLAYER_1;
  CuAssertIntEquals(tc, expectedsym, actualsym);

  board_free(b1);
}

//Test de board_put basique
void Test_board_put1(CuTest *tc){
  int expected,actual;
  char expectedsym,actualsym;
  Board b1;
  b1 = boardVide(10,7);

  
  actual = board_put(&b1,5);
  expected = 6;
  CuAssertIntEquals(tc, expected, actual);
  actualsym = b1.tab[6][4];
  expectedsym = SYM_PLAYER_1;
  CuAssertIntEquals(tc, expectedsym, actualsym);

  actual = board_put(&b1,5);
  expected = 5;
  CuAssertIntEquals(tc, expected, actual);
  actualsym = b1.tab[5][4];
  expectedsym = SYM_PLAYER_2;
  CuAssertIntEquals(tc, expectedsym, actualsym);

  actual = board_put(&b1,10);
  expected = 6;
  CuAssertIntEquals(tc, expected, actual);
  actualsym = b1.tab[6][9];
  expectedsym = SYM_PLAYER_1;
  CuAssertIntEquals(tc, expectedsym, actualsym);

  board_free(b1);
}

//Test de board_put sur une colonne pleine
void Test_board_put2(CuTest *tc){
  int expected,actual;
  Board b1;
  b1 = boardCol3Full();

  actual = board_put(&b1,3);
  expected = -1;
  CuAssertIntEquals(tc, expected, actual);
}

//Test de board_colIsFull
void Test_board_colIsFull(CuTest *tc){
  int expected,actual;
  Board b1,b2;
  
  b1 = boardCol3Full();
  actual = board_colIsFull(b1,3);
  expected = 1;
  CuAssertIntEquals(tc, expected, actual);

  b2 = boardVide(6,8);
  actual = board_colIsFull(b2,3);
  expected = 0;
  CuAssertIntEquals(tc, expected, actual);

  board_free(b1);
  board_free(b2);
}

void Test_board_undo(CuTest *tc){
  int expected,actual;
  Board b1;
  b1 = boardVide(10,7);

  board_put(&b1,5);
  board_put(&b1,5);
  actual = b1.tab[5][4];
  expected = SYM_PLAYER_2;
  CuAssertIntEquals(tc, expected, actual);
  
  actual = board_undo(&b1,1);
  expected = 5;
  CuAssertIntEquals(tc, expected, actual);
  actual = b1.tab[5][4];
  expected = VIDE;
  CuAssertIntEquals(tc, expected, actual);

  board_put(&b1,5);
  actual = b1.tab[5][4];
  expected = SYM_PLAYER_2;
  CuAssertIntEquals(tc, expected, actual);

  actual = board_undo(&b1,2);
  expected = 6;
  CuAssertIntEquals(tc, expected, actual);
  actual = b1.tab[6][4];
  expected = VIDE;
  CuAssertIntEquals(tc, expected, actual);
  
}

void Test_board_redo(CuTest *tc){
  int expected,actual;
  Board b1;
  b1 = boardVide(10,7);

  board_put(&b1,3);
  board_put(&b1,3);
  actual = b1.tab[5][2];
  expected = SYM_PLAYER_2;
  CuAssertIntEquals(tc, expected, actual);

  actual = board_undo(&b1,1);
  expected = 5;
  CuAssertIntEquals(tc, expected, actual);
  actual = b1.tab[5][2];
  expected = VIDE;
  CuAssertIntEquals(tc, expected, actual);

  actual = board_redo(&b1,1);
  expected = 5;
  CuAssertIntEquals(tc, expected, actual);
  actual = b1.tab[5][2];
  expected = SYM_PLAYER_2;
  CuAssertIntEquals(tc, expected, actual);

  actual = board_undo(&b1,2);
  expected = 6;
  CuAssertIntEquals(tc, expected, actual);
  actual = b1.tab[5][2];
  expected = VIDE;
  CuAssertIntEquals(tc, expected, actual);
  actual = b1.tab[6][2];
  expected = VIDE;
  CuAssertIntEquals(tc, expected, actual);

  actual = board_redo(&b1,2);
  expected = 5;
  CuAssertIntEquals(tc, expected, actual);
  actual = b1.tab[5][2];
  expected = SYM_PLAYER_2;
  CuAssertIntEquals(tc, expected, actual);
  actual = b1.tab[6][2];
  expected = SYM_PLAYER_1;
  CuAssertIntEquals(tc, expected, actual);
}


void Test_checknum(CuTest *tc){
  int i,expected,actual;
  Board b=boardVide(36,53);
  for(i=-3;i<b.width;i++){
    actual = checknum(i,b);
    expected = 1;
    CuAssertIntEquals(tc, expected, actual);
  }
  actual = checknum(-4,b);
  expected = 0;
  CuAssertIntEquals(tc, expected, actual);

  actual = checknum(b.width+1,b);
  expected = 0;
  CuAssertIntEquals(tc, expected, actual);
}

void Test_checkfull(CuTest *tc){
  int i,j,expected,actual;
  Board b=boardVide(15,22);
  for(i=0;i<b.height;i++){
    for(j=1;j<=b.width;j++){
      actual = checkfull(b);
      expected = 1;
      CuAssertIntEquals(tc, expected, actual);
      board_put(&b,j);
    }
  }
  actual = checkfull(b);
  expected = 0;
  CuAssertIntEquals(tc, expected, actual);
}


void Test_board_lastPlayRow(CuTest *tc){
  Board b = boardVide(5,5);
  int expected,actual;

  actual = board_lastPlayRow(b);
  expected = -1;
  CuAssertIntEquals(tc, expected, actual);

  board_put(&b,3);
  actual = board_lastPlayRow(b);
  expected = 4;
  CuAssertIntEquals(tc, expected, actual);

  board_put(&b,3);
  board_put(&b,3);
  board_put(&b,3);
  board_put(&b,3);
  actual = board_lastPlayRow(b);
  expected = 0;
  CuAssertIntEquals(tc, expected, actual);
}


/*
 *
 * score.c
 *
 */

void Test_horizontalScore(CuTest *tc){
  Board b=boardVide(8,7);
  int expected,actual;
  board_put(&b,1);
  board_put(&b,8);
  board_put(&b,2);
  board_put(&b,7);
  board_put(&b,3);
  board_put(&b,6);

  actual = horizontalScore(b,SYM_PLAYER_1);
  expected = 0;
  CuAssertIntEquals(tc, expected, actual);
  board_put(&b,4);
  actual = horizontalScore(b,SYM_PLAYER_1);
  expected = 1;
  CuAssertIntEquals(tc, expected, actual);

  
  actual = horizontalScore(b,SYM_PLAYER_2);
  expected = 0;
  CuAssertIntEquals(tc, expected, actual);
  board_put(&b,5);
  actual = horizontalScore(b,SYM_PLAYER_2);
  expected = 1;
  CuAssertIntEquals(tc, expected, actual);
}

void Test_verticalScore(CuTest *tc){
  Board b=boardVide(8,7);
  int expected,actual;
  board_put(&b,1);
  board_put(&b,2);
  board_put(&b,1);
  board_put(&b,2);
  board_put(&b,1);
  board_put(&b,2);

  actual = verticalScore(b,SYM_PLAYER_1);
  expected = 0;
  CuAssertIntEquals(tc, expected, actual);
  board_put(&b,1);
  actual = verticalScore(b,SYM_PLAYER_1);
  expected = 1;
  CuAssertIntEquals(tc, expected, actual);

  
  actual = verticalScore(b,SYM_PLAYER_2);
  expected = 0;
  CuAssertIntEquals(tc, expected, actual);
  board_put(&b,2);
  actual = verticalScore(b,SYM_PLAYER_2);
  expected = 1;
  CuAssertIntEquals(tc, expected, actual);

  
  board_put(&b,1);
  actual = verticalScore(b,SYM_PLAYER_1);
  expected = 1;
  CuAssertIntEquals(tc, expected, actual);
}

void Test_diagonal(CuTest *tc){
  Board b=boardVide(8,7);
  int expected,actual;
  board_put(&b,4);//1
  board_put(&b,3);//2
  board_put(&b,3);//1
  board_put(&b,2);//2
  board_put(&b,2);//1
  board_put(&b,1);//2
  board_put(&b,2);//1
  board_put(&b,1);//2
  board_put(&b,5);//1
  board_put(&b,1);//2

  actual = diagonal(b,SYM_PLAYER_1);
  expected = 0;
  CuAssertIntEquals(tc, expected, actual);
  board_put(&b,1);//1
  actual = diagonal(b,SYM_PLAYER_1);
  expected = 1;
  CuAssertIntEquals(tc, expected, actual);
}

void Test_diagonal1(CuTest *tc){
  Board b=boardVide(8,7);
  int expected,actual;
  board_put(&b,1);//1
  board_put(&b,2);//2
  board_put(&b,2);//1
  board_put(&b,3);//2
  board_put(&b,3);//1
  board_put(&b,4);//2
  board_put(&b,3);//1
  board_put(&b,4);//2
  board_put(&b,5);//1
  board_put(&b,4);//2

  actual = diagonal1(b,SYM_PLAYER_1);
  expected = 0;
  CuAssertIntEquals(tc, expected, actual);
  board_put(&b,4);//1
  actual = diagonal1(b,SYM_PLAYER_1);
  expected = 1;
  CuAssertIntEquals(tc, expected, actual);
}

/*
 *
 *ia.c
 *
 */
void Test_checkEmpty1(CuTest *tc){
 Board b = boardVide(5,7);
  int expected,actual;

  actual = checkEmpty1(b,0,6);
  expected = 1;
  CuAssertIntEquals(tc, expected, actual);

  board_put(&b,1);
  actual = checkEmpty1(b,0,5);
  expected = 1;
  CuAssertIntEquals(tc, expected, actual);
}

void Test_Medium(CuTest *tc){
  Board b = boardVide(20,20);
  int expected,actual;
  //TEST HORIZONTAL
  board_put(&b,1);
  board_put(&b,1);
  board_put(&b,2);
  board_put(&b,2);
  board_put(&b,3);
  actual = Medium(b,SYM_PLAYER_1);
  expected = 4;
  CuAssertIntEquals(tc, expected, actual);
  board_put(&b,actual);

  board_put(&b,5);
  board_put(&b,5);
  board_put(&b,6);
  board_put(&b,6);
  board_put(&b,8);
  actual = Medium(b,SYM_PLAYER_1);
  expected = 7;
  CuAssertIntEquals(tc, expected, actual);
  board_put(&b,actual);

  board_put(&b,11);
  board_put(&b,11);
  board_put(&b,12);
  board_put(&b,12);
  board_put(&b,13);
  actual = Medium(b,SYM_PLAYER_1);
  expected = 10;
  CuAssertIntEquals(tc, expected, actual);
  board_put(&b,actual);
  board_put(&b,13);
  board_put(&b,14);

  board_put(&b,16);
  board_put(&b,16);
  board_put(&b,18);
  board_put(&b,18);
  board_put(&b,19);
  actual = Medium(b,SYM_PLAYER_1);
  expected = 17;
  CuAssertIntEquals(tc, expected, actual);
  board_put(&b,actual);

  //TEST VERTICAL
  board_put(&b,1);
  board_put(&b,2);
  board_put(&b,1);
  board_put(&b,2);
  board_put(&b,1);
  actual = Medium(b,SYM_PLAYER_1);
  expected = 1;
  CuAssertIntEquals(tc, expected, actual);
  board_put(&b,actual);

  //TEST DIAGONAL bas gauche -> haut droite
  board_free(b);
  b = boardVide(10,10);
  b.tab[9][0] = SYM_PLAYER_1;
  b.tab[9][1] = SYM_PLAYER_1;
  b.tab[8][1] = SYM_PLAYER_1;
  b.tab[9][2] = SYM_PLAYER_1;
  b.tab[8][2] = SYM_PLAYER_1;
  b.tab[7][2] = SYM_PLAYER_1;
  b.tab[9][3] = SYM_PLAYER_2;
  b.tab[8][3] = SYM_PLAYER_2;
  b.tab[7][3] = SYM_PLAYER_2;
  b.tab[6][3] = SYM_PLAYER_1;
  b.tab[9][2] = SYM_PLAYER_2;
  int i;
  for(i=1;i<=4;i++){
    b.tab[10-i][i-1] = VIDE;
    actual = Medium(b,SYM_PLAYER_1);
    expected = i;
    CuAssertIntEquals(tc, expected, actual);
    b.tab[10-i][i-1] = SYM_PLAYER_1;
  }

   //TEST DIAGONAL haut gauche -> bas droite
  board_free(b);
  b = boardVide(10,10);
  b.tab[9][0] = SYM_PLAYER_2;
  b.tab[8][0] = SYM_PLAYER_2;
  b.tab[7][0] = SYM_PLAYER_2;
  b.tab[6][0] = SYM_PLAYER_1;
  b.tab[9][1] = SYM_PLAYER_2;
  b.tab[8][1] = SYM_PLAYER_2;
  b.tab[7][1] = SYM_PLAYER_1;
  b.tab[9][2] = SYM_PLAYER_2;
  b.tab[8][2] = SYM_PLAYER_1;
  b.tab[9][3] = SYM_PLAYER_1;

  for(i=1;i<=4;i++){
    b.tab[10-5+i][i-1] = VIDE;
    actual = Medium(b,SYM_PLAYER_1);
    expected = i;
    CuAssertIntEquals(tc, expected, actual);
    b.tab[10-5+i][i-1] = SYM_PLAYER_1;
  }
}

void Test_XMLformating(CuTest *tc){
  int expected,actual;
  int w,h,hs;
  XMLformating("exemples/config/config1.xml",&w,&h,&hs);
  
  actual = w;
  expected = 7;
  CuAssertIntEquals(tc, expected, actual);

  actual = h;
  expected = 6;
  CuAssertIntEquals(tc, expected, actual);

  actual = hs;
  expected = 5;
  CuAssertIntEquals(tc, expected, actual);

  XMLformating("exemples/config/config2.xml",&w,&h,&hs);
  actual = w;
  expected = 7;
  CuAssertIntEquals(tc, expected, actual);

  actual = h;
  expected = 6;
  CuAssertIntEquals(tc, expected, actual);

  actual = hs;
  expected = 5;
  CuAssertIntEquals(tc, expected, actual);
}

void Test_saveLoad(CuTest *tc){
  Board b = boardVide(10,10);
  char t[10][10];
  int expected,actual,i,j;

  board_put(&b,3);
  board_put(&b,1);
  board_put(&b,3);
  board_put(&b,5);
  board_put(&b,3);
  board_put(&b,3);
  board_put(&b,2);

  saveLoad(-2,&b);
  for(i=0;i<10;i++){
    for(j=0;j<10;j++){
      t[i][j] = b.tab[i][j];
    }
  }

  board_put(&b,1);
  board_put(&b,2);
  board_put(&b,3);
  board_put(&b,5);
  board_put(&b,7);
  board_put(&b,2);
  board_put(&b,9);

  saveLoad(-1,&b);
  for(i=0;i<10;i++){
    for(j=0;j<10;j++){
      actual = b.tab[i][j];
      expected = t[i][j];
      CuAssertIntEquals(tc, expected, actual);
    }
  }
}


CuSuite* StrUtilGetSuite() {
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, Test_board_put1);
    SUITE_ADD_TEST(suite, Test_board_put2);
    SUITE_ADD_TEST(suite, Test_board_colIsFull);
    SUITE_ADD_TEST(suite, Test_board_currentPlayerSymbole);
    SUITE_ADD_TEST(suite, Test_board_undo);
    SUITE_ADD_TEST(suite, Test_board_redo);
    SUITE_ADD_TEST(suite, Test_checknum);
    SUITE_ADD_TEST(suite, Test_checkfull);
    SUITE_ADD_TEST(suite, Test_board_lastPlayRow);
    SUITE_ADD_TEST(suite, Test_horizontalScore);
    SUITE_ADD_TEST(suite, Test_verticalScore);
    SUITE_ADD_TEST(suite, Test_diagonal);
    SUITE_ADD_TEST(suite, Test_diagonal1);
    SUITE_ADD_TEST(suite, Test_checkEmpty1);
    SUITE_ADD_TEST(suite, Test_Medium);
    SUITE_ADD_TEST(suite, Test_XMLformating);
    SUITE_ADD_TEST(suite, Test_saveLoad);
    return suite;
}
