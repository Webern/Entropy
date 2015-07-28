#pragma once
#include "typedefs.h"
#include "Pitch.h"
#include "Duration.h"
#include <vector>

namespace entropy
{
    class Note;
    using Notes = std::vector<Note>;
    using NotesIter = Notes::iterator;
    using NotesIterConst = Notes::const_iterator;
    
    class Note
    {
    public:
        Note( const Pitch& pitch, const Duration& duration );
        Note();
        // explicit Note( bool isRest );
        Pitch getPitch() const;
        Duration getDuration() const;
        void setPitch( const Pitch& value );
        void setDuration( const Duration& value );
        bool getIsRest() const;
        void setIsRest( const bool value );
    private:
        Pitch myPitch;
        Duration myDuration;
        bool myIsRest;
    };
}