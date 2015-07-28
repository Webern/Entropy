#pragma once
#include "typedefs.h"
#include "InstrumentList.h"
#include "Mx/DocumentPartwise.h"
#include "MxMeasure.h"

namespace entropy
{
    void writeMxMeasures( const mx::d::DocumentPartwisePtr& doc, const InstrumentListPtr& instrumentList );
}