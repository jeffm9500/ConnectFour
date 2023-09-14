#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <math.h>

#include "board.hpp"
#include "buffer.hpp"
#include "gamestate.hpp"


#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_W 119
#define KEY_A 97 //65
#define KEY_S 115 //83
#define KEY_D 100 //68
#define CTRL_C 3 //ctrl + c (to break out of loop)

// TODO:

// add more colours
// - light blue
// - purple
// - fix white for player - investigate
// remove green as a player colour option
// add no more valid moves (game board full) outcome


// add AI


// struct used to save the chain of 4 used to win the game
// winner=0 if no current winner
struct winChain {
    int winner;
    int chain[4][2];
};

// used to highlight active selection in start menu
enum startSelect {
    Start_Play,
    Start_HowToPlay,
    Start_Customize,
    Start_Quit
};
// used to iterate thru selections
inline startSelect &operator++(startSelect &s, int) { 
    if (s == Start_Quit) {
        s = Start_Play;
    } else {
        s = static_cast<startSelect>(s+1);
    }
    return s;
}
inline startSelect &operator--(startSelect &s, int) {
    if (s == Start_Play) {
        s = Start_Quit;
    } else {
        s = static_cast<startSelect>(s-1);
    }
    return s;
}

// customize screen
enum customizeSelect {
    Customize_p1Icon,
    Customize_p1Colour,
    Customize_p2Icon,
    Customize_p2Colour,
    Customize_Play,
    Customize_Back
};
inline customizeSelect &operator++(customizeSelect &s, int) { 
    if (s == Customize_Back) {
        s = Customize_p1Icon;
    } else {
        s = static_cast<customizeSelect>(s+1);
    }
    return s;
}
inline customizeSelect &operator--(customizeSelect &s, int) {
    if (s == Customize_p1Icon) {
        s = Customize_Back;
    } else {
        s = static_cast<customizeSelect>(s-1);
    }
    return s;
}

// end menu
enum endSelect {
    End_Rematch,
    End_MainMenu,
    End_Quit    
};
inline endSelect &operator++(endSelect &s, int) { 
    if (s == End_Quit) {
        s = End_Rematch;
    } else {
        s = static_cast<endSelect>(s+1);
    }
    return s;
}
inline endSelect &operator--(endSelect &s, int) {
    if (s == End_Rematch) {
        s = End_Quit;
    } else {
        s = static_cast<endSelect>(s-1);
    }
    return s;
}


// forward declaration to avoid circular dependency error
class GameState;

class Game {
    public:
        Game();
        void getMove();
        void playGame();
        inline Buffer *getBuffer()  {return buffer;}
        inline Board *getBoard()  {return board;}
        inline void setBuffer(Buffer b) {*buffer = b;};
        int playerTurn; // 1 for player 1, 2 for player 2

        winChain checkWinner();
        winChain winnerChain;
        winChain getWinningChain();

        // draw functions
        void drawStartScreen();
        void drawCustomizeScreen();
        void drawPlayScreen();
        void drawEndScreen();
        void drawHowToScreen();

        std::string getColumnSelectorString(int, std::string);

        inline GameState *getCurrentState() const { return currentState; }
        void setState(GameState &newState);
        int turns; // currently not used
        bool playingGame; // can i remove this somehow?
        bool quitGame = false; // can I remove this somehow?
        
        // screen selections
        enum startSelect startScreenSelection;
        enum customizeSelect customizeScreenSelection;
        enum endSelect endScreenSelection;

        // board colours
        std::string getBackgroundColour() const {return backgroundColour;}
        std::string getForegroundColour() const {return foregroundColour;}
        void setBackgroundColour(std::string c)  {backgroundColour = c;}
        void setForegroundColour(std::string c)  {foregroundColour = c;}
        // player customization
        std::string getColour(std::string);
        std::string getPlayer1(); //player 1 coloured icon
        std::string getPlayer2(); //player 2 (bot) coloured icon
        std::string getPlayer1(std::string colour); //player 1 icon with custom colour
        std::string getPlayer2(std::string colour); //player 2 icon with custom colour
        std::string getPlayer1Colour();
        std::string getPlayer2Colour();
        void setPlayer1Colour(std::string);
        void setPlayer2Colour(std::string);
        std::string getPlayer1Icon();
        std::string getPlayer2Icon();
        void setPlayer1Icon(std::string);
        void setPlayer2Icon(std::string);
        // array of colour options (dynamically exclude player colours)
        std::vector<std::string> PlayerColours;
        std::vector<std::string> PlayerColoursFormatted;
        std::vector<std::string> PlayerColoursSelected;
        int colourOffset[2] = {0,1};
        // array of icon options
        std::vector<std::string> PlayerIcons;
        int iconOffset[2] = {0,1};


    private:
        GameState *currentState;
        Buffer *buffer;
        Buffer trueBuffer = Buffer();
        Board *board;
        Board trueBoard = Board();
        

        // player customization
        std::map<std::string, std::string> Colours;
        std::string player1Colour;
        std::string player2Colour;
        std::string player1Icon;
        std::string player2Icon;
        std::string backgroundColour;
        std::string foregroundColour;

};