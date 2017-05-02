// Copyright (c) Matthew James Briggs

#include "Entropy/Entropy.h"
#include "Entropy/Config.h"
#include "mx/api/DocumentManager.h"
#include "Entropy/RandomDigits.h"

#include <iostream>
#include <fstream>

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>

int main( int argc, const char* argv[] )
{
    entropy::Config config{ argc, argv };
    auto& docMgr = mx::api::DocumentManager::getInstance();
    mx::api::ScoreData scoreData;
    scoreData.workTitle = config.getWorkTitle();
    const auto docId = docMgr.createFromScore( scoreData );
    docMgr.writeToFile( docId, config.getOutputFilePath() );
    docMgr.destroyDocument( docId );
    const auto vec = entropy::getRandomDigits();
    EN_UNUSED( vec );
    return 0;
}
