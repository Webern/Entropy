#include "cpulTestHarness.h"
#include "Range.h"

using namespace entropy;
using namespace std;

TEST(constructor01, Range)
{
    Range r;
    CHECK( true );
}
TEST( constructor02, Range)
{
    Range r{ Pitch{ "Ab3" }, Pitch{ "C6" } };
    CHECK_EQUAL( Pitch( "Ab3" ), r.getLow() )
    CHECK_EQUAL( Pitch( "C6" ), r.getHigh() )
}
TEST( inrange01, Range )
{
    Range r{ Pitch{ "G4" }, Pitch{ "Bb4" } };
    Pitch inRange{ "A4" };
    Pitch belowRange{ "C4" };
    Pitch aboveRange{ "B4" };
    CHECK( r.isInRange( inRange ) );
    CHECK( ! r.isInRange( belowRange ) );
    CHECK( ! r.isInRange( aboveRange ) );
    CHECK( ! r.isAboveRange( inRange ) );
    CHECK( ! r.isAboveRange( belowRange ) );
    CHECK( r.isAboveRange( aboveRange ) );
    CHECK( ! r.isBelowRange( inRange ) );
    CHECK( r.isBelowRange( belowRange ) );
    CHECK( ! r.isBelowRange( aboveRange ) );
}
TEST( inrange02, Range )
{
    Range r{ Pitch{ "A3" }, Pitch{ "A6" } };
    Pitch inRange{ "C4" };
    Pitch belowRange{ "Bb2" };
    Pitch aboveRange{ "Ab7" };
    CHECK( r.isInRange( inRange ) );
    CHECK( ! r.isInRange( belowRange ) );
    CHECK( ! r.isInRange( aboveRange ) );
    CHECK( ! r.isAboveRange( inRange ) );
    CHECK( ! r.isAboveRange( belowRange ) );
    CHECK( r.isAboveRange( aboveRange ) );
    CHECK( ! r.isBelowRange( inRange ) );
    CHECK( r.isBelowRange( belowRange ) );
    CHECK( ! r.isBelowRange( aboveRange ) );
}