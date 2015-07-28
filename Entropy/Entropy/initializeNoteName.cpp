#include "initializeNoteName.h"
#include "NoteName.h"

namespace entropy
{
    NoteName initializeNoteName( Scale& scale, const Rand& scalerand, const InstrumentPtr instr  )
    {
        scale.setCurrent( scalerand.get() );
        return scale.getCurrent();
    }
}