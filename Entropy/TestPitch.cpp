#include "cpulTestHarness.h"
#include "Pitch.h"

using namespace entropy;
using namespace std;

TEST(constructor01, Pitch)
{
    Pitch p;
    CHECK_EQUAL( 0, p.getNoteName().getPitchClass() )
    CHECK_EQUAL( 4, p.getOctave() )
}
TEST(constructor02, Pitch)
{
    Pitch p{ "G#5" };
    CHECK_EQUAL( 8, p.getNoteName().getPitchClass() )
    CHECK_EQUAL( 5, p.getOctave() )
    CHECK_EQUAL( 1, p.getNoteName().getAlter() )
}
TEST(equal, Pitch)
{
    Pitch p1{ "G#5" };
    Pitch p2{ "Ab5" };
    CHECK( p1 == p2 )
    CHECK( ! ( p1 != p2 ) )
    CHECK( p1 <= p2 )
    CHECK( p1 >= p2 )
}
TEST(notequal, Pitch)
{
    Pitch p1{ "A0" };
    Pitch p2{ "Bb0" };
    CHECK( p1 != p2 )
    CHECK( ! ( p1 == p2 ) )
    CHECK( p1 <= p2 )
    CHECK( ! ( p1 >= p2 ) )
}
TEST( greaterThan, Pitch)
{
    Pitch p1{ "B2" };
    Pitch p2{ "Bb2" };
    CHECK( p1 > p2 )
    CHECK( ! ( p1 < p2 ) )
    CHECK( ! ( p1 <= p2 ) )
    CHECK( p1 >= p2 )
}
TEST( lessThan, Pitch)
{
    Pitch p1{ "B1" };
    Pitch p2{ "Bb2" };
    CHECK( ! ( p1 > p2 ) )
    CHECK( p1 < p2 )
    CHECK( p1 <= p2 )
    CHECK( ! ( p1 >= p2 ) )
}