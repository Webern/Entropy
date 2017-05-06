// Copyright (c) Matthew James Briggs

#include <map>

#include "Entropy/Config.h"
#include "EazyXml/EazyXml.h"
#include "Entropy/Throw.h"

namespace entropy
{
    Config::Config( int argc, const char* argv[] )
    : myInputFilePath{}
    , myOutputFilePath{}
    , myInstrumentGroups{}
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
        addInstrumentNumberSuffixes();
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


    const std::vector<InstrumentGroupInfo>& Config::getInstrumentGroups() const
    {
        return myInstrumentGroups;
    }


    void Config::parseInput()
    {
        using namespace ezx;
        auto xdoc = XFactory::makeXDoc();
        xdoc->loadFile( getInputFilePath() );
        const auto root = xdoc->getRoot();
        ENTROPY_ASSERT( root->getName() == "entropy-input" );
        auto it = root->begin();
        const auto e = root->end();

        ENTROPY_ASSERT( it != e );
        ENTROPY_ASSERT( it->getName() == "metadata" );
        parseMetadata( *it );
        ++it;

        ENTROPY_ASSERT( it != e );
        ENTROPY_ASSERT( it->getName() == "instrument-dictionary" );
        parseInstrumentDictionary( *it );
        ++it;

        ENTROPY_ASSERT( it != e );
        ENTROPY_ASSERT( it->getName() == "score-setup" );
        parseScoreSetup( *it );
        ++it;

    }


    void Config::parseMetadata( const ezx::XElement& inElement )
    {
        auto child = inElement.begin();
        const auto child1 = child->getName();
        ENTROPY_ASSERT( child1 == "work-title" );
        ENTROPY_ASSERT( child->getType() == ezx::XElementType::text );
        myWorkTitle = child->getValue();
    }


    void Config::parseInstrumentDictionary( const ezx::XElement& inElement )
    {
        myInstrumentPrototypes.clear();
        ENTROPY_ASSERT( inElement.getName() == "instrument-dictionary" );
        auto it = inElement.begin();
        const auto e = inElement.end();

        for ( ; it != e; ++it )
        {
            parseInstrumentDefinition( *it );
        }
    }


    void Config::parseInstrumentDefinition( const ezx::XElement& inElement )
    {
        ENTROPY_ASSERT( inElement.getName() == "instrument-definition" );
        InstrumentInfo instrument;
        ENTROPY_ASSERT( inElement.attributesBegin() != inElement.attributesEnd() );
        auto attr = inElement.attributesBegin();
        ENTROPY_ASSERT( attr->getName() == "instrument-id" );
        instrument.instrumentTypeID = stringInstrumentTypeID( attr->getValue() );
        auto it = inElement.begin();
        const auto e = inElement.end();

        ENTROPY_ASSERT( it != e );
        ENTROPY_ASSERT( it->getName() == "name" );
        instrument.name = it->getValue();
        ++it;

        ENTROPY_ASSERT( it != e );
        ENTROPY_ASSERT( it->getName() == "abbreviation" );
        instrument.abbreviation = it->getValue();
        ++it;

        ENTROPY_ASSERT( it != e );
        ENTROPY_ASSERT( it->getName() == "starting-clefs" );
        for( auto c = it->begin(); c != it->end(); ++c )
        {
            ENTROPY_ASSERT( c->getName() == "clef" );
            instrument.startingClefs.push_back( stringClefName( c->getValue() ) );
        }
        ++it;

        ENTROPY_ASSERT( it != e );
        ENTROPY_ASSERT( it->getName() == "allowable-clefs" );
        for( auto c = it->begin(); c != it->end(); ++c )
        {
            ENTROPY_ASSERT( c->getName() == "clef" );
            instrument.allowableClefs.push_back( stringClefName( c->getValue() ) );
        }
        ++it;

        ENTROPY_ASSERT( it != e );
        ENTROPY_ASSERT( it->getName() == "musicxml-sound" );
        instrument.musicXmlSound = it->getValue();
        ++it;

        ENTROPY_ASSERT( it != e );
        ENTROPY_ASSERT( it->getName() == "transposition" );
        instrument.transposition = std::stoi(it->getValue());
        ++it;

        ENTROPY_ASSERT( it != e );
        ENTROPY_ASSERT( it->getName() == "range-low" );
        ENTROPY_ASSERT( it->getType() == ezx::XElementType::text );
        const auto rangeLowStr = it->getValue();
        if ( !instrument.rangeLow.parse( rangeLowStr ) )
        {
            instrument.rangeLow = Pitch( Spelling::Cn, -1 );
        }
        ++it;

        ENTROPY_ASSERT( it != e );
        ENTROPY_ASSERT( it->getName() == "range-high" );
        ENTROPY_ASSERT( it->getType() == ezx::XElementType::text );
        const auto rangeHighStr = it->getValue();
        if ( !instrument.rangeHigh.parse( rangeHighStr ) )
        {
            instrument.rangeHigh = Pitch( Spelling::Cn, 9 );
        }
        ++it;

        myInstrumentPrototypes.emplace_back( std::move( instrument ) );
    }


