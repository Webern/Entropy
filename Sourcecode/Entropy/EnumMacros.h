// Copyright (c) Matthew James Briggs

#pragma once

#include <string>
#include "Throw.h"

#define ENUM_TOSTR_BEGIN( enumClassName ) \
    inline std::string string##enumClassName( enumClassName inValue ) \
    { \
        switch ( inValue ) \
        { \

#define ENUM_TOSTR_VALUE( enumClassName, enumValue ) \
            case enumClassName::enumValue: return #enumValue; \

#define ENUM_TOSTR_END \
            default: return "ERROR"; \
        } \
    } \

#define ENUM_PARSE_BEGIN( enumClassName ) \
    inline enumClassName string##enumClassName( const std::string& inValue ) \
    { \

#define ENUM_PARSE_VALUE( enumClassName, enumValue ) \
        if( inValue == #enumValue ) \
        { \
            return enumClassName::enumValue; \
        } \

#define ENUM_PARSE_END \
        ENTROPY_THROW( "invalid string" ); \
    }
