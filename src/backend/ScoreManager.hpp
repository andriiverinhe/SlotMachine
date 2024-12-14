#pragma once

#include <vector>

#include "Figure.hpp"

struct Point {
  unsigned Circle = 0;
  unsigned Triangle = 0;
  unsigned Squere = 0;
  unsigned Star = 0;

  unsigned getAllPoint() const;

  void convertToPoint(const FigureType&, const unsigned&);
};

constexpr unsigned MINIMUM_NUMBER_OF_MATCHES = 3;

constexpr unsigned POINT_FOR_ONE_CIRCLE = 10;
constexpr unsigned POINT_FOR_ONE_TRIANGLE = 30;
constexpr unsigned POINT_FOR_ONE_SQUERE = 60;
constexpr unsigned POINT_FOR_ONE_STAR = 100;

class ScoreManager {
 private:
  std::vector<std::vector<Figure>> _figures;
  Point _point;

  void calculate();

 public:
  ScoreManager(const std::vector<std::vector<Figure>>&);
  ~ScoreManager();

  void setFigures(const std::vector<std::vector<Figure>>&);

  unsigned getScore();
  Point getPoint();
};