    void Config::parseScoreSetup( const ezx::XElement& inElement )
    {
        ENTROPY_ASSERT( inElement.getName() == "score-setup" );
        ENTROPY_ASSERT( inElement.getType() == ezx::XElementType::element );
        auto it = inElement.begin();
        const auto e = inElement.end();

        ENTROPY_ASSERT( it != e );
        parseInstrumentGroups( *it );
    }


    void Config::parseInstrumentGroups( const ezx::XElement& inElement )
    {
        ENTROPY_ASSERT( inElement.getName() == "instrument-groups" );
        ENTROPY_ASSERT( inElement.getType() == ezx::XElementType::element );
        auto it = inElement.begin();
        const auto e = inElement.end();
        for( ; it != e; ++it )
        {
            parseInstrumentGroup( *it );
        }
    }


    void Config::parseInstrumentGroup( const ezx::XElement& inElement )
    {
        ENTROPY_ASSERT( inElement.getName() == "instrument-group" );
        ENTROPY_ASSERT( inElement.getType() == ezx::XElementType::element );
        auto it = inElement.begin();
        const auto e = inElement.end();
        ENTROPY_ASSERT( it != e );
        ENTROPY_ASSERT( it->getName() == "group-name" );
        ENTROPY_ASSERT( it->getType() == ezx::XElementType::text );
        InstrumentGroupInfo grp;
        grp.name = it->getValue();
        ++it;

        ENTROPY_ASSERT( it != e );
        ENTROPY_ASSERT( it->getName() == "group-type" );
        ENTROPY_ASSERT( it->getType() == ezx::XElementType::text );
        grp.backetType = it->getValue();
        ++it;

        ENTROPY_ASSERT( it != e );
        ENTROPY_ASSERT( it->getName() == "instruments" );
        ENTROPY_ASSERT( it->getType() == ezx::XElementType::element );
        parseIntruments( *it, grp );
        ++it;

        myInstrumentGroups.push_back( grp );
    }


    void
    Config::parseIntruments( const ezx::XElement& inElement, InstrumentGroupInfo& outGroup )
    {
        ENTROPY_ASSERT( inElement.getName() == "instruments" );
        ENTROPY_ASSERT( inElement.getType() == ezx::XElementType::element );
        auto it = inElement.begin();
        const auto e = inElement.end();
        ENTROPY_ASSERT( it != e );

        for( ; it != e; ++it )
        {
            outGroup.instruments.push_back( parseInstrument( *it ) );
        }
    }


    InstrumentInfo Config::parseInstrument( const ezx::XElement& inElement )
    {
        ENTROPY_ASSERT( inElement.getName() == "instrument" );
        ENTROPY_ASSERT( inElement.getType() == ezx::XElementType::empty );
        const auto ait = inElement.attributesBegin();
        const auto e = inElement.attributesEnd();
        ENTROPY_ASSERT( ait != e );
        ENTROPY_ASSERT( ait->getName() == "id" );
        const auto valueStr = ait->getValue();
        const auto value = stringInstrumentTypeID( valueStr );
        const auto iter = std::find_if( std::cbegin( myInstrumentPrototypes ),
                                        std::cend( myInstrumentPrototypes ),
                                        [&]( const InstrumentInfo& inInfo )
                                        {
                                            return inInfo.instrumentTypeID == value;
                                        } );
        ENTROPY_ASSERT( iter != std::cend( myInstrumentPrototypes ) );
        return *iter;
    }


    void Config::addInstrumentNumberSuffixes()
    {
        std::map<InstrumentTypeID, int> uniqueInstrumentTypes;

        for( const auto& grp : myInstrumentGroups )
        {
            for( const auto& inst : grp.instruments )
            {
                const auto typ = inst.instrumentTypeID;
                const auto it = uniqueInstrumentTypes.find( typ );

                if( it == std::cend( uniqueInstrumentTypes ) )
                {
                    uniqueInstrumentTypes[typ] = 0;
                }

                ++uniqueInstrumentTypes[typ];
            }
        }

        auto countdown = uniqueInstrumentTypes;

        for( auto& grp : myInstrumentGroups )
        {
            for( auto& inst : grp.instruments )
            {
                const auto typ = inst.instrumentTypeID;
                const auto it = countdown.find( typ );

                if( it != std::cend( uniqueInstrumentTypes ) )
                {
                    const int total = uniqueInstrumentTypes.at( typ );

                    if( total > 1 )
                    {
                        const int remaining = it->second;
                        const int current = total - remaining + 1;
                        std::stringstream n;
                        n << inst.name << " " << current;
                        inst.name = n.str();
                        std::stringstream abbr;
                        abbr << inst.abbreviation << " " << current;
                        inst.abbreviation = abbr.str();
                    }
                    --it->second;
                }
            }
        }
    }
}
