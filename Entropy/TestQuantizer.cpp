#include "cpulTestHarness.h"
#include "Quantizer.h"

using namespace entropy;
using namespace std;


TEST(constructor01, Quantizer)
{
    Quantizer q{ 0, 100, 100 };
    CHECK( true );
}
TEST(getMinInputVal, Quantizer)
{
    Quantizer q{ -33.1, 33.1, 1000 };
    CHECK_DOUBLES_EQUAL( -33.1, q.getMinInputVal(), 0.000000001 )
}
TEST(getMaxInputVal, Quantizer)
{
    Quantizer q{ -99.9, 88.8, 7777 };
    CHECK_DOUBLES_EQUAL( 88.8, q.getMaxInputVal(), 0.000000001 )
}
TEST(getQuantumStateCount, Quantizer)
{
    Quantizer q{ -12345, 54321, 81 };
    CHECK_DOUBLES_EQUAL( 81, q.getQuantumStateCount(), 0.000000001 )
}
TEST(getQuantumState01, Quantizer)
{
    Quantizer q{ 0, 10, 10 };
    CHECK_EQUAL( 1, q.getQuantumState( 1.09 ) )
}
TEST(getQuantumState02, Quantizer)
{
    Quantizer q{ 0, 10, 10 };
    CHECK_EQUAL( 2, q.getQuantumState( 2.01 ) )
}
TEST(getQuantumState03, Quantizer)
{
    Quantizer q{ 0, 10, 10 };
    CHECK_EQUAL( 7, q.getQuantumState( 7.2 ) )
}
TEST(getQuantumState04, Quantizer)
{
    Quantizer q{ 0, 1000, 1000 };
    CHECK_EQUAL( 321, q.getQuantumState( 321.456789 ) )
}
TEST(getQuantumState05, Quantizer)
{
    Quantizer q{ 0, 10, 3 };
    CHECK_EQUAL( 2, q.getQuantumState( 7.12 ) )
}
