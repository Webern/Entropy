#include "setDuration.h"
#include "isDurationOk.h"
#include "setTupletCountdown.h"

namespace entropy
{
    Duration setDuration( Duration& prevDur, const Rand& rhythrand, const RhythmList& rhythmList, const Measure& newMeasure, Int& tupletCountdown, bool& safetyTripped )
    {
        Duration currDur;
        if ( prevDur.getTup() != Tup::Simple && tupletCountdown > 0 )
        {
            currDur = prevDur;
            --tupletCountdown;
        }
        else
        {
            Int safetyValve = 0;
            do
            {
                currDur = rhythmList[ rhythrand.get() ];
                ++safetyValve;
                if ( safetyValve > 1000 )
                {
                    std::cout << "safety valve tripped" << std::endl;
                    safetyTripped = true;
                    break;
                }
            }
            while ( ( !isDurationOk( currDur, newMeasure ) || newMeasure.getRemainingDivisions() == 0 ) && ! safetyTripped );
            if ( currDur.getTup() != Tup::Simple )
            {
                setTupletCountdown( currDur.getTup(), tupletCountdown );
            }
        }
        prevDur = currDur;
        return currDur;
    }
}