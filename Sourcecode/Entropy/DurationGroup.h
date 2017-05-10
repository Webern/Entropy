// Copyright (c) Matthew James Briggs

#pragma once

#include "Entropy/Duration.h"

namespace entropy
{
    class DurationGroup
    {
    public:
        DurationGroup();
        int getTicks() const;
        bool getIsCompound() const;
        void simplify();
        void addDuration( const Duration& inDuration );
        const std::vector<Duration>& getDurations() const;

    private:
        std::vector<Duration> myDurations;
    };
}
