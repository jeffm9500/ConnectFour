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
        inline int getWidth() {return width;}
        inline int getHeight() {return height;}
        inline int getGrid(int w, int h) {return grid[w][h];}
        inline void setGrid(int w, int h, int value){grid[w][h] = value;}

        int tops[7]; //height of each column

        int columnSelect;
        int updateBoard(Buffer*, int);
        void resetBoard();
        
        //int getMove();

    private:
        const int width = 7;
        const int height = 6;
        int grid[7][6];

       
        


};



