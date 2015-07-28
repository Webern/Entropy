#pragma once
#include "typedefs.h"
#include "Duration.h"
#include "RhythmList.h"
#include "Measure.h"
#include "Rand.h"

namespace entropy
{
    // currDur = setDuration( prevDur, rythrand, rythlist, newMeasure, safetyValve );
    Duration setDuration( Duration& prevDur, const Rand& rhythrand, const RhythmList& rhythmList, const Measure& newMeasure, Int& tupletCountdown, bool& safetyTripped );
}