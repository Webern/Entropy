// Copyright (c) Matthew James Briggs

#include "cpul/cpulTestHarness.h"
#include "Entropy/Pitch.h"

namespace entropy
{
    TEST( basicTest, Pitch )
    {
        Pitch p{ Spelling::Bb, 6 };
        CHECK( Spelling::Bb == p.getPitchClass().getSpelling() );
        CHECK_EQUAL( 6, p.getOctave() );
    }
    T_END

    TEST( midiNote60, Pitch )
    {
        Pitch p{ Spelling::Cn, 4 };
        CHECK_EQUAL( 60, p.getMidiNote() );
    }
    T_END

    TEST( midiNote00, Pitch )
    {
        Pitch p{ Spelling::Cn, -1 };
        CHECK_EQUAL( 0, p.getMidiNote() );
    }
    T_END

    TEST( midiNote11, Pitch )
    {
        Pitch p{ Spelling::Ax, -1 };
        CHECK_EQUAL( 11, p.getMidiNote() );
    }
    T_END

    TEST( midiNote33, Pitch )
    {
        Pitch p{ Spelling::An, 1 };
        CHECK_EQUAL( 33, p.getMidiNote() );
    }
    T_END

    TEST( midiNote127, Pitch )
    {
        Pitch p{ Spelling::Gn, 9 };
        CHECK_EQUAL( 127, p.getMidiNote() );
    }
    T_END
}
