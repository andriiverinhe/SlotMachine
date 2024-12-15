#include <vector>

#include "Figure.hpp"

class Drum {
 private:
  const unsigned DIRECTION_HORIZONTAL = 0;
  const unsigned DIRECTION_VERTICAL = 1;

  std::vector<Figure> _drum;
  Coordinates _startPos;
  Size _sizeOneFigure;
  Direction _direction[2] = {Direction::No, Direction::No};

  void CreateDrum(const unsigned&, const Coordinates&, const Size&);

 public:
  Drum(const unsigned&, const Coordinates&, const Size&);
  ~Drum();

  void setDirection(const Direction&, const Direction&);
  const Direction* getDirection(void);

  std::vector<Figure> getDrum(void);
  std::vector<Figure> getFigureWins();

  void rotation(const unsigned& size);
  bool isCorrectFigurePositions();
};
