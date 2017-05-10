// Copyright (c) Matthew James Briggs

#include "Entropy/DurationGroup.h"
#include "Entropy/Throw.h"

namespace entropy
{
    DurationGroup::DurationGroup()
    : myDurations{}
    {

    }


    int DurationGroup::getTicks() const
    {
        int result = 0;
        for( const auto& duration : getDurations() )
        {
            result += duration.getTicks();
        }
        return result;
    }


    bool DurationGroup::getIsCompound() const
    {
        return myDurations.size() > 0;
    }


    void DurationGroup::simplify()
    {
        ENTROPY_THROW( "not implemented" );
    }


    void DurationGroup::addDuration( const Duration& inDuration )
    {
        myDurations.push_back(inDuration);
    }


    const std::vector<Duration>& DurationGroup::getDurations() const
    {
        return myDurations;
    }
}
