#pragma once
#include "typedefs.h"
#include "Duration.h"
#include "Measure.h"

namespace entropy
{
    bool isDurationOk( const Duration& duration, const Measure& measure );
}