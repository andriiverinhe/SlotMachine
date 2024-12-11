#pragma once

struct Position
{
    int x;
    int y;
};

enum class FigureType
{
    circle = 0,
    triangle,
    square,
    star
};

constexpr unsigned CountFigureType = (unsigned)FigureType::star + 1;

class Figure
{
private:
    Position _position;
    FigureType _type;

public:
    Figure(const FigureType &, const Position &);
    void move(const int &x, const int &y);

    Position &getPosition();
};
