// Copyright (c) Matthew James Briggs

#pragma once

#include "Enums.h"

namespace entropy
{
    class PitchClass
    {
    public:
        PitchClass();
        PitchClass( int inValue );
        PitchClass( Spelling inValue );

        int getValue() const;
        void setValue( int inValue );
        Spelling getSpelling() const;
        void setSpelling( Spelling inValue );
        Step getStep() const;
        void setStep( Step inValue );
        Alter getAlter() const;
        void setAlter( Alter inValue );
        int getAlterAmount() const;
        void setAlterAmount( int inValue );

    private:
        Spelling mSpelling;
    };
}
