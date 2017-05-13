// Copyright (c) Matthew James Briggs

#include "Position.h"

namespace entropy
{
    Position::Position( ScorePtr inScore )
    : myScore{ std::move( inScore ) }
    , myPartIndex{ 0 }
    , myMeasureIndex{ 0 }
    , myStaffIndex{ 0 }
    , myVoiceIndex{ 0 }
    , myTick{ 0 }
    {
        ENTROPY_ASSERT( myScore );
    }


    ScorePtr Position::getScore() const
    {
        return myScore;
    }
    

    int Position::getPartIndex() const
    {
        validatePartIndex( myPartIndex );
        return myPartIndex;
    }


    void Position::setPartIndex( int inIndex )
    {
        validatePartIndex( inIndex );
        myPartIndex = inIndex;
    }


    const std::string& Position::getPartName() const
    {
        const auto partIndex = getPartIndex();
        const auto& result = myScore->getScoreData().parts.at( static_cast<size_t>( partIndex ) ).name;
        return result;
    }


    const std::string& Position::getPartId() const
    {
        const auto partIndex = getPartIndex();
        const auto& result = myScore->getScoreData().parts.at( static_cast<size_t>( partIndex ) ).uniqueId;
        return result;
    }


    int Position::getMeasureIndex() const
    {
        validateMeasureIndex( myMeasureIndex );
        return myMeasureIndex;
    }


    void Position::setMeasureIndex( int inIndex )
    {
        validateMeasureIndex( inIndex );
        myMeasureIndex = inIndex;
    }


    int Position::getStaffIndex() const
    {
        validateStaffIndex( myStaffIndex );
        return myStaffIndex;
    }


    void Position::setStaffIndex( int inIndex)
    {
        validateStaffIndex( inIndex );
        myStaffIndex = inIndex;
    }


    int Position::getVoiceIndex() const
    {
        validateVoiceIndex( myVoiceIndex );
        return myVoiceIndex;
    }


    void Position::setVoiceIndex( int inIndex )
    {
        validateVoiceIndex( inIndex );
        myVoiceIndex = inIndex;
    }


    int Position::getTick() const
    {
        return myTick;
    }


    void Position::setTick( int inTick )
    {
        ENTROPY_ASSERT( inTick >= 0 );
        // TODO validate that the tick position is not beyond
        // the range of the measure
        myTick = inTick;
    }


    int Position::getAbsoluteTick() const
    {
        int tickTotal = 0;
        const auto sigs = getScore()->getTimeSignatureChain();
        auto iter = sigs.cbegin();
        const auto end = sigs.cend();
        ENTROPY_ASSERT( iter != end );

        for( int m = 0; m < myMeasureIndex; ++m )
        {
            ENTROPY_ASSERT( m < static_cast<int>( sigs.size() ) );
            tickTotal += sigs.at( static_cast<size_t>( m ) ).getTicks();
        }

        tickTotal += myTick;
        return tickTotal;
    }

    //////////////////////////////////////////////////////////////////////////////
    // PRIVATE ///////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////

    void Position::validatePartIndex( int inIndex ) const
    {
        const int numParts = static_cast<int>( myScore->getScoreData().parts.size() );
        ENTROPY_ASSERT( inIndex >= 0 );
        ENTROPY_ASSERT( inIndex < numParts );
    }


    void Position::validateMeasureIndex( int inIndex ) const
    {
        const auto& part = myScore->getScoreData().parts.at( static_cast<size_t>( getPartIndex() ) );
        const int numMeasures = static_cast<int>( part.measures.size() );
        ENTROPY_ASSERT( inIndex >= 0 );
        ENTROPY_ASSERT( inIndex < numMeasures );
    }


    void Position::validateStaffIndex( int inIndex ) const
    {
        const auto& part = myScore->getScoreData().parts.at( static_cast<size_t>( getPartIndex() ) );
        const auto& measure = part.measures.at( static_cast<size_t>( getMeasureIndex() ) );
        const int numStaves = static_cast<int>( measure.staves.size() );
        ENTROPY_ASSERT( inIndex >= 0 );
        ENTROPY_ASSERT( inIndex < numStaves );
    }


    void Position::validateVoiceIndex( int inIndex ) const
    {
        const auto& part = myScore->getScoreData().parts.at( static_cast<size_t>( getPartIndex() ) );
        const auto& measure = part.measures.at( static_cast<size_t>( getMeasureIndex() ) );
        const auto& staff = measure.staves.at( static_cast<size_t>( getStaffIndex() ) );
        const auto iter = staff.voices.find( inIndex );
        ENTROPY_ASSERT( iter != std::end( staff.voices ) );
    }
}
