#include "CuTest.h"
#include "actions.h"
#include "board.h"

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

void Test_numX(CuTest *tc){
  Board b=boardVide(8,7);
  int expected,actual;
  b.tab[2][3]='X';
  b.tab[6][4]='X';
  b.tab[1][7]='X';
  b.tab[0][0]='X';
  b.tab[6][7]='O';
  b.tab[5][5]='O';
  b.tab[0][6]='O';
  actual = numX(b);
  expected = 4;
  CuAssertIntEquals(tc, expected, actual);
}

void Test_numO(CuTest *tc){
  Board b=boardVide(8,7);
  int expected,actual;
  b.tab[2][3]='X';
  b.tab[1][7]='X';
  b.tab[0][0]='X';
  b.tab[6][7]='O';
  b.tab[5][5]='O';
  b.tab[2][1]='O';
  b.tab[0][6]='O';
  actual = numO(b);
  expected = 4;
  CuAssertIntEquals(tc, expected, actual);
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
    SUITE_ADD_TEST(suite, Test_numX);
    SUITE_ADD_TEST(suite, Test_numO);
    return suite;
}
