#include "Config.h"
#include "parse.h"
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

namespace entropy
{
    Config::Config()
    :myDuration( 60 )
    ,myTempo( 120 )
    ,myComposer( "" )
    ,myTitle( "" )
    ,myCopyright( "" )
    ,myBeatsPerMeasure( 4 )
    {}
    
    void Config::setDuration( const Int value )
    {
        if ( value > 0 && value < 100000 )
        {
            myDuration = value;
        }
        else
        {
            throw std::out_of_range( "Duration should be between 1 and 100000 seconds." );
        }
    }
    void Config::setTempo( const Int value )
    {
        if ( value > 40 && value < 200 )
        {
            myTempo = value;
        }
        else
        {
            throw std::out_of_range( "Tempo should be between 40 and 200 Bpm." );
        }
    }
    void Config::setComposer( const String& value )
    {
        myComposer = value;
    }
    void Config::setTitle( const String& value )
    {
        myTitle = value;
    }
    void Config::setCopyright( const String& value )
    {
        myCopyright = value;
    }
    void Config::setBeatsPerMeasure( const Int value )
    {
        if ( value >= 2 && value <= 7 )
        {
            myBeatsPerMeasure = value;
        }
        else
        {
            throw std::out_of_range( "Beats per measure should be between 2 and 7.  This will always be 'over 4', i.e. 2/4, 3/4, etc." );
        }
            
    }
    
    Int Config::getDuration() const
    {
        return myDuration;
    }
    Int Config::getTempo() const
    {
        return myTempo;
    }
    String Config::getComposer() const
    {
        return myComposer;
    }
    String Config::getTitle() const
    {
        return myTitle;
    }
    String Config::getCopyright() const
    {
        return myCopyright;
    }
    Int Config::getBeatsPerMeasure() const
    {
        return myBeatsPerMeasure;
    }
    Int Config::getMeasureCount() const
    {
        Int measureCount = 0;
        if ( myDuration > 0 )
        {
            Float fTempo = (Float)myTempo;
            Float fBps = fTempo / ( (Float)60 );
            Float fDuration = (Float)myDuration;
            Float fTotalBeats = fDuration * fBps;
            Float fTotalMeasures = fTotalBeats / (Float)myBeatsPerMeasure;
            measureCount = std::ceilf( fTotalMeasures );
        }
        return measureCount;
    }
    void Config::addInstrumentConfig( const InstrumentConfig& value )
    {
        myInstrumentConfigs.push_back( value );
    }
    const InstrumentConfigs& Config::getInstrumentConfigs() const
    {
        return myInstrumentConfigs;
    }
    Config parseConfig( const String& filepath )
    {
        Config output;
        String line;
        std::ifstream file( filepath );
        std::vector<String> lines;
        if ( file.is_open() )
        {
            while ( getline( file, line ) )
            {
                lines.push_back( line );
            }
            file.close();
        }
        else
        {
            throw std::runtime_error("Error opening file." );
        }
        auto lineIter = lines.cbegin();
        auto end = lines.end();
        String key = "DURATION";
        String strVal = "";
        Int intVal = 0;
        if ( lineIter != end && parseConfigValue( *lineIter, key, intVal ) )
        {
            output.setDuration( intVal );
            ++lineIter;
        }
        key = "TEMPO";
        if ( lineIter != end && parseConfigValue( *lineIter, key, intVal ) )
        {
            output.setTempo( intVal );
            ++lineIter;
        }
        key = "COMPOSER";
        if ( lineIter != end && parseConfigValue( *lineIter, key, strVal ) )
        {
            output.setComposer( strVal );
            ++lineIter;
        }
        key = "TITLE";
        if ( lineIter != end && parseConfigValue( *lineIter, key, strVal ) )
        {
            output.setTitle( strVal );
            ++lineIter;
        }
        key = "COPYRIGHT";
        if ( lineIter != end && parseConfigValue( *lineIter, key, strVal ) )
        {
            output.setCopyright( strVal );
            ++lineIter;
        }
        key = "BEATS_PER_MEASURE";
        if ( lineIter != end && parseConfigValue( *lineIter, key, intVal ) )
        {
            output.setBeatsPerMeasure( intVal );
            ++lineIter;
        }
        key = "INSTRUMENT";
        while ( lineIter != end && parseConfigValue( *lineIter, key, strVal ) )
        {
            StringRow row;
            auto c = strVal.cbegin();
            auto e = strVal.cend();
            while ( c != e )
            {
                std::string fieldValue = readToNextDelim( c, e, '|', "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789., #-" );
                row.push_back( fieldValue );
            }
            static const char* msg = "improper instrument configuration string";
            if ( row.size() != 7 )
            {
                throw new std::runtime_error( msg );
            }
            auto valIter = row.cbegin();
            auto valEnd = row.cend();
            InstrumentConfig iconf;
            if ( valIter != valEnd )
            {
                //[] (const S& s) { return s.S1 == 0; } );
                auto outBeg = output.getInstrumentConfigs().cbegin();
                auto outEnd = output.getInstrumentConfigs().cend();
                auto found = find_if(outBeg, outEnd, [&valIter] (const InstrumentConfig& inside) { return inside.ID == *valIter; } );
                if ( found != outEnd )
                {
                    throw new std::runtime_error( msg );
                }
                iconf.ID = *valIter;
                ++valIter;
            }
            if ( valIter != valEnd )
            {
                iconf.Name = *valIter;
                ++valIter;
            }
            if ( valIter != valEnd )
            {
                iconf.Abbr = *valIter;
                ++valIter;
            }
            if ( valIter != valEnd )
            {
                iconf.RangeLow = Pitch{ *valIter };
                ++valIter;
            }
            if ( valIter != valEnd )
            {
                iconf.RangeHigh = Pitch{ *valIter };
                ++valIter;
            }
            if ( valIter != valEnd )
            {
                iconf.ScoreGroup = std::stoi( valIter->substr( 10 ) );
                ++valIter;
            }
            if ( valIter != valEnd )
            {
                iconf.LogicGroup = std::stoi( valIter->substr( 10 ) );
                ++valIter;
            }
            output.addInstrumentConfig( iconf );
            ++lineIter;
        }
        return output;
    }
    
}