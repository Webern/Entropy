#pragma once
#include <iostream>
#include <string>
#include "typedefs.h"
#include "Range.h"
#include <memory>
#include "Measure.h"

namespace entropy
{
    class Instrument;
    using InstrumentPtr = std::shared_ptr<Instrument>;
    using Instruments = std::vector<InstrumentPtr>;
    using InstrumentsIter = Instruments::iterator;
    using InstrumentsConst = Instruments::const_iterator;
    
    InstrumentPtr makeInstrument( const InstrumentPtr& other );
    InstrumentPtr makeInstrument( const Instrument& other );
    InstrumentPtr makeInstrument( const String& ID, const String& name, const String& abbr, const Range& range );
    
    class Instrument
    {
    public:
        Instrument( const String& ID, const String& name, const String& abbr, const Range& range );
        String getID() const;
        String getName() const;
        String getAbbreviation() const;
        Range getRange() const;
        void addMeasure( const Measure measure );
        MeasuresIter getMeasuresBegin();
        MeasuresIterConst getMeasuresBeginConst() const;
        MeasuresIter getMeasuresEnd();
        MeasuresIterConst getMeasuresEndConst() const;
        Int getMeasuresCount() const;
    private:
        String myID;
        String myName;
        String myAbbreviation;
        Range myRange;
        Measures myMeasures;
    };
    bool operator==( const Instrument& l, const Instrument& r );
    bool operator!=( const Instrument& l, const Instrument& r );
    bool operator<( const Instrument& l, const Instrument& r );
    bool operator>( const Instrument& l, const Instrument& r );
    bool operator<=( const Instrument& l, const Instrument& r );
    bool operator>=( const Instrument& l, const Instrument& r );
}