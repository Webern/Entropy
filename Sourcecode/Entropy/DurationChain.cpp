// Copyright (c) Matthew James Briggs

#include "DurationChain.h"

namespace entropy
{
    DurationChain::DurationChain()
    : myDurationGroups{}
    {

    }


    int DurationChain::getTicks() const
    {
        int result = 0;

        for( const auto& group : getDurationGroups() )
        {
            result += group.getTicks();
        }

        return result;
    }


    void DurationChain::addDurationGroup( const DurationGroup& inDurationGroup )
    {
        myDurationGroups.push_back( inDurationGroup );
    }


    const std::vector<DurationGroup>&
    DurationChain::getDurationGroups() const
    {
        return myDurationGroups;
    }
}
