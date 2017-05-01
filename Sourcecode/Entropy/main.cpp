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
    std::ifstream ifile{ config.getInputFilePath() };
    std::string icontents( ( std::istreambuf_iterator<char>( ifile ) ), std::istreambuf_iterator<char>() );
    scoreData.workTitle = icontents;
    const auto docId = docMgr.createFromScore( scoreData );
    docMgr.writeToFile( docId, config.getOutputFilePath() );
    docMgr.destroyDocument( docId );
    return 0;
}
