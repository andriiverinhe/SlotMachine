#pragma once

#include <memory>
#include <vector>

#include "Drum.hpp"

class Drums {
 private:
  static constexpr unsigned COUNT_DRUM = 5;

  Size _sizeSectionDrum = {30, 30};
  unsigned _countDrum;
  std::vector<std::unique_ptr<Drum>> _drums;

  void CreateDrums();

 public:
  Drums(const Size& SizeSectionDrum, const unsigned& CountDrum);
  ~Drums() = default;

  void signalToStart();

  bool rotation();
  void stop();
  std::vector<std::vector<Figure>> getWinFigures(void);
  std::vector<std::vector<Figure>> getFigureFromRange(const unsigned& min,
                                         const unsigned& max);
};
