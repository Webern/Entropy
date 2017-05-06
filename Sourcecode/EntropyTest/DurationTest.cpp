// Copyright (c) Matthew James Briggs

#include "cpul/cpulTestHarness.h"
#include "Entropy/Duration.h"
#include "Entropy/Constants.h"

namespace entropy
{
    TEST( x, Duration )
    {
        Duration d{};
        const auto& proto = d.getDurationPrototypes();
        CHECK_EQUAL( TICKS_PER_QUARTER, d.getTicks() )
    }
    T_END


}
