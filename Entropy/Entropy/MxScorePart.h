#pragma once
#include "typedefs.h"
#include "Mx/Elements.h"
#include "MxScorePartParameters.h"
#include "Instrument.h"

namespace entropy
{
    
    class MxScorePart
    {
    public:
        MxScorePart( const MxScorePartParameters& params );
        MxScorePart();
        MxScorePartParameters getParameters() const;
        void setParameters( const MxScorePartParameters& params );
        mx::e::ScorePartPtr makeScorePart() const;
        mx::e::PartGroupOrScorePartPtr makePartGroupOrScorePart() const;
    private:
        MxScorePartParameters myParams;
    };
    void addScorePartToPartList( const mx::e::PartListPtr& partList, const Instrument& instrument, bool isFirstInstrument );
}