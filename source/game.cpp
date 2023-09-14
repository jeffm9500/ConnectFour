#include "game.hpp"


Game::Game() {
    // set up pointers
    buffer = &trueBuffer;
    board = &trueBoard;
    // initialize winnerchain to defaults
    winnerChain.winner = 0;
    // sets winnerChain.chain to all 0's
    getWinningChain();

    // set state to start on new game creation
    currentState = &StartState::getInstance();
    startScreenSelection = Start_Play;
    endScreenSelection = End_Rematch;

    
    // setup colours
    Colours["reset"]= "\033[0m";
    Colours["blue"]="\033[94;1m"; //1;94
    Colours["red"]="\033[31;1m";
    Colours["white"]="\033[37m";
    Colours["white_bg"]="\033[47m"; //maybe 37;3
    Colours["green"]="\033[32;1m";
    Colours["yellow"]="\033[33;1m";

    
    // populate available player colours (strings so they can be printed as text)
    PlayerColours.push_back("red");
    PlayerColours.push_back("yellow");
    PlayerColours.push_back("white");
    PlayerColours.push_back("green");
    PlayerColours.push_back("blue");

    PlayerColoursFormatted.push_back("  Red     ");
    PlayerColoursFormatted.push_back("  Yellow  ");
    PlayerColoursFormatted.push_back("  White   ");
    PlayerColoursFormatted.push_back("  Green   ");
    PlayerColoursFormatted.push_back("  Blue    ");

    PlayerColoursSelected.push_back("> Red <   ");
    PlayerColoursSelected.push_back("> Yellow <");
    PlayerColoursSelected.push_back("> White < ");
    PlayerColoursSelected.push_back("> Green < ");
    PlayerColoursSelected.push_back("> Blue <  ");

    setBackgroundColour(getColour("red"));
    setForegroundColour(getColour("yellow"));

    PlayerIcons.push_back("1");
    PlayerIcons.push_back("2");
    PlayerIcons.push_back("X");
    PlayerIcons.push_back("0");
    PlayerIcons.push_back("$");
    PlayerIcons.push_back("@");
    PlayerIcons.push_back("&");
    PlayerIcons.push_back("#");
    PlayerIcons.push_back("*");

    // player customization defaults
    setPlayer1Colour(getColour(PlayerColours.at(colourOffset[0])));
    setPlayer2Colour(getColour(PlayerColours.at(colourOffset[1])));
    setPlayer1Icon(PlayerIcons.at(iconOffset[0]));
    setPlayer2Icon(PlayerIcons.at(iconOffset[1]));

}

void Game::playGame() {
    while (!quitGame) {

        currentState->draw(this);
        currentState->update(this);

    }
    // game over/quit
}



void Game::setState(GameState& newState) {
    currentState->exit(this);
    currentState = &newState;
    currentState->enter(this);
}

winChain Game::getWinningChain() {
    winChain rVal;
    for (int j=0;j<4;j++) {
        for (int k=0;k<2;k++){
            if (winnerChain.winner != 0) {
                // winner = 0 if undeclared, otherwise 1 or 2
                rVal.chain[j][k] = winnerChain.chain[j][k];
            } else {
                // if no winner declared, set chain to 0
                rVal.chain[j][k] = 0;
            }
        }
    }
    rVal.winner = winnerChain.winner;
    return rVal;
}

// player customization
std::string Game::getColour(std::string c) {
    return Colours[c];
}

std::string Game::getPlayer1() {
    return getPlayer1Colour() + getPlayer1Icon() + getColour("reset");
}
std::string Game::getPlayer2() {
    return getPlayer2Colour() + getPlayer2Icon() + getColour("reset");
}
std::string Game::getPlayer1(std::string colour) {
    return getColour(colour) + getPlayer1Icon() + getColour("reset");
}
std::string Game::getPlayer2(std::string colour) {
    return getColour(colour) + getPlayer2Icon() + getColour("reset");
}

std::string Game::getPlayer1Colour() {return player1Colour;}
std::string Game::getPlayer2Colour() {return player2Colour;}
std::string Game::getPlayer1Icon() {return player1Icon;}
std::string Game::getPlayer2Icon() {return player2Icon;}

void Game::setPlayer1Icon(std::string icon) {
    player1Icon = icon;
}
void Game::setPlayer2Icon(std::string icon) {
    player2Icon = icon;
}

void Game::setPlayer1Colour(std::string newColour) {
    player1Colour = newColour;
}

void Game::setPlayer2Colour(std::string newColour) {
    player2Colour = newColour;
}

