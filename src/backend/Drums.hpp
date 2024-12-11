#pragma once

#include "Drum.hpp"
#include <vector>
#include <memory>

class Drums
{
private:
    static constexpr unsigned COUNT_DRUM = 5;

    Size _sizeSectionDrum = {30, 30};
    unsigned _countDrum;
    std::vector<std::unique_ptr<Drum>> _drums;

    void CreateDrums();

public:
    Drums(const Size& SizeSectionDrum, const unsigned& CountDrum);
    ~Drums() = default;

    void start();
    void stop();
    
};

