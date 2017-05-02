// Copyright (c) Matthew James Briggs

#pragma once

#include <string>

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

    private:
        void parseInput();
        void parseMetadata( const ezx::XElement& inElement );
    };
}
