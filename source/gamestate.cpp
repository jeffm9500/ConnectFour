#include "gamestate.hpp"


// Start
void StartState::enter(Game* game) {
    game->playingGame = true;
    game->turns = 0;
    game->playerTurn = 1;
    game->startScreenSelection = Start_Play;
    
}

void StartState::draw(Game *game) {
    system("cls");
    
        
    game->drawStartScreen();
    

    game->getBuffer()->display();
    game->getBuffer()->clear();
}

void StartState::update(Game* game) {
    // check for input up/down and adjust selection
    int c;
    c = getch();
    while (!c) {
        c = getch();
    }
    //std::cout << "Entered character is "<< char(c) << " and it's ASCII value is " << int(c) << std::endl;
    switch(c) {
        case KEY_S:
        case KEY_DOWN:
            // ++ because enum is top->down low->high
            std::cout << "key down" << std::endl;
            game->startScreenSelection++;
            break;

        case KEY_W:
        case KEY_UP:
            std::cout << "key up" << std::endl;
            game->startScreenSelection--;
            break;
        case KEY_LEFT:
        case KEY_RIGHT:
        case KEY_A:
        case KEY_D:
        case KEY_ENTER:
            switch(game->startScreenSelection) {
                case Start_Play:
                    //std::cout << "switching to play" << std::endl;
                    //disable AI
                    game->setAIDifficulty(0);
                    game->setState(PlayState::getInstance());
                    break;
                case Start_AI:
                    game->setState(AIState::getInstance());
                    break;
                case Start_HowToPlay:
                    //std::cout << "switching to howtoplay" << std::endl;
                    game->setState(HowToState::getInstance());
                    break;
                case Start_Customize:
                    //std::cout << "switching to customize" << std::endl;
                    game->setState(CustomizeState::getInstance());
                    break;
                case Start_Quit:
                    //std::cout << "switching to quit" << std::endl;
                    game->setState(QuitState::getInstance());
                    break;
            }
            break;
        case KEY_ESC:
        case CTRL_C:
            // end game (dont actually switch to end game screen)
            game->setState(QuitState::getInstance());
            break;
        default:
            //std::cout << "default, polling again" << std::endl;
            update(game);
            break;
    }

}

void StartState::exit(Game* game) {

}

GameState &StartState::getInstance() {
    static StartState s;
    return s;
}


// How To Play
void HowToState::enter(Game *game) {
}

void HowToState::draw(Game *game) {
    system("cls");
    game->drawHowToScreen();
    game->getBuffer()->display();
    game->getBuffer()->clear();
}

void HowToState::update(Game *game) {
    int c;
    c = getch();
    while (!c) {
        c = getch();
    }
    //std::cout << "Entered character is "<< char(c) << " and it's ASCII value is " << int(c) << std::endl;
    switch(c) {
        case KEY_ENTER:
        case KEY_ESC:
        case KEY_LEFT:
        case KEY_RIGHT:
        case KEY_A:
        case KEY_D:
            game->setState(StartState::getInstance());
            break;
        
        case CTRL_C:
            // end game (dont actually switch to end game screen)
            game->setState(QuitState::getInstance());
            break;
        default:
            //std::cout << "default, polling again" << std::endl;
            update(game);
            break;
    }
}

void HowToState::exit(Game *game) {
}

GameState &HowToState::getInstance() {
    static HowToState h;
    return h;
}



// Customize
void CustomizeState::enter(Game* game) {
    game->customizeScreenSelection = Customize_p1Icon;
    
}

void CustomizeState::draw(Game *game) {
    system("cls");
    game->drawCustomizeScreen();
    game->getBuffer()->display();
    game->getBuffer()->clear();
}

