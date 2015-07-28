#include "TimeSignature.h"

namespace entropy
{
    const Int TimeSignature::ourDivisions = DIVISIONS;
    
    TimeSignature::TimeSignature()
    :myNumerator( 4 )
    ,myDenominator( 4 )
    {
        
    }
    TimeSignature::TimeSignature( Int numerator, Int denominator )
    :myNumerator( 4 )
    ,myDenominator( 4 )
    {
        setNumerator( numerator );
        setDenominator( denominator );
    }
    Int TimeSignature::getNumerator() const
    {
        return myNumerator;
    }
    Int TimeSignature::getDenominator() const
    {
        return myDenominator;
    }
    void TimeSignature::setNumerator( Int value )
    {
        if ( value >= 2 && value <= 7 )
        {
            myNumerator = value;
        }
        else
        {
            throw std::runtime_error( "improper TimeSignature numerator" );
        }
    }
    void TimeSignature::setDenominator( Int value )
    {
        if ( value == 4 )
        {
            myDenominator = value;
        }
        else
        {
            throw std::runtime_error( "improper TimeSignature denominator" );
        }
    }
    Int TimeSignature::getDivisionsPerMeasure() const
    {
        if ( myDenominator != 4 )
        {
            throw std::runtime_error( "this function will not work if denominator != 4" );
        }
        return ourDivisions * myNumerator;
    }
    
    Int TimeSignature::getDivisionsPerQuarter() const
    {
        return ourDivisions;
    }
}