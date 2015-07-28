#include "initializeOctave.h"

namespace entropy
{
    Int initializeOctave( NoteName& nn, const InstrumentPtr instr, const Int entrpy  )
    {
        Int octave = 4;
        bool isHighEntropy = entrpy >= 9;
        bool isLowEntropy = entrpy <= 3;
        if ( isHighEntropy )
        {
            octave = instr->getRange().getHigh().getOctave();
        }
        else if ( isLowEntropy )
        {
            octave = instr->getRange().getLow().getOctave();
        }
        else
        {
            Int low = instr->getRange().getLow().getOctave();
            Int high = instr->getRange().getHigh().getOctave();
            octave = ( high + low ) / 2;
            
        }
        Pitch tmpPitch{ nn, octave };
        if ( !instr->getRange().isInRange( tmpPitch ) )
        {
            if ( instr->getRange().isAboveRange( tmpPitch ) )
            {
                --octave;
            }
            else if ( instr->getRange().isBelowRange( tmpPitch ) )
            {
                ++octave;
            }
        }
        return octave;
    }
}