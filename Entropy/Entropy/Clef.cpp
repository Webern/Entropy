#include "Clef.h"
#include "ci_find_substr.h"

namespace entropy
{
    Clf inferClef( NotesIterConst beg, NotesIterConst end, const InstrumentPtr& instr )
    {
        Clf c = Clf::Treble;
        auto viola = ci_find_substr( instr->getName(), String{ "viola" } );
        auto flute = ci_find_substr( instr->getName(), String{ "flute" } );
        auto bassoon = ci_find_substr( instr->getName(), String{ "bassoon" } );
        auto trombone = ci_find_substr( instr->getName(), String{ "trombone" } );
        auto tuba = ci_find_substr( instr->getName(), String{ "tuba" } );
        auto cello = ci_find_substr( instr->getName(), String{ "cello" } );
        auto bass = ci_find_substr( instr->getName(), String{ "bass" } );
        if ( viola != String::npos )
        {
            c = Clf::Viola;
        }
        else if ( flute != String::npos )
        {
            c = Clf::Treble;
        }
        else if ( bassoon != String::npos )
        {
            c = Clf::Bass;
        }
        else if ( trombone != String::npos )
        {
            c = Clf::Bass;
        }
        else if ( tuba != String::npos )
        {
            c = Clf::Bass;
        }
        else if ( cello != String::npos )
        {
            c = Clf::Bass;
        }
        else if ( bass != String::npos )
        {
            c = Clf::Bass;
        }
        return c;
    }
}