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
    /// @brief TODO
    ///
    /// @detailed TODO
    ///
    class Note
    {
    public:
        Note(ScorePtr inScore);

    public:
        ScorePtr getScore() const;

        ///@{ Testing 123
        bool getIsPositioned() const;
        void setIsPositioned(bool inValue);
        Position getPosition() const;
        void setPosition( Position inPosition );
        ///@}

        Pitch getPitch() const;
        void setPitch( Pitch inPitch );
        Duration getDuration() const;
        void setDuration( Duration inDuration );
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

    private:
        Position myPosition;
        bool myIsPositioned;
        int myUnpositionedTicks;
        Pitch myPitch;
        Duration myDuration;
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
