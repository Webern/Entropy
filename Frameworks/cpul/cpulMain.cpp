#include <iostream>
#include "cpul/cpulRun.h"
#include "cpul/cpulTestTimer.h"

int main(int argc, const char * argv[])
{
    //MxRtiTest::rtiMain();
    UNUSED_PARAMETER( argc )
    UNUSED_PARAMETER( argv )
    cpul::TestTimer timer;
    cpulRun( true );
    timer.report( "Total runtime for all tests" );
    return 0;
}
