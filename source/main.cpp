#include "buffer.hpp"
#include "board.hpp"
#include "game.hpp"




/*
TODO:

- add bot AI
- remove debug text
- polish start/end game text
- add different symbol options (+ colours)





*/


using namespace std;

int main() {

    
    //Buffer buffer;
    Game game = Game();  

    //system("cls");
    /*
    std::cout << "Enter a key" << std::endl;
    char c = getch();
    std::cout << c << std::endl;
    */
    



    //game.board.drawBoard(buffer, game.playerTurn);

    game.playGame();
    
    



}