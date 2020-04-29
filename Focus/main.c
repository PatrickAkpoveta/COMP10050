//
// Created by Lili on 26/03/2020.
//

#include <stdio.h>

#include "input_output.h"

int numRedSquares=0, numGreenSquares=0;  //declaring global variables that keep track of how many squares there are with either a red or green piece on top

int main() {

    // declaration of the players and the board
    player players[PLAYERS_NUM];
    square board[BOARD_SIZE][BOARD_SIZE];
    char playerColorStrArr[2][6] = {"Red", "Green"};  //declaration of array that holds string form of colours
    int n,round=0,loser=2;   //n, signals which player, round keeps track of which round/turn it is and allows n to be calculated, loser keeps track of if a win has occured and who the winner is

    initialize_players(players);  //initialising players

    initialize_board(board);    //initialising board

    //prints the board along with how many squares have a top red piece or a top green piece respectively
    printBoardStacks(board);
    printf("\nredSquares- %d, greenSquares - %d\n", numRedSquares, numGreenSquares);


    while(loser != 0 && loser != 1){   //loops until loser either equal 0 or 1(winner determined)
        n = round%2;  //calculates which player based on the modulo of the round number, either 0(red) or 1(green)
        turn(players[n].player_color, playerColorStrArr[n], players, n, board);     //calling "turn" function
        printBoardStacks(board);   //printing the board along with how many squares have a top red piece or a top green piece respectively
        printf("\nredSquares- %d, greenSquares - %d\n", numRedSquares, numGreenSquares);
        loser = winner(players);   //checks if winner can be determined
        round++;  //increments round(next player's turn)
    }
    switch(loser){   //depending on the value of loser, appropriate prints the winner message
        case 0:
            printf("\n%s(%s) wins!\nTotal pieces captured by %s: %d\n", players[1].name, playerColorStrArr[1], players[1].name, players[1].numPiecesCap);
            break;
        case 1:
            printf("\n%s(%s) wins!\nTotal pieces captured by %s: %d\n", players[0].name, playerColorStrArr[0], players[0].name, players[0].numPiecesCap);
            break;
    }
    return 0;
}
