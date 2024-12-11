#include "Figure.hpp"

Figure::Figure(const FigureType &type, const Position &position) : _type(type), _position(position) {}
void Figure::move(const int &x, const int &y)
{
    this->_position.x += x;
    this->_position.y += y;
}

Position &Figure::getPosition()
{
    return _position;
}