// gameplay
void Game::getMove() {

    int c;
    int temp;
    int i,j,k;
    // clear key buffer
    
    c = getch();
    //std::cout << "Entered character is "<< char(c) << " and it's ASCII value is " << int(c) << std::endl;;

    switch(c){
        case KEY_ENTER:
        case KEY_DOWN:
        case KEY_S:
            // down (enter move)
            //std::cout << std::endl << "Down" << std::endl;   // key down
            std::cout << getBoard()->tops[getBoard()->columnSelect] << std::endl;
            
            // check if move can be done
            if (getBoard()->tops[getBoard()->columnSelect] < getBoard()->getHeight()){
                // do move
                getBoard()->setGrid(getBoard()->columnSelect, getBoard()->getHeight()-1, playerTurn);
                getBoard()->updateBoard(getBuffer(), playerTurn);
                
                // update column tops
                getBoard()->tops[getBoard()->columnSelect]++;
                //std::cout << "Turn played by player " << playerTurn << std::endl;

                //swap player turn
                playerTurn = (playerTurn == 1) ? 2 : 1; 
                
            }//else wait for new valid input (on non-full column)
            break;
        case KEY_LEFT:
        case KEY_A:
            // move left
            temp = (getBoard()->columnSelect-1) % getBoard()->getWidth();
            getBoard()->columnSelect = (temp >= 0) ? temp : (temp + 7);
            break;
        case KEY_RIGHT:
        case KEY_D:
            // move right
            getBoard()->columnSelect = (getBoard()->columnSelect+1) % getBoard()->getWidth();
            break;
        case KEY_ESC:
            // end the game, return to home screen
            setState(StartState::getInstance());
            break;
        case CTRL_C:
            // exit program
            setState(QuitState::getInstance());
            return;
            //break;
        default:
            //std::cout << "default, polling again" << std::endl;
            getMove();
            break;
        
    }
    
    return;
}





winChain Game::checkWinner() {
    // check for 4 in a row
    // set default return value to no winner
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
    for (int w=0;w<getBoard()->getWidth();w++) {
        for (int h=0;h<getBoard()->getHeight();h++) {
            current = getBoard()->getGrid(w, h);
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
                            returnData.winner = current;
                            for (int j=0;j<4;j++) {
                                for (int k=0;k<2;k++){
                                    returnData.chain[j][k] = chain[current-1][j][k];
                                }
                            }
                            //std::cout << "Column win";
                            return returnData;
                        }
                    }
                }
            } else {
                streakCount[0] = 0;
                streakCount[1] = 0;
            }   
        }
    }
    streakCount[0] = 0;
    streakCount[1] = 0;
    // check rows
    for (int h=0;h<getBoard()->getHeight();h++) {
        for (int w=0;w<getBoard()->getWidth();w++) {
            current = getBoard()->getGrid(w, h);
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
                            
                            returnData.winner = current;
                            for (int j=0;j<4;j++) {
                                for (int k=0;k<2;k++){
                                    returnData.chain[j][k] = chain[current-1][j][k];
                                }
                            }
                            //std::cout << "Row win";
                            return returnData;
                        }
                    }
                }
            } else {
                streakCount[0] = 0;
                streakCount[1] = 0;
            }   
        }
    }
    streakCount[0] = 0;
    streakCount[1] = 0;

    // check diagonal
    // go row by row starting from the bottom up
    // check slope: /
    
    for (int h=0;h<getBoard()->getHeight()-3;h++) {
        for (int w=0;w<getBoard()->getWidth()-3;w++) {
            
            current = getBoard()->getGrid(w, h);
            // check if its a player
            if (current != 0) {
                // increase current player count
                int streak = ++streakCount[current-1];
                // reset other player's streak count (remember streakCount is 0-index, so P1=0, P2=1)
                streakCount[(current == 1 ? 1 : 0)] = 0;
                // streak should never be 0 at this point
                chain[current-1][streak-1][0] = w;
                chain[current-1][streak-1][1] = h;

                int offset = 1; //keep track of offset from (+1,+1) to (+3,+3)
                
                while (streak > 0) {
                    
                    if (streak == 4) {
                        
                        returnData.winner = current;
                        for (int j=0;j<4;j++) {
                            for (int k=0;k<2;k++){
                                returnData.chain[j][k] = chain[current-1][j][k];
                            }
                        }
                        //std::cout << "/ slope win";
                        return returnData;
                    } else {
                        next = getBoard()->getGrid(w+offset, h+offset);
                        
                        if (next == current) {
                            // streak continues
                            // increase streakCout, and then update streak
                            streak = ++streakCount[current-1];
                            // add coordinate to the chain
                            chain[current-1][streak-1][0] = w+offset;
                            chain[current-1][streak-1][1] = h+offset;
                            // increase offset for next iteration
                            offset++;
                        } else {
                            streakCount[current-1] = 0;
                            // will cause while loop to end
                        }
                    }
                    // update streak
                    streak = streakCount[current-1];
                }   
            } else {
                streakCount[0] = 0;
                streakCount[1] = 0;
            }   
        }
    }
    /* check slope: \           */
    streakCount[0] = 0;
    streakCount[1] = 0;
    for (int h=0;h<getBoard()->getHeight()-3;h++) {
        for (int w=3;w<getBoard()->getWidth();w++) {
            
            current = getBoard()->getGrid(w, h);
            // check if its a player
            if (current != 0) {
                // increase current player count
                int streak = ++streakCount[current-1];
                // reset other player's streak count (remember streakCount is 0-index, so P1=0, P2=1)
                streakCount[(current == 1 ? 1 : 0)] = 0;
                // streak should never be 0 at this point
                chain[current-1][streak-1][0] = w;
                chain[current-1][streak-1][1] = h;

                int offset = 1; //keep track of offset from (+1,+1) to (+3,+3)
                
                while (streak > 0) {
                    
                    if (streak == 4) {
                        
                        returnData.winner = current;
                        for (int j=0;j<4;j++) {
                            for (int k=0;k<2;k++){
                                returnData.chain[j][k] = chain[current-1][j][k];
                            }
                        }
                        //std::cout << "/ slope win";
                        return returnData;
                    } else {
                        next = getBoard()->getGrid(w-offset, h+offset);
                        
                        if (next == current) {
                            // streak continues
                            // increase streakCout, and then update streak
                            streak = ++streakCount[current-1];
                            // add coordinate to the chain
                            chain[current-1][streak-1][0] = w-offset;
                            chain[current-1][streak-1][1] = h+offset;
                            // increase offset for next iteration
                            offset++;
                        } else {
                            streakCount[current-1] = 0;
                            // will cause while loop to end

                        }
                    }
                    // update streak
                    streak = streakCount[current-1];
                }   
            } else {
                streakCount[0] = 0;
                streakCount[1] = 0;
            }   
        }
    }
    return returnData;
}



