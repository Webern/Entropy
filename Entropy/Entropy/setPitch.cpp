#include "setPitch.h"
#include "goUp.h"
#include "skipSize.h"

namespace entropy
{
    void setPitch( const Rand& scalerand, Scale& scale, const InstrumentPtr& instr, const Int entrpy, const Rand& rand0to12, Pitch& currPitch, Pitch& prevPitch )
    {
        Int scaleDegree = scale.findScaleDegree( prevPitch.getNoteName() );
        Int octave = prevPitch.getOctave();
        if ( scaleDegree < 0 )
        {
            scaleDegree = 0;
        }
        else if ( scaleDegree >= (Int)scale.size() )
        {
            scaleDegree = (Int)scale.size() - 1;
        }
        bool up = goUp( entrpy, rand0to12 );
        Int skip = skipSize( entrpy );
        for ( Int i = 0; i < skip; ++i )
        {
            if ( up )
            {
                if ( scaleDegree == scale.size() - 1 )
                {
                    scaleDegree = 0;
                    ++octave;
                }
                else
                {
                    ++scaleDegree;
                }
            }
            else // if down
            {
                if ( scaleDegree == 0 )
                {
                    scaleDegree = scale.size()-1;
                    --octave;
                }
                else
                {
                    --scaleDegree;
                }
            }
        }
        scale.setCurrent( scaleDegree );
        currPitch = Pitch{ scale.getCurrent(), octave };
        if ( instr->getRange().isInRange( currPitch ) )
        {
            return;
        }
        else
        {
            if ( instr->getRange().isBelowRange( currPitch ) )
            {
                for ( Int o = 6; o > 0; --o )
                {
                    currPitch.setOctave( o );
                    if ( instr->getRange().isInRange( currPitch ) )
                    {
                        return;
                    }
                }
            }
            else if ( instr->getRange().isAboveRange( currPitch ) )
            {
                for ( Int o = 0; o < 7; ++o )
                {
                    currPitch.setOctave( o );
                    if ( instr->getRange().isInRange( currPitch ) )
                    {
                        return;
                    }
                }
            }
        }
        std::cout << "problem in setPitch function" << std::endl;
    }
}