void CustomizeState::update(Game *game) {
    int c, temp;
    c = getch();
    while (!c) {
        c = getch();
    }
    //std::cout << "Entered character is "<< char(c) << " and it's ASCII value is " << int(c) << std::endl;
    switch(c) {
        case KEY_S:
        case KEY_DOWN:
            // ++ because enum is top->down low->high
            std::cout << "key down" << std::endl;
            game->customizeScreenSelection++;
            break;

        case KEY_W:
        case KEY_UP:
            std::cout << "key up" << std::endl;
            game->customizeScreenSelection--;
            break;
        case KEY_ENTER:
            switch(game->customizeScreenSelection) {
                case Customize_p1Icon:
                    
                    
                    break;
                case Customize_p1Colour:
                    
                    
                    break;
                case Customize_p2Icon:
                    
                    
                    break;
                case Customize_p2Colour:
                    
                    
                    break;
                case Customize_Play:
                    //disable AI
                    game->setAIDifficulty(0);
                    game->setState(PlayState::getInstance());
                    break;
                case Customize_Back:
                    game->setState(StartState::getInstance());
                    break;
            }
            break;
        case KEY_LEFT:
        case KEY_A:
            // move --
            switch(game->customizeScreenSelection) {
                case Customize_p1Icon:
                    //move offset pointer --
                    //std::cout << "colourOffset: " << game->colourOffset[0] << ", " << game->colourOffset[1] << std::endl;
                    // edge case: decrement when already at 0
                    if (game->iconOffset[0] == 0) {
                        //check if other player is at end of list already
                        if (game->iconOffset[1] == game->PlayerIcons.size()-1) {
                            // if so, skip end of list and go to 2nd last
                            game->iconOffset[0] = game->PlayerIcons.size()-2;
                        } else {
                            // otherwise, just set to end of list
                            game->iconOffset[0] = game->PlayerIcons.size()-1;
                        }
                    // edge case: current = 1 and other player = 0, cant decrement into 0
                    } else if (game->iconOffset[0] == 1 && game->iconOffset[1] == 0){
                        game->iconOffset[0] = game->PlayerIcons.size()-1;
                    } else {
                        // decrement would overlap, so skip over
                        if (game->iconOffset[0]-1 == game->iconOffset[1]) {
                            game->iconOffset[0] = game->iconOffset[0] - 2;
                        } else {
                            // otherwise just decrement normally (no collision)
                            game->iconOffset[0] = game->iconOffset[0] - 1;
                        }
                    }
                    
                    break;
                case Customize_p1Colour:
                    //move offset pointer --
                    //std::cout << "colourOffset: " << game->colourOffset[0] << ", " << game->colourOffset[1] << std::endl;
                    // edge case: decrement when already at 0
                    if (game->colourOffset[0] == 0) {
                        //check if other player is at end of list already
                        if (game->colourOffset[1] == game->PlayerColours.size()-1) {
                            // if so, skip end of list and go to 2nd last
                            game->colourOffset[0] = game->PlayerColours.size()-2;
                        } else {
                            // otherwise, just set to end of list
                            game->colourOffset[0] = game->PlayerColours.size()-1;
                        }
                    // edge case: current = 1 and other player = 0, cant decrement into 0
                    } else if (game->colourOffset[0] == 1 && game->colourOffset[1] == 0){
                        game->colourOffset[0] = game->PlayerColours.size()-1;
                    } else {
                        // decrement would overlap, so skip over
                        if (game->colourOffset[0]-1 == game->colourOffset[1]) {
                            game->colourOffset[0] = game->colourOffset[0] - 2;
                        } else {
                            // otherwise just decrement normally (no collision)
                            game->colourOffset[0] = game->colourOffset[0] - 1;
                        }
                    }
                
                    //std::cout << "colourOffset: " << game->colourOffset[0] << ", " << game->colourOffset[1] << std::endl;
                    break;
                case Customize_p2Icon:
                    //move offset pointer --
                    // edge case: decrement when already at 0
                    if (game->iconOffset[1] == 0) {
                        //check if other player is at end of list already
                        if (game->iconOffset[0] == game->PlayerIcons.size()-1) {
                            // if so, skip end of list and go to 2nd last
                            game->iconOffset[1] = game->PlayerIcons.size()-2;
                        } else {
                            // otherwise, just set to end of list
                            game->iconOffset[1] = game->PlayerIcons.size()-1;
                        }
                    // edge case: current = 1 and other player = 0, cant decrement into 0
                    } else if (game->iconOffset[1] == 1 && game->iconOffset[0] == 0){
                        game->iconOffset[1] = game->PlayerIcons.size()-1;
                    } else {
                        // decrement would overlap, so skip over
                        if (game->iconOffset[1]-1 == game->iconOffset[0]) {
                            game->iconOffset[1] = game->iconOffset[1] - 2;
                        } else {
                            // otherwise just decrement normally (no collision)
                            game->iconOffset[1] = game->iconOffset[1] - 1;
                        }
                    }
                    
                    break;
                case Customize_p2Colour:
                    //move offset pointer --
                    //std::cout << "colourOffset: " << game->colourOffset[0] << ", " << game->colourOffset[1] << std::endl;
                    // edge case: decrement when already at 0
                    if (game->colourOffset[1] == 0) {
                        //check if other player is at end of list already
                        if (game->colourOffset[0] == game->PlayerColours.size()-1) {
                            // if so, skip end of list and go to 2nd last
                            game->colourOffset[1] = game->PlayerColours.size()-2;
                        } else {
                            // otherwise, just set to end of list
                            game->colourOffset[1] = game->PlayerColours.size()-1;
                        }
                    // edge case: current = 1 and other player = 0, cant decrement into 0
                    } else if (game->colourOffset[1] == 1 && game->colourOffset[0] == 0){
                        game->colourOffset[1] = game->PlayerColours.size()-1;
                    } else {
                        // decrement would overlap, so skip over
                        if (game->colourOffset[1]-1 == game->colourOffset[0]) {
                            game->colourOffset[1] = game->colourOffset[1] - 2;
                        } else {
                            // otherwise just decrement normally (no collision)
                            game->colourOffset[1] = game->colourOffset[1] - 1;
                        }
                    }
                    break;
                case Customize_Play:
                    game->setState(PlayState::getInstance());
                    break;
                case Customize_Back:
                    game->setState(StartState::getInstance());
                    break;
            }
            break;
        case KEY_RIGHT:
        case KEY_D:
            // move ++
            switch(game->customizeScreenSelection) {
                case Customize_p1Icon:
                    if (game->iconOffset[0] == game->PlayerIcons.size()-1) {
                        //check if other player is at start of list already
                        if (game->iconOffset[1] == 0) {
                            // if so, skip start of list and go to 2nd
                            game->iconOffset[0] = 1;
                        } else {
                            // otherwise, just set to end of list
                            game->iconOffset[0] = 0;
                        }
                    // edge case: current = len-1 and other player = len, cant increment into len
                    } else if (game->iconOffset[0] == game->PlayerIcons.size()-2 && game->iconOffset[1] == game->PlayerIcons.size()-1){
                        game->iconOffset[0] = 0;
                    } else {
                        if (game->iconOffset[0]+1 == game->iconOffset[1]) {
                        // increment would overlap, so skip over
                            game->iconOffset[0] = game->iconOffset[0] + 2;
                        } else {
                            // otherwise just decrement normally (no collision)
                            game->iconOffset[0] = game->iconOffset[0] + 1;
                        }
                    }
                    
                    break;
                case Customize_p1Colour:
                    //move offset pointer ++
                    //std::cout << "colourOffset: " << game->colourOffset[0] << ", " << game->colourOffset[1] << std::endl;
                    // edge case: increment when already at max length
                    if (game->colourOffset[0] == game->PlayerColours.size()-1) {
                        //check if other player is at start of list already
                        if (game->colourOffset[1] == 0) {
                            // if so, skip start of list and go to 2nd
                            game->colourOffset[0] = 1;
                        } else {
                            // otherwise, just set to end of list
                            game->colourOffset[0] = 0;
                        }
                    // edge case: current = len-1 and other player = len, cant increment into len
                    } else if (game->colourOffset[0] == game->PlayerColours.size()-2 && game->colourOffset[1] == game->PlayerColours.size()-1){
                        game->colourOffset[0] = 0;
                    } else {
                        if (game->colourOffset[0]+1 == game->colourOffset[1]) {
                        // increment would overlap, so skip over
                            game->colourOffset[0] = game->colourOffset[0] + 2;
                        } else {
                            // otherwise just decrement normally (no collision)
                            game->colourOffset[0] = game->colourOffset[0] + 1;
                        }
                    }
                    break;
                case Customize_p2Icon:
                    if (game->iconOffset[1] == game->PlayerIcons.size()-1) {
                        //check if other player is at start of list already
                        if (game->iconOffset[0] == 0) {
                            // if so, skip start of list and go to 2nd
                            game->iconOffset[1] = 1;
                        } else {
                            // otherwise, just set to end of list
                            game->iconOffset[1] = 0;
                        }
                    // edge case: current = len-1 and other player = len, cant increment into len
                    } else if (game->iconOffset[1] == game->PlayerIcons.size()-2 && game->iconOffset[0] == game->PlayerIcons.size()-1){
                        game->iconOffset[1] = 0;
                    } else {
                        if (game->iconOffset[1]+1 == game->iconOffset[0]) {
                        // increment would overlap, so skip over
                            game->iconOffset[1] = game->iconOffset[1] + 2;
                        } else {
                            // otherwise just decrement normally (no collision)
                            game->iconOffset[1] = game->iconOffset[1] + 1;
                        }
                    }
                    
                    break;
                case Customize_p2Colour:
                    //move offset pointer ++
                    //std::cout << "colourOffset: " << game->colourOffset[0] << ", " << game->colourOffset[1] << std::endl;
                    // edge case: increment when already at max length
                    if (game->colourOffset[1] == game->PlayerColours.size()-1) {
                        //check if other player is at start of list already
                        if (game->colourOffset[0] == 0) {
                            // if so, skip start of list and go to 2nd
                            game->colourOffset[1] = 1;
                        } else {
                            // otherwise, just set to end of list
                            game->colourOffset[1] = 0;
                        }
                    // edge case: current = len-1 and other player = len, cant increment into len
                    } else if (game->colourOffset[1] == game->PlayerColours.size()-2 && game->colourOffset[0] == game->PlayerColours.size()-1){
                        game->colourOffset[1] = 0;
                    } else {
                        if (game->colourOffset[1]+1 == game->colourOffset[0]) {
                        // increment would overlap, so skip over
                            game->colourOffset[1] = game->colourOffset[1] + 2;
                        } else {
                            // otherwise just decrement normally (no collision)
                            game->colourOffset[1] = game->colourOffset[1] + 1;
                        }
                    }
                    break;
                case Customize_Play:
                    game->setState(PlayState::getInstance());
                    break;
                case Customize_Back:
                    game->setState(StartState::getInstance());
                    break;
            }
            break;
        case KEY_ESC:
        case CTRL_C:
            // end game (dont actually switch to end game screen)
            game->setState(QuitState::getInstance());
            break;
        default:
            //std::cout << "default, polling again" << std::endl;
            update(game);
            break;
    }
    // update colours and icons based off selection
    game->setPlayer1Colour(game->getColour(game->PlayerColours.at(game->colourOffset[0])));
    game->setPlayer2Colour(game->getColour(game->PlayerColours.at(game->colourOffset[1])));
    game->setPlayer1Icon(game->PlayerIcons.at(game->iconOffset[0]));
    game->setPlayer2Icon(game->PlayerIcons.at(game->iconOffset[1]));

}

