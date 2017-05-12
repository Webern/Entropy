// Copyright (c) Matthew James Briggs

#include "Entropy/TimeSignature.h"
#include "Entropy/Constants.h"
#include "Entropy/Throw.h"
#include "Entropy/Entropy.h"

#include <numeric>

namespace entropy
{
    TimeSignature::TimeSignature()
    : myTopNumber{ 4 }
    , myBottomNumber{ 4 }
    , myDurationChain{}
    {
        setSimpleGrouping( { 1, 1, 1, 1 } );
    }


    TimeSignature::TimeSignature(int inTopNumber, int inBottomNumber)
    : TimeSignature{}
    {
        setTopNumber( inTopNumber );
        setBottomNumber( inBottomNumber );
    }


    int
    TimeSignature::getTicks() const
    {
        const auto ticksPerUnit = convertBottomNumberToTicks( getBottomNumber() );
        const auto result = getTopNumber() * ticksPerUnit;
        return result;
    }


    int TimeSignature::getTopNumber() const
    {
        return myTopNumber;
    }


    void TimeSignature::setTopNumber( int inTopNumber )
    {
        const auto formerTopNumber = myTopNumber;
        myTopNumber = std::max( 1, std::min( MAX_TIME_SIGNATURE_TOP, inTopNumber ) );

        if( myTopNumber != formerTopNumber )
        {
            resetGrouping();
        }
    }


    int TimeSignature::getBottomNumber() const
    {
        return myBottomNumber;
    }


    void TimeSignature::setBottomNumber( int inBottomNumber )
    {
        if ( inBottomNumber == myBottomNumber )
        {
            return;
        }

        validateBottomNumber( inBottomNumber );
        myBottomNumber = inBottomNumber;
        resetGrouping();
    }


    Duration TimeSignature::getBottomDuration() const
    {
        const auto ticks = convertBottomNumberToTicks( myBottomNumber );
        const auto result = Duration::getDurationPrototypes().at( ticks );
        return result;
    }


    void TimeSignature::setSimpleGrouping( std::vector<int> inGrouping )
    {
        const auto total = std::accumulate( std::begin(inGrouping), std::end(inGrouping), 0 );
        ENTROPY_ASSERT( total == getTopNumber() );
        const auto bottomDir = getBottomDuration();
        myDurationChain = DurationChain{};

        for( const auto& val : inGrouping )
        {
            ENTROPY_ASSERT( val > 0 );
            const auto ticks = val * bottomDir.getTicks();
            const auto duration = Duration::getDurationPrototypes().at( ticks );
            DurationGroup dg{};
            dg.addDuration( duration );
            myDurationChain.addDurationGroup( dg );
        }
    }


    void TimeSignature::setComplexGrouping( DurationChain inDurationChain )
    {
        const int myTicks = getTicks();
        const int incomingTicks = inDurationChain.getTicks();
        ENTROPY_ASSERT( incomingTicks == myTicks );
        myDurationChain = inDurationChain;
    }


    void TimeSignature::resetGrouping()
    {
        std::vector<int> grouping( static_cast<size_t>( getTopNumber() ), 1 );
        setSimpleGrouping( grouping );
    }


    std::vector<int> TimeSignature::getBeatLengths() const
    {
        std::vector<int> lengths;

        for( const auto& grp : myDurationChain.getDurationGroups() )
        {
            lengths.push_back( grp.getTicks() );
        }

        return lengths;
    }


    std::vector<int> TimeSignature::getBeatLocations() const
    {
        int position = 0;
        std::vector<int> lengths;

        for( const auto& grp : myDurationChain.getDurationGroups() )
        {
            lengths.push_back( position );
            position += grp.getTicks();
        }

        return lengths;
    }


    int TimeSignature::convertBottomNumberToTicks( const int inBottomNumber )
    {
        switch ( inBottomNumber )
        {
            case 1: return TIME_SIGNATURE_1;
            case 2: return TIME_SIGNATURE_2;
            case 4: return TIME_SIGNATURE_4;
            case 8: return TIME_SIGNATURE_8;
            case 16: return TIME_SIGNATURE_16;
            case 32: return TIME_SIGNATURE_32;
            case 64: return TIME_SIGNATURE_64;
        }

        ENTROPY_THROW( "invalid time signature bottom" );
    }


    int TimeSignature::convertTicksToBottomNumber( const int inTicks )
    {
        switch ( inTicks )
        {
            case TIME_SIGNATURE_1: return 1;
            case TIME_SIGNATURE_2: return 2;
            case TIME_SIGNATURE_4: return 4;
            case TIME_SIGNATURE_8: return 8;
            case TIME_SIGNATURE_16: return 16;
            case TIME_SIGNATURE_32: return 32;
            case TIME_SIGNATURE_64: return 64;
        }

        ENTROPY_THROW( "invalid time ticks value" );
    }


    void TimeSignature::validateBottomNumber( int inBottomNumber ) const
    {
        convertBottomNumberToTicks( inBottomNumber );
    }
}
