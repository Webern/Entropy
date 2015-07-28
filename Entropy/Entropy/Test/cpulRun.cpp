#include "cpulRun.h"

void cpulRun( bool runTests, bool holdConsole )
{
    if ( runTests )
    {
        // random number generator used in some tests
        srand(::time_t(NULL));
        
        TestResult tr;
        TestRegistry::runAllTests(tr);
        
        // force console screen to hold
        if ( holdConsole )
        {
            char ch;
            std::cin >> ch;
        }
    }
	
}