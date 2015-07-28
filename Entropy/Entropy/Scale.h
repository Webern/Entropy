#pragma once
#include "Mx/Enums.h"
#include <vector>
#include "NoteName.h"

namespace entropy
{
    using mx::t::StepEnum;
    class Scale
    {
    public:
        Scale();
        Int size() const;
        void addNoteName( const NoteName& value );
        void removeNoteName( const NoteName& value );
        NoteName getNoteName( const Int whichNote ) const;
        NoteName getCurrent() const;
        void setCurrent( const Int value );
        Scale& increment( const Int scaleDegrees );
        Scale& increment();
        Scale& decrement();
        void parse( const String& str );
        String toString() const;
        Int findScaleDegree( const NoteName& notename ) const;
        Int getCurrentScaleDegree() const;
    private:
        std::vector<NoteName> myNotes;
        Int myCurrent;
    };
}