void CustomizeState::exit(Game* game) {
    // save selections (currently redundant)
    game->setPlayer1Colour(game->getColour(game->PlayerColours.at(game->colourOffset[0])));
    game->setPlayer2Colour(game->getColour(game->PlayerColours.at(game->colourOffset[1])));
    game->setPlayer1Icon(game->PlayerIcons.at(game->iconOffset[0]));
    game->setPlayer2Icon(game->PlayerIcons.at(game->iconOffset[1]));
}

GameState &CustomizeState::getInstance() {
    static CustomizeState c;
    return c;
}


// Play
void PlayState::enter(Game* game) {
    game->playingGame = true;
    game->turns = 0;
    game->playerTurn = 1;
}

void PlayState::draw(Game *game) {
    system("cls");

    //game->getBoard()->drawBoard(game->getBuffer(), game->playerTurn);
    game->drawPlayScreen();
    game->getBuffer()->display();
    game->getBuffer()->clear();
}

void PlayState::update(Game *game) {

    // check if board is full
    game->checkFullBoard();

    // check for inputs, and alternate player turn after each input

    // in case AI gets implemented, this needs a switch since user wont input both players (eventually)
    switch(game->playerTurn) {
        case 1:
            // user's turn:
            game->getMove();
            break;
        case 2:
            // P2 turn (currently human)
            if (game->getAIDifficulty() > 0) {
                // ai present
                game->doAIMove();
            } else {
                // no AI, poll for player 2 move
                game->getMove();
            }
            
            break;
    }
    // resolve falling pieces
    while(game->getBoard()->updateBoard(game->getBuffer(), game->playerTurn)) {
        // updating board until completion, draw after each iteration
        draw(game);
    }
    // check if there is a winner
    winChain data = game->checkWinner();
    game->winnerChain.winner = data.winner;
    
    if (game->winnerChain.winner) {
        //std::cout << std::endl << "Printing chain" << std::endl;
        for (int j=0;j<4;j++) {
            for (int k=0;k<2;k++){
                game->winnerChain.chain[j][k] = data.chain[j][k];
                //std::cout << chain[j][k];
            }
        }
        //std::cout << std::endl << "Winner detected: Player " << game->winnerChain.winner << std::endl;
        game->setState(EndState::getInstance());
    } //else, no winner detected so continue playing

}

