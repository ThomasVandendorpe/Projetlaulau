#include "CuTest.h"
#include "actions.h"
#include "board.h"


void Test_numX(CuTest *tc) {
    Board input = board_new(10,10,1);
    input.tab[1][1]='X';
    input.tab[5][1]='X';
    input.tab[1][3]='X';
    input.tab[6][0]='X';
    input.tab[6][1]='X';
    input.tab[4][7]='X';
    input.tab[8][8]='X';
    input.tab[5][0]='X';

    int actual = numX(input);
    int expected = 8;
    CuAssertIntEquals(tc, expected, actual);
}

CuSuite* StrUtilGetSuite() {
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, Test_numX);
    return suite;
}