#pragma once

#include "Drums.hpp"

enum class Action
{
    Start,
    Stop,
    NoAction
};

enum class State
{
    START,
    WORK,
    SCORING,
    STOP,
    NoSTATE
};

struct GameInfo {
    // point for figure or all point --

    Size _sizeSection; 
    std::vector<Figure> _data; // 
};

class SlotMachine
{
private:
    Drums _drums;
    State _state = State::START;

public:
    SlotMachine() = default;
    ~SlotMachine() = default;

    void UserInput(const Action &action);
    GameInfo getGameInfoForUpdateView(void);  
};
