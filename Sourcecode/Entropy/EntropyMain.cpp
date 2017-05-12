// Copyright (c) Matthew James Briggs

#include "Entropy/Entropy.h"
#include "Entropy/Config.h"
#include "mx/api/DocumentManager.h"
#include "Entropy/RandomDigits.h"



int main( int argc, const char* argv[] )
{
    entropy::Config config{ argc, argv };
    auto score = config.getScoreSetup();
    auto& scoreData = score->getScoreData();

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

    // add some measures
    score->addTimeSignature( 2, entropy::TimeSignature{ 5, 8 } );

    // save the document
    auto& docMgr = mx::api::DocumentManager::getInstance();
    const auto docId = docMgr.createFromScore( scoreData );
    docMgr.writeToFile( docId, config.getOutputFilePath() );
    docMgr.destroyDocument( docId );

    // other stuff
    const auto vec = entropy::getRandomDigits();
    ENTROPY_UNUSED( vec );

    return 0;
}
