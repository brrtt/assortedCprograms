/* ECE 209 - Program 2
 
 bglite -- a backgammon-like game
 
 User interface code (main function) is provided by G. Byrd.
 
 ***** J. Barrett Chesebrough *****
 * the sub functions perform the functions necessary for the main code to run
 by using if statements, arrays and while loops.
 *
 October 2016
 */

#include <stdio.h>
#include <stdlib.h>

/* functions that you must write */

void initBoard(int *);  /* initialize the board */
int isWinner(int, int *);  /* check if player wins */
int anyLegalMoves(int, int *, int);  /* check for any move */
int isLegalMove(int, int *, int, int); /* check a specific move */
void doMove(int, int *, int, int);  /* perform a move */
void jailBreak(int, int*, int);   /* get one checker out of jail */

/* functions provided */
void printBoard(int *board);
void printPlayer(int player);
void printCheckers(int checkers);
int isInJail(int player, int *board);

#ifndef NOMAIN    /* ignore this line -- will explain later */

int main()
{
    int mPlayer;   /* current player: +1 = Red, -1 = Blue */
    int mBoard[16];  /* board array -- see spec */
    
    int seed;      /* seed for random number generator */
    int roll;      /* result of rolling one six-sided die */
    int guess;     /* predicted roll */
    int move;      /* move counter */
    int start;     /* user-entered start position for move */
    int winner;    /* flag for winning */
    
    printf("Welcome to BG-Lite\n\n");
    printf("Enter an arbitrary seed value: ");
    scanf("%d", &seed);
    srand(seed);   /* seed the random number generator */
    
    initBoard(mBoard);   /* initialize the playing board */
    
    mPlayer = -1; /* set to Blue, will flip in the loop */
    winner = 0;
    
    do {  /* loop will end when winner found */
        
        mPlayer *= -1;   /* alternate player */
        
        printBoard(mBoard);  /* print the board */
        printf("**** ");
        printPlayer(mPlayer);
        printf("'s turn\n");
        
        printf("Enter a prediction: ");
        scanf("%d", &guess);
        
        roll = 1 + rand() % 6;  /* number between 1 and 6 */
        printf("Roll is %d.\n", roll);
        
        if (roll == guess) {
            printf("Congratulations!! You get two moves.\n");
            move = 2;
        }
        else {
            printf("Better luck next time.\n");
            move = 1;
        }
        
        while (!winner && (move > 0)) {
            
            if (! anyLegalMoves(mPlayer, mBoard, roll)) {
                printf("There are no legal moves for that roll.\n");
                break;  /* break out of outer loop */
            }
            
            if (isInJail(mPlayer, mBoard)) {
                printf("\n======== JAIL BREAK! ========\n");
                jailBreak(mPlayer, mBoard, roll);
            }
            else {
                while (1) {
                    printf("Enter starting position of your move: ");
                    scanf("%d", &start);
                    if (isLegalMove(mPlayer, mBoard, roll, start)) {
                        doMove(mPlayer, mBoard, roll, start);
                        break;  /* completed move break out of inner loop */
                    }
                    else {
                        printf("Move is not legal -- try again.\n");
                    }
                }
            }
            
            /* check to see if player has won */
            winner = isWinner(mPlayer, mBoard);
            move--;
            /* if pending move, print board */
            if (move) printBoard(mBoard);
        }
        
    } while (!winner);  /* until a winner is found */
    
    printPlayer(mPlayer);
    printf(" WINS!!!\n\n");
    
    return EXIT_SUCCESS;
}

#endif    /* ignore this line -- will explain later */

/* printBoard -- print an ASCII representation of the playing board */
/* input: 16-element board array                                    */
/* output: none                                                     */

void printBoard(int *board) {
    int pos;  /* position */
    
    printf("\n");
    
    /* print checkers in each spot */
    for (pos = 0; pos <= 13; pos++) {
        printCheckers(board[pos]);
        printf("  ");
    }
    printf("\n");
    
    /* print label for each spot:
     BH = blue home, RH = red home */
    printf("BH   ");
    for (pos = 1; pos <= 12; pos++) {
        printf("%02d   ", pos);
    }
    printf("RH\n");
    
    /* print JAIL */
    printf("JAIL: ");
    if (board[14]) {
        printCheckers(board[14]);
        if (board[15]) printf(",");
    }
    if (board[15]) {
        printCheckers(board[15]);
    }
    
    printf("\n\n");
    return;
}

/* printCheckers -- print number and color of checkers   */
/* input: number of checkers; pos = red, neg = blue      */
/* output: none                                          */
/* prints as three characters, left-justified            */

void printCheckers(int checkers) {
    char color = 'R';
    if (checkers < 0) {
        checkers = -checkers;   /* convert to positive */
        color = 'B';            /* and chance color */
    }
    if (checkers == 0) printf("   ");
    else if (checkers <= 8) printf("%d%c ", checkers, color);
    else printf("%d%c", checkers, color);
    return;
}

/* printPlayer -- prints name of player, all caps */
/* input: player = 1 if red, -1 if blue           */
/* output: none                                   */

void printPlayer(int p) {
    if (p == 1) printf("RED");
    else if (p == -1) printf("BLUE");
    return;
}

