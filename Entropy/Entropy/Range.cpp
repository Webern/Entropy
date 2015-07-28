#include "Range.h"

namespace entropy
{
    Range::Range()
    :myLow( Pitch( NoteName( Step::a, 0 ), -2 ) )
    ,myHigh(  Pitch( NoteName( Step::c, 0 ), 9 ) )
    {
        checkRange( myLow, myHigh );
    }
    Range::Range( const Pitch& low, const Pitch& high )
    :myLow( low )
    ,myHigh(  high )
    {
        checkRange( myLow, myHigh );
    }
    Pitch Range::getLow() const
    {
        return myLow;
    }
    Pitch Range::getHigh() const
    {
        return myHigh;
    }
    bool Range::isInRange( const Pitch& pitch ) const
    {
        return (!isAboveRange(pitch)) && (!isBelowRange(pitch));
    }
    bool Range::isAboveRange( const Pitch& pitch ) const
    {
        return pitch > myHigh;
    }
    bool Range::isBelowRange( const Pitch& pitch ) const
    {
        return pitch < myLow;
    }
    bool Range::checkRange( const Pitch& low, const Pitch& high ) const
    {
        if ( ! ( myLow <= myHigh ) )
        {
            throw std::runtime_error( "when defining a range, the high pitch cannot be lower than the low pitch" );
        }
        return true;
    }
}