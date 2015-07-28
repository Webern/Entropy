#pragma once
#include "Rand.h"

namespace entropy
{
    inline bool goUp( const Int entropyValue, const Rand& randomizer0to12 )
    {
        Int randomNumber = randomizer0to12.get();
        return randomNumber < entropyValue;
    }
}