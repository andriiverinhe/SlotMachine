#pragma once

#include <chrono>

#include "Drums.hpp"
#include "SlotMachineInfo.hpp"

constexpr int DEFAULT_DRUMS = 5;
constexpr int DEFAULT_FIGURE_FROM_DRUM = 12;
constexpr Coordinates DEFAULT_COORDINATES = {0, 0};

constexpr double DEFAULT_TIME = 20;
constexpr double DEFAULT_TIME_STOP = 5;
constexpr double DEFAULT_TIME_REMAINS = 3;

enum class Action { Start, Stop, NoAction };

enum class State { START, WORK, SCORING, STOP, NoSTATE };

struct Time {
  std::chrono::steady_clock::time_point _start;
  std::chrono::steady_clock::time_point _end;

  double time = DEFAULT_TIME;
  bool timeIsSet = false;

  void calculateTheTime();
  bool isOverTime(void);
  double getRemains(void);
};

class SlotMachine {
 private:
  Drums _drums;
  Time _time;
  SlotMachineInfo _info;

  State _state = State::START;
  unsigned speed = 1;

  void initSlotMachineInfo(const unsigned& countDrum,
                           const Size& sizeOneFigure);
  void rotate(const double& remainsTime, const unsigned& maxSpeed, bool& stop);

 public:
  SlotMachine();
  SlotMachine(const unsigned& countDrum, const unsigned& countFigure,
              const Coordinates& startPos, const Size& sizeOneFigure);

  ~SlotMachine() = default;

  void UserInput(const Action& action);
  SlotMachineInfo getGameInfoForUpdateView(void);
};
