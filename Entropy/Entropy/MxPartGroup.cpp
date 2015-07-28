#include "MxPartGroup.h"
#include <sstream>

namespace entropy
{
    mx::e::PartGroupPtr makePartGroupStart( int ID )
    {
        auto r = mx::e::makePartGroup();
        std::stringstream gss;
        gss << ID;
        r->getAttributes()->number = mx::t::XsToken( gss.str() );
        r->getAttributes()->hasNumber = true;
        r->getAttributes()->type = mx::t::StartStop::start;
        r->getGroupSymbol()->setValue( mx::t::GroupSymbolValue::square );
        r->getGroupSymbol()->getAttributes()->defaultX = mx::t::TenthsValue( -10 );
        r->getGroupSymbol()->getAttributes()->hasDefaultX = true;
        r->setHasGroupSymbol( true );
        r->getGroupBarline()->setValue( mx::t::GroupBarlineValue::yes );
        r->setHasGroupBarline( true );
        return r;
    }
    mx::e::PartGroupPtr makePartGroupStop( int ID )
    {
        auto r = mx::e::makePartGroup();
        std::stringstream gss;
        gss << ID;
        r->getAttributes()->number = mx::t::XsToken( gss.str() );
        r->getAttributes()->hasNumber = true;
        r->getAttributes()->type = mx::t::StartStop::stop;
        return r;
    }
    
    mx::e::PartGroupOrScorePartPtr makePartGroupStart( int ID, bool dummy )
    {
        return convertPartGroup( makePartGroupStart( ID ) );
    }
    mx::e::PartGroupOrScorePartPtr makePartGroupStop( int ID, bool dummy )
    {
        return convertPartGroup( makePartGroupStop( ID ) );
    }
    mx::e::PartGroupOrScorePartPtr convertPartGroup( const mx::e::PartGroupPtr& partGroup )
    {
        auto enumPartGroup = mx::e::PartGroupOrScorePart::Choice::partGroup;
        auto pgosp = mx::e::makePartGroupOrScorePart();
        pgosp->setChoice( enumPartGroup );
        pgosp->setPartGroup( partGroup );
        return pgosp;
    }
    void addPartGroupStartToPartList( const mx::e::PartListPtr& partList, Int ID, bool isBeforeFirstInstrument )
    {
        if ( isBeforeFirstInstrument )
        {
            partList->addPartGroup( makePartGroupStart( ID ) );
        }
        else
        {
            partList->addPartGroupOrScorePart( makePartGroupStart( ID, true ) );
        }
    }
    
    
}