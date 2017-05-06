// Copyright (c) Matthew James Briggs

#pragma once

#include "mx/api/DurationData.h"

#include <map>

namespace entropy
{
    struct Tuplet
    {
        int actual;
        int normal;
    };

    class Duration
    {
    public:
        Duration();

        mx::api::DurationData getDurationData() const;
        Tuplet getTuplet() const;
        void setTuplet(Tuplet inTuplet);
        void clearTuplet();
        int getTicks() const;

        static const std::vector<const int>& getDurationSizes();
        static const std::map<const int, const Duration>& getDurationPrototypes();
        static const std::map<const int, const mx::api::DurationName>& getDurationNames();
        static int applyDots(int inTicks, int inDots);
        static int applyTuplet(int inTicks, Tuplet inTuplet);

    private:
        mx::api::DurationData myDuration;

    private:
        void setTicks();
    };
}
