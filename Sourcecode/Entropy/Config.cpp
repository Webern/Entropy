// Copyright (c) Matthew James Briggs

#include "Entropy/Config.h"

namespace entropy
{
    Config::Config( int argc, const char* argv[] )
    : myInputFilePath{}
    , myOutputFilePath{}
    {
        myAppPath = argv[0];

        if( argc > 1 )
        {
            myInputFilePath = argv[1];
        }
        else
        {
            myInputFilePath = DEFAULT_INPUT;
        }

        if( argc > 2 )
        {
            myOutputFilePath = argv[2];
        }
        else
        {
            myOutputFilePath = DEFAULT_OUTPUT;
        }
    }


    const std::string& Config::getInputFilePath() const
    {
        return myInputFilePath;
    }


    const std::string& Config::getOutputFilePath() const
    {
        return myOutputFilePath;
    }
}
