// Copyright (c) Matthew James Briggs

#include "Entropy/TimeSignature.h"
#include "Entropy/Constants.h"
#include "Entropy/Throw.h"

namespace entropy
{
    TimeSignature::TimeSignature()
    : myTopNumber{ 4 }
    , myBottomNumber{ 4 }
    , myDurationChain{}
    {
        const auto d = Duration::getDurationPrototypes().at(TIME_SIGNATURE_4);Duration::getDurationPrototypes().at(TIME_SIGNATURE_4);

        for( int i = 0; i < 4; ++i )
        {
            DurationGroup dg{};
            dg.addDuration(d);
            myDurationChain.addDurationGroup(dg);
        }
    }
}
