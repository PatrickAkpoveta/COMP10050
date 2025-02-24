//
// Created by Lili on 26/03/2020.
//

//
// Created by Lili on 24/03/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include "game_init.h"
extern int numRedSquares;  //global variables from main
extern int numGreenSquares;

void initialize_players(player players[PLAYERS_NUM]){
    for(size_t i=0;i<PLAYERS_NUM;i++){
        switch(i){   //switch statement so player colours can be set
            case 0: //(initialisng player)
                players[i].player_color = RED;
                printf("\nEnter the name of player 1(Red)(Max 20 characters)(Red plays first):\n");
                scanf("%s", players[i].name); //receiving player name
                players[i].numPiecesCap = 0;
                players[i].numPiecesSaved = 0;
                break;
            case 1:
                players[i].player_color = GREEN;
                printf("Enter the name of player 2(Green)(Max 20 characters):\n");
                scanf("%s", players[i].name);
                players[i].numPiecesCap = 0;
                players[i].numPiecesSaved = 0;
                break;
        }
    }

}

//Set Invalid Squares (where it is not possible to place stacks)
set_invalid(square * s){
s->type = INVALID;
s->stack = NULL;
s->num_pieces = 0;
}

//Set Empty Squares (with no pieces/stacks)
set_empty(square * s){
s->type = VALID;
s->stack = NULL;
s->num_pieces = 0;
}

//Set squares  with a GREEN piece
set_green(square * s){
s->type = VALID;
s->stack = (piece *) malloc (sizeof(piece));
s->stack->p_color = GREEN;
s->stack->next = NULL;
s->num_pieces = 1;
numGreenSquares++;  //incrementing numGreenSquares to keep track of how many squares there are with a green top piece
}

//Set squares with a RED piece
set_red(square * s){
s->type = VALID;
s->stack = (piece *) malloc (sizeof(piece));
s->stack->p_color = RED;
s->stack->next = NULL;
s->num_pieces = 1;
numRedSquares++;     //incrementing numRedSquares to keep track of how many squares there are with a red top piece
}

//initializes the board
void initialize_board(square board [BOARD_SIZE][BOARD_SIZE]){

    for(int i=0; i< BOARD_SIZE; i++){
        for(int j=0; j< BOARD_SIZE; j++){
            //invalid squares
            if((i==0 && (j==0 || j==1 || j==6 || j==7)) ||
               (i==1 && (j==0 || j==7)) ||
               (i==6 && (j==0 || j==7)) ||
               (i==7 && (j==0 || j==1 || j==6 || j==7)))
                set_invalid(&board[i][j]);

            else{
                //squares with no pieces
                if(i==0 || i ==7 || j==0 || j == 7)
                    set_empty(&board[i][j]);
                else{
                    //squares with red pieces
                    if((i%2 == 1 && (j < 3 || j> 4)) ||
                       (i%2 == 0 && (j == 3 || j==4)))
                        set_red(&board[i][j]);
                        //green squares
                    else set_green(&board[i][j]);
                }
            }
        }


    }


}

