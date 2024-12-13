#include "Drums.hpp"

Drums::Drums(const Size &SizeSectionDrum, const unsigned &CountDrum)
    : _sizeSectionDrum(SizeSectionDrum), _countDrum(CountDrum) {
  CreateDrums();
}

void Drums::CreateDrums() {
  if (_countDrum <= 0) _countDrum = COUNT_DRUM;
  _drums.reserve(_countDrum);

  for (unsigned i = 0; i < _countDrum; i++) {
    if ((int)i % 2 == 0)
      _drums.push_back(
          std::make_unique<Drum>(8, Direction::Down, _sizeSectionDrum, 3));
    else
      _drums.push_back(
          std::make_unique<Drum>(8, Direction::Up, _sizeSectionDrum, 3));
  }
}

void Drums::signalToStart() {
  for (const auto &drum : _drums) drum->setIsRotation(true);
}

bool Drums::rotation() {
  bool isStopedDrums = true;

  for (const auto &drum : _drums) {
    if (drum->getIsRotation() == true) {
      drum->rotation();
      if (drum->getIsRotation() == true) isStopedDrums = false;
    }
  }

  return isStopedDrums;
}

void Drums::stop() {
  for (const auto &drum : _drums) drum->normalize();
}

std::vector<std::vector<Figure>> Drums::getWinFigures(void) {
  std::vector<std::vector<Figure>> win;
  win.reserve(_countDrum);
  for (const auto &drum : _drums) win.push_back(drum->getWinFigure(3));
  return win;
}

std::vector<std::vector<Figure>> Drums::getFigureFromRange(
    const unsigned &min, const unsigned &max) {
      
  std::vector<std::vector<Figure>> figures;
  for (const auto &drum : _drums) {
    figures.push_back(drum->getFigureFromRange(min, max));
  }
  return figures;
}

// int main() {
//   Drums drums({30, 30}, 5);
//   drums.rotation();
//   return 0;
// }