#pragma once
#include <iostream>
#include "typedefs.h"
#include "Duration.h"
#include <vector>

namespace entropy
{
    using RhythmList = std::vector<Duration>;
    using RhythmIter = RhythmList::iterator;
    using RhythmIterConst = RhythmList::const_iterator;
    
    using RhythmBook = std::vector<RhythmList>;
    using RhythmBookIter = RhythmBook::iterator;
    using RhythmBookIterConst = RhythmBook::const_iterator;
    
    RhythmBook makeRhythmBook();
    Duration getRhythm( const Int listIndex, const Int rhythmIndex );
}