#include "Figure.hpp"

#include <random>

Figure::Figure(const FigureType& type, const Coordinates& location,
               const Size& size)
    : _figure(type), _location(location), _size(size) {}

Figure::~Figure() {}

FigureType Figure::getType(void) const { return _figure; }

Coordinates Figure::getLocation(void) { return _location; }

const Coordinates& Figure::getLocation(void) const { return _location; }

Size Figure::getSize(void) { return _size; }

void Figure::setLocation(Coordinates location) { _location = location; }

void Figure::setSize(Size size) { _size = size; }

void Figure::setType(FigureType figure) { _figure = figure; }

void Figure::move(const Direction& H, const unsigned& sizeH, const Direction& V,
                  const unsigned& sizeV) {
  switch (H) {
    case Direction::Left:
      _location.x -= sizeH;
      break;
    case Direction::Right:
      _location.x += sizeH;
      break;
    case Direction::No:
      break;
  }

  switch (V) {
    case Direction::Up:
      _location.y -= sizeV;
      break;
    case Direction::Down:
      _location.y += sizeV;
      break;
    case Direction::No:
      break;
  }
}

FigureType getRandomFigure() { return static_cast<FigureType>(rand() % 4); }