#include "Drum.hpp"
#include <iostream>
#include <chrono>
#include <thread>

Drum::Drum(void) : _countFigure(COUNT_FIGURE) { CreateDrum(); }
Drum::Drum(const unsigned count, const Size &SizeSection) : _countFigure(count), _sizeSection(SizeSection) { CreateDrum(); }
Drum::Drum(const unsigned count, const Direction direction, const Size &SizeSection) : _countFigure(count), _direction(direction), _sizeSection(SizeSection) { CreateDrum(); }

Position Drum::getPositionFigure(unsigned indexSection)
{
    const unsigned &h = _sizeSection.height;
    const unsigned &w = _sizeSection.width;

    int y = h * indexSection + h / 2;
    int x = w / 2;
    return {x, y};
}

void Drum::CreateDrum()
{
    if (this->_countFigure <= 0)
        _countFigure = COUNT_FIGURE;

    this->_drum.reserve(_countFigure);
    unsigned figure = 0;

    for (unsigned i = 0; i < _countFigure; i++)
    {
        _drum.push_back(*(new Figure((FigureType)figure++, getPositionFigure(i))));
        if (figure >= CountFigureType)
            figure = 0;
    }
}

void Drum::normalize()
{
    unsigned firstMid = this->_sizeSection.height / 2;
    int x = 0;
    int y = 0;
    if (_direction == Direction::Up)
    {
        x = 0;
        y = -1;
    }
    else
    {
        x = 0;
        y = 1;
    }
    unsigned countOk = 0;
    while (countOk != _countFigure)
    {
        countOk = 0;
        for (auto &figure : _drum)
        {
            bool move_code = true;

            unsigned yPosCurrentFigure = figure.getPosition().y;
            for (size_t i = 0; i < _countFigure; i++)
            {

                unsigned midForCurrentFigure = i * this->_sizeSection.height + firstMid;

                if (yPosCurrentFigure == midForCurrentFigure)
                {
                    move_code = false;
                    countOk++;
                    continue;
                }
            }

            if (move_code == true)
            {
                figure.move(x, y);
                auto &pos = figure.getPosition();

                if (pos.y >= _countFigure * _sizeSection.height && _direction == Direction::Down)
                    pos.y = 0;
                if (pos.y == 0 && _direction == Direction::Up)
                    pos.y = _countFigure * _sizeSection.height;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}

void Drum::rotation()
{
    if (_drum.empty())
        return;

    int x = 0;
    int y = 0;
    if (_direction == Direction::Up)
    {
        x = 0;
        y = -1;
    }
    else
    {
        x = 0;
        y = 1;
    }

    auto startTime = std::chrono::steady_clock::now();
    auto endTime = startTime + std::chrono::duration<double>(_rotationTime);
    std::cout << "Start\n";

    while (std::chrono::steady_clock::now() < endTime && _stopRotation == false)
    {
        std::cout << "Work\n";
        for (auto &figure : _drum)
        {
            figure.move(x, y);
            auto &pos = figure.getPosition();

            if (pos.y >= _countFigure * _sizeSection.height && _direction == Direction::Down)
                pos.y = 0;
            if (pos.y == 0 && _direction == Direction::Up)
                pos.y = _countFigure * _sizeSection.height;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    normalize();
}

void Drum::rotationInThread()
{
    if (_rotation && _rotation->joinable())
        stopRotation();

    _stopRotation = false;
    _rotation = std::make_unique<std::thread>(&Drum::rotation, this);
}

void Drum::stopRotation()
{
    std::cout << "Stop Rotation function!" << std::endl;
    _stopRotation = true;
    if (_rotation && _rotation->joinable())
    {
        _rotation->join();
        _rotation.reset();
    }
}

std::vector<Figure> Drum::getWinFigure(const unsigned &CountWin)
{
    unsigned countWin = CountWin;
    if (countWin > _drum.size())
        countWin = _drum.size();

    std::vector<Figure> winFigure;
    winFigure.reserve(countWin);
    unsigned firstMid = this->_sizeSection.height / 2;

    for (unsigned i = 0; i < countWin; i++)
    {
        unsigned mid = i * this->_sizeSection.height + firstMid;
        for (auto figure : _drum)
        {
            if (figure.getPosition().y == mid)
                winFigure.push_back(figure);
        }
    }
    return winFigure;
}

// int main()
// {
//     Drum drum;
//     // drum.rotation();
//     drum.rotationInThread();
//     // auto win = drum.getWinFigure(3);
// }