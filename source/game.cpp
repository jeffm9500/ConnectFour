#include "game.hpp"

Game::Game(Buffer b) {
    Board board = Board();
    buffer = b;
    turns = 0;
    playerTurn = 1;
    Game *self = this;
    playingGame = true;
}

void Game::playGame() {

    
    while (playingGame) {
        turns++;
        switch(playerTurn) {
            case 1:
                // user's turn:
                getMove();
                board.drawBoard(buffer, playerTurn);
                break;
            case 2:
                
                getMove();
                board.drawBoard(buffer, playerTurn);
                break;
        }

    }

    


    /*
    for (int i=0; i<board.getWidth();i++){
        for (int j=0; j<board.getHeight();j++){
            if (j == i) 
                board.setGrid(i, j, 2);
            if (i == 4)
                board.setGrid(i, j, 1);
        }
    }
    */
}

void Game::getMove() {
    std::cout << "input: " << std::endl;
    int c;
    int temp;
    int winner = 0; //value changes based on checkWinner()
    int chain[4][2];
    int i,j,k;
    
    // clear key buffer
    
    c = getch();
        
    

    std::cout << "Entered character is "<< char(c) << " and it's ASCII value is " << int(c) << std::endl;;

    switch(c){
        case KEY_ENTER:
        case KEY_DOWN:
        case KEY_S:
            // down (enter move)
            std::cout << std::endl << "Down" << std::endl;   // key down
            std::cout << board.tops[board.columnSelect] << std::endl;

            if (playerTurn == 1) {
                // check if move can be done
                if (board.tops[board.columnSelect] < board.getHeight()){
                    // do move
                    board.setGrid(board.columnSelect, board.getHeight()-1, playerTurn);
                    board.updateBoard(buffer, playerTurn);
                    winChain data = checkWinner();
                    winner = data.winner;
                    for (k=0;i<4;k++) {
                        for (j=0;j<2;j++){
                            chain[k][j] = data.chain[k][j];
                        }
                    }
                    if (winner) {
                        board.drawBoard(buffer, chain);
                    }
                    board.tops[board.columnSelect]++;

                    
                    std::cout << "Turn played" << std::endl;

                }
                playerTurn = 2;
            } else {
                // check if move can be done
                if (board.tops[board.columnSelect] < board.getHeight()){
                    // do move
                    board.setGrid(board.columnSelect, board.getHeight()-1, playerTurn);
                    board.updateBoard(buffer, playerTurn);
                    checkWinner();
                    board.tops[board.columnSelect]++;

                    board.drawBoard(buffer, playerTurn);
                    std::cout << "Turn played" << std::endl;

                }
                playerTurn = 1;
            }
            break;
        case KEY_LEFT:
        case KEY_A:
            // move left
            std::cout << std::endl << "Left" << std::endl;   // key left
            temp = (board.columnSelect-1) % board.getWidth();
            board.columnSelect = (temp >= 0) ? temp : (temp + 7);
            std::cout << board.columnSelect << std::endl;
            break;
        case KEY_RIGHT:
        case KEY_D:
            // move right
            std::cout << std::endl << "Right" << std::endl;   // key right
            board.columnSelect = (board.columnSelect+1) % board.getWidth();
            std::cout << board.columnSelect << std::endl;
            break;
        case KEY_ESC:
        std::cout << "Ending game" << std::endl;
            // end the game
            endGame();
            return;
            //break;
            
        
    }
    
    return;
}


void Game::endGame() {
    playingGame = false;
}


winChain Game::checkWinner() {
    // check for 4 in a row
    winChain returnData;    
    for (auto &i : returnData.chain) {
        i[0] = 0;
        i[1] = 0;
    }
    returnData.winner = 0;
    
    
    
    int streakCount[2] = {0, 0};
    // 2 players, 4 tiles of 2 coordinates
    int chain[2][4][2];
    int current, next;
    // check columns
    for (int w=0;w<board.getWidth();w++) {
        for (int h=0;h<board.getHeight();h++) {
            current = board.getGrid(w, h);
            // check if its a player
            if (current != 0) {
                //increase current player count
                streakCount[current-1]++;
                // reset other player's streak count
                streakCount[(current == 1 ? 1 : 0)] = 0;
                for (int i=1;i<=4;i++){
                    if (streakCount[current-1] == i) {
                        chain[current-1][i-1][0] = w;
                        chain[current-1][i-1][1] = h;
                        if (streakCount[current-1] == 4) {
                            winGame(current);
                            returnData.winner = current;
                            for (int k=0;i <4;k++) {
                                for (int j=0;j<2;j++){
                                    returnData.chain[k][j] = chain[current-1][k][j];
                                }
                            }
                            return returnData;
                        }
                    }
                }
            }
        }
    }
    streakCount[0] = 0;
    streakCount[1] = 0;
    // check rows
    for (int h=0;h<board.getHeight();h++) {
        for (int w=0;w<board.getWidth();w++) {
            current = board.getGrid(w, h);
            // check if its a player
            if (current != 0) {
                //increase current player count
                streakCount[current-1]++;
                // reset other player's streak count
                streakCount[(current == 1 ? 1 : 0)] = 0;
                for (int i=1;i<=4;i++){
                    
                    if (streakCount[current-1] == i) {
                        chain[current-1][i-1][0] = w;
                        chain[current-1][i-1][1] = h;
                        if (streakCount[current-1] == 4) {
                            winGame(current);
                            returnData.winner = current;
                            for (int k=0;i <4;k++) {
                                for (int j=0;j<2;j++){
                                    returnData.chain[k][j] = chain[current-1][k][j];
                                }
                            }
                            return returnData;
                        }
                    }
                }
            }
        }
    }
    streakCount[0] = 0;
    streakCount[1] = 0;

    // check diagonal
    // go row by row starting from the bottom up
    // check slope: /
    for (int h=0;h<std::min(board.getHeight()-3, 0);h++) {
        for (int w=0;w<std::min(board.getWidth()-3, 0);w++) {
            current = board.getGrid(w, h);
            // check if its a player
            if (current != 0) {
                // increase current player count
                int i = ++streakCount[current-1];
                // reset other player's streak count
                streakCount[(current == 1 ? 1 : 0)] = 0;
                chain[current-1][0][0] = w;
                chain[current-1][0][1] = h;
                
                while (streakCount[current-1] > 0) {
                    i = streakCount[current-1];
                    if (i >= 4) {
                        winGame(current);
                        returnData.winner = current;
                        for (int k=0;i <4;k++) {
                            for (int j=0;j<2;j++){
                                returnData.chain[k][j] = chain[current-1][k][j];
                            }
                        }
                        return returnData;
                    } else {
                        next = board.getGrid(w+1, h+1);
                        if (next != 0) {
                            // streak continues
                            chain[current-1][i-1][0] = w;
                            chain[current-1][i-1][1] = h;
                            streakCount[current-1]++;
                            w++;
                            h++;
                        } else {
                            streakCount[current-1] = 0;
                        }
                    }
                }   
            } else {
                streakCount[0] = 0;
                streakCount[1] = 0;
            }   

        }

        /* check slope: \
        */

    }


    return returnData;
}


void Game::winGame(int player) {
    endGame();
    std::cout << "Player " << player << " wins!" << std::endl;
}