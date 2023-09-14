#include "board.hpp"


Board::Board() {

    // set grid (game board)
    for (int i=0; i<Board::getWidth();i++){
        for (int j=0; j<Board::getHeight();j++){
            grid[i][j] = 0;
        }
    }
    for (auto &i: tops){
        i = 0;
    }
    columnSelect = 3; // default selection is middle of 7 (0 index)
}

void Board::resetBoard() {
    // call constructor, but somehow dont leak memory
    // set grid (game board)
    for (int i=0; i<Board::getWidth();i++){
        for (int j=0; j<Board::getHeight();j++){
            grid[i][j] = 0;
        }
    }
    for (auto &i: tops){
        i = 0;
    }
    columnSelect = 3; // default selection is middle of 7 (0 index)
}


int Board::updateBoard(Buffer* buffer, int playerTurn) {
    // update gravity
    for (int h=getHeight()-1; h>0;h--){

        for (int w=0; w<getWidth();w++){
            if (getGrid(w, h) != 0) {
                // if grid spot not empty, check below it
                if (getGrid(w, h-1) == 0) {
                    // move down
                    setGrid(w, h-1, getGrid(w, h));
                    setGrid(w, h, 0);
                    
                    // draw new board
                    //drawBoard(buffer, playerTurn);
                    // something changed, so call updateBoard again
                    //updateBoard(buffer, playerTurn);
                    // while updates still need to occur, return 1
                    return 1;
                }
            }

        }
    }
    // when all updates are resolved, return 0
    return 0;
}


