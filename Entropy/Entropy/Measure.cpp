#include "Measure.h"
#include "Duration.h"
#include "Instrument.h"

namespace entropy
{
    Measure::Measure()
    :myNotes()
    ,myTimeSignature()
    ,myInstrument( makeInstrument( "", "", "", Range{} ) )
    {}
    
    Measure::Measure( const TimeSignature& timeSignature )
    :myNotes()
    ,myTimeSignature( timeSignature )
    ,myInstrument( makeInstrument( "", "", "", Range{} ) )
    {}
    
    Measure::Measure( const InstrumentPtr& instr, const TimeSignature& timeSignature )
    :myNotes()
    ,myTimeSignature( timeSignature )
    ,myInstrument( instr )
    {}
    
    /* get / set */
    const Notes& Measure::getNotes() const
    {
        return myNotes;
    }
    void Measure::addNote( const Note& note )
    {
        if ( canAdd( note ) )
        {
            myNotes.push_back( note );
        }
        else
        {
            throw std::runtime_error( "cannot add note to measure" );
        }
    }
    void Measure::removeNote( const NotesIterConst& iter )
    {
        if ( iter != myNotes.cend() )
        {
            if ( getCount() > 0 )
            {
                myNotes.erase( iter );
            }
        }
        else
        {
            throw std::runtime_error( "cannot remove note from measure" );
        }
    }
    TimeSignature Measure::getTimeSignature() const
    {
        return myTimeSignature;
    }
    void Measure::setTimeSignature( const TimeSignature value )
    {
        if ( getTotalDivisions() > value.getDivisionsPerMeasure() )
        {
            throw std::runtime_error( "notes will not fit if time signature is changed" );
        }
        myTimeSignature = value;
    }
    
    /* content analysis */
    bool Measure::getIsFull() const
    {
        return getTotalDivisions() >= ( myTimeSignature.getDivisionsPerMeasure() - 1 );
    }
    Int Measure::getCount() const
    {
        return (Int)myNotes.size();
    }
    Int Measure::getRemainingDivisions() const
    {
        return myTimeSignature.getDivisionsPerMeasure() - getTotalDivisions();
    }
    Int Measure::getTotalDivisions() const
    {
        Int total = 0;
        for ( auto n : myNotes )
        {
            total += n.getDuration().getDivisions();
        }
        return total;
    }
    bool Measure::canAdd( const Note& note ) const
    {
        return canAdd( note.getDuration() );
    }
    bool Measure::canAdd( const Duration& duration ) const
    {
        return duration.getDivisions() <= getRemainingDivisions();
    }
    bool Measure::canStartTuplet( const Duration& duration ) const
    {
        return isOnBeat() && duration.getDivisionsToCompleteTuplet() <= getRemainingDivisions();
    }
    bool Measure::isOnBeat() const
    {
        return  0 == ( getTotalDivisions() % ( myTimeSignature.getDivisionsPerMeasure() / myTimeSignature.getNumerator() ) );
    }
    const InstrumentPtr& Measure::getInstrument() const
    {
        return myInstrument;
    }
}