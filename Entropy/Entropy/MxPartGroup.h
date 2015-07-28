#pragma once
#include "typedefs.h"
#include "Mx/Elements.h"

namespace entropy
{
    mx::e::PartGroupPtr makePartGroupStart( int ID );
    mx::e::PartGroupPtr makePartGroupStop( int ID );
    mx::e::PartGroupOrScorePartPtr makePartGroupStart( int ID, bool dummy );
    mx::e::PartGroupOrScorePartPtr makePartGroupStop( int ID, bool dummy );
    mx::e::PartGroupOrScorePartPtr convertPartGroup( const mx::e::PartGroupPtr& partGroup );
    void addPartGroupStartToPartList( const mx::e::PartListPtr& partList, Int ID, bool isBeforeFirstInstrument );
    
}