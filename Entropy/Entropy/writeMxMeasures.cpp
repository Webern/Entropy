#include "writeMxMeasures.h"

namespace entropy
{
    void writeMxMeasures( const mx::d::DocumentPartwisePtr& doc, const InstrumentListPtr& instrumentList )
    {
        auto scoreGrpsBeg = instrumentList->getScoreGroups().begin();
        auto scoreGrpsEnd = instrumentList->getScoreGroups().end();
        auto scoreGrpsItr = scoreGrpsBeg;
        for ( ; scoreGrpsItr != scoreGrpsEnd; ++scoreGrpsItr )
        {
            auto beg = (*scoreGrpsItr)->getInstruments().begin();
            auto end = (*scoreGrpsItr)->getInstruments().end();
            auto itr = beg;
            for (; itr != end; ++itr )
            {
                Int m = 1;
                for ( auto measure = (*itr)->getMeasuresBegin(); measure != (*itr)->getMeasuresEnd(); ++measure )
                {
                    auto currentInstrument = *itr;
                    auto mxmeasure = getMeasure( doc, currentInstrument->getID(), m );
                    fillMxMeasure( mxmeasure, *measure );
                    ++m;
                }
            }
        }
    }
}