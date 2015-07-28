#pragma once
#include "typedefs.h"
#include "Pitch.h"
#include <vector>

namespace entropy
{
    struct InstrumentConfig
    {
        String ID;
        String Name;
        String Abbr;
        Pitch RangeLow;
        Pitch RangeHigh;
        Int ScoreGroup;
        Int LogicGroup;
    };
    
    using InstrumentConfigs = std::vector<InstrumentConfig>;
    
    class Config
    {
    public:
        Config();
        
        void setDuration( const Int value );
        void setTempo( const Int value );
        void setComposer( const String& value );
        void setTitle( const String& value );
        void setCopyright( const String& value );
        void setBeatsPerMeasure( const Int value );
        
        Int getDuration() const;
        Int getTempo() const;
        String getComposer() const;
        String getTitle() const;
        String getCopyright() const;
        Int getMeasureCount() const;
        Int getBeatsPerMeasure() const;
        void addInstrumentConfig( const InstrumentConfig& value );
        const InstrumentConfigs& getInstrumentConfigs() const;
        
    private:
        Int myDuration;
        Int myTempo;
        String myComposer;
        String myTitle;
        String myCopyright;
        Int myBeatsPerMeasure;
        InstrumentConfigs myInstrumentConfigs;
    };
    
    Config parseConfig( const String& filepath );
}