void PlayState::exit(Game* game) {
    game->playingGame = false;
}

GameState &PlayState::getInstance() {
    static PlayState p;
    return p;
}


// End
void EndState::enter(Game* game) {
    // player has won the game

}

void EndState::draw(Game *game) {
    system("cls");
    game->drawEndScreen();
    game->getBuffer()->display();
    game->getBuffer()->clear();

}

void EndState::update(Game *game) {
    int c;
    c = getch();
    while (!c) {
        c = getch();
    }
    //std::cout << "Entered character is "<< char(c) << " and it's ASCII value is " << int(c) << std::endl;
    switch(c) {
        case KEY_S:
        case KEY_DOWN:
            // ++ because enum is top->down low->high
            std::cout << "key down" << std::endl;
            game->endScreenSelection++;
            break;

        case KEY_W:
        case KEY_UP:
            std::cout << "key up" << std::endl;
            game->endScreenSelection--;
            break;

        case KEY_ENTER:
            //switch for EndState menu options
            switch(game->endScreenSelection) {
                case End_Rematch:
                    game->setState(PlayState::getInstance());
                    break;
                case End_MainMenu:
                    game->setState(StartState::getInstance());
                    break;
                case End_Quit:
                    game->setState(QuitState::getInstance());
                    break;
            }
            
            break;
        case KEY_ESC:
        case CTRL_C:
            // end game (dont actually switch to end game screen)
            game->setState(QuitState::getInstance());
            break;
        default:
            //std::cout << "default, polling again" << std::endl;
            update(game);
            break;
    }
}

