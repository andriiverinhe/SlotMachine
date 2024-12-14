#include "SlotMachine.hpp"
#include "ScoreManager.hpp"

SlotMachine::SlotMachine() : _drums(5, 8, {0, 0}, {240, 240}) {}

bool Time::isOverTime(void) {
  return (_end < std::chrono::steady_clock::now());
}

void Time::recalculateTheTime() {
  _start = std::chrono::steady_clock::now();
  _end = _start + std::chrono::seconds(static_cast<int>(time));

  timeIsSet = true;
}

void SlotMachine::UserInput(const Action &action) {
  switch (_state) {
    case State::START:
      if (action == Action::Start) {
        _state = State::WORK;
        _time.recalculateTheTime();
      }
      break;

    case State::WORK:
      if (!_time.isOverTime())
        _drums.rotation();
      else if (_drums.normalize())
        _state = State::SCORING;
      break;

    case State::SCORING:
      auto res = _drums.getFigureWins();
      ScoreManager manager(res);
      _gameInfo.point = manager.getScore(); 
      break;

    // case State::STOP:
    //   break;
    // case State::NoSTATE:
    // default:
    //   break;
  }
}

GameInfo SlotMachine::getGameInfoForUpdateView(void) {
  _gameInfo._data = _drums.getDrums();
  return _gameInfo;
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