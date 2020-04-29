
//
// Created by Lili on 24/03/2020.
//

#ifndef FOCUS_INPUT_OUTPUT_H
#define FOCUS_INPUT_OUTPUT_H

#endif //FOCUS_INPUT_OUTPUT_H

#include "game_init.h"

//Function to print the board
void print_board(square board[BOARD_SIZE][BOARD_SIZE]);

void printBoardStacks(square board[BOARD_SIZE][BOARD_SIZE]); //function to print the board along with the size of each stack

void turn(color playerColor, char playerColorStr[], player players[], int playerNum, square board[BOARD_SIZE][BOARD_SIZE]); //function that handles the turns of each player

void dest(int row1, int col1, int*row2Ptr, int* col2Ptr, square board[BOARD_SIZE][BOARD_SIZE]); //function used to calculate the destination of the piece/stack and ensure that this move is ((valid

void moveBoard(int row1, int col1, int row2, int col2, player* playerPtr,square board[BOARD_SIZE][BOARD_SIZE]);  //function that takes care of actual moving of stacks/pieces and the capturing and collecting/saving of pieces

void place(int row2, int col2, player* playerPtr, square board[BOARD_SIZE][BOARD_SIZE]);  //function used when adding/placing reserved pieces on the board

void removeGrFive(int row2, int col2, piece* pieceFive, player* playerPtr, square board[BOARD_SIZE][BOARD_SIZE]); //funcion to remove the bottom pieces of a stack of more than 5 pieces

int winner(player playerW[]); //function that checks if the game has been won, returns 0 for Red(loser), 1 for Green(loser), 2 for no winner