// Copyright (c) Matthew James Briggs

#include "Score.h"

namespace entropy
{
    void Score::setScoreData( mx::api::ScoreData inScoreData )
    {
        myScore = std::move( inScoreData );
    }

    const mx::api::ScoreData& Score::getScoreData() const
    {
        return myScore;
    }

    mx::api::ScoreData& Score::getScoreData()
    {
        return myScore;
    }

    void Score::appendmeasures( int inNumMeasures )
    {
        for( auto& part : myScore.parts )
        {
            const auto& lastMeasure = part.measures.back();
            const auto staffCount = static_cast<int>( lastMeasure.staves.size() );
            std::set<int> voices;

            for( const auto& staff : lastMeasure.staves )
            {
                for( const auto& voice : staff.voices )
                {
                    voices.insert( voice.first );
                }
            }

            for( int i = 0; i < inNumMeasures; ++i )
            {
                mx::api::MeasureData newMeasure{};
                newMeasure.timeSignature = lastMeasure.timeSignature;
                newMeasure.timeSignature.isImplicit = true;
                newMeasure.timeSignature.display = mx::api::Bool::unspecified;

                for( int s = 0; s < staffCount; ++s )
                {
                    mx::api::StaffData staff{};

                    for( const auto& voiceIndex : voices )
                    {
                        staff.voices[voiceIndex] = mx::api::VoiceData{};
                    }

                    newMeasure.staves.push_back( staff );
                }

                part.measures.push_back( newMeasure );
            }
        }
    }
}
