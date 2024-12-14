#include "Drum.hpp"

Drum::Drum(const unsigned& countFigure, const Coordinates& startPos,
           const Size& sizeOneFigure) {
  CreateDrum(countFigure, startPos, sizeOneFigure);
}

void Drum::CreateDrum(const unsigned& countFigure, const Coordinates& startPos,
                      const Size& sizeOneFigure) {
  if (_drum.capacity() < countFigure) _drum.reserve(countFigure);

  _startPos = startPos;
  _sizeOneFigure = sizeOneFigure;

  for (unsigned i = 0; i < countFigure; i++) {
    const FigureType t = getRandomFigure();
    const Size s = sizeOneFigure;
    const Coordinates c = {startPos.x, startPos.y + ((int)i * s.height)};
    
    _drum.push_back(Figure(t, c, s));
  }
}

Drum::~Drum() {}

void Drum::setDirection(const Direction& H, const Direction& V) {
  _direction[DIRECTION_HORIZONTAL] = H;
  _direction[DIRECTION_VERTICAL] = V;
}

const Direction* Drum::getDirection(void) { return _direction; }

void Drum::rotation() {
  if (_direction[DIRECTION_HORIZONTAL] == Direction::No &&
      _direction[DIRECTION_VERTICAL] == Direction::No)
    return;
  if (_drum.empty()) return;

  const Direction& H = _direction[DIRECTION_HORIZONTAL];
  const Direction& V = _direction[DIRECTION_VERTICAL];
  const unsigned size = 1;

  for (auto& figure : _drum) {
    figure.move(H, size, V, size);

    if (V == Direction::Down) {
      int p = (_startPos.y + (_sizeOneFigure.height * (_drum.size() - 1)));
      if (figure.getLocation().y > p)
        figure.setLocation(
            {figure.getLocation().x,
             -_sizeOneFigure.height + (figure.getLocation().y - p)});
    }
    if (V == Direction::Up) {
      int p1 = _startPos.y - _sizeOneFigure.height;
      if (figure.getLocation().y == p1)
        figure.setLocation({figure.getLocation().x,
                            _sizeOneFigure.height * ((int)_drum.size() - 1)});
    }
  }
}

std::vector<Figure> Drum::getDrum(void) {
  std::vector<Figure> tmp;

  for (auto& f : _drum) {
    const auto& posY = f.getLocation().y;
    if (posY >= _startPos.y - _sizeOneFigure.height &&
        posY <= (_sizeOneFigure.height * 4))
      tmp.push_back(f);
  }

  return tmp;
}