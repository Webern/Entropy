#include "initializePitch.h"
#include "NoteName.h"
#include "initializeNoteName.h"
#include "initializeOctave.h"

namespace entropy
{
    Pitch initializePitch( Scale& scale, const Rand& scalerand, const InstrumentPtr& instr, const Int entrpy  )
    {
        NoteName nn = initializeNoteName( scale, scalerand, instr );
        Int octave = initializeOctave( nn, instr, entrpy );
        return Pitch{ nn, octave };
    }
}