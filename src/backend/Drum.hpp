#pragma once

#include <atomic>
#include <memory>
#include <thread>
#include <vector>

#include "Figure.hpp"

enum class Direction { Up, Down };

struct Size {
  unsigned width = 30;
  unsigned height = 30;
};

struct Time {
  std::chrono::steady_clock::time_point _start;
  std::chrono::steady_clock::time_point _end;

  double time = 3;
  bool timeIsSet = false;

  void recalculateTheTime();
  bool isOverTime(void);
};

class Drum {
 private:
  static constexpr unsigned COUNT_FIGURE = 8;
  static constexpr double TIME_FOR_WAIT = 3;

  unsigned _countFigure;
  std::vector<Figure> _drum;
  Direction _direction = Direction::Down;
  Size _sizeSection;

  bool _isRotation = false;

  Time _time;

  void CreateDrum();
  Position getPositionFigure(unsigned indexSection);
  bool checkRange(const unsigned &, const unsigned &, const Figure &);

 public:
  Drum(void);
  Drum(const unsigned count, const Size &SizeSection, const double &time);
  Drum(const unsigned count, const Direction direction, const Size &SizeSection,
       const double &time);

  ~Drum() = default;

  void setIsRotation(const bool &);
  bool getIsRotation(void);

  void rotation();
  void normalize();

  std::vector<Figure> getWinFigure(const unsigned &CountWin);

  std::vector<Figure> getFigureFromRange(const unsigned &min,
                                         const unsigned &max);
};
