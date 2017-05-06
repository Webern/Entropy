// Copyright (c) Matthew James Briggs

#pragma once

#include <cstdint>

namespace entropy
{
    constexpr const int MIN_OCTAVE = -1;
    constexpr const int MAX_OCTAVE = 9;
    constexpr const int TICKS_PER_QUARTER = 20160;
    constexpr const int TICKS_PER_HALF = TICKS_PER_QUARTER * 2;
    constexpr const int TICKS_PER_WHOLE = TICKS_PER_QUARTER * 4;
    constexpr const int TICKS_PER_8TH = TICKS_PER_QUARTER / 2;
    constexpr const int TICKS_PER_16TH = TICKS_PER_QUARTER / 4;
    constexpr const int TICKS_PER_32ND = TICKS_PER_QUARTER / 8;
    constexpr const int TICKS_PER_64TH = TICKS_PER_QUARTER / 16;
    constexpr const int MAX_TUPLET_ACTUAL = 9;
    constexpr const int MAX_TUPLET_NORMAL = 8;
    constexpr const int MAX_DOTS = 2;
}
