// Copyright (c) Matthew James Briggs

#pragma once

#include "Entropy/Enums.h"
#include "Entropy/Pitch.h"
#include "Entropy/Duration.h"
#include "Entropy/Position.h"
#include "Entropy/Score.h"
#include "Entropy/Constants.h"

#include <string>

namespace entropy
{
    /// @brief A class to represent musical notes.
    ///
    /// @detailed Note has Pitch, Duration and Position relative to the Score.
    /// The position of a note is complicated, see the description below.
    ///
    class Note
    {
    public:
        Note(ScorePtr inScore);

    public:
        ScorePtr getScore() const;

        //@{
        //!
        //! A Note can either be positioned to a Part, Measure and Time withing the Score, or
        //! it can be positioned in a pure tick space. So if you want to hold a string of notes
        //! that represent a melodic fragment, you could setIsPositioned( false ) and the notes
        //! would no longer carry any information about Measure, Voice, etc. In this mode a
        //! note's 'position' is meaningless and is simpy relative to the note that comes before
        //! and after it. But when you setIsPositioned( true ) then the getPosition() and
        //! setPosition() functions become meaningful as the specify the note's precise location
        //! within the score. Another way to conceptualize this is that a note is not in a score
        //! when isPositioned is false and a note is in a score when isPositioned is true. When
        //! you setIsPositioned( true ) the setPosition( p ) will cease to function and
        //! getPosition() will always return 0, 0, 0...
        //!
        bool getIsPositioned() const;
        void setIsPositioned(bool inValue);
        Position getPosition() const;
        void setPosition( Position inPosition );
        //@}

        //@{
        Pitch getPitch() const;
        void setPitch( Pitch inPitch );
        Duration getDuration() const;
        void setDuration( Duration inDuration );
        bool getIsRest() const;
        void setIsRest( bool inValue );
        bool getIsTiedToNext() const;
        void setIsTiedToNext( bool inValue );
        bool getIsTiedFromPrevious() const;
        void setIsTiedFromPrevious( bool inValue );
        int getDynamic() const;
        void setDynamic( int inDynamic );
        bool getIsDynamicVisible() const;
        void setIsDynamicVisible( bool inValue );
        bool getIsStaccato() const;
        void setIsStaccato( bool inValue );
        bool getIsAccented() const;
        void setIsAccented( bool inValue );
        bool getIsTenuto() const;
        void setIsTenuto( bool inValue );
        bool getIsMarcato() const;
        void setIsMarcato( bool inValue );
        bool getIsDownbow() const;
        void setIsDownbow( bool inValue );
        bool getIsUpbow() const;
        void setIsUpbow( bool inValue );
        //@}

    private:
        Position myPosition;
        bool myIsPositioned;
        Pitch myPitch;
        Duration myDuration;
        bool myIsRest;
        bool myIsTiedToNext;
        bool myIsTiedFromPrevious;
        int myDynamic;
        bool myIsDynamicVisible;
        bool myIsStaccato;
        bool myIsAccented;
        bool myIsTenuto;
        bool myIsMarcato;
        bool myIsDownbow;
        bool myIsUpbow;

    private:
        void privateFunc();
        
    };
}
