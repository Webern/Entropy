// Copyright (c) Matthew James Briggs

#include "cpul/cpulTestHarness.h"
#include "Entropy/PitchClass.h"

namespace entropy
{
    TEST( ctorDefault, PitchClass )
    {
        PitchClass p{};
        CHECK_EQUAL( 0, p.getValue() );
        CHECK( Spelling::Cn == p.getSpelling() );
        CHECK( Step::C == p.getStep() );
        CHECK( Alter::NATURAL == p.getAlter() );
        CHECK_EQUAL( 0, p.getAlterAmount() );
    }
    T_END

    TEST( ctorInt, PitchClass )
    {
        PitchClass p{ 6 };
        CHECK_EQUAL( 6, p.getValue() );
        CHECK( Spelling::Fs == p.getSpelling() );
        CHECK( Step::F == p.getStep() );
        CHECK( Alter::SHARP == p.getAlter() );
        CHECK_EQUAL( 1, p.getAlterAmount() );
    }
    T_END

    TEST( ctorSpelling, PitchClass )
    {
        PitchClass p{ Spelling::Bx };
        CHECK_EQUAL( 1, p.getValue() );
        CHECK( Spelling::Bx == p.getSpelling() );
        CHECK( Step::B == p.getStep() );
        CHECK( Alter::DOUBLE_SHARP == p.getAlter() );
        CHECK_EQUAL( 2, p.getAlterAmount() );
    }
    T_END

    TEST( setSpelling, PitchClass )
    {
        PitchClass p{ 6 };
        p.setSpelling( Spelling::Gd );
        CHECK_EQUAL( 5, p.getValue() );
        CHECK( Spelling::Gd == p.getSpelling() );
        CHECK( Step::G == p.getStep() );
        CHECK( Alter::DOUBLE_FLAT == p.getAlter() );
        CHECK_EQUAL( -2, p.getAlterAmount() );
    }
    T_END

    TEST( setValue, PitchClass )
    {
        PitchClass p{ Spelling::Bx };
        p.setValue( 13 );
        CHECK_EQUAL( 11, p.getValue() );
        CHECK( Spelling::Bn == p.getSpelling() );
        CHECK( Step::B == p.getStep() );
        CHECK( Alter::NATURAL == p.getAlter() );
        CHECK_EQUAL( 0, p.getAlterAmount() );
    }
    T_END

    TEST( setAlter, PitchClass )
    {
        PitchClass p{ 6 };
        p.setSpelling( Spelling::Gd );
        p.setAlter( Alter::DOUBLE_SHARP );
        CHECK_EQUAL( 9, p.getValue() );
        CHECK( Spelling::Gx == p.getSpelling() );
        CHECK( Step::G == p.getStep() );
        CHECK( Alter::DOUBLE_SHARP == p.getAlter() );
        CHECK_EQUAL( 2, p.getAlterAmount() );
    }
    T_END

    TEST( setAlterAmount, PitchClass )
    {
        PitchClass p{ Spelling::Bx };
        p.setValue( 7 );
        p.setAlterAmount( -1 );
        CHECK_EQUAL( 6, p.getValue() );
        CHECK( Spelling::Gb == p.getSpelling() );
        CHECK( Step::G == p.getStep() );
        CHECK( Alter::FLAT == p.getAlter() );
        CHECK_EQUAL( -1, p.getAlterAmount() );
    }
    T_END
}

