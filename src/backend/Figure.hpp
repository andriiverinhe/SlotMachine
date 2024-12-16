#pragma once

constexpr int COUNT_FIGURE = 4;

struct Coordinates {
  int x;
  int y;
};

struct Size {
  int width;
  int height;
};

enum class FigureType { circle = 0, triangle, square, star };
enum class Direction { Up = 0, Down, Left, Right, No };

class Figure {
 private:
  FigureType _figure;
  Coordinates _location;
  Size _size;

 public:
  Figure(const FigureType&, const Coordinates&, const Size&);
  ~Figure();

  FigureType getType(void) const;

  Coordinates getLocation(void);
  const Coordinates& getLocation(void) const;

  Size getSize(void);

  void setLocation(Coordinates);
  void setSize(Size);
  void setType(FigureType);

  void move(const Direction&, const unsigned&, const Direction&,
            const unsigned&);
};

FigureType getRandomFigure();