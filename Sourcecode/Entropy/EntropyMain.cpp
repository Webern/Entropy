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
