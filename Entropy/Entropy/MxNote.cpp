#include "MxNote.h"

namespace entropy
{
    using namespace mx::d;
    using namespace mx::e;
    using namespace mx::t;
    
    MxNoteIterator::MxNoteIterator( MxMeasureIterator measureIter )
    :myMeasureIter( measureIter )
    ,myIsEnd( true )
    ,myCurrentNote( makeNote() )
    {
        setBegin();
    }
    bool MxNoteIterator::isBegin() const
    {
        auto notes = extractNotesFromMeasure();
        auto nBeg = notes.cbegin();
        auto nEnd = notes.cend();
        if ( nBeg != nEnd )
        {
            if ( (*nBeg).get() == (operator*()).get() )
            {
                return true;
            }
        }
        return false;
    }
    bool MxNoteIterator::isEnd() const
    {
        auto notes = extractNotesFromMeasure();
        auto nBeg = notes.cbegin();
        auto nEnd = notes.cend();
        if ( nBeg == nEnd )
        {
            return true;
        }
        return myIsEnd;
    }
    bool MxNoteIterator::isValid() const
    {
        if ( myMeasureIter.isValid() )
        {
            auto notes = extractNotesFromMeasure();
            auto nBeg = notes.cbegin();
            auto nEnd = notes.cend();
            if ( nBeg != nEnd )
            {
                if ( !myIsEnd )
                {
                    return true;
                }
            }
        }
        return false;
    }
    bool MxNoteIterator::next()
    {
        auto notes = extractNotesFromMeasure();
        auto nBeg = notes.cbegin();
        auto nEnd = notes.cend();
        auto iter = nBeg;
        for ( ; iter != nEnd; ++iter )
        {
            if ( (*iter).get() == myCurrentNote.get() )
            {
                break;
            }
        }
        ++iter;
        if ( iter == nEnd )
        {
            myIsEnd = true;
            myCurrentNote = makeNote();
        }
        else
        {
            myIsEnd = false;
            myCurrentNote = *iter;
        }
        return false;
    }
    bool MxNoteIterator::previous()
    {
        auto notes = extractNotesFromMeasure();
        auto nBeg = notes.cbegin();
        auto nEnd = notes.cend();
        auto iter = nBeg;
        for ( ; iter != nEnd; ++iter )
        {
            if ( (*iter).get() == myCurrentNote.get() )
            {
                break;
            }
        }
        if ( iter == nBeg )
        {
            throw std::runtime_error( "attempt to move before the first note" );
        }
        else
        {
            --iter;
            myCurrentNote = *iter;
            if ( iter == nBeg )
            {
                return true;
            }
        }
        return false;
    }
    bool MxNoteIterator::setBegin()
    {
        auto notes = extractNotesFromMeasure();
        if ( notes.size() == 0 )
        {
            myIsEnd = true;
        }
        else
        {
            myIsEnd = false;
        }
        auto nBeg = notes.cbegin();
        auto nEnd = notes.cend();
        if ( nBeg != nEnd )
        {
            myCurrentNote = *nBeg;
            return true;
        }
        return false;
    }
    Int MxNoteIterator::getDivisionsPosition() const
    {
        return 0;
    }
    bool MxNoteIterator::isOnBeat() const
    {
        return false;
    }
    bool MxNoteIterator::isTuplet() const
    {
        bool istuplet = false;
        if ( isValid() )
        {
            istuplet = ::entropy::isTuplet( myCurrentNote );
        }
        return istuplet;
    }
    const mx::e::NotePtr& MxNoteIterator::operator*() const
    {
        checkValid();
        return myCurrentNote;
    }
    mx::e::NotePtr MxNoteIterator::operator*()
    {
        checkValid();
        return myCurrentNote;
    }
    const mx::e::NotePtr& MxNoteIterator::operator->() const
    {
        checkValid();
        return myCurrentNote;
    }
    mx::e::NotePtr MxNoteIterator::operator->()
    {
        checkValid();
        return myCurrentNote;
    }
    bool MxNoteIterator::nextMeasure()
    {
        if ( ! myMeasureIter.isEnd() )
        {
            myMeasureIter.next();
            return true;
        }
        return false;
    }
    bool MxNoteIterator::previousMeasure()
    {
        if ( ! myMeasureIter.isBegin() )
        {
            myMeasureIter.previous();
            return true;
        }
        return false;
    }
    Int MxNoteIterator::getMeasureTotalDivisionsSetting() const /* total divisions allowable in the measure */
    {
        checkValid();
        Int beats = 0;
        Int divis = 0;
        getMeasureBeatsAndDivisions( beats, divis );
        return beats*divis;
    }
    Int MxNoteIterator::getMeasureDivisionsPerBeatSetting() const /* divisions per quarter note */
    {
        checkValid();
        Int beats = 0;
        Int divis = 0;
        getMeasureBeatsAndDivisions( beats, divis );
        return divis;
    }
    Int MxNoteIterator::getTimeSignatureBeatCountTotal() const
    {
        checkValid();
        Int beats = 0;
        Int divis = 0;
        getMeasureBeatsAndDivisions( beats, divis );
        return beats;
    }
    Int MxNoteIterator::getMeasureNoteDivisionsCurrent() const
    {
        checkValid();
        return (Int)myCurrentNote->getNoteChoice()->getNormalNoteGroup()->getDuration()->getValue().getValue();
    }
    Int MxNoteIterator::getMeasureNoteDivisionsTotal() const
    {
        checkValid();
        auto notes = extractNotesFromMeasure();
        Int totalDivs = 0;
        for ( auto n : notes )
        {
            totalDivs += (Int)myCurrentNote->getNoteChoice()->getNormalNoteGroup()->getDuration()->getValue().getValue();
        }
        return totalDivs;
    }
    void MxNoteIterator::getMeasureBeatsAndDivisions( Int& quartersPerMeasure, Int& divisionsPerQuarter ) const
    {
        divisionsPerQuarter = -1;
        quartersPerMeasure = -1;
        if ( myMeasureIter.isValid() )
        {
            auto measure = *myMeasureIter;
            auto choices = measure->getMusicDataGroup()->getMusicDataChoiceSet();
            for ( auto choice : choices )
            {
                if( choice->getChoice() == MusicDataChoice::Choice::properties )
                {
                    auto properties = choice->getProperties();
                    divisionsPerQuarter = (Int)properties->getDivisions()->getValue().getValue();
                    auto timeset = properties->getTimeSet();
                    for ( auto t : timeset )
                    {
                        if( t->getTimeChoice()->getChoice() == TimeChoice::Choice::timeSignature )
                        {
                            auto timesig = t->getTimeChoice()->getTimeSignature();
                            quartersPerMeasure = std::stoi( timesig->getBeats()->getValue().getValue() );
                        }
                    }
                }
            }
        }
        if ( quartersPerMeasure < 2 || divisionsPerQuarter < 1 )
        {
            throw std::runtime_error( "problem parsing a measures time signature and divisions values" );
        }
    }
    mx::e::NoteSet MxNoteIterator::extractNotesFromMeasure() const
    {
        NoteSet notes;
        if ( myMeasureIter.isValid() )
        {
            for ( auto mdc : myMeasureIter->getMusicDataGroup()->getMusicDataChoiceSet() )
            {
                if( mdc->getChoice() == MusicDataChoice::Choice::note )
                {
                    auto note = mdc->getNote();
                    if ( note->getNoteChoice()->getChoice() == NoteChoice::Choice::normal )
                    {
                        notes.push_back( note );
                    }
                }
            }
        }
        return notes;
    }
    void MxNoteIterator::checkValid() const
    {
        if ( !isValid() )
        {
            throw std::runtime_error( "attempted to do something with an invalid MxNoteIterator" );
        }
    }
    MxNote::MxNote( const Note& note )
    :myNote( note )
    {}
    mx::e::NotePtr MxNote::getMxNote() const
    {
        mx::t::NoteTypeValue durval = convert( myNote.getDuration().getDur() );
        auto note = mx::e::makeNote();
        note->getType()->setValue( durval );
        note->setHasType( true );
        note->getNoteChoice()->setChoice( mx::e::NoteChoice::Choice::normal );
        auto noteGroup = note->getNoteChoice()->getNormalNoteGroup();
        noteGroup->getDuration()->setValue( mx::t::PositiveDivisionsValue( myNote.getDuration().getDivisions() ) );
        noteGroup->getFullNoteGroup()->getFullNoteTypeChoice()->setChoice( mx::e::FullNoteTypeChoice::Choice::pitch );
        noteGroup->getFullNoteGroup()->getFullNoteTypeChoice()->getPitch()->getStep()->setValue( convert( myNote.getPitch().getNoteName().getStep() ) );
        noteGroup->getFullNoteGroup()->getFullNoteTypeChoice()->getPitch()->getOctave()->setValue( mx::t::OctaveValue( myNote.getPitch().getOctave() ));
        if ( myNote.getPitch().getNoteName().getAlter() != 0 )
        {
            noteGroup->getFullNoteGroup()->getFullNoteTypeChoice()->getPitch()->setHasAlter( true );
            noteGroup->getFullNoteGroup()->getFullNoteTypeChoice()->getPitch()->getAlter()->setValue( mx::t::Semitones( myNote.getPitch().getNoteName().getAlter() ) );
            mx::t::AccidentalValue accidental = mx::t::AccidentalValue::natural;
            switch ( myNote.getPitch().getNoteName().getAlter() )
            {
                case -2:
                    accidental = mx::t::AccidentalValue::flatFlat;
                    break;
                case -1:
                    accidental = mx::t::AccidentalValue::flat;
                    break;
                case 1:
                    accidental = mx::t::AccidentalValue::sharp;
                    break;
                case 2:
                    accidental = mx::t::AccidentalValue::doubleSharp;
                    break;
                default:
                    break;
            }
            note->getAccidental()->setValue( accidental );
            note->setHasAccidental( true );
        }
        for ( Int d = 0; d < myNote.getDuration().getDots(); ++d )
        {
            note->addDot( mx::e::makeDot() );
        }
        if( myNote.getDuration().getTup() != Tup::Simple )
        {
            note->setHasTimeModification( true );
            auto notations = mx::e::makeNotations();
            auto notationschoice = mx::e::makeNotationsChoice();
            notationschoice->setChoice( mx::e::NotationsChoice::Choice::tuplet );
            notationschoice->getTuplet()->getAttributes()->type = mx::t::StartStop::stop;
            notations->addNotationsChoice( notationschoice );
            note->addNotations( notations );
            switch ( myNote.getDuration().getTup() )
            {
                case Tup::Triplet:
                {
                    note->getTimeModification()->getActualNotes()->setValue( mx::t::NonNegativeInteger( 3 ) );
                    note->getTimeModification()->getNormalNotes()->setValue( mx::t::NonNegativeInteger( 2 ) );
                }
                    break;
                case Tup::Quintuplet:
                {
                    note->getTimeModification()->getActualNotes()->setValue( mx::t::NonNegativeInteger( 5 ) );
                    note->getTimeModification()->getNormalNotes()->setValue( mx::t::NonNegativeInteger( 4 ) );
                }
                    break;
                case Tup::Sextuplet:
                {
                    note->getTimeModification()->getActualNotes()->setValue( mx::t::NonNegativeInteger( 6 ) );
                    note->getTimeModification()->getNormalNotes()->setValue( mx::t::NonNegativeInteger( 4 ) );
                }
                    break;
                default:
                    break;
            }
        }
        /* if it's a rest ... */
        if ( myNote.getIsRest() )
        {
            note->getNoteChoice()->getNormalNoteGroup()->getFullNoteGroup()->getFullNoteTypeChoice()->setChoice( FullNoteTypeChoice::Choice::rest );
        }
        return note;
    }
    mx::e::MusicDataChoicePtr MxNote::getMusicDataChoice() const
    {
        using namespace mx::e;

        auto note = getMxNote();
        auto choice = makeMusicDataChoice();
        choice->setChoice( MusicDataChoice::Choice::note );
        choice->setNote( note );
        return choice;
    }
    mx::t::NoteTypeValue convert( const Dur value )
    {
        mx::t::NoteTypeValue durval = mx::t::NoteTypeValue::quarter;
        switch ( value )
        {
            case Dur::Sixteenth:
                durval = mx::t::NoteTypeValue::sixteenth;
                break;
            case Dur::Eighth:
                durval = mx::t::NoteTypeValue::eighth;
                break;
            case Dur::Quarter:
                durval = mx::t::NoteTypeValue::quarter;
                break;
            case Dur::Half:
                durval = mx::t::NoteTypeValue::half;
                break;
            case Dur::Whole:
                durval = mx::t::NoteTypeValue::whole;
                break;
            default:
                break;
        }
        return durval;
    }
    Dur convert( const mx::t::NoteTypeValue value )
    {
        Dur durval = Dur::Quarter;
        switch ( value )
        {
            case mx::t::NoteTypeValue::sixteenth:
                durval = Dur::Sixteenth;
                break;
            case mx::t::NoteTypeValue::eighth:
                durval = Dur::Eighth;
                break;
            case mx::t::NoteTypeValue::quarter:
                durval = Dur::Quarter;
                break;
            case mx::t::NoteTypeValue::half:
                durval = Dur::Half;
                break;
            case mx::t::NoteTypeValue::whole:
                durval = Dur::Whole;
                break;
            default:
                break;
        }
        return durval;
    }
    
