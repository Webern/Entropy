#pragma once
#include "Mx/Enums.h"
#include <vector>
#include "typedefs.h"

namespace entropy
{
    using Step = mx::t::StepEnum;
    Step convert( const Step value );
    
    class NoteName
    {
    public:
        NoteName( const Step step, const Int alter );
        NoteName();
        NoteName( const String& name );
        void setAlter( const Int value );
        void setStep( const Step value );
        Int getAlter() const;
        Step getStep() const;
        void parse( const String& value );
        String toString() const;
        Int getPitchClass() const;
        void setPitchClass( const Int pitchClass );
    private:
        Step myStep;
        Int myAlter;
    };
    
    bool operator==( const NoteName& l, const NoteName& r );
    bool operator!=( const NoteName& l, const NoteName& r );
    bool operator>( const NoteName& l, const NoteName& r );
    bool operator<( const NoteName& l, const NoteName& r );
    bool operator>=( const NoteName& l, const NoteName& r );
    bool operator<=( const NoteName& l, const NoteName& r );
    
}