void Game::drawStartScreen() {
    *getBuffer() << getBackgroundColour();
    std::vector<std::string> displayString;
    displayString.push_back("| " + getForegroundColour()+ "CLI Connect 4" + getBackgroundColour()+ " |");
    displayString.push_back("|               |");
    displayString.push_back("|   Play Game   |");
    displayString.push_back("|  How To Play  |");
    displayString.push_back("|   Customize   |");
    displayString.push_back("|     Quit      |");
    displayString.push_back("| "+getPlayer1Colour()+"P1: "+getPlayer1Icon()+getPlayer2Colour()+"   P2: "+getPlayer2Icon()+ getBackgroundColour()+ " |");
    displayString.push_back("-----------------");
    // todo: add colour
    switch(startScreenSelection) {
        case Start_Play:
            displayString.at(2) = "| " + getForegroundColour()+ "> Play Game <" + getBackgroundColour()+ " |";
            break;
        case Start_HowToPlay:
            displayString.at(3) = "|" + getForegroundColour()+ "> How To Play <" + getBackgroundColour()+ "|";
            break;
        case Start_Customize:
            displayString.at(4) = "| " + getForegroundColour()+ "> Customize <" + getBackgroundColour()+ " |";
            break;
        case Start_Quit:
            displayString.at(5) = "|   " + getForegroundColour()+ "> Quit <" + getBackgroundColour()+ "    |";
            break;
    }
    
    for (int i=0; i<displayString.size();i++) {
        *getBuffer() << displayString.at(i);
        *getBuffer() << "\n";
    }
    *getBuffer() << getColour("reset");
}

