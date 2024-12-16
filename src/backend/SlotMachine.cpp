#include "SlotMachine.hpp"

#include "ScoreManager.hpp"

using namespace std::chrono;

void SlotMachine::initSlotMachineInfo(const unsigned& countDrum,
                                      const Size& sizeOneFigure) {
  _info.data.reserve(countDrum);
  _info.sizeOneFigure = sizeOneFigure;
  _info.point = DEFAULT_POINT;
}

SlotMachine::SlotMachine()
    : _drums(DEFAULT_DRUMS, DEFAULT_FIGURE_FROM_DRUM, DEFAULT_COORDINATES,
             {DEFAULT_WIDTH, DEFAULT_HEIGHT}) {
  initSlotMachineInfo(DEFAULT_DRUMS, {DEFAULT_WIDTH, DEFAULT_HEIGHT});
}

SlotMachine::SlotMachine(const unsigned& countDrum, const unsigned& countFigure,
                         const Coordinates& startPos, const Size& sizeOneFigure)
    : _drums(countDrum, countFigure, startPos, sizeOneFigure) {
  initSlotMachineInfo(countDrum, sizeOneFigure);
}

double Time::getRemains(void) {
  return time - (duration_cast<seconds>(steady_clock::now() - _start).count());
}

bool Time::isOverTime(void) { return (_end < steady_clock::now()); }

void Time::calculateTheTime() {
  _start = steady_clock::now();
  _end = _start + seconds(static_cast<int>(time));

  timeIsSet = true;
}

void SlotMachine::rotate(const double& remainsTime, const unsigned& maxSpeed,
                         bool& stop) {
  if (!_time.isOverTime()) {
    _drums.rotation(speed);

    if (_time.getRemains() > remainsTime) {
      if (speed <= maxSpeed) speed++;
    } else {
      if (speed > 1) speed--;
    }
    stop = false;
  } else if (_drums.normalize(1))
    stop = true;
  else
    stop = false;
}

void SlotMachine::UserInput(const Action& action) {
  switch (_state) {
    case State::START:
      if (action == Action::Start) {
        _time.calculateTheTime();
        _info.point = DEFAULT_POINT;
        speed = 1;
        _state = State::WORK;
      }
      break;

    case State::STOP: {
      bool stop = false;
      const unsigned maxSpeed = (_info.sizeOneFigure.height * 0.21);
      rotate(DEFAULT_TIME_REMAINS, maxSpeed, stop);
      if (stop == true) {
        _time.time = DEFAULT_TIME;
        _state = State::SCORING;
      }
      break;
    }

    case State::WORK:
      if (action == Action::Stop && _time.getRemains() > DEFAULT_TIME_STOP) {
        _state = State::STOP;
        _time.time = DEFAULT_TIME_STOP;
        _time.calculateTheTime();
      } else {
        bool stop = false;
        const unsigned maxSpeed = (_info.sizeOneFigure.height * 0.21);
        rotate(DEFAULT_TIME_REMAINS, maxSpeed, stop);
        if (stop == true) _state = State::SCORING;
      }
      break;

    case State::SCORING: {
      ScoreManager manager(_drums.getFigureWins());
      _info.point = manager.getScore();
      _state = State::START;
      break;
    }

    case State::NoSTATE:
    default:
      break;
  }
}

SlotMachineInfo SlotMachine::getGameInfoForUpdateView(void) {
  _info.data = _drums.getDrums();
  return _info;
}