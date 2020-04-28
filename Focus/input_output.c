//
// Created by Lili on 26/03/2020.
//

//
// Created by Lili on 24/03/2020.
//

#include <stdio.h>
#include "input_output.h"
#include <stdlib.h>

extern int numRedSquares;  //global variables from main
extern int numGreenSquares;

/* Function to print the board:
 * Invalid Squares are printed as | - |
 * Valid empty squares are printed as |   |
 * Valid squares with a GREEN piece are printed as | G |
 * Valid squares with a RED piece are printed as | R | */

void print_board(square board[BOARD_SIZE][BOARD_SIZE]){
    printf("\n****** The Board ******\n");
    for(int i = 0; i < BOARD_SIZE; i ++){
        for (int j = 0; j < BOARD_SIZE; j++){
            if(board[i][j].type == VALID) {
                if(board[i][j].stack == NULL)
                    printf("|   ");
                else{
                    if (board[i][j].stack->p_color == GREEN)
                        printf("| G ");
                    else printf("| R ");
                }
            }
            else
                printf("| - ");
        }
        printf("|\n");
    }
}

void printBoardStacks(square board[BOARD_SIZE][BOARD_SIZE]){  //function prints the board along with top piece of the stack and the number of pieces in the stack
    int rowNum=0, colNum=0;
    printf("\n****** The Board ******\n      0      1      2      3      4      5      6      7  \n");
    for(int i = 0; i < BOARD_SIZE; i ++){
        printf("%d  ", i);
        for (int j = 0; j < BOARD_SIZE; j++){
            if(board[i][j].type == VALID) {
                if(board[i][j].stack == NULL)
                    printf("|   (%d)", board[i][j].num_pieces);
                else{
                    if (board[i][j].stack->p_color == GREEN)
                        printf("| G (%d)", board[i][j].num_pieces);
                    else printf("| R (%d)", board[i][j].num_pieces);
                }
            }
            else
                printf("| -  - ");
        }
        printf("|\n");
    }
}