void Game::drawHowToScreen() {
    *getBuffer() << getBackgroundColour();
    std::vector<std::string> displayString;
    displayString.push_back("|          " + getForegroundColour()+ "How To Play" + getBackgroundColour()+ "         |");
    displayString.push_back("|                              |");
    displayString.push_back("| " + getForegroundColour()+ "- Current column is selected" + getBackgroundColour()+ " |");
    displayString.push_back("|  " + getForegroundColour()+ "with the 'V'" + getBackgroundColour()+ "                |");
    displayString.push_back("| " + getForegroundColour()+ "- Move with left/right arrow" + getBackgroundColour()+ " |");
    displayString.push_back("|  " + getForegroundColour()+ "keys or the A and D keys" + getBackgroundColour()+ "    |");
    displayString.push_back("| " + getForegroundColour()+ "- Press down or enter to" + getBackgroundColour()+ "     |");
    displayString.push_back("|  " + getForegroundColour()+ "place your piece" + getBackgroundColour()+ "            |");
    displayString.push_back("| " + getForegroundColour()+ "- First to 4 in a row or" + getBackgroundColour()+ "     |");
    displayString.push_back("|  " + getForegroundColour()+ "column or diagonal wins!" + getBackgroundColour()+ "    |");
    displayString.push_back("| " + getForegroundColour()+ "- Esc to quit active game" + getBackgroundColour()+ "    |");
    displayString.push_back("|                              |");
    displayString.push_back("|           " + getForegroundColour()+ "> Back <" + getBackgroundColour()+ "           |");
    displayString.push_back("--------------------------------");
    // todo: add colour

    
    for (int i=0; i<displayString.size();i++) {
        *getBuffer() << displayString.at(i);
        *getBuffer() << "\n";
    }
    *getBuffer() << getColour("reset");
}


//todo: add icons instead of O and X
void Game::drawCustomizeScreen() {
    std::vector<std::string> displayString;
    displayString.push_back(getBackgroundColour() + "|   " + getForegroundColour()+ "Customize" + getBackgroundColour()+ "   |");
    displayString.push_back("| " + getPlayer1Colour()+ "P1    "+getPlayer1Icon()+"  " + getBackgroundColour()+ "     |");
    displayString.push_back("| " + getPlayer1Colour()+ "Col "+ PlayerColoursFormatted.at(colourOffset[0]) + getBackgroundColour()+ "|");
    displayString.push_back("|               |");
    displayString.push_back("| " + getPlayer2Colour()+ "P2    "+getPlayer2Icon()+"  " + getBackgroundColour()+ "     |");
    displayString.push_back("| " + getPlayer2Colour()+ "Col "+PlayerColoursFormatted.at(colourOffset[1]) + getBackgroundColour()+ "|");
    displayString.push_back("|               |");
    displayString.push_back("|   " + getForegroundColour()+ "Play Game" + getBackgroundColour()+ "   |");
    displayString.push_back("|     " + getForegroundColour()+ "Back" + getBackgroundColour()+ "      |");
    displayString.push_back("-----------------");

    switch(customizeScreenSelection) {
        case Customize_p1Icon:
            displayString.at(1) = "| " + getPlayer1Colour()+ "P1  > "+getPlayer1Icon()+" <" + getBackgroundColour()+ "     |";
            break;
        case Customize_p1Colour:
            displayString.at(2) = "| " + getPlayer1Colour()+ "Col "+ PlayerColoursSelected.at(colourOffset[0]) + getBackgroundColour()+ "|";
            break;
        case Customize_p2Icon:
            displayString.at(4) = "| " + getPlayer2Colour()+ "P2  > "+getPlayer2Icon()+" <" + getBackgroundColour()+ "     |";
            break;
        case Customize_p2Colour:
            displayString.at(5) = "| " + getPlayer2Colour()+ "Col "+PlayerColoursSelected.at(colourOffset[1]) + getBackgroundColour()+ "|";
            break;
        case Customize_Play:
            displayString.at(7) = "| " + getForegroundColour()+ "> Play Game <" + getBackgroundColour()+ " |";
            break;
        case Customize_Back:
            displayString.at(8) = "|   " + getForegroundColour()+ "> Back <" + getBackgroundColour()+ "    |";
            break;
    }

    for (int i=0; i<displayString.size();i++) {
        *getBuffer() << displayString.at(i);
        *getBuffer() << "\n";
    }
    *getBuffer() << getColour("reset");
}




void Game::drawPlayScreen() {
    //std::cout << "drawing board (turn)" << std::endl;
    *getBuffer() << getBackgroundColour();
    std::string colour = (playerTurn == 1) ? getPlayer1Colour() : getPlayer2Colour();
    *getBuffer() << "Turn: Player "+std::to_string(playerTurn)+" ("+((playerTurn == 1) ? (getPlayer1Colour() + getPlayer1Icon()) : (getPlayer2Colour() + getPlayer2Icon())) + getBackgroundColour()+")";
    *getBuffer() << "\n";

    // add column selection
    *getBuffer() << getColumnSelectorString(getBoard()->columnSelect, ((playerTurn == 1) ? (getPlayer1Colour() + getPlayer1Icon()) : (getPlayer2Colour() + getPlayer2Icon())));
    *getBuffer() << "\n";

    // draw top down, row by row
    for (int h=getBoard()->getHeight()-1; h>=0;h--){

        for (int w=-1; w<getBoard()->getWidth()+1;w++){

            if ((w == getBoard()->getWidth()) || (w == -1)) {
                // add border
                *getBuffer() << "| ";
            } else {
                // populate grid
                if (getBoard()->getGrid(w, h) == 1) {
                    // add player1's plays
                    *getBuffer() << getPlayer1();
                } else if (getBoard()->getGrid(w, h) == 2) {
                    // add player2's plays
                    *getBuffer() << getPlayer2();
                } else {
                    // add empty space
                    *getBuffer() << "-";
                }
                // add space between each character
                *getBuffer() << " ";
            }
        }
        // new row
        *getBuffer() << "\n";
    }
    // end of game board
    *getBuffer() << "-----------------\n";
    *getBuffer() << getColour("reset");

    //buffer.display();
}

