#pragma once
#include "Pitch.h"
#include "Rand.h"
#include "Scale.h"
#include "Instrument.h"

namespace entropy
{
    void setPitch( const Rand& scalerand, Scale& scale, const InstrumentPtr& instr, const Int entrpy, const Rand& rand0to12, Pitch& currPitch, Pitch& prevPitch );
}