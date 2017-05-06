// Copyright (c) Matthew James Briggs

#include "cpul/cpulTestHarness.h"
#include "Entropy/Score.h"

namespace entropy
{
    TEST( x, Score )
    {
        Score s{};
        CHECK( &s != nullptr )
    }
    T_END
}
