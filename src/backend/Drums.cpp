#include "Drums.hpp"

Drums::Drums(const Size &SizeSectionDrum, const unsigned &CountDrum) : _sizeSectionDrum(SizeSectionDrum), _countDrum(CountDrum)
{
    CreateDrums();
}

void Drums::CreateDrums()
{
    if (_countDrum <= 0)
        _countDrum = COUNT_DRUM;
    _drums.reserve(_countDrum);

    for (unsigned i = 0; i < _countDrum; i++)
    {
        if ((int)i % 2 == 0)
            _drums.push_back(std::make_unique<Drum>(8, Direction::Down, _sizeSectionDrum));
        else
            _drums.push_back(std::make_unique<Drum>(8, Direction::Up, _sizeSectionDrum));
    }
}

void Drums::start()
{
    for (const auto &drum : _drums)
        drum->rotationInThread();
}

void Drums::stop()
{
    for (const auto &drum : _drums)
        drum->stopRotation();
}

int main()
{
    Drums drums({30, 30}, 5);
    drums.start();
    return 0;
}