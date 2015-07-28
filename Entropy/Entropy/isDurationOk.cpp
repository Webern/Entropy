#include "isDurationOk.h"

namespace entropy
{
    bool isDurationOk( const Duration& duration, const Measure& measure )
    {
        //while ( ( ! newMeasure.canAdd( currDur ) || ! newMeasure.canStartTuplet( currDur ) || newMeasure.getRemainingDivisions() == 0 ) && ! safetyTripped );
        bool isTupletOk = false;
        if ( duration.getTup() == Tup::Simple )
        {
            isTupletOk = true;
        }
        else
        {
            isTupletOk = measure.canStartTuplet( duration );
        }
        return isTupletOk && measure.canAdd( duration );
    }
}