/* isInJail -- checks whether player has any checkers in Jail */
/* input: player = 1 if Red, -1 if Blue           */
/*        board = board array                     */
/* output: 1 if in Jail, 0 if not                 */

int isInJail(int p, int *b) {
    return
    ((p > 0) && (b[14] != 0))
    || ((p < 0) && (b[15] != 0));
}


/****************************************************************/
/***  YOUR CODE GOES BELOW THIS LINE                            */
/***  DO NOT WRITE ABOVE THIS LINE                              */
/****************************************************************/
/* initBoard initializes an array that represents the board and places
 checkers in the appropriate positions in the array */
void initBoard(int *mBoard){
    *(mBoard)=0;                        /*blue home*/
    *(mBoard+1)=5;
    *(mBoard+2)=0;
    *(mBoard+3)=0;
    *(mBoard+4)=0;
    *(mBoard+5)=3;
    *(mBoard+6)=2;
    *(mBoard+7)=-2;
    *(mBoard+8)=-3;
    *(mBoard+9)=0;
    *(mBoard+10)=0;
    *(mBoard+11)=0;
    *(mBoard+12)=-5;
    *(mBoard+13)=0;                     /*red home*/
    *(mBoard+14)=0;                     /*red jail*/
    *(mBoard+15)=0;                     /*blue jail*/
    return;
}
/*isWinner detects if there is a winner by checking the number of
 checkers in each color's home. */
int isWinner(int mPlayer, int *mBoard){
    if(mPlayer==1){
        if((*mBoard+13)==10){
            return 1;
        }
    }
    else{
        if(mPlayer==-1){
            if(*mBoard==-10){
                return 1;
            }
        }
    }
    return 0;
}
/* anyLegalMoves checks each possible move case. Any one case failing returns a 0,
 all cases succeeding returns a 1 and allows the player to choose a starting
 position to move from */
int anyLegalMoves(int mPlayer, int* mBoard,int roll) {
    if(mPlayer==1){
        int i=0;
        if(mBoard[14]!=0){
            if(mBoard[roll] < -1){
                return 0;
            }
        }
        else{ while(i<=12){
            if (mBoard[roll] < -1){
                return 0;
            }
            i++;
        }
        }
    }
    if(mPlayer==-1){
        int i=12;
        if((mBoard[15])!=0){
            if(mBoard[13-roll] > 1){
                return 0;
            }
        }
        else{ while(i>=0){
            if (mBoard[i-roll] < 1){
                return 1;
            }
            i--;
        }
        }
    }
    return 1;
}
/* isLegalMove checks the players move choice. the variability that is
 * accounted for with while loops in anyLegalMove is replaced by the
 * integer start, which represents the user's move choice, and checks
 * that move with the same algorithmic approach */
int isLegalMove(int mPlayer, int *mBoard, int roll, int start){
    if(mPlayer==1 ){
        if(mBoard[14]!=0){
            if(mBoard[roll] >= -1){
                return 1;
            }
        }
    }
    if (start<1 || start>12){
        return 0;
    }
    if((start+roll)>13){
        int i=0;
        while(i<start){
            if((start-i)!=0){
                return 0;
            }
            i++;
        }
        return 1;
    }
    
    if(mBoard[start]>=1){
        if(mBoard[start+roll] >= -1){
            return 1;
        }
    }
    
    
    if(mPlayer==-1){
        if(mBoard[15]!=0){
            if(mBoard[12-roll] <= 1){
                return 1;
            }
        }
        if (start<1 || start>12){
            return 0;
        }
        if((start-roll)<0){
            int i=0;
            while(i>start){
                if((i)!=0){
                    return 0;
                }
                i--;
            }
            return 1;
        }
        
        if(mBoard[start]<=-1){
            if(mBoard[start-roll] <= 1){
                return 1;
            }
            return 0;
        }
    }
}
/*doMove occurs only when anyLegalMove and isLegalMove are satisfied.
 It "moves" a checker to another position in accordance with isLegalMove
 by subtracting from its initial location and adding to its new location,
 as well as moving pieces to jail.*/
void doMove(int mPlayer, int *mBoard, int roll, int start){
    if(mPlayer==1){
        if(mBoard[start+roll]==-1){
            mBoard[15]-=1;
            mBoard[start+roll]+=1;
        }
        *(mBoard+start)-=1;
        *(mBoard+start+roll)+=1;
        
    }
    if(mPlayer==-1){
        if(mBoard[start-roll]==1){
            mBoard[14]+=1;
            mBoard[start-roll]-=1;
        }
        *(mBoard+start)+=1;
        *(mBoard+start-roll)-=1;
    }
    return;
}
/*jailBreak happens when a piece is eligible to be moved out of jail in accordance
 with isLegalMove and anyLegalMove using the same mechanics as doMove*/
void jailBreak(int mPlayer, int *mBoard, int roll){
    if(mPlayer==1){
        if(mBoard[roll]==-1){
            mBoard[15]-=1;
            mBoard[roll]+=1;
        }
        mBoard[roll]+=1;
        mBoard[14]-=1;
    }
    if(mPlayer==-1){
        if(mBoard[13-roll]==1){
            mBoard[14]+=1;
            mBoard[13-roll]-=1;
        }
        mBoard[13-roll]-=1;
        mBoard[15]+=1;
    }
    return;
}


