#pragma once
#include <iostream>
#include "typedefs.h"
#include <vector>

namespace entropy
{
    class Quantizer
    {
    public:
        Quantizer( Float minInputVal, Float maxInputVal, Int quantumStateCount );
        Float getMinInputVal() const;
        Float getMaxInputVal() const;
        Int getQuantumStateCount() const;
        Int getQuantumState( const Float valueToQuantize ) const;
    private:
        Float myMinInputVal;
        Float myMaxInputVal;
        Int myQuantumStateCount;
        Float myStateBoundryDelta;
        std::vector<Float> myStateBoundries;
        void initialize();
    };
}