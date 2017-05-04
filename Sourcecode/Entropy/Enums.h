// Copyright (c) Matthew James Briggs

#pragma once

#include <string>

#include "EnumMacros.h"

namespace entropy
{
    enum class ClefName
    {
        TREBLE,
        ALTO,
        TENOR,
        BASS,
    };

    ENUM_TOSTR_BEGIN( ClefName )
    ENUM_TOSTR_VALUE( ClefName, TREBLE )
    ENUM_TOSTR_VALUE( ClefName, ALTO )
    ENUM_TOSTR_VALUE( ClefName, TENOR )
    ENUM_TOSTR_VALUE( ClefName, BASS )
    ENUM_TOSTR_END;

    ENUM_PARSE_BEGIN( ClefName )
    ENUM_PARSE_VALUE( ClefName, TREBLE )
    ENUM_PARSE_VALUE( ClefName, ALTO )
    ENUM_PARSE_VALUE( ClefName, TENOR )
    ENUM_PARSE_VALUE( ClefName, BASS )
    ENUM_PARSE_END;

    enum class InstrumentTypeID
    {
        VIOLIN,
        VIOLA,
        CELLO,
        DOUBLE_BASS,
    };

    ENUM_TOSTR_BEGIN( InstrumentTypeID )
    ENUM_TOSTR_VALUE( InstrumentTypeID, VIOLIN )
    ENUM_TOSTR_VALUE( InstrumentTypeID, VIOLA )
    ENUM_TOSTR_VALUE( InstrumentTypeID, CELLO )
    ENUM_TOSTR_VALUE( InstrumentTypeID, DOUBLE_BASS )
    ENUM_TOSTR_END;

    ENUM_PARSE_BEGIN( InstrumentTypeID )
    ENUM_PARSE_VALUE( InstrumentTypeID, VIOLIN )
    ENUM_PARSE_VALUE( InstrumentTypeID, VIOLA )
    ENUM_PARSE_VALUE( InstrumentTypeID, CELLO )
    ENUM_PARSE_VALUE( InstrumentTypeID, DOUBLE_BASS )
    ENUM_PARSE_END;
}
