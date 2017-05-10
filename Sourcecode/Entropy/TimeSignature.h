// Copyright (c) Matthew James Briggs

#pragma once

#include "Entropy/DurationChain.h"

namespace entropy
{
    class TimeSignature
    {
    public:
        TimeSignature();
        int getTopNumber() const;
        void setTopNumber( int inTopNumber );
        int getBottomNumber() const;
        void setBottomNumber( int inBottomNumber );
        Duration getBottomDuration() const;
        void setSimpleGrouping( std::vector<int> inGrouping );
        void resetGrouping();

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
