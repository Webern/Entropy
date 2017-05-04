// Copyright (c) Matthew James Briggs

#pragma once

#include <string>

namespace entropy
{
    enum class ClefName
    {
        TREBLE,
        ALTO,
        TENOR,
        BASS
    };

    inline std::string clefName( ClefName inValue )
    {
        switch ( inValue )
        {
            case ClefName::TREBLE: return "TREBLE";
            case ClefName::ALTO: return "ALTO";
            case ClefName::TENOR: return "TENOR";
            case ClefName::BASS: return "BASS";
            default: return "ERROR";
        }
    }
}
