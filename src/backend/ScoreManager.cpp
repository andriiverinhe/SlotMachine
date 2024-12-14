#include "ScoreManager.hpp"

unsigned Point::getAllPoint() const {
  return Circle + Triangle + Squere + Star;
}

void Point::convertToPoint(const FigureType& type, const unsigned& count) {
  if (count < MINIMUM_NUMBER_OF_MATCHES) return;

  switch (type) {
    case FigureType::circle:
      Circle = count * POINT_FOR_ONE_CIRCLE;
      break;
    case FigureType::triangle:
      Triangle = count * POINT_FOR_ONE_TRIANGLE;
      break;
    case FigureType::square:
      Squere = count * POINT_FOR_ONE_SQUERE;
      break;
    case FigureType::star:
      Star = count * POINT_FOR_ONE_STAR;
      break;
    default:
      break;
  }
}

ScoreManager::ScoreManager(const std::vector<std::vector<Figure>>& f) {
  _figures = f;
  calculate();
}

ScoreManager::~ScoreManager() {}

void ScoreManager::setFigures(const std::vector<std::vector<Figure>>& f) {
  _figures = f;
  calculate();
}

unsigned ScoreManager::getScore() { return _point.getAllPoint(); }

Point ScoreManager::getPoint() { return _point; }

void ScoreManager::calculate() {
  unsigned count_circle = 0, count_triangle = 0, count_squere = 0,
           count_star = 0;

  for (const auto& i : _figures)
    for (const auto& j : i) {
      switch (j.getType()) {
        case FigureType::circle:
          count_circle++;
          break;
        case FigureType::triangle:
          count_triangle++;
          break;
        case FigureType::square:
          count_squere++;
          break;
        case FigureType::star:
          count_star++;
          break;

        default:
          break;
      }
    }

  _point.convertToPoint(FigureType::circle, count_circle);
  _point.convertToPoint(FigureType::triangle, count_triangle);
  _point.convertToPoint(FigureType::square, count_squere);
  _point.convertToPoint(FigureType::star, count_star);
}