void turn(color playerColor, char playerColorStr[], player players[], int playerNum, square board[BOARD_SIZE][BOARD_SIZE]){
    int choice=0;   //keeps track of player choice
    int validChoice=0;   //signals if choice is valid or not
    int row1, col1, row2, col2;   //coordinates of the current piece/stack(1) and where it will be moved(2)
    int* row2Ptr=&row2, *col2Ptr = &col2;  //pointers to destination coordinates
    player* playerPtr=&players[playerNum];

    //while loop for selected piece(to be moved/placed)
    while(!(validChoice)) {   //loops until a valid choice/square is chosen
        printf("\n%s's(%s) turn(you have %d reserved pieces):\n", players[playerNum].name, playerColorStr, players[playerNum].numPiecesSaved);  //prints current player's name and how many reserved pieces they have

        ///printf("Enter 1 to select a piece/stack from the board to move or enter 2 to place a reserved piece on the board: ");  //(player's choice) !!!!!!!TAKE CARE OF INFI LOOP WHEN GEYTTING CHOICE!!!!
        while (choice != 1 && choice != 2) {
            printf("Enter 1 to select a piece/stack from the board to move or enter 2 to place a reserved piece on the board:\n");  //(player's choice)
            scanf("%d", &choice);
        }
        switch(choice) {   //switch to take care of choices and ensure validity
            case 1:
                  do{
                    printf("Enter the coordinates of the piece/stack you want to move(the coordinates of the very top left square would be 0,0 (row, column)):\n");  //receives coordinates of selected piece/stack
                    scanf(" %1d%*c %1d", &row1, &col1);
                    if(row1<0 || col1<0 || row1>=BOARD_SIZE || col1>=BOARD_SIZE || board[row1][col1].type != VALID || board[row1][col1].num_pieces==0 || (*board[row1][col1].stack).p_color != playerColor){   //if given coordinates are invalid, prints appropriate message to the user
                        printf("Invalid coordinates given, please try again:\n");
                        //choice = 0; //reinitialising choice
                    }
                    if(players[playerNum].player_color == RED){
                        if(numRedSquares==0){
                            choice=2;
                        }
                    } else if (numGreenSquares==0){
                        choice=2;
                    }
                  }while((((row1<0 || row1>=BOARD_SIZE) || (col1<0 || col1>=BOARD_SIZE)) || board[row1][col1].type != VALID || board[row1][col1].num_pieces==0) || (*board[row1][col1].stack).p_color != playerColor);  //loops while given coordinates are invalid,for a coordinate to be valid it must be in the correct range, valid and have either a top piece the same colour as the player and not be empty
                validChoice=1;  //signals valid choice
                break;
            case 2:
                validChoice = 1;   //assumes valid choice, player has at least 1 reserved piece
                if(players[playerNum].numPiecesSaved == 0){   //if choice not valid prints message and sets validChoice to zero
                    printf("Invalid choice, player currently has 0 reserved pieces, please choose a valid piece/stack on the board to move:");
                    validChoice=0;
                    choice = 1; //reinitialisng choice
                }
                break;
        }
    }

    validChoice=0;  //reinitialising validChoice

    //while loop for destination
    while(!(validChoice)) {  //loops until a valid choice/square is chosen
        switch(choice) {   //switch to take care of choices and ensure validity
            case 1:
                do{   ////FIXXXXX DIDDNT WORK WHEN DESTINATION WAS EMPTY!!!!!!!
                    dest(row1, col1, row2Ptr, col2Ptr, board);  //destination function, handles calculation of destination square
                    if(row2<0 || col2<0 || row2>=BOARD_SIZE || col2>=BOARD_SIZE || board[row2][col2].type != VALID /*&& ( (*board[row2][col2].stack).p_color != playerColor || board[row2][col2].num_pieces!=0)*/){   //if given coordinates are invalid, prints appropriate message to the user
                        printf("Invalid move, please try again:\n");
                    }
                }while(row2<0 || col2<0 || row2>=BOARD_SIZE || col2>=BOARD_SIZE || board[row2][col2].type != VALID /*&& ( (*board[row2][col2].stack).p_color != playerColor || board[row2][col2].num_pieces!=0 )*/ );  //loops while given coordinates are invalid,for a destination coordinate to be valid it must be in the correct range, and valid
                validChoice=1;  //sets valid choice to 1(true)
                moveBoard(row1, col1, row2, col2, playerPtr, board);
                break;
            case 2:
                do{
                    printf("Enter the coordinates of the square where you want to place the piece(the coordinates of the very top left square would be 0,0 (row, column)):\n");  //receiving destination coordinates of reserved piece
                    scanf(" %1d%*c %1d", &row2, &col2);
                    if(row2<0 && col2<0 && row2>=BOARD_SIZE && col2>=BOARD_SIZE && board[row2][col2].type != VALID /*&& ( (*board[row2][col2].stack).p_color != playerColor || board[row2][col2].num_pieces!=0)*/){   //if given coordinates were invalid, prints appropriate message to the user
                        printf("Invalid coordinates given, please try again:\n");
                    }
                }while(row2<0 && col2<0 && row2>=BOARD_SIZE && col2>=BOARD_SIZE && board[row2][col2].type != VALID /*&& ( (*board[row2][col2].stack).p_color != playerColor || board[row2][col2].num_pieces!=0 ) */);  //loops while given coordinates are invalid,for a destination coordinate to be valid it must be in the correct range and valid
                validChoice=1;  //sets valid choice to 1(true)
                place(row2, col2, playerPtr,board);
                break;
        }
    }

}
////FIXX FOR WHEN MORE THAN 1 DIRECTION!!!!!
void dest(int row1, int col1, int*row2Ptr, int* col2Ptr, square board[BOARD_SIZE][BOARD_SIZE]){  //destination function, calculates destination coordinates
    char inputStr[21] = "";   //variable to hold the letters
    char c; //variable that holds each individual letter
    int moves=0;  //keeps track of amount of moves made
    int numPieces  = board[row1][col1].num_pieces;   //saves number of pieces/max moves to a variable
    int letterNum=0;
    *row2Ptr = row1;   //(saves the current position of the piece to the destination position pointer variables)
    *col2Ptr = col1;
    printf("Enter a series of up to %d letters(directions)(u(up,^), d(down,v), l(left,<), r(right,>)) to move your piece/stack, currently at %d,%d, to the desired coordinates(e.g. u,l,l):\n", numPieces, row1, col1);  //instructs player on how to enter their moves


    getchar();  //opening stdin
    gets(inputStr);
    while (letterNum<sizeof(inputStr)) {  ///see if Stdin needs to be "cleared"
        c = inputStr[letterNum];
        if (moves < numPieces) {
            switch (c) {  //increments or decrements the row and column variables accordingly depending on the letter
                case 'u':
                    (*row2Ptr)--;
                    moves++;
                    break;
                case 'd':
                    (*row2Ptr)++;
                    moves++;
                    break;
                case 'l':
                    (*col2Ptr)--;
                    moves++;
                    break;
                case 'r':
                    (*col2Ptr)++;
                    moves++;
                    break;
            }
        }
        letterNum++;
    }

}


