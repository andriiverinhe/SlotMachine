#pragma once
#include <vector>

#include "Figure.hpp"

constexpr int DEFAULT_WIDTH = 240;
constexpr int DEFAULT_HEIGHT = 240;
constexpr int DEFAULT_POINT = 0;

struct GameInfo {
  std::vector<std::vector<Figure>> data;
  Size sizeOneFigure = {DEFAULT_WIDTH, DEFAULT_HEIGHT};
  unsigned point = DEFAULT_POINT;
};