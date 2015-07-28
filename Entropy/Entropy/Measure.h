#pragma once
#include <iostream>
#include "typedefs.h"
#include "Note.h"
#include "TimeSignature.h"
#include <vector>


namespace entropy
{
    class Measure;
    using Measures = std::vector<Measure>;
    using MeasuresIter = Measures::iterator;
    using MeasuresIterConst = Measures::const_iterator;
    
    class Instrument;
    using InstrumentPtr = std::shared_ptr<Instrument>;
    
    class Measure
    {
    public:
        /* constructors */
        Measure();
        Measure( const TimeSignature& timeSignature );
        Measure( const InstrumentPtr& instr, const TimeSignature& timeSignature );
        
        /* get / set */
        const Notes& getNotes() const;
        void addNote( const Note& note );
        void removeNote( const NotesIterConst& iter );
        TimeSignature getTimeSignature() const;
        void setTimeSignature( const TimeSignature value );
        
        /* content analysis */
        bool getIsFull() const;
        Int getCount() const;
        Int getRemainingDivisions() const;
        Int getTotalDivisions() const;
        bool canAdd( const Note& note ) const;
        bool canAdd( const Duration& duration ) const;
        bool canStartTuplet( const Duration& duration ) const;
        bool isOnBeat() const;
        const InstrumentPtr& getInstrument() const;
    private:
        Notes myNotes;
        TimeSignature myTimeSignature;
        InstrumentPtr myInstrument;
    };
}