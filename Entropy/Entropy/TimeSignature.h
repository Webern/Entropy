#pragma once
#include <iostream>
#include "typedefs.h"
#include "Divisions.h"

namespace entropy
{
    class TimeSignature
    {
    public:
        TimeSignature();
        TimeSignature( Int numerator, Int denominator );
        Int getNumerator() const;
        Int getDenominator() const;
        void setNumerator( Int value );
        void setDenominator( Int value );
        Int getDivisionsPerMeasure() const;
        Int getDivisionsPerQuarter() const;
    private:
        Int myNumerator;
        Int myDenominator;
        static const Int ourDivisions;
    };
}