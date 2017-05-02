// Copyright (c) Matthew James Briggs

#include "Entropy/Entropy.h"
#include "Entropy/Config.h"
#include "mx/api/DocumentManager.h"

#include <iostream>
#include <fstream>

int main( int argc, const char* argv[] )
{
    entropy::Config config{ argc, argv };
    auto& docMgr = mx::api::DocumentManager::getInstance();
    mx::api::ScoreData scoreData;
    scoreData.workTitle = config.getWorkTitle();
    const auto docId = docMgr.createFromScore( scoreData );
    docMgr.writeToFile( docId, config.getOutputFilePath() );
    docMgr.destroyDocument( docId );
    return 0;
}
