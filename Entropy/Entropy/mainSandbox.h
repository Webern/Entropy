#pragma once
#include "typedefs.h"
#include "Mx/DocumentPartwise.h"
#include "Config.h"
#include "Numbers.h"
#include "Scales.h"
#include "InstrumentList.h"

namespace entropy
{
    void mainSandbox( const mx::d::DocumentPartwisePtr& doc, const Config& conf, const Numbers& quanta, const Scales& scales, const InstrumentListPtr& instrumentList  );
}