#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <math.h>
#include "board.hpp"
#include "buffer.hpp"

#define KEY_UP 72 //unused
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_A 97 //65
#define KEY_S 115 //83
#define KEY_D 100 //68
#define CTRL_C 3 //ctrl + c (to break out of loop)

struct winChain {
    int winner;
    int chain[4][2];
};

class Game {
    public:
        Game(Buffer);
        Board board;
        void playGame();
        void getMove();
        void endGame();
        int playerTurn; //1 for player 1, 2 for player 2
        winChain checkWinner();
        void winGame(int);
        Buffer buffer;
    private:
        int turns;
        bool playingGame;
        

};
