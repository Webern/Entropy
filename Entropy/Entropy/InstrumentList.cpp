#include "InstrumentList.h"
#include <set>

namespace entropy
{
    InstrumentListPtr makeInstrumentList()
    {
        return std::make_shared<InstrumentList>();
    }
    void InstrumentList::addScoreGroup( const InstrumentGroupPtr& group )
    {
        if ( group )
        {
            myScoreGroups.insert( group );
        }
    }
    void InstrumentList::addLogicGroup( const InstrumentGroupPtr& group )
    {
        if ( group )
        {
            myLogicGroups.insert( group );
        }
    }
    const InstrumentGroups& InstrumentList::getScoreGroups() const
    {
        return myScoreGroups;
    }
    const InstrumentGroups& InstrumentList::getLogicGroups() const
    {
        return myLogicGroups;
    }
    InstrumentListPtr createInstrumentList( const Config& config )
    {
        auto ilist = makeInstrumentList();
        auto iconfsBegin = config.getInstrumentConfigs().cbegin();
        auto iconfsEnd = config.getInstrumentConfigs().cend();
        InstrumentGroups scoreGroups;
        InstrumentGroups logicGroups;
        for (auto i = iconfsBegin; i != iconfsEnd; ++i )
        {
            scoreGroups.insert( makeInstrumentGroup( i->ScoreGroup ) );
            logicGroups.insert( makeInstrumentGroup( i->LogicGroup ) );
        }
        for (auto i = iconfsBegin; i != iconfsEnd; ++i )
        {
            auto instrument = makeInstrument( i->ID, i->Name, i->Abbr, Range{ i->RangeLow, i->RangeHigh } );
            auto score = find( scoreGroups, i->ScoreGroup );
            auto logic = find( logicGroups, i->LogicGroup );
            score->addInstrument( instrument );
            logic->addInstrument( instrument );
        }
        for ( auto sg : scoreGroups )
        {
            ilist->addScoreGroup( sg );
        }
        for ( auto lg : logicGroups )
        {
            ilist->addLogicGroup( lg );
        }
        return ilist;
    }
}