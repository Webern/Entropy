// Copyright (c) Matthew James Briggs

#pragma once

#include "Entropy/Enums.h"
#include "mx/api/ScoreData.h"

namespace entropy
{
    class Score;
    using ScorePtr = std::shared_ptr<Score>;
    
    class Score
    {
    public:
        void setScoreData( mx::api::ScoreData inScoreData );
        mx::api::ScoreData getScoreData() const;

    private:
        mx::api::ScoreData myScore;
    };
}
