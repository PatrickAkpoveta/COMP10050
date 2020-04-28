//
// Created by Lili on 26/03/2020.
//

#include <stdio.h>

#include "input_output.h"

int numRedSquares=0, numGreenSquares=0;  //declaring global variables that keep track of how many squares there are with either red or green piece on top

int main() {

    // declaration of the players and the board
    player players[PLAYERS_NUM];
    square board[BOARD_SIZE][BOARD_SIZE];
    char playerColorStrArr[2][6] = {"Red", "Green"};
    int n,round=0,loser=2;

    initialize_players(players);

    initialize_board(board);

    print_board(board);
    printBoardStacks(board);
    printf("\nredSquares- %d, greenSquares - %d\n", numRedSquares, numGreenSquares);

    /*turn(players[0].player_color, "Red", players, 0, board);
    printBoardStacks(board);
    printf("r - %d, g - %d", numRedSquares, numGreenSquares);

    turn(color playerColor, char playerColorStr[], player players[], int playerNum, square board[BOARD_SIZE][BOARD_SIZE])*/

    while(loser != 0 && loser != 1){
        n = round%2;
        turn(players[n].player_color, playerColorStrArr[n], players, n, board);
        printBoardStacks(board);
        printf("\nredSquares- %d, greenSquares - %d\n", numRedSquares, numGreenSquares);
        loser = winner(players);
        round++;
    }
    switch(loser){
        case 0:
            printf("\n%s(%s) wins!\nTotal pieces captured by %s: %d\n", players[1].name, playerColorStrArr[1], players[1].name, players[1].numPiecesCap);
            break;
        case 1:
            printf("\n%s(%s) wins!\nTotal pieces captured by %s: %d\n", players[0].name, playerColorStrArr[0], players[0].name, players[0].numPiecesCap);
            break;
    }
    return 0;
}
