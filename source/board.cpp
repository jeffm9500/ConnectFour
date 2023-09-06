#include "board.hpp"


Board::Board() {
    // set colours
    Colours["reset"]= "\033[0m";
    Colours["blue"]="\033[1;94m";
    Colours["red"]="\033[1;31m";
    Colours["white"]="\033[1;37m";
    Colours["white_bg"]="\033[47m";
    Colours["green"]="\033[1;32m";
    Colours["yellow"]="\033[1;33m";
    //Colours[""]="";

    // set grid (game board)
    for (int i=0; i<Board::getWidth();i++){
        for (int j=0; j<Board::getHeight();j++){
            grid[i][j] = 0;
        }
    }
    // default player colours
    player1Colour = getColour("yellow");
    player2Colour = getColour("red");
    player1Icon = "1";
    player2Icon = "2";

    for (auto &i: tops){
        i = 0;
    }
    columnSelect = 3; // default selection is middle of 7 (0 index)

}

inline int Board::getWidth() {
    return width;
}

int Board::getHeight() {
    return height;
}

int Board::getGrid(int w, int h) {
    return grid[w][h];
}

void Board::setGrid(int w, int h, int value) {
    grid[w][h] = value;
    return;
}

void Board::drawBoard(Buffer buffer, int playerTurn) {
    system("cls");
    buffer.clear();
    buffer << getColour("reset");
    std::string colour = (playerTurn == 1) ? getPlayer1Colour() : getPlayer2Colour();

    // add column selection
    buffer << getColumnSelectorString(columnSelect, colour);


    // draw top down, row by row
    for (int h=getHeight()-1; h>=0;h--){

        for (int w=-1; w<getWidth()+1;w++){

            if ((w == getWidth()) || (w == -1)) {
                // add border
                buffer << "| ";
            } else {
                // populate grid
                if (getGrid(w, h) == 1) {
                    // add player1's plays
                    buffer << player1();
                } else if (getGrid(w, h) == 2) {
                    // add player2's plays
                    buffer << player2();
                } else {
                    // add empty space
                    buffer << "-";
                }
                // add space between each character
                buffer << " ";
            }
        }
        // new row
        buffer << "\n";
    }
    // end of game board
    buffer << "-----------------\n";

    buffer.display();

}

void Board::drawBoard(Buffer buffer, int chain[4][2]){
    // chain should be a [4][2] array
    system("cls");
    buffer.clear();
    buffer << getColour("reset");

    // add column selection
    buffer << getColumnSelectorString(columnSelect, getColour("green"));
    bool isPartOfWinningChain = false;

    // draw top down, row by row
    for (int h=getHeight()-1; h>=0;h--){

        for (int w=-1; w<getWidth()+1;w++){

            if ((w == getWidth()) || (w == -1)) {
                // add border
                buffer << "| ";
            } else {
                // populate grid
                if (getGrid(w, h) == 1) {
                    // add player1's plays
                    // check winning chain
                    
                    for (int i=0;i<4;i++){
                        if (chain[i][0] == w && chain[i][1] == h) {
                            isPartOfWinningChain = true;
                        }
                    }
                    if (isPartOfWinningChain){
                        //std::cout << "colouring (" << w << ", " << h << ") green" << std::endl;
                        buffer << player1("green");
                        isPartOfWinningChain = false;
                    } else {
                        buffer << player1();
                    } 
                } else if (getGrid(w, h) == 2) {
                    // add player2's plays
                    // check winning chain
                    
                    for (int i=0;i<4;i++){
                        if (chain[i][0] == w && chain[i][1] == h) {
                            isPartOfWinningChain = true;
                        }
                    }
                    if (isPartOfWinningChain){
                        buffer << player2("green");
                        isPartOfWinningChain = false;
                    } else {
                        buffer << player2();
                    } 
                } else {
                    // add empty space
                    buffer << "-";
                }
                // add space between each character
                buffer << " ";
            }
        }
        // new row
        buffer << "\n";
    }
    // end of game board
    buffer << "-----------------\n";

    buffer.display();

}

std::string Board::getColour(std::string c) {
    return Colours[c];
}

std::string Board::player1() {
    return getPlayer1Colour() + "1" + getColour("reset");
}
std::string Board::player2() {
    return getPlayer2Colour() + "2" + getColour("reset");
}

std::string Board::player1(std::string colour){
    return getColour(colour) + "1" + getColour("reset");
}
std::string Board::player2(std::string colour){
    return getColour(colour) + "2" + getColour("reset");
}

std::string Board::player1(std::string colour, std::string icon){
    return getColour(colour) + icon + getColour("reset");
}
std::string Board::player2(std::string colour, std::string icon){
    return getColour(colour) + icon + getColour("reset");
}

std::string Board::getPlayer1Colour() {
    return player1Colour;
}
std::string Board::getPlayer2Colour() {
    return player2Colour;
}

std::string Board::getPlayer1Icon() {
    return player1Icon;
}
std::string Board::getPlayer2Icon() {
    return player2Icon;
}

void Board::setPlayer1Icon(std::string icon) {
    player1Icon = icon;
    return;
}
void Board::setPlayer2Icon(std::string icon) {
    player2Icon = icon;
    return;
}

void Board::setPlayer1Colour(std::string newColour) {
    player1Colour = newColour;
}

void Board::setPlayer2Colour(std::string newColour) {
    player2Colour = newColour;
}

std::string Board::getColumnSelectorString(int columnSelect, std::string colour) {

    std::string string;
    for (int i=0;i<=columnSelect;i++){
        string += "  ";
    }
    string += colour + "V\n" + getColour("reset");
    return string;
}


void Board::updateBoard(Buffer buffer, int playerTurn) {
    drawBoard(buffer, playerTurn);
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
                    updateBoard(buffer, playerTurn);
                    break;
                }
            }

        }
    }
    

    

    return;
}


