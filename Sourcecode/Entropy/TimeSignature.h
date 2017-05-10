// Copyright (c) Matthew James Briggs

#pragma once

#include "Entropy/DurationChain.h"

namespace entropy
{
    class TimeSignature
    {
    public:
        TimeSignature();

    private:
        int myTopNumber;
        int myBottomNumber;
        DurationChain myDurationChain;
    };
}
