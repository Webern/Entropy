#pragma once
#include "Instrument.h"
#include <set>

namespace entropy
{
    class InstrumentGroup;
    bool operator==( const InstrumentGroup& l, const InstrumentGroup& r );
    bool operator!=( const InstrumentGroup& l, const InstrumentGroup& r );
    bool operator<( const InstrumentGroup& l, const InstrumentGroup& r );
    bool operator>( const InstrumentGroup& l, const InstrumentGroup& r );
    bool operator<=( const InstrumentGroup& l, const InstrumentGroup& r );
    bool operator>=( const InstrumentGroup& l, const InstrumentGroup& r );
    using InstrumentGroupPtr = std::shared_ptr<InstrumentGroup>;
    struct InstrumentGroupPtrCompare
    {
        bool operator() ( const InstrumentGroupPtr& l, const InstrumentGroupPtr& r ) const
        {
            return (*l) < (*r);
        }
    };
    using InstrumentGroups = std::set<InstrumentGroupPtr,InstrumentGroupPtrCompare>;
    using InstrumentGroupsIter = InstrumentGroups::iterator;
    using InstrumentGroupsConstIter = InstrumentGroups::const_iterator;
    InstrumentGroupPtr makeInstrumentGroup( const Int ID );
    class InstrumentGroup
    {
    public:
        InstrumentGroup( const Int ID );
        void addInstrument( const InstrumentPtr& instrument );
        const Instruments& getInstruments() const;
        Int getID() const;
    private:
        Int myID;
        Instruments myInstruments;
    };
    InstrumentGroupPtr find( const InstrumentGroups& groups, const Int ID );
}