#pragma once
#include "typedefs.h"
#include "Note.h"
#include "Mx/Elements.h"
#include "MxMeasure.h"

namespace entropy
{
    mx::t::NoteTypeValue convert( const Dur value );
    Dur convert( const mx::t::NoteTypeValue value );
    
    //TODO: This class name is confusing wrt to MxNote
    class MxNoteIterator
    {
    public:
        MxNoteIterator( MxMeasureIterator measureIter );
        bool isBegin() const;
        bool isEnd() const;
        bool isValid() const;
        bool next();
        bool previous();
        bool setBegin();
        Int getDivisionsPosition() const;
        bool isOnBeat() const;
        bool isTuplet() const;
        const mx::e::NotePtr& operator*() const;
        mx::e::NotePtr operator*();
        const mx::e::NotePtr& operator->() const;
        mx::e::NotePtr operator->();
        bool nextMeasure();
        bool previousMeasure();
        Int getMeasureTotalDivisionsSetting() const; /* total divisions allowable in the measure */
        Int getMeasureDivisionsPerBeatSetting() const; /* divisions per quarter note */
        Int getMeasureNoteDivisionsTotal() const;
        Int getMeasureNoteDivisionsCurrent() const;
        Int getTimeSignatureBeatCountTotal() const;
    private:
        MxMeasureIterator myMeasureIter;
        mx::e::NotePtr myCurrentNote;
        bool myIsEnd;
        void checkValid() const;
        mx::e::NoteSet extractNotesFromMeasure() const;
        void getMeasureBeatsAndDivisions( Int& beatsPerMeasure, Int& divisionsPerQuarter ) const;
    };
    
    //TODO: This is not really a class
    class MxNote
    {
    public:
        MxNote( const Note& note );
        mx::e::NotePtr getMxNote() const;
        mx::e::MusicDataChoicePtr getMusicDataChoice() const;
    private:
        Note myNote;
    };

    bool isTuplet( const mx::e::NotePtr note );
    Int getTupletActualNotes( const mx::e::NotePtr note );
    Int getTupletNormalNotes( const mx::e::NotePtr note );
    void showAccidental( const mx::e::NotePtr& note );
    void hideAccidental( const mx::e::NotePtr& note );
}