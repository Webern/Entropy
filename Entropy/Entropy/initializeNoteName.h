#pragma once
#include "typedefs.h"
#include "Pitch.h"
#include "Scale.h"
#include "Instrument.h"
#include "Rand.h"

namespace entropy
{
    NoteName initializeNoteName( Scale& scale, const Rand& scalerand, const InstrumentPtr instr  );
}