#pragma once
#include <vector>

#include "Drum.hpp"

class Drums {
 private:
  std::vector<Drum> _drums;

  void setDirection(void);
  void CreateDrums(const unsigned&, const unsigned&, const Coordinates&,
                   const Size&);

 public:
  Drums(const unsigned&, const unsigned&, const Coordinates&, const Size&);
  ~Drums() = default;

  void rotation();
  std::vector<std::vector<Figure>> getDrums(void);
};
