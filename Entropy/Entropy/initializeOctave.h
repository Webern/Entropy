#pragma once
#include "typedefs.h"
#include "Pitch.h"
#include "Scale.h"
#include "Instrument.h"
#include "Rand.h"

namespace entropy
{
    Int initializeOctave( NoteName& nn, const InstrumentPtr instr, const Int entrpy  );
}