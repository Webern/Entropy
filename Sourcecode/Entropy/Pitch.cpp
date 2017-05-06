// Copyright (c) Matthew James Briggs

#include <sstream>

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


    bool Pitch::parse( const std::string& inValue )
    {
        const auto pos = inValue.find_first_of("0123456789-");

        if( pos == std::string::npos )
        {
            return false;
        }

        const auto nameStr = inValue.substr( 0, inValue.size() - pos );
        const auto octStr = inValue.substr( pos );

        const auto spelling = stringSpelling( nameStr );

        if( spelling == Spelling::ERROR )
        {
            return false;
        }

        std::stringstream ss{ octStr };
        int oct = 0;
        ss >> oct;
        setOctave( oct );
        mPitchClass.setSpelling( spelling );
        return true;
    }
}
