// Copyright (c) Matthew James Briggs

#pragma once

#include "Entropy/DurationChain.h"

namespace entropy
{
    class TimeSignature
    {
    public:
        TimeSignature();
        TimeSignature(int inTopNumber, int inBottomNumber);

        int getTicks() const;

        int getTopNumber() const;
        void setTopNumber( int inTopNumber );

        int getBottomNumber() const;
        void setBottomNumber( int inBottomNumber );
        Duration getBottomDuration() const;

        /// set groups of the base dur. for example in 5/8
        /// setting { 2, 3 } would cause groupings of 2 eighths
        /// and 3 eighths. If you want to group at a more granular
        /// level then use setComplexGrouping
        void setSimpleGrouping( std::vector<int> inGrouping );
        void setComplexGrouping( DurationChain inDurationChain );
        void resetGrouping();

        std::vector<int> getBeatLengths() const;
        std::vector<int> getBeatLocations() const;

    public:
        static int convertBottomNumberToTicks( const int inBottomNumber );
        static int convertTicksToBottomNumber( const int inBottomNumber );

    private:
        int myTopNumber;
        int myBottomNumber;
        DurationChain myDurationChain;

    private:
        void validateBottomNumber( int inBottomNumber ) const;
    };
}
