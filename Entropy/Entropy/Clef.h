#pragma once
#include "typedefs.h"
#include "Note.h"
#include "Instrument.h"

namespace entropy
{
    enum class Clf
    {
        Treble = 0,
        Bass = 1,
        Viola = 2
    };
    
    Clf inferClef( NotesIterConst beg, NotesIterConst end, const InstrumentPtr& instr );
}