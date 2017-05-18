// Copyright (c) Matthew James Briggs

#include "Entropy/Note.h"

namespace entropy
{

////////////////////////////////////////////////////////////////////////////////
// CTOR AND COPY ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

	Note::Note( ScorePtr inScore )
    : myPosition{ inScore }
    , myIsPositioned{ false }
    , myPitch{}
    , myDuration{}
    , myIsRest{ false }
    , myIsTiedToNext{ false }
    , myIsTiedFromPrevious{ false }
    , myDynamic{ DYNAMIC_MF }
    , myIsDynamicVisible{ false }
    , myIsStaccato{ false }
    , myIsAccented{ false }
    , myIsTenuto{ false }
    , myIsMarcato{ false }
    , myIsDownbow{ false }
    , myIsUpbow{ false }
	{

	}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

	ScorePtr 
    Note::getScore() const
    {
    	return myPosition.getScore();
    }


    bool Note::getIsPositioned() const
    {
        return myIsPositioned;
    }


    void Note::setIsPositioned( bool inValue )
    {
        myIsPositioned = inValue;
    }


    Position
    Note::getPosition() const
    {
        ENTROPY_ASSERT(myIsPositioned);
    	return myPosition;
    }

    
    void 
    Note::setPosition( Position inPosition )
    {
        ENTROPY_ASSERT(myIsPositioned);
    	myPosition = inPosition;
    }

    
    Pitch 
    Note::getPitch() const
    {
    	return myPitch;
    }

    
    void 
    Note::setPitch( Pitch inPitch )
    {
    	myPitch = inPitch;
    }

    
    Duration 
    Note::getDuration() const
    {
    	return myDuration;
    }

    
    void 
    Note::setDuration( Duration inDuration )
    {
    	myDuration = inDuration;
    }


    bool
    Note::getIsRest() const
    {
        return myIsRest;
    }


    void
    Note::setIsRest( bool inValue )
    {
        myIsRest = inValue;
    }


    bool
    Note::getIsAccidentalVisible() const
    {
        return myIsAccidentalVisible;
    }


    void
    Note::setIsAccidentalVisible( bool inValue )
    {
        myIsAccidentalVisible = inValue;
    }


    bool
    Note::getIsTiedToNext() const
    {
    	return myIsTiedToNext;
    }

    
    void 
    Note::setIsTiedToNext( bool inValue )
    {
    	myIsTiedToNext = inValue;
    }

    
    bool 
    Note::getIsTiedFromPrevious() const
    {
    	return myIsTiedFromPrevious;
    }

    
    void 
    Note::setIsTiedFromPrevious( bool inValue )
    {
    	myIsTiedFromPrevious = inValue;
    }

    
    int 
    Note::getDynamic() const
    {
    	return myDynamic;
    }

    
    void 
    Note::setDynamic( int inDynamic )
    {
    	myDynamic = inDynamic;
    }

    
    bool 
    Note::getIsDynamicVisible() const
    {
    	return myIsDynamicVisible;
    }

    
    void 
    Note::setIsDynamicVisible( bool inValue )
    {
    	myIsDynamicVisible = inValue;
    }

    
    bool 
    Note::getIsStaccato() const
    {
    	return myIsStaccato;
    }

    
    void 
    Note::setIsStaccato( bool inValue )
    {
    	myIsStaccato = inValue;
    }

    
    bool 
    Note::getIsAccented() const
    {
    	return myIsAccented;
    }

    
    void 
    Note::setIsAccented( bool inValue )
    {
    	myIsAccented = inValue;
    }

    
    bool 
    Note::getIsTenuto() const
    {
    	return myIsTenuto;
    }

    
    void 
    Note::setIsTenuto( bool inValue )
    {
    	myIsTenuto = inValue;
    }

    
    bool 
    Note::getIsMarcato() const
    {
    	return myIsMarcato;
    }

    
    void 
    Note::setIsMarcato( bool inValue )
    {
    	myIsMarcato = inValue;
    }

    
    bool 
    Note::getIsDownbow() const
    {
    	return myIsDownbow;
    }

    
    void 
    Note::setIsDownbow( bool inValue )
    {
    	myIsDownbow = inValue;
    }

    
    bool 
    Note::getIsUpbow() const
    {
    	return myIsUpbow;
    }

    
    void 
    Note::setIsUpbow( bool inValue )
    {
    	myIsUpbow = inValue;
    }

    mx::api::NoteData
    Note::createWithoutInsert() const
    {
        mx::api::NoteData outNote;
        outNote.pitchData.step = convertStep( myPitch.getPitchClass().getStep() );
        outNote.pitchData.alter = myPitch.getPitchClass().getAlterAmount();
        outNote.pitchData.octave = myPitch.getOctave();

        if( getIsPositioned() )
        {
            outNote.tickTimePosition = getPosition().getTick();
        }
        else
        {
            outNote.tickTimePosition = 0;
        }

        outNote.isRest = getIsRest();

        const auto alter = myPitch.getPitchClass().getAlter();

        if( getIsAccidentalVisible() && alter != Alter::ERROR )
        {
            outNote.pitchData.accidental = convertAlter( alter );
        }

        return outNote;
    }


    void
    Note::createAndInsert() const
    {

    }


////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS ///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

    void
    Note::privateFunc()
    {

    }

}
