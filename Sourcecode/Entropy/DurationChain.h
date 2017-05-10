// Copyright (c) Matthew James Briggs

#pragma once

#include "Entropy/DurationGroup.h"

namespace entropy
{
    class DurationChain
    {
    public:
        DurationChain();
        int getTicks() const;
        void addDurationGroup( const DurationGroup& inDurationGroup );
        const std::vector<DurationGroup>& getDurationGroups() const;

    private:
        std::vector<DurationGroup> myDurationGroups;
    };
}