void Game::drawEndScreen() {
    // chain should be a [4][2] array
    //system("cls");
    //buffer.clear();
    //std::cout << "drawing board (chain)" << std::endl;
    *getBuffer() << getColour("reset");

    // add column selection
    *getBuffer() << getColumnSelectorString(getBoard()->columnSelect, getPlayer1("green"));
    bool isPartOfWinningChain = false;

    // draw top down, row by row
    for (int h=getBoard()->getHeight()-1; h>=0;h--){

        for (int w=-1; w<getBoard()->getWidth()+1;w++){

            if ((w == getBoard()->getWidth()) || (w == -1)) {
                // add border
                *getBuffer() << getBackgroundColour() + "| ";
            } else {
                // populate grid
                if (getBoard()->getGrid(w, h) == 1) {
                    // add player1's plays
                    // check winning chain
                    
                    for (int i=0;i<4;i++){
                        if (winnerChain.chain[i][0] == w && winnerChain.chain[i][1] == h) {
                            isPartOfWinningChain = true;
                        }
                    }
                    if (isPartOfWinningChain){
                        //std::cout << "colouring (" << w << ", " << h << ") green" << std::endl;
                        *getBuffer() << getPlayer1("green");
                        isPartOfWinningChain = false;
                    } else {
                        *getBuffer() << getPlayer1();
                    } 
                } else if (getBoard()->getGrid(w, h) == 2) {
                    // add player2's plays
                    // check winning chain
                    
                    for (int i=0;i<4;i++){
                        if (winnerChain.chain[i][0] == w && winnerChain.chain[i][1] == h) {
                            isPartOfWinningChain = true;
                        }
                    }
                    if (isPartOfWinningChain){
                        *getBuffer() << getPlayer2("green");
                        isPartOfWinningChain = false;
                    } else {
                        *getBuffer() << getPlayer2();
                    } 
                } else {
                    // add empty space
                    *getBuffer() << getBackgroundColour() + "-";
                }
                // add space between each character
                *getBuffer() << " ";
            }
        }
        // new row
        *getBuffer() << "\n";
    }
    // end of game board
    *getBuffer() << getBackgroundColour() + "-----------------";
    *getBuffer() << "\n";

    //todo: add end screen menu buttons for rematch/home/quit

    std::vector<std::string> tempString;
    tempString.push_back("| Player "+std::to_string(winnerChain.winner)+" Wins |");
    tempString.push_back("|    " + getForegroundColour()+ "Rematch" + getBackgroundColour()+ "    |");
    tempString.push_back("|   " + getForegroundColour()+ "Main Menu" + getBackgroundColour()+ "   |");
    tempString.push_back("|     " + getForegroundColour()+ "Quit" + getBackgroundColour()+ "      |");
    
    // todo: add colour
    switch(endScreenSelection) {
        case End_Rematch:
            tempString.at(1) = "|  " + getForegroundColour()+ "> Rematch <" + getBackgroundColour()+ "  |";
            break;
        case End_MainMenu:
            tempString.at(2) = "| " + getForegroundColour()+ "> Main Menu <" + getBackgroundColour()+ " |";
            break;
        case End_Quit:
            tempString.at(3) = "|   " + getForegroundColour()+ "> Quit <" + getBackgroundColour()+ "    |";
            break;
    }
    
    for (int i=0; i<tempString.size();i++) {
        *getBuffer() << tempString.at(i);
        *getBuffer() << "\n";
    }

    *getBuffer() << getColour("reset");
}

std::string Game::getColumnSelectorString(int columnSelect, std::string icon) {
    // input colour has to already have been passed thru getColour(), do not pass in colour text like "green"
    std::string string;
    for (int i=0;i<=columnSelect;i++){
        string += "  ";
    }
    string += icon + getColour("reset");
    //return does not include newline
    return string;
}
