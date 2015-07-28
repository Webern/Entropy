#include "InstrumentGroup.h"
#include <algorithm>

namespace entropy
{
    InstrumentGroup::InstrumentGroup( const Int ID )
    :myID( ID )
    {}
    InstrumentGroupPtr makeInstrumentGroup( const Int ID )
    {
        return std::make_shared<InstrumentGroup>( ID );
    }
    void InstrumentGroup::addInstrument( const InstrumentPtr& instrument )
    {
        if ( instrument )
        {
            auto beg = myInstruments.cbegin();
            auto end = myInstruments.cend();
            auto found = find_if(beg, end, [&instrument](const InstrumentPtr& inside) { return inside->getID() == instrument->getID(); } );
            if ( found == end )
            {
                myInstruments.push_back( instrument );
            }
        }
    }
    const Instruments& InstrumentGroup::getInstruments() const
    {
        return myInstruments;
    }
    Int InstrumentGroup::getID() const
    {
        return myID;
    }
    bool operator==( const InstrumentGroup& l, const InstrumentGroup& r )
    {

        return (!( l < r )) && (!( r < l ));
    }
    bool operator!=( const InstrumentGroup& l, const InstrumentGroup& r )
    {
        return ! ( l == r );
    }
    bool operator<( const InstrumentGroup& l, const InstrumentGroup& r )
    {
        return l.getID() < r.getID();
    }
    bool operator>( const InstrumentGroup& l, const InstrumentGroup& r )
    {
        return r < l;
    }
    bool operator<=( const InstrumentGroup& l, const InstrumentGroup& r )
    {
        return ( l < r ) || ( l == r );
    }
    bool operator>=( const InstrumentGroup& l, const InstrumentGroup& r )
    {
        return ( l > r ) || ( l == r );
    }
    InstrumentGroupPtr find( const InstrumentGroups& groups, const Int ID )
    {
        auto beg = groups.cbegin();
        auto end = groups.cend();
        auto found = find_if(beg, end, [&ID](const InstrumentGroupPtr& inside) { return inside->getID() == ID; } );
        if ( found == end )
        {
            return makeInstrumentGroup( -1 );
        }
        return *found;
    }
}