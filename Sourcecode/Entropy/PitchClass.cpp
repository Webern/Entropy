// Copyright (c) Matthew James Briggs

#include "PitchClass.h"

namespace entropy
{
    PitchClass::PitchClass()
    : mSpelling{ Spelling::Cn }
    {
        
    }


    PitchClass::PitchClass( int inValue )
    : PitchClass{}
    {
        setValue( inValue );
    }


    PitchClass::PitchClass( Spelling inValue )
    : PitchClass{}
    {
        setSpelling( inValue );
    }


    int PitchClass::getValue() const
    {
        return intSpelling( mSpelling );
    }


    void PitchClass::setValue( int inValue )
    {
        if ( inValue < 0 )
        {
            mSpelling = intSpelling( 0 );
        }
        else if ( inValue > 11 )
        {
            mSpelling = intSpelling( 11 );
        }
        else
        {
            mSpelling = intSpelling( inValue );
        }
    }


    Spelling PitchClass::getSpelling() const
    {
        return mSpelling;
    }


    void PitchClass::setSpelling( Spelling inValue )
    {
        mSpelling = inValue;
    }


    Step PitchClass::getStep() const
    {
        const auto result = SpellingTables::getStepMap().at( mSpelling );
        return result;
    }


    void PitchClass::setStep( Step inValue )
    {
        const auto alter = getAlter();
        const auto spelling = spell( inValue, alter );
        setSpelling( spelling );
    }


    Alter PitchClass::getAlter() const
    {
        const auto result = SpellingTables::getAlterMap().at( mSpelling );
        return result;
    }


    void PitchClass::setAlter( Alter inValue )
    {
        const auto step = getStep();
        const auto spelling = spell( step, inValue );
        setSpelling( spelling );
    }


    int PitchClass::getAlterAmount() const
    {
        const auto alter = SpellingTables::getAlterMap().at( mSpelling );
        return intAlter( alter );
    }


    void PitchClass::setAlterAmount( int inValue )
    {
        const auto step = getStep();
        const auto alter = intAlter( inValue );
        const auto spelling = spell( step, alter );
        setSpelling( spelling );
    }


}
