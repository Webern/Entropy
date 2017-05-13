// Copyright (c) Matthew James Briggs

#pragma once

#include <string>
#include <vector>

#include "Entropy/Enums.h"
#include "Entropy/Pitch.h"

namespace entropy
{
    class InstrumentInfo
    {
    public:
        InstrumentTypeID instrumentTypeID;
        std::string name;
        std::string abbreviation;
        std::vector<ClefName> startingClefs;
        std::vector<ClefName> allowableClefs;
        std::string musicXmlSound;
        Pitch rangeLow;
        Pitch rangeHigh;
        int transposition;
    };

    class InstrumentGroupInfo
    {
    public:
        std::string name;
        std::string bracketType;
        std::vector<InstrumentInfo> instruments;
    };
}
