#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int width=0, height=0, highscores=0;

void print(char **board);
int checknum(int num, char **board);
void player(char **board, int num, char character);
int checkfull(char **board);
int horizontalScore(char **board, char character);
int verticalScore(char **board, char character);
int diagonal(char **board, char character);
int diagonal1(char **board, char character);
int rowNum(int num, char **board);
int checkEmpty(char **board);
int checkCol(int num, char **board);
void undoRedo(char *x, char **board, int num, int *undoCol,
               int *undoRow, int *k, int *l, int *z,
               int *redoCol, int *redoRow, int *q);
void Easy(char **board, int *num);
int checkEmpty1(char **board,int num,int numOfrow);
int Medium(char **board, char character, int *num);
void Hard(char **board, int *num);
void undoRedoLimit(int num, int *undoCounter, int *redoCounter);
int numX(char **board);
int numO(char **board);
void XMLformating();
void highscore(int high);
void saveLoad(int *num, char **board);

int main()
{
    int high=0;
    XMLformating();
    char playAgain;
    do{
        int flag, score1=0, score2=0, *compUndoCol, undoCounter=0,
            redoCounter=0, compUndoCounter =0, choose;
        int i, j, num=0, *undoCol, k, *undoRow,
            *redoCol, *redoRow, l, *compUndoRow;
        static int q=0, z=0, d=0, c=0;
        char **board, x='X', o='O';
	undoCol = (int *)malloc(height*width*sizeof(int));
        for(i=0;i<height*width;i++){
            undoCol[i] = 0;
        }
	redoCol = (int *)malloc(height*width*sizeof(int));
        for(i=0;i<height*width;i++){
            redoCol[i] = 0;
        }
	undoRow = (int *)malloc(height*width*sizeof(int));
        for(i=0;i<height*width;i++){
            undoRow[i] = 0;
        }
	redoRow = (int *)malloc(height*width*sizeof(int));
        for(i=0;i<height*width;i++){
            redoRow[i] = 0;
        }
	compUndoCol = (int *)malloc(height*width*sizeof(int));
        for(i=0;i<height*width;i++){
            compUndoCol[i] = 0;
        }
	compUndoRow = (int *)malloc(height*width*sizeof(int));
        for(i=0;i<height*width;i++){
            compUndoRow[i] = 0;
        }
	board = (char **)malloc(height*sizeof(char *));
        for(i=0; i<height; i++)
        {
            for(j=0; j<width; j++)
            {
                board[i][j]= '\0';
            }
        }
        printf("\n\n                     **** WELCOME TO THE GAME ****\n\n");
	printf("Player1 vs Player2: press 1 \n\nPlayer vs Computer: press 2 \n\n");
        scanf("%d", &choose);
        while((choose!=1 && choose!=2) || isalpha(choose))
        {
            printf("Enter 1 or 2\n");
	    printf("Player1 vs Player2: press 1 \n\nPlayer vs Computer: press 2 \n\n");
            scanf("%d", &choose);
        }
        if(choose == 1){
            print(board);
            do{
	        printf("\nif you want to undo, press 0\n");
	        printf("if you want to redo, press -3, to load, press -1, to save, press -2\n");
                if(numX(board) <= numO(board)){
                    printf("\nplayer 1 enter number of the column:");
                    scanf("%d", &num);
                    saveLoad(&num, board);
                    num = checknum(num,board);
                    if(checkCol(num,board)){
                        while(board[0][num-1]!='\0')
                          {
                            print(board);
                            printf("Invalid input. Do another move : ");
                            scanf("%d", &num);
                            saveLoad(&num, board);
                            if(num == 0 || num == -3){
                                break;
                            }
                          }
                    }
                    if(redoCounter >= undoCounter){
                        while(num == -3){
                            print(board);
                            printf("\ncannot redo!! play again");
                            scanf("%d", &num);
                            saveLoad(&num, board);
                            if(num == 0){
                                break;
                            }
                        }
                    }
                    while(num == 0 && checkEmpty(board)){
                        print(board);
                        printf("\ncannot undo! play again");
                        scanf("%d", &num);
                        saveLoad(&num, board);
                        if(num == -3){
                            if(redoCounter >= undoCounter){
                                while(num == -3){
                                    print(board);
                                    printf("\ncannot redo!! play again");
                                    scanf("%d", &num);
                                    if(num == 0){
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    undoRedoLimit(num,&undoCounter,&redoCounter);
                    undoRedo(&x,board,num,undoCol,undoRow,&k,&l,&z,redoCol,redoRow,&q);
                    score1=horizontalScore(board,x)+verticalScore(board,x)+diagonal(board,x)+diagonal1(board,x);
                    printf("\n***************************************************");
                    printf("\n***************************************************");
                    printf("\n**                      **                       **");
                    printf("\n** player1 score : %d    **   player2 score  : %d  **", score1, score2);
                    printf("\n**                      **                       **");
                    printf("\n***************************************************");
                    printf("\n***************************************************");
                }
	        printf("\nif you want to undo, press 0\n");
	        printf("if you want to redo, press -3, to load, press -1, to save, press -2\n");
                if(numO(board) < numX(board)){
                    printf("\nplayer 2 enter number of the column:");
                    scanf("%d", &num);
                    saveLoad(&num, board);
                    num = checknum(num,board);
                    if(checkCol(num,board)){
                        while(board[0][num-1]!='\0')
                          {
                            print(board);
                            printf("Invalid input. Do another move : ");
                            scanf("%d", &num);
                            saveLoad(&num, board);
                            if(num == 0 || num == -3){
                                break;
                            }
                          }
                    }
                    if(redoCounter >= undoCounter){
                        while(num == -3){
                            print(board);
                            printf("\ncannot redo!! play again");
                            scanf("%d", &num);
                            saveLoad(&num, board);
                            if(num == 0){
                                break;
                            }
                        }
                    }
                    while(num == 0 && checkEmpty(board)){
                        print(board);
                        printf("\ncannot undo! play again");
                        scanf("%d", &num);
                        saveLoad(&num, board);
                        if(num == -3){
                            if(redoCounter >= undoCounter){
                                while(num == -3){
                                    print(board);
                                    printf("\ncannot redo!! play again");
                                    scanf("%d", &num);
                                    saveLoad(&num, board);
                                    if(num == 0){break;}
                                }
                            }
                        }
                    }
                    undoRedoLimit(num,&undoCounter,&redoCounter);
                    undoRedo(&o,board,num,undoCol,undoRow,&k,&l,&z,redoCol,redoRow,&q);
                    score2=horizontalScore(board,o)+verticalScore(board,o)+diagonal(board,o)+diagonal1(board,o);
                    printf("\n***************************************************");
                    printf("\n***************************************************");
                    printf("\n**                      **                       **");
                    printf("\n** player1 score : %d    **   player2 score  : %d  **", score1, score2);
                    printf("\n**                      **                       **");
                    printf("\n***************************************************");
                    printf("\n***************************************************");
                }
            }while(checkfull(board));

            if(score2>score1){
                high=score2;
                printf("\nPLAYER 2 WINS");
            }
            else if(score1==score2){
                high=score1;
                printf("\nDRAW");
            }
            else{
                high=score1;
                printf("\nPLAYER 1 WINS");
            }
        }
        else
        {
            printf("\nEasy (press 1), Medium (press 2), Hard (press 3)\n");
            scanf("%d", &choose);
            while(choose!=1 && choose!=2 && choose!=3)
            {
                printf("Enter 1 , 2 or 3\n");
                printf("\nEasy (press 1), Medium (press 2), Hard (press 3)\n");
                scanf("%d", &choose);
            }
            print(board);
            do{
	        printf("\nif you want to undo, press 0\n");
	        printf("if you want to redo, press -3, to load, press -1, to save, press -2\n");
                printf("\nenter number of the column:");
                scanf("%d", &num);
                saveLoad(&num, board);
                num = checknum(num,board);
                if(checkCol(num,board)){
                    while(board[0][num-1]!='\0')
                      {
                        print(board);
                        printf("Invalid input. Do another move : ");
                        scanf("%d", &num);
                        saveLoad(&num, board);
                        if(num == 0 || num == -3){
                            break;
                        }
                      }
                }
                if(redoCounter >= compUndoCounter){
                    while(num == -3){
                        print(board);
                        printf("\ncannot redo!! play again");
                        scanf("%d", &num);
                        saveLoad(&num, board);
                        if(num == 0){
                            break;
                        }
                    }
                }
                while(num == 0 && checkEmpty(board)){
                    print(board);
                    printf("\ncannot undo! play again");
                    scanf("%d", &num);
                    saveLoad(&num, board);
                    if(num == -3){
                        if(redoCounter >= compUndoCounter){
                            while(num == -3){
                                print(board);
                                printf("\ncannot redo!! play again");
                                scanf("%d", &num);
                                saveLoad(&num, board);
                                if(num == 0){
                                    break;
                                }
                            }
                        }
                    }
                }
                undoRedoLimit(num,&undoCounter,&redoCounter);
                undoRedo(&x,board,num,undoCol,undoRow,&k,&l,&z,redoCol,redoRow,&q);
                score1=horizontalScore(board,x)+verticalScore(board,x)+diagonal(board,x)+diagonal1(board,x);
                printf("\n***************************************************");
                printf("\n***************************************************");
                printf("\n**                      **                       **");
                printf("\n**   User  score : %d    **  Computer score  : %d  **", score1, score2);
                printf("\n**                      **                       **");
                printf("\n***************************************************");
                printf("\n***************************************************");
                switch(choose)
                {
                    case 1:{
                        if(num != 0 && num != -1 && num != -2){
                            Easy(board, &num);
                            compUndoCol[d++] = num-1 ;
                            compUndoRow[c++] = rowNum(num,board)+1;
                            compUndoCounter = 0;
                        }
                        if(num == 0){
                            compUndoCounter += 1;
                            c--;
                            d--;
                            board[compUndoRow[c]][compUndoCol[d]] = '\0';
                        }
                        break;
                    }
                    case 2: {
                        if(num != 0 && num != -1 && num != -2){
                            flag=0;
                            if(Medium(board,x,&num)==1){flag=1;}
                            if(flag!=1){Easy(board, &num);}
                            compUndoCol[d++] = num-1 ;
                            compUndoRow[c++] = rowNum(num,board)+1;
                            compUndoCounter = 0;
                        }
                        if(num == 0){
                            compUndoCounter += 1;
                            c--;
                            d--;
                            board[compUndoRow[c]][compUndoCol[d]] = '\0';
                        }
                        break;
                    }
                    case 3:{
                        if(num != 0 && num != -1 && num != -2){
                            Hard(board,&num);
                            compUndoCol[d++] = num-1 ;
                            compUndoRow[c++] = rowNum(num,board)+1;
                            compUndoCounter = 0;
                        }
                        if(num == 0){
                            compUndoCounter += 1;
                            c--;
                            d--;
                            board[compUndoRow[c]][compUndoCol[d]] = '\0';
                        }
                        break;
                    }
                }
                print(board);
                score2=horizontalScore(board,o)+verticalScore(board,o)+diagonal(board,o)+diagonal1(board,o);
                printf("\n***************************************************");
                printf("\n***************************************************");
                printf("\n**                      **                       **");
                printf("\n**   User  score : %d    **  Computer score  : %d  **", score1, score2);
                printf("\n**                      **                       **");
                printf("\n***************************************************");
                printf("\n***************************************************");
            }while(checkfull(board));
            if(score2>score1){
                high=score2;
                printf("\nComputer WINS\n");
            }
            else if(score1==score2){
                high=score1;
                printf("\nDRAW\n");
            }
            else{
                high=score1;
                printf("\nUser WINS\n");
            }
        }
        highscore(high);
        printf("\nif you you want to play again press y, else press any key\n");
        scanf("\n%c",&playAgain);
    }while(playAgain == 'y');
    return 0;
}

void print(char **board)
{
    int i, j;
    for(i=0; i<height; i++)
    {
        printf("\n+");
        for(j=0; j<width; j++)
        {
            printf("---+");
        }
        printf("\n|");
        for(j=0; j<width; j++)
        {
            printf(" %c |", board[i][j]);
        }
    }
    printf("\n+");
    for(i=0; i<width; i++)
    {
        printf("---+");
    }
    printf("\n");
    for(i=1;i<=width;i++){
        printf("   %d",i);
    }
    printf("\n\n\n");
}
int checknum(int num, char **board)
{
    while((num<-3) || (num>width))
    {
        print(board);
        printf("\nPlease enter a number between 1 and %d :", width);
        scanf("%d", &num);
        }
    return num;
}

void player(char **board, int num, char character)
{
    int i;
    for(i=(height-1); i>=0;i--)
    {
        if(board[i][num-1]=='\0')
        {
            board[i][num-1] = character;
            break;
        }
    }
    print(board);
}
int checkfull(char **board)
{
    int i, j;
    for(i=0; i<height; i++)
    {
        for(j=0; j<width; j++)
        {
            if(board[i][j] == '\0')
            {
                return 1;
            }
        }

    }
    return 0;
}
int horizontalScore(char **board, char character){
    int u, v;
    int score1=0;
    for(u=0;u<height;u++)
    {
        for(v=0;v<(width-3);v++)
        {
            if(board[u][v] == character && board[u][v+1] == character && board[u][v+2] == character && board[u][v+3] == character){
                score1++;
            }
        }
    }
    return score1;
}
int verticalScore(char **board, char character){
    int u, v;
    int score1=0;
    for(v=0;v<width;v++)
    {
        for(u=0;u<(height-3);u++)
        {
            if(board[u][v] == character && board[u+1][v] == character && board[u+2][v] == character && board[u+3][v] == character){
                score1++;
            }
        }
    }
    return score1;
}
int diagonal(char **board, char character){
    int u, v;
    int score1=0;
    for(u=(height-1);u>=3;u--)
    {
        for(v=0;v<(width-3);v++)
        {
            if(board[u][v] == character && board[u-1][v+1] == character && board[u-2][v+2] == character && board[u-3][v+3] == character){
                score1++;
            }
        }
    }
    return score1;
}
int diagonal1(char **board, char character){
    int u, v;
    int score1=0;
    for(u=(height-1);u>=3;u--)
    {
        for(v=(width-1);v>=3;v--)
        {
            if(board[u][v] == character && board[u-1][v-1] == character && board[u-2][v-2] == character && board[u-3][v-3] == character){
                score1++;
            }
        }
    }
    return score1;
}
int rowNum(int num, char **board){
    int i=0;
    for(i=0;i<height;i++){
        if(num == 0){return 0;}
        if(board[i][num-1]!='\0'){break;}
    }
    return i-1;
}
int checkEmpty(char **board){
    int n, m;
    for(n=0;n<height;n++){
        for(m=0;m<width;m++){
            if(board[n][m] != '\0'){return 0;}
        }
    }
    return 1;
}
int checkCol(int num, char **board){
    int i, counter=0;
    for(i=height-1;i>=0;i--){
        if(board[i][num-1] == '\0'){
            counter = 0;
            break;
        }
        else{
            counter = 1;
        }
    }
    return counter;
}
void undoRedo(char *x, char **board, int num, int *undoCol,
               int *undoRow, int *k, int *l, int *z,
               int *redoCol, int *redoRow, int *q){
        static int ccounter = 0, dcounter = 0;
        if(num != 0 && !checkCol(num, board) && num != -3 && !(num<-3) && !(num>width) && !(num == -2)){
            undoCol[*q] = num-1;
            *k = rowNum(num, board);
            undoRow[*q] = *k;
        }
        if(num != 0 && !checkCol(num, board) && num != -3 && !(num<-3) && !(num>width) && !(num == -2)){
            redoCol[*z] = num-1;
            *l = rowNum(num, board);
            redoRow[*z] = *l;
            *z+=1;
        }
        if(num == 0){
            ccounter +=1;
            board[undoRow[(*q-1)]][undoCol[(*q-1)]] = '\0';
            print(board);
            *q-=1;
            *z-=1;
        }
        else if(num == -3){
            dcounter += 1;
            if((dcounter <= ccounter)){
                board[redoRow[*z]][redoCol[*z]] = *x;
                print(board);
                *q+=1;
                undoCol[*q] = redoCol[*z+1];
                undoRow[*q] = redoRow[*z+1];
                *z+=1;
            }
        }
        else if(num == -1){
            printf("Game Loaded Successfully");
        }
        else if(num == -2){
            printf("Game saved Successfully");
            print(board);
        }
        else{
            *q+=1;
            player(board,num,*x);
            ccounter = 0;
            dcounter = 0;
        }
}
void Easy(char **board, int *num)
{
    int i, j, flag, l;
    l = rand() % width;
    for(i=(height-1); i>=0; i--)
    {
        if(board[i][l]=='\0')
        {
            board[i][l] = 'O';
            break;
        }
        flag = 0;
        while(i==0 && board[i][l]!='\0')
        {
            l = rand() % width;
            flag = 1;
        }
        for(j=(height-1); flag==1; j--)
        {
            if(board[j][l]=='\0')
            {
                board[j][l] = 'O';
                break;
            }
        }
    }
    *num = l+1;
}
int checkEmpty1(char **board,int num,int numOfrow)
{
    if(numOfrow==(height-1) && board[numOfrow][num]=='\0'){return 1;}
    else if(board[numOfrow+1][num]!='\0' && board[numOfrow][num]=='\0'){return 1;}
    return 0;
}
int Medium(char **board, char character, int *num)
{
    int i, j;
    for(i=height-1; i>=3; i--)
    {
        for(j=0; j<width; j++)
        {
            if(board[i][j] == character && board[i-1][j] == character && board[i-2][j] == character && board[i-3][j]=='\0')
            {
                board[i-3][j] = 'O';
                *num = j+1;
                return 1;
            }
        }
    }
    for(i=0;i<height;i++)
    {
        for(j=0;j<(width-3);j++)
        {
            if(board[i][j] == character && board[i][j+1] == character && board[i][j+2] == character && checkEmpty1(board,j+3,i)){
                board[i][j+3] = 'O';
                *num = j+3+1;
                return 1;
            }
            if(board[i][j+1] == character && board[i][j+2] == character && board[i][j+3] == character && checkEmpty1(board,j,i)){
                board[i][j] = 'O';
                *num = j+1;
                return 1;
            }
            if(board[i][j] == character && board[i][j+2] == character && board[i][j+3] == character && checkEmpty1(board,j+1,i)){
                board[i][j+1] = 'O';
                *num = j+1+1;
                return 1;
            }
            if(board[i][j] == character && board[i][j+1] == character && board[i][j+3] == character && checkEmpty1(board,j+2,i)){
                board[i][j+2] = 'O';
                *num = j+2+1;
                return 1;
            }
        }
    }
    for(i=height-1; i>=3; i--)
    {
        for(j=0;j<(width-3);j++)
        {
            if(board[i][j] == character && board[i-1][j+1] == character && board[i-2][j+2] == character && checkEmpty1(board,j+3,i-3)){
                board[i-3][j+3] = 'O';
                *num = j+3+1;
                return 1;
            }
            if(board[i-1][j+1] == character && board[i-2][j+2] == character && board[i-3][j+3] == character && checkEmpty1(board,j,i)){
                board[i][j] = 'O';
                *num = j+1;
                return 1;
            }
            if(board[i][j] == character && board[i-2][j+2] == character && board[i-3][j+3] == character && checkEmpty1(board,j+1,i-1)){
                board[i-1][j+1] = 'O';
                *num = j+1+1;
                return 1;
            }
            if(board[i][j] == character && board[i-1][j+1] == character && board[i-3][j+3] == character && checkEmpty1(board,j+2,i-2)){
                board[i-2][j+2] = 'O';
                *num = j+2+1;
                return 1;
            }
        }
    }
    for(i=height-1; i>=3; i--)
    {
        for(j=width-1; j>=3; j--)
        {
            if(board[i][j] == character && board[i-1][j-1] == character && board[i-2][j-2] == character && checkEmpty1(board,j-3,i-3)){
                board[i-3][j-3] = 'O';
                *num = j-3+1;
                return 1;
            }
            if(board[i-1][j-1] == character && board[i-2][j-2] == character && board[i-3][j-3] == character && checkEmpty1(board,j,i)){
                board[i][j] = 'O';
                *num = j+1;
                return 1;
            }
            if(board[i][j] == character && board[i-2][j-2] == character && board[i-3][j-3] == character && checkEmpty1(board,j-1,i-1)){
                board[i-1][j-1] = 'O';
                *num = j-1+1;
                return 1;
            }
            if(board[i][j] == character && board[i-1][j-1] == character && board[i-3][j-3] == character && checkEmpty1(board,j-2,i-2)){
                board[i-2][j-2] = 'O';
                *num = j-2+1;
                return 1;
            }
        }
    }
    return 0;
}
void Hard(char **board, int *num)
{
    int i, j;
    char x='X',o='O';
    if(Medium(board,x,num)==1)return;
    if(Medium(board,o,num)==1)return;
    for(i=height-1; i>=2; i--)
    {
        for(j=0; j<width; j++)
        {
            if(board[i][j] == 'O' && board[i-1][j] == 'O' && board[i-2][j]=='\0')
            {
                board[i-2][j] = 'O';
                *num = j+1;
                return;
            }
        }
    }
    for(i=0;i<height;i++)
    {
        for(j=0;j<(width-2);j++)
        {
            if(board[i][j] == 'O' && board[i][j+1] == 'O' && checkEmpty1(board,j+2,i)){
                board[i][j+2] = 'O';
                *num = j+2+1;
                return;
            }
            if(board[i][j+1] == 'O' && board[i][j+2] == 'O' && checkEmpty1(board,j,i)){
                board[i][j] = 'O';
                *num = j+1;
                return;
            }
        }
    }
    for(i=height-1; i>=2; i--)
    {
        for(j=0;j<(width-2);j++)
        {
            if(board[i][j] == 'O' && board[i-1][j+1] == 'O' && checkEmpty1(board,j+2,i-2)){
                board[i-2][j+2] = 'O';
                *num = j+2+1;
                return;
            }
            if(board[i-1][j+1] == 'O' && board[i-2][j+2] == 'O' && checkEmpty1(board,j,i)){
                board[i][j] = 'O';
                *num = j+1;
                return;
            }
        }
    }
    for(i=height-1; i>=2; i--)
    {
        for(j=width-1; j>=2; j--)
        {
            if(board[i][j] == 'O' && board[i-1][j-1] == 'O' && checkEmpty1(board,j-2,i-2)){
                board[i-2][j-2] = 'O';
                *num = j-2+1;
                return;
            }
            if(board[i-1][j-1] == 'O' && board[i-2][j-2] == 'O' && checkEmpty1(board,j,i)){
                board[i][j] = 'O';
                *num = j+1;
                return;
            }
        }
    }
    Easy(board,num);
}
void undoRedoLimit(int num, int *undoCounter, int *redoCounter){
    if(num == 0){
        *undoCounter += 1;
    }
    else if(num == -3){
        *redoCounter += 1;
    }
    else{
        *undoCounter = 0;
        *redoCounter = 0;
    }
}
int numX(char **board){
    int i, j, counter=0;
    for(i=height-1;i>=0;i--){
        for(j=width-1;j>=0;j--){
            if(board[i][j] == 'X'){;
            counter+=1;
            }
        }
    }
    return counter;
}
int numO(char **board){
    int i, j, counter=0;
    for(i=height-1;i>=0;i--){
        for(j=width-1;j>=0;j--){
            if(board[i][j] == 'O'){;
            counter+=1;
            }
        }
    }
    return counter;
}
void XMLformating()
{
    char c, c1, c2, c3, c4, c5, c6, c7, widthTag, heightTag, highscoresTag;
    int start=0, End=0, flag1=0, flag2=0, widthflag=0, heightflag=0, highscoresflag=0;
    FILE *file= fopen("config1.xml", "r");
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
        while(fscanf(file,"%c", &c5)!=EOF){
            fscanf(file,"< Width >%d < / Width %c", &width, &widthTag);
            if( (widthTag=='>') && (width>=4) && ftell(file)<End ) {widthflag=1; break;}
        }
        fseek(file,start,SEEK_SET);
        while(fscanf(file,"%c", &c6)!=EOF){
            fscanf(file,"< Height >%d < / Height %c", &height, &heightTag);
            if( (heightTag=='>') && (height>=4) && ftell(file)<End ) {heightflag=1; break;}
        }
        fseek(file,start,SEEK_SET);
        while(fscanf(file,"%c", &c7)!=EOF){
            fscanf(file,"< Highscores >%d < / Highscores %c", &highscores, &highscoresTag);
            if( (highscoresTag=='>') && (highscores>=4) && ftell(file)<End ) {highscoresflag=1; break;}
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
    if(highscores==0 || highscoresflag==0){
        highscores=5;
        printf("Incorrect file format, default value of highscore list (5) is loaded\n");
    }
    fclose(file);
}
void highscore(int high)
{
    int i=0, n=0, temp;
    int highs[highscores];
    FILE *highsc = fopen("highscores.text", "r");
    fscanf(highsc, "%d", &highs[i]);
    do
    {
        i++;
        if(fscanf(highsc, "%d", &n)!=EOF){highs[i]=n;}
        else {break;}
    }while(i<highscores);
    while(highscores>i){highs[i]=0;i++;}
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
    highsc = fopen("highscores.text", "w");
    printf("\n\t      High Scores\n\t\t*****");
    for(i=0; i<highscores; i++)
    {
        fprintf(highsc,"%d ", highs[i]);
        printf("\n\t\t* %d *", highs[i]);
    }
    printf("\n\t\t*****");
    fclose(highsc);
}
void saveLoad(int *num, char **board){
    FILE *pfile;
    int r, t;
    if(*num == -2){
        printf("Game Saved Successfully");
        pfile = fopen("save.txt", "w");
        for(r=height-1;r>=0;r--){
            for(t=width-1;t>=0;t--){
                fprintf(pfile, "%c", board[r][t]);
            }
        }
        fclose(pfile);
    }
    if(*num == -1){
        pfile = fopen("save.txt", "r");
        for(r=height-1;r>=0;r--){
            for(t=width-1;t>=0;t--){
                fscanf(pfile, "%c", &board[r][t]);
            }
        }
        fclose(pfile);
        print(board);
    }
}


