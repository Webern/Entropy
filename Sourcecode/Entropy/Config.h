// Copyright (c) Matthew James Briggs

#pragma once

#include "InstrumentInfo.h"

#include <string>
#include <vector>

namespace ezx
{
    class XElement;
}

namespace entropy
{
    class Config
    {
    public:
        Config( int argc, const char* argv[] );
        const std::string& getInputFilePath() const;
        const std::string& getOutputFilePath() const;
        const std::string& getWorkTitle() const;

        static constexpr const char* const DEFAULT_INPUT = "./Config.entropy";
        static constexpr const char* const DEFAULT_OUTPUT = "./Entropy.xml";

    private:
        std::string myAppPath;
        std::string myInputFilePath;
        std::string myOutputFilePath;
        std::string myWorkTitle;
        std::vector<InstrumentInfo> myInstrumentPrototypes;
        
    private:
        void parseInput();
        void parseMetadata( const ezx::XElement& inElement );
        void parseInstrumentDictionary( const ezx::XElement& inElement );
        void parseInstrumentDefinition( const ezx::XElement& inElement );
    };
}
