#pragma once

#include <iostream>
#include <string>

#include "game.hpp"

enum states {
    StartState,
    CustomizeState,
    PlayState,
    EndState, 
    QuitState
};

class Game;

// abstract
class GameState {
    public:
        virtual void enter(Game* game) = 0;
        virtual void draw(Game* game) = 0;
        virtual void update(Game* game) = 0;
        virtual void exit(Game* game) = 0;
        virtual ~GameState() {}

};

// Start
class StartState : public GameState {
    public:
        void enter(Game* game);
        void draw(Game* game);
        void update(Game* game);
        void exit(Game* game);
        static GameState& getInstance();

    private:
        StartState() {}
        StartState(const StartState& state);
        StartState& operator=(StartState& state) {return state;};
};

// Customize screen
class CustomizeState : public GameState {
    public:
        void enter(Game* game);
        void draw(Game* game);
        void update(Game* game);
        void exit(Game* game);
        static GameState& getInstance();

    private:
        CustomizeState() {}
        CustomizeState(const CustomizeState& state);
        CustomizeState& operator=(CustomizeState& state) {return state;};
};


// Play
class PlayState : public GameState {
    public:
        void enter(Game* game);
        void draw(Game* game);
        void update(Game* game);
        void exit(Game* game);
        static GameState& getInstance();

    private:
        PlayState() {}
        PlayState(const PlayState& state);
        PlayState& operator=(PlayState& state) {return state;};
};


// End
class EndState : public GameState {
    public:
        void enter(Game* game);
        void draw(Game* game);
        void update(Game* game);
        void exit(Game* game);
        static GameState& getInstance();

    private:
        EndState() {}
        EndState(const EndState& state);
        EndState& operator=(EndState& state) {return state;};
};

// Quit
class QuitState : public GameState {
    public:
        void enter(Game* game);
        void draw(Game* game) {};
        void update(Game* game) {};
        void exit(Game* game) {};
        static GameState& getInstance();

    private:
        QuitState() {}
        QuitState(const QuitState& state);
        QuitState& operator=(QuitState& state) {return state;};
};

class HowToState : public GameState {
    public:
        void enter(Game* game);
        void draw(Game* game);
        void update(Game* game);
        void exit(Game* game);
        static GameState& getInstance();

    private:
        HowToState() {}
        HowToState(const HowToState& state);
        HowToState& operator=(HowToState& state) {return state;};
};