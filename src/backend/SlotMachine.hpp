#pragma once

#include "Drums.hpp"
#include <chrono>

enum class Action { Start, Stop, NoAction };

enum class State { START, WORK, SCORING, STOP, NoSTATE };

struct Time {
  std::chrono::steady_clock::time_point _start;
  std::chrono::steady_clock::time_point _end;

  double time = 5;
  bool timeIsSet = false;

  void recalculateTheTime();
  bool isOverTime(void);
};

struct GameInfo {
  std::vector<std::vector<Figure>> _data;
};

class SlotMachine {
 private:
  Drums _drums;
  Time _time;
  State _state = State::START;

 public:
  SlotMachine();
  ~SlotMachine() = default;

  void UserInput(const Action &action);
  GameInfo getGameInfoForUpdateView(void);
};
