#include "Note.h"

namespace entropy
{
    Note::Note( const Pitch& pitch, const Duration& duration )
    :myPitch( pitch )
    ,myDuration( duration )
    ,myIsRest( false )
    {
        if ( myIsRest )
        {
            throw new std::runtime_error( "wtf?" );
        }
    }
    
    Note::Note()
    :myPitch()
    ,myDuration()
    ,myIsRest( false )
    {
        if ( myIsRest )
        {
            throw new std::runtime_error( "wtf?" );
        }
    }
    
//    Note::Note( bool isRest )
//    :myPitch()
//    ,myDuration()
//    ,myIsRest( isRest )
//    {}
    
    Pitch Note::getPitch() const
    {
        return myPitch;
    }
    Duration Note::getDuration() const
    {
        return myDuration;
    }
    void Note::setPitch( const Pitch& value )
    {
        myPitch = value;
    }
    void Note::setDuration( const Duration& value )
    {
        myDuration = value;
    }
    bool Note::getIsRest() const
    {
        return myIsRest;
    }
    void Note::setIsRest( const bool value )
    {
        myIsRest = value;
    }
}