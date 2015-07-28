#pragma once
#include "typedefs.h"
#include "Quantizer.h"
#include <set>

namespace entropy
{
    class Rand
    {

    public:
        Rand( Int low, Int high );
        Int get() const;
    private:
        Quantizer myQuantizer;
        static Int ourCallCount;
        static std::set<Int> ourUsedSeeds;
        Int myLow;
        Int myHigh;
        void seed() const;
        Int createSeed() const;
        bool hasSeedBeenUsed( Int seet ) const;
        static bool ourIsFirstInit;
    };
}