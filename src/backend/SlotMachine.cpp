#include "SlotMachine.hpp"

#include "ScoreManager.hpp"

SlotMachine::SlotMachine()
    : _drums(DEFAULT_DRUMS, DEFAULT_FIGURE_FROM_DRUM, DEFAULT_COORDINATES,
             {DEFAULT_WIDTH, DEFAULT_HEIGHT}) {
  _gameInfo.data.reserve(DEFAULT_DRUMS);
  _gameInfo.sizeOneFigure = {DEFAULT_WIDTH, DEFAULT_HEIGHT};
  _gameInfo.point = DEFAULT_POINT;
}

SlotMachine::SlotMachine(const unsigned& countDrum, const unsigned& countFigure,
                         const Coordinates& startPos, const Size& sizeOneFigure)
    : _drums(countDrum, countFigure, startPos, sizeOneFigure) {
  _gameInfo.data.reserve(countDrum);
  _gameInfo.sizeOneFigure = sizeOneFigure;
  _gameInfo.point = DEFAULT_POINT;
}

bool Time::isOverTime(void) {
  remains = std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::steady_clock::now() - _start)
                .count();
  return (_end < std::chrono::steady_clock::now());
}

void Time::calculateTheTime() {
  _start = std::chrono::steady_clock::now();
  _end = _start + std::chrono::seconds(static_cast<int>(time));

  timeIsSet = true;
}

void SlotMachine::setTime(const double time) { _time.time = time; }

void SlotMachine::UserInput(const Action& action) {
  switch (_state) {
    case State::START:
      if (action == Action::Start) {
        _time.calculateTheTime();
        _gameInfo.point = DEFAULT_POINT;
        _state = State::WORK;
      }
      break;

    case State::STOP:
      if (!_time.isOverTime()) {
        _drums.rotation(size);

        if (_time.remains < (_time.time / 1.5)) {
          if (size < (_gameInfo.sizeOneFigure.height / 4)) size++;
        } else {
          if (size > 1) size--;
        }
      } else if (_drums.normalize(1)) {
        _time.time = DEFAULT_TIME;
        _state = State::SCORING;
      }
      break;

    case State::NoSTATE:
      break;

    case State::WORK:
      if (action == Action::Stop && _time.remains < DEFAULT_TIME_STOP) {
        _state = State::STOP;
        _time.time = DEFAULT_TIME_STOP;
        _time.calculateTheTime();
      } else {
        if (!_time.isOverTime()) {
          _drums.rotation(size);

          if (_time.remains < (_time.time / 1.5)) {
            if (size < (_gameInfo.sizeOneFigure.height / 2)) size++;
          } else {
            if (size > 1) size--;
          }
        } else if (_drums.normalize(1))
          _state = State::SCORING;
      }
      break;

    case State::SCORING: {
      ScoreManager manager(_drums.getFigureWins());
      _gameInfo.point = manager.getScore();
      _state = State::START;
      break;
    }
    default:
      break;
  }
}

GameInfo SlotMachine::getGameInfoForUpdateView(void) {
  _gameInfo.data = _drums.getDrums();
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
