#include "Pitch.h"
#include <sstream>

namespace entropy
{
    Pitch::Pitch()
    :myNoteName( mx::t::StepEnum::c, 0 )
    ,myOctave( 4 )
    {}
    Pitch::Pitch( const NoteName& noteName, const Int octave )
    :myNoteName( noteName )
    ,myOctave( octave )
    {}
    
    Pitch::Pitch( const String& value )
    :myNoteName( mx::t::StepEnum::c, 0 )
    ,myOctave( 4 )
    {
        parse( value );
    }
    Int Pitch::getOctave() const
    {
        return myOctave;
    }
    void Pitch::setOctave( const Int value )
    {
        myOctave = value;
    }
    void Pitch::setNoteName( const NoteName& value )
    {
        myNoteName = value;
    }
    NoteName Pitch::getNoteName() const
    {
        return myNoteName;
    }
    String Pitch::toString() const
    {
        std::stringstream ss;
        ss << myNoteName.toString();
        ss << myOctave;
        return ss.str();
    }
    void Pitch::parse( const String& value )
    {
        auto oct_pos = value.find_first_of( "-0123456789" );
        if ( oct_pos == String::npos )
        {
            throw std::runtime_error( "error parsing pitch." );
        }
        String noteNameStr = value.substr( 0, oct_pos );
        String octStr = value.substr( oct_pos );
        NoteName noteName( noteNameStr );
        std::stringstream octSs( octStr );
        Int oct = 0;
        octSs >> oct;
        myNoteName = noteName;
        myOctave = oct;
    }
    std::ostream& operator<<( std::ostream& os, const Pitch& pitch )
    {
        return os << pitch.toString();
    }
    bool operator<( const Pitch& l, const Pitch& r )
    {
        if( l.getOctave() != r.getOctave() )
        {
            return l.getOctave() < r.getOctave();
        }
        return l.getNoteName().getPitchClass() < r.getNoteName().getPitchClass();
    }
    bool operator>( const Pitch& l, const Pitch& r )
    {
        return r < l;
    }
    bool operator==( const Pitch& l, const Pitch& r )
    {
        return ( ! ( l < r ) ) && ( ! ( r < l ) );
    }
    bool operator!=( const Pitch& l, const Pitch& r )
    {
        return ( l < r ) || ( r < l );
    }
    bool operator<=( const Pitch& l, const Pitch& r )
    {
        return ( l < r ) || ( l == r );
    }
    bool operator>=( const Pitch& l, const Pitch& r )
    {
        return ( l > r ) || ( l == r );
    }
}