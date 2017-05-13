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
    constexpr const int TIME_SIGNATURE_1 = TICKS_PER_WHOLE;
    constexpr const int TIME_SIGNATURE_2 = TICKS_PER_HALF;
    constexpr const int TIME_SIGNATURE_4 = TICKS_PER_QUARTER;
    constexpr const int TIME_SIGNATURE_8 = TICKS_PER_8TH;
    constexpr const int TIME_SIGNATURE_16 = TICKS_PER_16TH;
    constexpr const int TIME_SIGNATURE_32 = TICKS_PER_32ND;
    constexpr const int TIME_SIGNATURE_64 = TICKS_PER_64TH;
    constexpr const int MAX_TUPLET_ACTUAL = 9;
    constexpr const int MAX_TUPLET_NORMAL = 8;
    constexpr const int MAX_DOTS = 2;
    constexpr const int MAX_TIME_SIGNATURE_TOP = 99;
    constexpr const int DYNAMIC_PPP = 1;
    constexpr const int DYNAMIC_PP = 2;
    constexpr const int DYNAMIC_P = 3;
    constexpr const int DYNAMIC_MP = 4;
    constexpr const int DYNAMIC_MF = 5;
    constexpr const int DYNAMIC_F = 6;
    constexpr const int DYNAMIC_FF = 7;
    constexpr const int DYNAMIC_FFF = 8;
}
