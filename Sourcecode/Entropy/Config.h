// Copyright (c) Matthew James Briggs

#pragma once

#include "InstrumentInfo.h"
#include "Score.h"

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
        const std::vector<InstrumentGroupInfo>& getInstrumentGroups() const;

        Score getScoreSetup() const;

        static constexpr const char* const DEFAULT_INPUT = "./Config.entropy";
        static constexpr const char* const DEFAULT_OUTPUT = "./Entropy.xml";

    private:
        std::string myAppPath;
        std::string myInputFilePath;
        std::string myOutputFilePath;
        std::string myWorkTitle;
        std::vector<InstrumentInfo> myInstrumentPrototypes;
        std::vector<InstrumentGroupInfo> myInstrumentGroups;
        
    private:
        void parseInput();
        void parseMetadata( const ezx::XElement& inElement );
        void parseInstrumentDictionary( const ezx::XElement& inElement );
        void parseInstrumentDefinition( const ezx::XElement& inElement );
        void parseScoreSetup( const ezx::XElement& inElement );
        void parseInstrumentGroups( const ezx::XElement& inElement );
        void parseInstrumentGroup( const ezx::XElement& inElement );
        void parseIntruments( const ezx::XElement& inElement, InstrumentGroupInfo& outGroup );
        InstrumentInfo parseInstrument( const ezx::XElement& inElement );
        void addInstrumentNumberSuffixes();
    };
}
