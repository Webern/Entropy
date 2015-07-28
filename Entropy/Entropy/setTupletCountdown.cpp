#include "setTupletCountdown.h"

namespace entropy
{
    void setTupletCountdown( const Tup tup_in, Int& countdown_out )
    {
        switch ( tup_in )
        {
            case Tup::Triplet:
                countdown_out = 2;
                break;
            case Tup::Quintuplet:
                countdown_out = 4;
                break;
            case Tup::Sextuplet:
                countdown_out = 5;
                break;
            default:
                break;
        }
    }
}