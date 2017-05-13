// Copyright (c) Matthew James Briggs

#pragma once

#include "Entropy/Enums.h"
#include "Entropy/TimeSignature.h"
#include "mx/api/ScoreData.h"

namespace entropy
{
    class Score;
    using ScorePtr = std::shared_ptr<Score>;
    
    class Score
    {
    public:
        void setScoreData( mx::api::ScoreData inScoreData );
        const mx::api::ScoreData& getScoreData() const;
        mx::api::ScoreData& getScoreData();
        void appendmeasures( int inNumMeasures );

        void addTimeSignature( int inMeasureIndex, TimeSignature inTimeSignature );
        bool removeTimeSignature( int inMeasureIndex );
        void clearTimeSignatures();
        const std::map<int, TimeSignature>& getTimeSignatureMap() const;

        /// returns the time signature for each measure
        std::vector<TimeSignature> getTimeSignatureChain() const;

    private:
        mx::api::ScoreData myScore;
        std::map<int, TimeSignature> myTimeSignatureMap;

    private:
        void updateMeasureTimeSignatures();
        
    };
}
