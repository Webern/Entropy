#pragma once
#include <iostream>
#include "typedefs.h"
#include <set>
#include "Divisions.h"

namespace entropy
{
    enum class Dur
    {
        Sixteenth = 0,
        Eighth = 1,
        Quarter = 2,
        Half = 3,
        Whole = 4
    };
    enum class Tup
    {
        Simple = 0,
        Triplet = 1,
        Quintuplet = 2,
        Sextuplet = 3
    };
    
    class Duration;
    
    Duration parseDuration( const String& value );
    
    class Duration
    {
    public:
        Duration();
        Duration( const Dur dur );
        Duration( const Dur dur, const Tup tup );
        Duration( const Dur dur, const Int dots );
        Duration( const Dur dur, const Int dots, const Tup tup );
        
        /* get / set */
        Dur getDur() const;
        Tup getTup() const;
        Int getDots() const;
        Int getQuarterDivisions() const;
        void setDur( const Dur value );
        void setTup( const Tup value );
        void setDots( const Int value );
        void setQuarterDivisions( const Int value );
        
        /* calculations */
        Int getDivisions() const;
        String toString() const;
        Int getDivisionsToCompleteTuplet() const;
        
    private:
        Dur myDur;
        Tup myTup;
        Int myDots;
        Int myDivisions;
    };
    
    bool operator==( const Duration& l, const Duration& r );
    
    struct DurationString
    {
        const String name;
        const Duration duration;
    };
    
    bool operator==( const DurationString& l, const DurationString& r );
    bool operator!=( const DurationString& l, const DurationString& r );
    bool operator<( const DurationString& l, const DurationString& r );
    bool operator>( const DurationString& l, const DurationString& r );
    bool operator<=( const DurationString& l, const DurationString& r );
    bool operator>=( const DurationString& l, const DurationString& r );
    
    using DurationStrings = std::set<DurationString>;
    using DurationStringsIter = DurationStrings::iterator;
    using DurationStringsIterConst = DurationStrings::const_iterator;
    
    static const DurationStrings DurationStringLookup;
    
}