    bool isTuplet( const mx::e::NotePtr note )
    {
        return note->getHasTimeModification();
    }
    Int getTupletActualNotes( const mx::e::NotePtr note )
    {
        Int val = 1;
        if ( isTuplet( note ) )
        {
            val = note->getTimeModification()->getActualNotes()->getValue().getValue();
        }
        return val;
    }
    Int getTupletNormalNotes( const mx::e::NotePtr note )
    {
        Int val = 1;
        if ( isTuplet( note ) )
        {
            val = note->getTimeModification()->getActualNotes()->getValue().getValue();
        }
        return val;
    }
    
    void showAccidental( const mx::e::NotePtr& note )
    {
        auto pitch = note->getNoteChoice()->getNormalNoteGroup()->getFullNoteGroup()->getFullNoteTypeChoice()->getPitch();
        Semitones alterval = pitch->getAlter()->getValue();
        if ( ! pitch->getHasAlter() )
        {
            alterval = Semitones{ 0 };
        }
        note->setHasAccidental( true );
        switch ( (Int)alterval.getValue() )
        {
            case -2:
                note->getAccidental()->setValue( AccidentalValue::flatFlat );
                break;
            case -1:
                note->getAccidental()->setValue( AccidentalValue::flat );
                break;
            case 0:
                note->getAccidental()->setValue( AccidentalValue::natural );
                break;
            case 1:
                note->getAccidental()->setValue( AccidentalValue::sharp );
                break;
            case 2:
                note->getAccidental()->setValue( AccidentalValue::doubleSharp );
                break;
            default:
                throw new std::runtime_error( "alter values must be between -2 and 2" );
                break;
        }
    }
    void hideAccidental( const mx::e::NotePtr& note )
    {
        note->setHasAccidental( false );
    }
}