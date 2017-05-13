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


    void Score::addTimeSignature( int inMeasureIndex, TimeSignature inTimeSignature )
    {
        myTimeSignatureMap[inMeasureIndex] = inTimeSignature;
        updateMeasureTimeSignatures();
    }


    bool Score::removeTimeSignature( int inMeasureIndex )
    {
        const auto iter = myTimeSignatureMap.find( inMeasureIndex );
        const bool isFound = iter != std::end( myTimeSignatureMap );
        myTimeSignatureMap.erase( iter );

        if (isFound)
        {
            updateMeasureTimeSignatures();
        }

        return isFound;
    }


    void Score::clearTimeSignatures()
    {
        myTimeSignatureMap.clear();
        updateMeasureTimeSignatures();
    }


    const std::map<int, TimeSignature>& Score::getTimeSignatureMap() const
    {
        return myTimeSignatureMap;
    }


    std::vector<TimeSignature>
    Score::getTimeSignatureChain() const
    {
        std::vector<TimeSignature> sigs;
        ENTROPY_ASSERT( !myScore.parts.empty() );
        const int measureCount = static_cast<int>( myScore.parts.front().measures.size() );

        TimeSignature currentTimeSignature;

        for( int m = 0; m < measureCount; ++m )
        {
            const auto iter = myTimeSignatureMap.find( m );
            const bool isFound = iter != std::end( myTimeSignatureMap );

            if( isFound )
            {
                currentTimeSignature = iter->second;
            }

            sigs.push_back( currentTimeSignature );
        }

        return sigs;
    }


    void Score::updateMeasureTimeSignatures()
    {
        if ( myTimeSignatureMap.empty() )
        {
            for( auto& part : myScore.parts )
            {
                bool isFirst = true;
                for( auto& measure : part.measures )
                {
                    measure.timeSignature = mx::api::TimeSignatureData{};

                    if( isFirst )
                    {
                        measure.timeSignature.isImplicit = false;
                        measure.timeSignature.display = mx::api::Bool::yes;
                        isFirst = false;
                    }
                }
            }

            return;
        }

        const int lastTimeSignatureMeasureIndex = myTimeSignatureMap.crbegin()->first;
        const int measuresToAppend = 1 + lastTimeSignatureMeasureIndex - myScore.getNumMeasures();

        if( measuresToAppend > 0 )
        {
            appendmeasures( measuresToAppend );
        }

        for( auto& part : myScore.parts )
        {
            TimeSignature current{};
            TimeSignature previous{};
            int measureIndex = 0;

            for( auto& measure : part.measures )
            {
                bool show = false;
                const auto iter = myTimeSignatureMap.find( measureIndex );
                const bool isFound = iter != std::end( myTimeSignatureMap );
                const bool isFirstMeasure = measureIndex == 0;

                if( isFound )
                {
                    const auto oldTemp = current;
                    current = iter->second;
                    const bool topSame = previous.getTopNumber() == current.getTopNumber();
                    const bool bottomSame = previous.getBottomNumber() == current.getBottomNumber();
                    show = ( !topSame ) || ( !bottomSame ) || ( isFirstMeasure );
                    previous = oldTemp;
                }
                else if ( isFirstMeasure )
                {
                    show = true;
                }
                else
                {
                    show = false;
                }

                measure.timeSignature.beats = current.getTopNumber();
                measure.timeSignature.beatType = current.getBottomNumber();
                measure.timeSignature.symbol = mx::api::TimeSignatureSymbol::unspecified;
                measure.timeSignature.display = show ? mx::api::Bool::yes : mx::api::Bool::unspecified;
                measure.timeSignature.isImplicit = !show;
                ++measureIndex;
            }
        }

    }
}
