// Copyright (c) Matthew James Briggs

#pragma once

#include "PitchClass.h"

namespace entropy
{
    class Pitch
    {
    public:
        Pitch();
        Pitch( PitchClass inPitchClass, int inOctave );
        Pitch( Spelling inSpelling, int inOctave );
        Pitch( int inPitchClass, int inOctave );
        int getOctave() const;
        void setOctave( int inOctave );
        const PitchClass& getPitchClass() const;
        void setPitchClass( const PitchClass inPitchClass );
        int getMidiNote() const;
        bool parse( const std::string& inValue );

    private:
        PitchClass mPitchClass;
        int mOctave;
    };
}
