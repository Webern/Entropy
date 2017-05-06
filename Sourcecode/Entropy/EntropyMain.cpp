// Copyright (c) Matthew James Briggs

#include "Entropy/Entropy.h"
#include "Entropy/Config.h"
#include "mx/api/DocumentManager.h"
#include "Entropy/RandomDigits.h"



int main( int argc, const char* argv[] )
{
    entropy::Config config{ argc, argv };
    mx::api::ScoreData scoreData;
    scoreData.workTitle = config.getWorkTitle();
    scoreData.composer = "Matthew James Briggs";
    scoreData.copyright = "© 2017 by Matthew James Briggs";
    scoreData.ticksPerQuarter = entropy::TICKS_PER_QUARTER;
    
    int instrumentIndex = 0;
    const auto& grps = config.getInstrumentGroups();

    mx::api::TimeSignatureData timeSig{};
    timeSig.beats = 4;
    timeSig.beatType = 4;
    timeSig.isImplicit = false;
    timeSig.display = mx::api::Bool::yes;

    std::vector<std::string> part_ids;
    
    for( const auto& grp : grps )
    {
        int start = instrumentIndex;

        for( const auto& inst : grp.instruments )
        {
            mx::api::PartData part{};
            part.uniqueId = std::string{ entropy::stringInstrumentTypeID( inst.instrumentTypeID ) } + std::string{ "_PART_INDEX_" } + std::to_string(instrumentIndex);
            part_ids.push_back( part.uniqueId );
            part.name = inst.name;
            part.abbreviation = inst.abbreviation;
            part.instrumentData.uniqueId = std::string{ "I_" } + part.uniqueId;
            part.instrumentData.sound = inst.musicXmlSound;
            part.instrumentData.name = inst.name;
            mx::api::MeasureData measure;

            for( const auto& clef : inst.startingClefs )
            {
                mx::api::ClefData clefData{};

                if( clef == entropy::ClefName::TREBLE )
                {
                    clefData.setTreble();
                }
                else if( clef == entropy::ClefName::TENOR )
                {
                    clefData.setTenor();
                }
                else if( clef == entropy::ClefName::ALTO )
                {
                    clefData.setAlto();
                }
                else if( clef == entropy::ClefName::BASS )
                {
                    clefData.setBass();
                }
                else
                {
                    ENTROPY_THROW( "unsupported clef" );
                }

                mx::api::StaffData staff{};
                staff.clefs.push_back( clefData );
                measure.staves.push_back( staff );
            }
            measure.timeSignature = timeSig;
            part.measures.push_back( measure );
            scoreData.parts.push_back( part );
            ++instrumentIndex;
        }

        int stop = instrumentIndex - 1;
        mx::api::PartGroupData pg{};
        pg.name = grp.name;
        pg.bracketType = mx::api::BracketType::bracket;
        pg.firstPartIndex = start;
        pg.lastPartIndex = stop;
        scoreData.partGroups.push_back( pg );
    }

    mx::api::NoteData note{};
    note.durationData.durationTimeTicks = entropy::TICKS_PER_QUARTER;
    auto voiceP = &scoreData.parts.at(0).measures.at(0).staves.at(0).voices[0];
    note.pitchData.octave = 5;
    note.pitchData.step = mx::api::Step::a;
    note.durationData.durationName = mx::api::DurationName::quarter;
    note.tickTimePosition = 0;
    voiceP->notes.push_back( note );
    note.tickTimePosition += entropy::TICKS_PER_QUARTER;
    note.pitchData.step = mx::api::Step::b;
    voiceP->notes.push_back( note );
    note.tickTimePosition += entropy::TICKS_PER_QUARTER;
    note.pitchData.step = mx::api::Step::e;
    voiceP->notes.push_back( note );
    note.tickTimePosition += entropy::TICKS_PER_QUARTER;
    note.pitchData.step = mx::api::Step::f;
    voiceP->notes.push_back( note );

    voiceP = &scoreData.parts.at(1).measures.at(0).staves.at(0).voices[0];
    note.pitchData.octave = 4;
    note.pitchData.step = mx::api::Step::c;
    note.durationData.durationName = mx::api::DurationName::quarter;
    note.tickTimePosition = 0;
    voiceP->notes.push_back( note );
    note.tickTimePosition += entropy::TICKS_PER_QUARTER;
    note.pitchData.step = mx::api::Step::g;
    voiceP->notes.push_back( note );
    note.tickTimePosition += entropy::TICKS_PER_QUARTER;
    note.pitchData.step = mx::api::Step::d;
    voiceP->notes.push_back( note );
    note.tickTimePosition += entropy::TICKS_PER_QUARTER;
    note.pitchData.step = mx::api::Step::b;
    voiceP->notes.push_back( note );

    voiceP = &scoreData.parts.at(2).measures.at(0).staves.at(0).voices[0];
    note.pitchData.octave = 3;
    note.pitchData.step = mx::api::Step::e;
    note.durationData.durationName = mx::api::DurationName::quarter;
    note.tickTimePosition = 0;
    voiceP->notes.push_back( note );
    note.tickTimePosition += entropy::TICKS_PER_QUARTER;
    note.pitchData.step = mx::api::Step::e;
    voiceP->notes.push_back( note );
    note.tickTimePosition += entropy::TICKS_PER_QUARTER;
    note.pitchData.step = mx::api::Step::f;
    voiceP->notes.push_back( note );
    note.tickTimePosition += entropy::TICKS_PER_QUARTER;
    note.pitchData.step = mx::api::Step::e;
    voiceP->notes.push_back( note );

    voiceP = &scoreData.parts.at(3).measures.at(0).staves.at(0).voices[0];
    note.pitchData.octave = 2;
    note.pitchData.step = mx::api::Step::d;
    note.durationData.durationName = mx::api::DurationName::quarter;
    note.tickTimePosition = 0;
    voiceP->notes.push_back( note );
    note.tickTimePosition += entropy::TICKS_PER_QUARTER;
    note.pitchData.step = mx::api::Step::f;
    voiceP->notes.push_back( note );
    note.tickTimePosition += entropy::TICKS_PER_QUARTER;
    note.pitchData.step = mx::api::Step::d;
    voiceP->notes.push_back( note );
    note.tickTimePosition += entropy::TICKS_PER_QUARTER;
    note.pitchData.step = mx::api::Step::g;
    voiceP->notes.push_back( note );

    // save the document
    auto& docMgr = mx::api::DocumentManager::getInstance();
    const auto docId = docMgr.createFromScore( scoreData );
    docMgr.writeToFile( docId, config.getOutputFilePath() );
    docMgr.destroyDocument( docId );

    // other stuff
    const auto vec = entropy::getRandomDigits();
    EN_UNUSED( vec );

    return 0;
}
