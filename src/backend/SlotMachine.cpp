#include "SlotMachine.hpp"

void SlotMachine::UserInput(const Action &action)
{
    switch (_state)
    {
    case State::START:
        if (action == Action::Start)
            _state = State::WORK;
        break;

    case State::WORK:
        if (action == Action::NoAction)
            _drums.start();
        else if (action == Action::Stop)
            _state = State::STOP;
        break;

    case State::SCORING:
        // Состояние для подсчета результата
        _state = State::START;
        break;

    case State::STOP:
        _drums.stop();
        _state = State::SCORING;
        break;
    default:
        break;
    }
}


GameInfo getGameInfoForUpdateView(void) {
    
}