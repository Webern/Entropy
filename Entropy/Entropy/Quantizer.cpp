#include "Quantizer.h"

namespace entropy
{
    Quantizer::Quantizer( Float minInputVal, Float maxInputVal, Int quantumStateCount )
    :myMinInputVal( minInputVal )
    ,myMaxInputVal( maxInputVal )
    ,myQuantumStateCount( quantumStateCount )
    ,myStateBoundryDelta( 0 )
    {
        initialize();
    }
    Float Quantizer::getMinInputVal() const
    {
        return myMinInputVal;
    }
    Float Quantizer::getMaxInputVal() const
    {
        return myMaxInputVal;
    }
    Int Quantizer::getQuantumStateCount() const
    {
        return myQuantumStateCount;
    }
    Int Quantizer::getQuantumState( const Float valueToQuantize ) const
    {
        Int qval = 0;
        if ( valueToQuantize > myMinInputVal )
        {
            auto iter = std::find_if( myStateBoundries.cbegin(), myStateBoundries.cend(), [&valueToQuantize,this](const Float& inside)
                                     {
                                         return ( valueToQuantize > inside ) && ( valueToQuantize <= ( inside + myStateBoundryDelta ) );
                                     });
            if ( iter != myStateBoundries.end() )
            {
                qval = (Int)std::distance( myStateBoundries.begin(), iter );
            }
            else
            {
                qval = myMaxInputVal;
            }
        }
        return qval;
    }
    void Quantizer::initialize()
    {
        Float scount = (Float)myQuantumStateCount;
        myStateBoundryDelta = ( myMaxInputVal - myMinInputVal ) / scount;
        for ( Int i = 0; i < myQuantumStateCount; ++i )
        {
            Float currBoundry = myMinInputVal + ( myStateBoundryDelta * (Float)i );
            myStateBoundries.push_back( currBoundry );
        }
        return;
    }
}