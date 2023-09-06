#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <map>


#include "buffer.hpp"



class Board {
    public:
        Board();
        int getWidth();
        int getHeight();
        int getGrid(int w, int h);
        void setGrid(int, int, int);
        void drawBoard(Buffer, int);
        void drawBoard(Buffer, int[4][2]);
        std::string getColour(std::string);
        std::string player1(); //player 1
        std::string player2(); //player 2 (bot)
        std::string player1(std::string colour); //custom colour
        std::string player2(std::string colour);
        std::string player1(std::string colour, std::string icon); //custom colour and icon
        std::string player2(std::string colour, std::string icon);
        std::string getPlayer1Colour();
        std::string getPlayer2Colour();
        void setPlayer1Colour(std::string);
        void setPlayer2Colour(std::string);
        std::string getPlayer1Icon();
        std::string getPlayer2Icon();
        void setPlayer1Icon(std::string);
        void setPlayer2Icon(std::string);
        int tops[7]; //height of each column
   
        int columnSelect;
        void updateBoard(Buffer, int);
        
        //int getMove();

    private:
        const int width = 7;
        const int height = 6;
        int grid[7][6];
        std::map<std::string, std::string>Colours;
        std::string player1Colour;
        std::string player2Colour;
        std::string player1Icon;
        std::string player2Icon;
        std::string getColumnSelectorString(int, std::string);
        


};



