// Copyright (c) Matthew James Briggs

#include "cpul/cpulTestHarness.h"
#include "Entropy/TimeSignature.h"
#include "Entropy/Constants.h"

namespace entropy
{
    TEST( test01, TimeSignature )
    {
        TimeSignature t{};
        CHECK_EQUAL( 4, t.getTopNumber() );
        CHECK_EQUAL( 4, t.getBottomNumber() );
        CHECK_EQUAL( 4 * TICKS_PER_QUARTER, t.getTicks() );
    }
    T_END;

    
    TEST( test02, TimeSignature )
    {
        TimeSignature t{5, 8};
        CHECK_EQUAL( 5, t.getTopNumber() );
        CHECK_EQUAL( 8, t.getBottomNumber() );
        CHECK_EQUAL( 5 * TICKS_PER_8TH, t.getTicks() );
    }
    T_END;


    TEST( test03, TimeSignature )
    {
        TimeSignature t{7, 8};
        CHECK_EQUAL( 7, t.getTopNumber() );
        CHECK_EQUAL( 8, t.getBottomNumber() );
        CHECK_EQUAL( 7 * TICKS_PER_8TH, t.getTicks() );
        t.setSimpleGrouping( { 2, 2, 3 } );

        const auto beatLengths = t.getBeatLengths();
        CHECK_EQUAL( 3, beatLengths.size() );
        auto beatIter = beatLengths.cbegin();

        CHECK_EQUAL( 2 * TICKS_PER_8TH, *beatIter );
        ++beatIter;
        CHECK( beatIter != beatLengths.cend() )

        CHECK_EQUAL( 2 * TICKS_PER_8TH, *beatIter );
        ++beatIter;
        CHECK( beatIter != beatLengths.cend() )

        CHECK_EQUAL( 3 * TICKS_PER_8TH, *beatIter );
    }
    T_END;


    TEST( test04, TimeSignature )
    {
        TimeSignature t{7, 8};
        CHECK_EQUAL( 7, t.getTopNumber() );
        CHECK_EQUAL( 8, t.getBottomNumber() );
        CHECK_EQUAL( 7 * TICKS_PER_8TH, t.getTicks() );
        t.setSimpleGrouping( { 2, 2, 3 } );

        int position = 0;
        const auto beatLocations = t.getBeatLocations();
        CHECK_EQUAL( 3, beatLocations.size() );
        auto beatIter = beatLocations.cbegin();
        CHECK_EQUAL( position, *beatIter );
        ++beatIter;
        CHECK( beatIter != beatLocations.cend() )

        position += ( 2 * TICKS_PER_8TH );
        CHECK_EQUAL( position, *beatIter );
        ++beatIter;
        CHECK( beatIter != beatLocations.cend() )

        position += ( 2 * TICKS_PER_8TH );
        CHECK_EQUAL( position, *beatIter );
        ++beatIter;
    }
    T_END;
}
