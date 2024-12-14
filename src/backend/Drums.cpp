#include "Drums.hpp"

Drums::Drums(const unsigned& numDrums, const unsigned& countFigure,
             const Coordinates& startPos, const Size& sizeOneFigure) {
  CreateDrums(numDrums, countFigure, startPos, sizeOneFigure);
}

void Drums::CreateDrums(const unsigned& numDrums, const unsigned& countFigure,
                        const Coordinates& startPos,
                        const Size& sizeOneFigure) {
  if (_drums.capacity() < numDrums) _drums.reserve(numDrums);

  for (unsigned i = 0; i < numDrums; ++i)
    _drums.push_back(Drum(countFigure, startPos, sizeOneFigure));
  setDirection();
}

void Drums::setDirection(void) {
  for (int i = 0; i < _drums.size(); ++i) {
    if (i % 2 == 0)
      _drums[i].setDirection(Direction::No, Direction::Down);
    else
      _drums[i].setDirection(Direction::No, Direction::Up);
  }
}

void Drums::rotation() {
  for (auto& drum : _drums) drum.rotation();
}

bool Drums::normalize(void) {
  unsigned c = 0;

  for (auto& drum : _drums) {
    if (drum.isCorrectFigurePositions())
      c++;
    else
      drum.rotation();
  }
  
  return c == _drums.size();
}

std::vector<std::vector<Figure>> Drums::getDrums(void) {
  std::vector<std::vector<Figure>> res;
  res.reserve(_drums.size());
  for (auto& drum : _drums) res.push_back(drum.getDrum());
  return res;
}