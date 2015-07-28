#include "Rand.h"
#include <cstdlib>
#include <string>

namespace entropy
{
    using namespace std;
    Int Rand::ourCallCount{ 0 };
    std::set<Int> Rand::ourUsedSeeds;
    bool Rand::ourIsFirstInit = true;
    
    Rand::Rand( Int low, Int high )
    :myQuantizer{ 0, static_cast<Float>(RAND_MAX), ( ( high - low ) + 1 ) }
    ,myLow( low )
    ,myHigh( high )
    {
        if ( ourIsFirstInit )
        {
            srand ( createSeed() );
            ourIsFirstInit = false;
        }
    }
    
    Int Rand::get() const
    {
        Int val{ static_cast<Int>(myQuantizer.getMinInputVal()) };
#if 1==0
        if ( ourCallCount >= 1000 )
        {
            Int safety = 0;
            Int newSeed = createSeed();
            while ( ourUsedSeeds.size() < 1000 && hasSeedBeenUsed( newSeed ) && safety < 9000  )
            {
                newSeed = createSeed();
                ++safety;
            }
            srand( static_cast<unsigned int>(newSeed) );
            ourCallCount = 0;
        }
#endif
        val = myQuantizer.getQuantumState( static_cast<Float>(rand()) )+myLow;

        ++ourCallCount;
        return val;
    }
    Int Rand::createSeed() const
    {
        auto clockstr = to_string( clock() );
        auto clockpart = stoi( clockstr.substr( clockstr.length()-4 ) );
        return clockpart;
    }
    bool Rand::hasSeedBeenUsed( Int seed ) const
    {
        auto result = ourUsedSeeds.insert( seed );
        return ! result.second;
    }
}