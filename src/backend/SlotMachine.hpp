#pragma once

#include <chrono>

#include "Drums.hpp"
#include "SlotMachineInfo.hpp"

constexpr int DEFAULT_DRUMS = 5;
constexpr int DEFAULT_FIGURE_FROM_DRUM = 12;
constexpr Coordinates DEFAULT_COORDINATES = {0, 0};

enum class Action { Start, Stop, NoAction };

enum class State { START, WORK, SCORING, STOP, NoSTATE };

constexpr int DEFAULT_TIME = 20;
constexpr int DEFAULT_TIME_STOP = 10;

struct Time {
  std::chrono::steady_clock::time_point _start;
  std::chrono::steady_clock::time_point _end;

  double time = DEFAULT_TIME;
  double remains = 0;
  bool timeIsSet = false;

  void calculateTheTime();
  bool isOverTime(void);
};

class SlotMachine {
 private:
  Drums _drums;
  Time _time;
  GameInfo _gameInfo;

  State _state = State::START;
  unsigned size = 1;

 public:
  SlotMachine();
  SlotMachine(const unsigned& countDrum, const unsigned& countFigure,
              const Coordinates& startPos, const Size& sizeOneFigure);

  void setTime(const double time);

  ~SlotMachine() = default;

  void UserInput(const Action& action);
  GameInfo getGameInfoForUpdateView(void);
};
