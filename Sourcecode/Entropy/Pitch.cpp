// Copyright (c) Matthew James Briggs

#include "Pitch.h"
#include "Constants.h"

namespace entropy
{
    Pitch::Pitch()
    : Pitch{ Spelling::Cn, 4 }
    {

    }


    Pitch::Pitch( PitchClass inPitchClass, int inOctave )
    : mPitchClass( inPitchClass )
    , mOctave{ 0 }
    {
        setOctave( inOctave );
    }


    Pitch::Pitch( Spelling inSpelling, int inOctave )
    : Pitch{ PitchClass{ inSpelling }, inOctave }
    {

    }


    Pitch::Pitch( int inPitchClass, int inOctave )
    : Pitch{ intSpelling( inPitchClass ), inOctave }
    {

    }


    int Pitch::getOctave() const
    {
        return mOctave;
    }


    void Pitch::setOctave( int inOctave )
    {
        mOctave = std::max( MIN_OCTAVE, std::min( MAX_OCTAVE, inOctave ) );
    }


    const PitchClass& Pitch::getPitchClass() const
    {
        return mPitchClass;
    }


    void Pitch::setPitchClass( const PitchClass inPitchClass )
    {
        mPitchClass = inPitchClass;
    }


    int Pitch::getMidiNote() const
    {
        const auto pc = mPitchClass.getValue();
        const auto oct = 12 * (getOctave() + 1);
        const auto result = pc + oct;
        return result;
    }
}
