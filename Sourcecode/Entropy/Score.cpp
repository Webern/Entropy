// Copyright (c) Matthew James Briggs

#include "Score.h"

namespace entropy
{
    void Score::setScoreData( mx::api::ScoreData inScoreData )
    {
        myScore = std::move( inScoreData );
    }

    mx::api::ScoreData Score::getScoreData() const
    {
        return myScore;
    }
}
