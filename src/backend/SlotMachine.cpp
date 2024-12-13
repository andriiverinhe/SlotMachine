#include "SlotMachine.hpp"

SlotMachine::SlotMachine() : _drums({30, 30}, 5) {}

void SlotMachine::UserInput(const Action &action) {
  switch (_state) {
    case State::START:
      if (action == Action::Start) {
        _drums.signalToStart();
        _state = State::WORK;
      }
      break;

    case State::WORK:
      if (action == Action::NoAction) {
        if (_drums.rotation() == true)
         _state = State::SCORING;
      } else if (action == Action::Stop)
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

GameInfo SlotMachine::getGameInfoForUpdateView(void) {
  return {{30, 30}, _drums.getFigureFromRange(0, 90)};
}

// int main() {
//   SlotMachine sm;
//   while (1) {
//     Action a = Action::NoAction;
//     sm.UserInput(a);

//     auto gi = sm.getGameInfoForUpdateView();
//   }

//   return 0;
// }