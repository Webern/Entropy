#include "rest.h"

namespace entropy
{
    bool rest( const Int entrpy, const Rand& rand0to12 )
    {
        Int r = rand0to12.get();
        switch ( entrpy )
        {
            case 0:
                return r > 10;
                break;
            case 1:
                return r > 10;
                break;
            case 2:
                return r > 10;
                break;
            case 3:
                return r > 9;
                break;
            case 4:
                return r > 9;
                break;
            case 5:
                return r > 8;
                break;
            case 6:
                return r > 8;
                break;
            case 7:
                return r > 8;
                break;
            case 8:
                return r > 7;
                break;
            case 9:
                return r > 7;
                break;
            case 10:
                return r > 6;
                break;
            case 11:
                return r > 6;
                break;
            case 12:
                return r > 5;
                break;
            default:
                break;
        }
        return false;
    }
}