void moveBoard(int row1, int col1, int row2, int col2, player* playerPtr,square board[BOARD_SIZE][BOARD_SIZE]){  //add choice variable
    int totPieces=0, pieceNum=1;  //pieceNum is initialised to 1 as piece 1(the top piece) of the stack is the first piece we look at
    piece* currPiece;

    if(board[row2][col2].stack != NULL) {  //checking if square is not empty
        if ((*board[row2][col2].stack).p_color == RED) {
            numRedSquares--;
        } else if ((*board[row2][col2].stack).p_color == GREEN) {
            numGreenSquares--;
        }
    }

    totPieces = (board[row1][col1].num_pieces + board[row2][col2].num_pieces);

    currPiece = board[row1][col1].stack;  //current piece is top of stack to be moved

    while(pieceNum < (board[row1][col1].num_pieces)){
        currPiece = (*currPiece).next;
        pieceNum++;
    }

    ////printf("\n\n%d\n\n", totPieces);

    (*currPiece).next = board[row2][col2].stack;
    board[row2][col2].stack = board[row1][col1].stack;
    board[row1][col1].stack = NULL;
    board[row1][col1].num_pieces = 0;
    board[row2][col2].num_pieces = totPieces;


    if(board[row2][col2].num_pieces > 5){
        pieceNum = 1;
        currPiece = board[row2][col2].stack;
        while(pieceNum < 5){
            currPiece = (*currPiece).next;
            pieceNum++;
        }
        removeGrFive(row2, col2, currPiece, playerPtr, board);
    }



}

void place(int row2, int col2, player* playerPtr, square board[BOARD_SIZE][BOARD_SIZE]){
    int pieceNum=1;
    piece* currPiece;
    piece* resPiece = (piece*)malloc(sizeof(piece));

    if(board[row2][col2].stack != NULL) {  //checking if square is not empty
        if ((*board[row2][col2].stack).p_color == RED) {
            numRedSquares--;
        } else if ((*board[row2][col2].stack).p_color == GREEN) {
            numGreenSquares--;
        }
    }

    (*resPiece).p_color = (*playerPtr).player_color;
    (*resPiece).next = board[row2][col2].stack;
    board[row2][col2].stack = resPiece;

    (board[row2][col2].num_pieces)++;
    ((*playerPtr).numPiecesSaved)--;

    if((*resPiece).p_color == RED){
        (numRedSquares)++;
    }
    else{
        (numGreenSquares)++;
    }

    if(board[row2][col2].num_pieces > 5){
        currPiece = board[row2][col2].stack;
        while(pieceNum < 5){
            currPiece = (*currPiece).next;
            pieceNum++;
        }
        removeGrFive(row2, col2, currPiece, playerPtr, board);
    }
}

void removeGrFive(int row2, int col2, piece* pieceFive, player* playerPtr, square board[BOARD_SIZE][BOARD_SIZE]){  //add in functionality for captured and saved pieces and num pieces -5
    piece* curr, *toRemove;
    curr = (*pieceFive).next;
    while(curr!=NULL){
        toRemove = curr;
        curr = (*curr).next;
        if((*toRemove).p_color == (*playerPtr).player_color){
            ((*playerPtr).numPiecesSaved)++;
        }
        else{
            ((*playerPtr).numPiecesCap)++;
        }
        free(toRemove);
        (board[row2][col2].num_pieces)--;
    }
    (*pieceFive).next = NULL;
}

int winner(player playerW[]){  //function that checks if the game has been won, returns 0 for Red, 1 for Green, 2 for no winner
    int loser;
    for(loser=0;loser<PLAYERS_NUM;loser++){
        if(playerW[loser].numPiecesSaved == 0){
            break;
        }
    }

    switch(loser){
        case 0:
            if(numRedSquares!=0){
                loser=2;
            }
            break;
        case 1:
            if(numGreenSquares != 0){
                loser=2;
            }
            break;
    }

    return loser;
}