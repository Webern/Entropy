// Copyright (c) Matthew James Briggs

#pragma once

#include "Entropy/Score.h"

namespace entropy
{
    class Position
    {
    public:
        Position( ScorePtr inScore );
        int getPartIndex() const;
        void setPartIndex( int inIndex );
        const std::string& getPartName() const;
        const std::string& getPartId() const;
        int getMeasureIndex() const;
        void setMeasureIndex( int inIndex );
        int getStaffIndex() const;
        void setStaffIndex( int inIndex);
        int getVoiceIndex() const;
        void setVoiceIndex( int inIndex );

    private:
        ScorePtr myScore;
        int myPartIndex;
        int myMeasureIndex;
        int myStaffIndex;
        int myVoiceIndex;

    private:
        void validatePartIndex( int inIndex ) const;
        void validateMeasureIndex( int inIndex ) const;
        void validateStaffIndex( int inIndex ) const;
        void validateVoiceIndex( int inIndex ) const;
    };
}
