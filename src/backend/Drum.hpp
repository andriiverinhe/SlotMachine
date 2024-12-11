#pragma once

#include "Figure.hpp"
#include <vector>
#include <thread>
#include <memory>
#include <atomic>

enum class Direction
{
    Up,
    Down
};

struct Size
{
    unsigned width = 30;
    unsigned height = 30;
};

class Drum
{
private:
    static constexpr unsigned COUNT_FIGURE = 8;

    unsigned _countFigure;
    std::vector<Figure> _drum;
    Direction _direction = Direction::Down;
    Size _sizeSection;

    double _rotationTime = 2;

    std::atomic<bool> _stopRotation = false;
    std::unique_ptr<std::thread> _rotation;

    void CreateDrum();
    Position getPositionFigure(unsigned indexSection);
    void normalize();

public:
    Drum(void);
    Drum(const unsigned count, const Size &SizeSection);
    Drum(const unsigned count, const Direction direction, const Size &SizeSection);

    ~Drum()
    {
        if (_rotation && _rotation->joinable())
        {
            _rotation->join();
            _rotation.reset();
        }
    }

    void rotation();
    void rotationInThread();
    void stopRotation();

    std::vector<Figure> getWinFigure(const unsigned& CountWin);
};
