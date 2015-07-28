#pragma once
#include "Mx/Enums.h"
#include <vector>
#include "typedefs.h"
#include "NoteName.h"

namespace entropy
{
    class Pitch
    {
    public:
        Pitch();
        Pitch( const NoteName& noteName, const Int octave );
        Pitch( const String& value );
        Int getOctave() const;
        void setOctave( const Int value );
        void setNoteName( const NoteName& value );
        NoteName getNoteName() const;
        String toString() const;
        void parse( const String& value );
        
    private:
        NoteName myNoteName;
        Int myOctave;
    };
    
    std::ostream& operator<<( std::ostream& os, const Pitch& pitch );
    bool operator<( const Pitch& l, const Pitch& r );
    bool operator>( const Pitch& l, const Pitch& r );
    bool operator==( const Pitch& l, const Pitch& r );
    bool operator!=( const Pitch& l, const Pitch& r );
    bool operator<=( const Pitch& l, const Pitch& r );
    bool operator>=( const Pitch& l, const Pitch& r );
    
}