void EndState::exit(Game* game) {
    game->getBoard()->resetBoard();
}

GameState &EndState::getInstance() {
    static EndState e;
    return e;
}


// Quit
void QuitState::enter(Game *game) {
    
    //std::cout << "quitting game" << std::endl;
    game->quitGame = true;
    //game->playingGame = false;
}

GameState &QuitState::getInstance() {
    static QuitState q;
    return q;
}

// Pick AI difficulty
void AIState::enter(Game *game) {
    // set default selection to easy
    game->aiScreenSelection = AI_Easy;
    game->setAIDifficulty(game->aiScreenSelection);
    game->setAIColour(game->getColour("green"));
}

void AIState::draw(Game *game) {
    system("cls");
    game->drawAIScreen();
    game->getBuffer()->display();
    game->getBuffer()->clear();
}

void AIState::update(Game *game) {
    int c;
    c = getch();
    while (!c) {
        c = getch();
    }
    //std::cout << "Entered character is "<< char(c) << " and it's ASCII value is " << int(c) << std::endl;
    switch(c) {
        case KEY_S:
        case KEY_DOWN:
            // ++ because enum is top->down low->high
            std::cout << "key down" << std::endl;
            game->aiScreenSelection++;
            break;

        case KEY_W:
        case KEY_UP:
            std::cout << "key up" << std::endl;
            game->aiScreenSelection--;
            break;
        case KEY_LEFT:
        case KEY_RIGHT:
        case KEY_A:
        case KEY_D:
        case KEY_ENTER:
            //switch for EndState menu options
            switch(game->aiScreenSelection) {
                case AI_Easy:
                    game->setAIDifficulty(game->aiScreenSelection);
                    game->setAIColour(game->getColour("green"));
                    break;
                case AI_Medium:
                    game->setAIDifficulty(game->aiScreenSelection);
                    game->setAIColour(game->getColour("yellow"));
                    break;
                case AI_Hard:
                    game->setAIDifficulty(game->aiScreenSelection);
                    game->setAIColour(game->getColour("red"));
                    break;
                case AI_Play:
                    // check that difficulty has been set
                    if (game->getAIDifficulty() > 0) {
                        game->setState(PlayState::getInstance());
                    } 
                    // else ignore input 
                    // this should not happen since difficulty is set to default=easy on this page
                    break;
                case AI_Back:
                    game->setState(StartState::getInstance());
                    break;
            }
            
            break;
        case KEY_ESC:
        case CTRL_C:
            // end game (dont actually switch to end game screen)
            game->setState(StartState::getInstance());
            break;
        default:
            //std::cout << "default, polling again" << std::endl;
            update(game);
            break;
    }
}

void AIState::exit(Game *game) {

}

GameState &AIState::getInstance() {
    static AIState a;
    return a;
}
