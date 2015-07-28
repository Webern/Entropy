#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "typedefs.h"

namespace entropy
{
    inline String readToNextDelim( String::const_iterator& c, String::const_iterator end, const char delim = ',', const String validChars = "-.0123456789" )
    {
        std::stringstream output;
        for ( ; c != end && *c != delim; ++c )
        {
            if ( validChars.find( *c ) != String::npos )
            {
                output << *c;
            }
        }
        if ( c != end )
        {
            if ( *c == delim )
            {
                ++c;
            }
        }
        return output.str();
    }
    inline Float getNextFloat( String::const_iterator& c, String::const_iterator end, const char delim = ',', const String validChars = "-.0123456789" )
    {
        std::stringstream strval( readToNextDelim( c, end, delim, validChars ) );
        Float output{ 0 };
        strval >> output;
        return output;
    }
    inline bool parseConfigValue( const String& input_line, const String& key, String& output_value )
    {
        auto key_length = key.length();
        bool success = false;
        if ( input_line.substr( 0, key_length ) == key )
        {
            output_value = input_line.substr( key_length + 1 );
            success = true;
        }
        return success;
    }
    inline bool parseConfigValue( const String& input_line, const String& key, Int& output_value )
    {
        String temp_value;
        if ( ! parseConfigValue( input_line, key, temp_value ) )
        {
            return false;
        }
        std::stringstream ss_value( temp_value );
        ss_value >> output_value;
        return true;
    }
//    inline bool parseConfigValue( const std::vector<String>& input_lines, const String& key, String& output_value )
//    {
//        for ( auto l : input_lines )
//        {
//            if ( parseConfigValue( l, key, output_value ) )
//            {
//                return true;
//            }
//        }
//        return false;
//    }
//    inline bool parseConfigValue( const std::vector<String>& input_lines, const String& key, Int& output_value )
//    {
//        std::string temp_value;
//        if ( parseConfigValue( input_lines, key, temp_value ) )
//        {
//            std::stringstream ss_value( temp_value );
//            ss_value >> output_value;
//            return true;
//        }
//        return false;
//    }
}