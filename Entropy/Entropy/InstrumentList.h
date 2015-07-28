#pragma once
#include "typedefs.h"
#include <memory>
#include "InstrumentGroup.h"
#include "Config.h"

namespace entropy
{
    class InstrumentList;
    using InstrumentListPtr = std::shared_ptr<InstrumentList>;

    
    InstrumentListPtr makeInstrumentList();
    
    class InstrumentList
    {
    public:
        void addScoreGroup( const InstrumentGroupPtr& group );
        void addLogicGroup( const InstrumentGroupPtr& group );
        const InstrumentGroups& getScoreGroups() const;
        const InstrumentGroups& getLogicGroups() const;
    private:
        InstrumentGroups myScoreGroups;
        InstrumentGroups myLogicGroups;
    };
    
    InstrumentListPtr createInstrumentList( const Config& config );
}