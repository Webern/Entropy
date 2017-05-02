// Copyright (c) Matthew James Briggs

#include "Entropy/Config.h"
#include "EazyXml/EazyXml.h"
#include "Entropy/Throw.h"

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

        parseInput();
    }


    const std::string& Config::getInputFilePath() const
    {
        return myInputFilePath;
    }


    const std::string& Config::getOutputFilePath() const
    {
        return myOutputFilePath;
    }


    const std::string& Config::getWorkTitle() const
    {
        return myWorkTitle;
    }


    void Config::parseInput()
    {
        using namespace ezx;
        auto xdoc = XFactory::makeXDoc();
        xdoc->loadFile( getInputFilePath() );
        const auto root = xdoc->getRoot();
        ENTROPY_ASSERT( root->getName() == "entropy-input" );
        auto rootChild = root->begin();
        const auto rootEnd = root->end();
        ENTROPY_ASSERT( rootChild != rootEnd );
        const auto rootChild1 = rootChild->getName();
        ENTROPY_ASSERT( rootChild1 == "metadata" );
        parseMetadata( *rootChild );
    }


    void Config::parseMetadata( const ezx::XElement& inElement )
    {
        auto child = inElement.begin();
        const auto child1 = child->getName();
        ENTROPY_ASSERT( child1 == "work-title" );
        ENTROPY_ASSERT( child->getType() == ezx::XElementType::text );
        myWorkTitle = child->getValue();
    }
}
