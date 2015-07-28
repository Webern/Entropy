#include "Instrument.h"

namespace entropy
{
    Instrument::Instrument( const String& ID, const String& name, const String& abbr, const Range& range )
    :myID( ID )
    ,myName( name )
    ,myAbbreviation( abbr )
    ,myRange( range )
    {}
    String Instrument::getID() const
    {
        return myID;
    }
    String Instrument::getName() const
    {
        return myName;
    }
    String Instrument::getAbbreviation() const
    {
        return myAbbreviation;
    }
    Range Instrument::getRange() const
    {
        return myRange;
    }
    void Instrument::addMeasure( const Measure measure )
    {
        myMeasures.push_back( measure );
    }
    MeasuresIter Instrument::getMeasuresBegin()
    {
        return myMeasures.begin();
    }
    MeasuresIterConst Instrument::getMeasuresBeginConst() const
    {
        return myMeasures.cbegin();
    }
    MeasuresIter Instrument::getMeasuresEnd()
    {
        return myMeasures.end();
    }
    MeasuresIterConst Instrument::getMeasuresEndConst() const
    {
        return myMeasures.cend();
    }
    Int Instrument::getMeasuresCount() const
    {
        return (Int)myMeasures.size();
    }
    InstrumentPtr makeInstrument( const InstrumentPtr& other )
    {
        return std::make_shared<Instrument>( *other );
    }
    InstrumentPtr makeInstrument( const Instrument& other )
    {
        return std::make_shared<Instrument>( other );
    }
    InstrumentPtr makeInstrument( const String& ID, const String& name, const String& abbr, const Range& range )
    {
        return std::make_shared<Instrument>( ID, name, abbr, range );
    }
    
    bool operator==( const Instrument& l, const Instrument& r )
    {
        
        return (!( l < r )) && (!( r < l ));
    }
    bool operator!=( const Instrument& l, const Instrument& r )
    {
        return ! ( l == r );
    }
    bool operator<( const Instrument& l, const Instrument& r )
    {
        return l.getID() < r.getID();
    }
    bool operator>( const Instrument& l, const Instrument& r )
    {
        return r < l;
    }
    bool operator<=( const Instrument& l, const Instrument& r )
    {
        return ( l < r ) || ( l == r );
    }
    bool operator>=( const Instrument& l, const Instrument& r )
    {
        return ( l > r ) || ( l == r );
    }
}