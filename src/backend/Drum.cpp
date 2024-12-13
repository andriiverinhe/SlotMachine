#include "Drum.hpp"

#include <chrono>
#include <iostream>
#include <thread>

Drum::Drum(void) : _countFigure(COUNT_FIGURE) {
  _time.time = TIME_FOR_WAIT;
  CreateDrum();
}

Drum::Drum(const unsigned count, const Size &SizeSection, const double &time)
    : _countFigure(count), _sizeSection(SizeSection) {
  _time.time = time;
  CreateDrum();
}
Drum::Drum(const unsigned count, const Direction direction,
           const Size &SizeSection, const double &time)
    : _countFigure(count), _direction(direction), _sizeSection(SizeSection) {
  _time.time = time;
  CreateDrum();
}

Position Drum::getPositionFigure(unsigned indexSection) {
  const unsigned &h = _sizeSection.height;
  const unsigned &w = _sizeSection.width;

  int y = h * indexSection + h / 2;
  int x = w / 2;
  return {x, y};
}

void Drum::setIsRotation(const bool &rotation) { _isRotation = rotation; }

bool Drum::getIsRotation(void) { return _isRotation; }

void Drum::CreateDrum() {
  if (this->_countFigure <= 0) _countFigure = COUNT_FIGURE;

  this->_drum.reserve(_countFigure);
  unsigned figure = 0;

  for (unsigned i = 0; i < _countFigure; i++) {
    _drum.push_back(*(new Figure((FigureType)figure++, getPositionFigure(i))));
    if (figure >= CountFigureType) figure = 0;
  }
}

void Drum::normalize() {
  unsigned firstMid = this->_sizeSection.height / 2;
  int x = 0;
  int y = 0;
  if (_direction == Direction::Up) {
    x = 0;
    y = -1;
  } else {
    x = 0;
    y = 1;
  }
  unsigned countOk = 0;
  while (countOk != _countFigure) {
    countOk = 0;
    for (auto &figure : _drum) {
      bool move_code = true;

      unsigned yPosCurrentFigure = figure.getPosition().y;
      for (size_t i = 0; i < _countFigure; i++) {
        unsigned midForCurrentFigure = i * this->_sizeSection.height + firstMid;

        if (yPosCurrentFigure == midForCurrentFigure) {
          move_code = false;
          countOk++;
          break;
          ;
        }
      }

      if (move_code == true) {
        figure.move(x, y);
        auto &pos = figure.getPosition();

        if (pos.y >= _countFigure * _sizeSection.height &&
            _direction == Direction::Down)
          pos.y = 0;
        if (pos.y == 0 && _direction == Direction::Up)
          pos.y = _countFigure * _sizeSection.height;
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
  }
}

bool Time::isOverTime(void) {
  return (_end < std::chrono::steady_clock::now());
}

void Time::recalculateTheTime() {
  _start = std::chrono::steady_clock::now();
  _end = _start + std::chrono::seconds(static_cast<int>(time));

  // timeIsOver = isOverTime();
  timeIsSet = true;
}

void Drum::rotation() {
  if (_drum.empty()) return;

  if (_isRotation == true) {
    if (_time.timeIsSet == false) _time.recalculateTheTime();
    if (_time.isOverTime()) {
      _time.timeIsSet = false;
      _isRotation = false;
      normalize();
      return;
    }
  } else
    return;

  int x = 0;
  int y = 0;
  if (_direction == Direction::Up) {
    x = 0;
    y = -1;
  } else {
    x = 0;
    y = 1;
  }

  std::cout << "Work\n";
  for (auto &figure : _drum) {
    figure.move(x, y);
    auto &pos = figure.getPosition();

    if (pos.y >= _countFigure * _sizeSection.height &&
        _direction == Direction::Down)
      pos.y = 0;
    if (pos.y == 0 && _direction == Direction::Up)
      pos.y = _countFigure * _sizeSection.height;
  }
}

std::vector<Figure> Drum::getWinFigure(const unsigned &CountWin) {
  unsigned countWin = CountWin;
  if (countWin > _drum.size()) countWin = _drum.size();

  std::vector<Figure> winFigure;
  winFigure.reserve(countWin);
  unsigned firstMid = this->_sizeSection.height / 2;

  for (unsigned i = 0; i < countWin; i++) {
    unsigned mid = i * this->_sizeSection.height + firstMid;
    for (auto figure : _drum) {
      if (figure.getPosition().y == mid) winFigure.push_back(figure);
    }
  }
  return winFigure;
}

bool Drum::checkRange(const unsigned &min, const unsigned &max,
                      const Figure &figure) {
  if (max < min) return false;

  auto pos = figure.getPosition();

  auto posMinY = pos.y - _sizeSection.height / 2;
  auto posMaxY = pos.y + _sizeSection.height / 2;

  if (posMinY <= 0) posMinY = _countFigure * _sizeSection.height + posMinY;
  if (posMaxY >= _countFigure * _sizeSection.height)
    posMaxY = posMaxY - _countFigure * _sizeSection.height;

  bool code = false;

  if ((posMinY >= min && posMinY <= max) || (posMaxY <= max && posMaxY >= min))
    code = true;

  return code;
}

std::vector<Figure> Drum::getFigureFromRange(const unsigned &min,
                                             const unsigned &max) {
  if (min > max) return {};

  std::vector<Figure> figureInRange;

  for (const auto &figure : _drum)

    if (checkRange(min, max, figure)) {
      Figure tmp = figure;
      tmp.getPosition().y -= _sizeSection.height / 2;

      if (tmp.getPosition().y >= _sizeSection.height * _countFigure &&
          _direction == Direction::Down)
        tmp.getPosition().y -= _sizeSection.height * _countFigure;
      if (tmp.getPosition().y < 0 && _direction == Direction::Up)
        tmp.getPosition().y += _sizeSection.height * _countFigure;

      figureInRange.push_back(tmp);
    }

  return figureInRange;
}

// int main()
// {
//     Drum drum;
//     // drum.rotation();
//     drum.rotationInThread();
//     // auto win = drum.getWinFigure(3);
// }