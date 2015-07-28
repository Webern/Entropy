#pragma once
#include <vector>
#include "typedefs.h"
#include "Pitch.h"

namespace entropy
{
    class Range
    {
    public:
        Range();
        Range( const Pitch& low, const Pitch& high );
        Pitch getLow() const;
        Pitch getHigh() const;
        bool isInRange( const Pitch& pitch ) const;
        bool isBelowRange( const Pitch& pitch ) const;
        bool isAboveRange( const Pitch& pitch ) const;
    private:
        Pitch myLow;
        Pitch myHigh;
        bool checkRange( const Pitch& low, const Pitch& high ) const;
    };
}