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
    {
        ENTROPY_ASSERT( myScore );
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
        ENTROPY_ASSERT( iter != std::cend( staff.voices ) );
    }
}
