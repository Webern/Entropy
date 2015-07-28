#pragma once
#include "typedefs.h"

namespace entropy
{
    inline Int skipSize( const Int entropyValue )
    {
        Rand r{ 0, 4 };
        switch ( entropyValue )
        {
            case 0:
                r = Rand{ 0, 1 };
                break;
            case 1:
                r = Rand{ 0, 1 };
                break;
            case 2:
                r = Rand{ 0, 1 };
                break;
            case 3:
                r = Rand{ 0, 2 };
                break;
            case 4:
                r = Rand{ 0, 2 };
                break;
            case 5:
                r = Rand{ 0, 2 };
                break;
            case 6:
                r = Rand{ 0, 2 };
                break;
            case 7:
                r = Rand{ 0, 3 };
                break;
            case 8:
                r = Rand{ 0, 3 };
                break;
            case 9:
                r = Rand{ 0, 4 };
                break;
            case 10:
                r = Rand{ 0, 4 };
                break;
            case 11:
                r = Rand{ 0, 5 };
                break;
            case 12:
                r = Rand{ 0, 6 };
                break;
            default:
                r = Rand{ 0, 7 };
                break;
        }
        return r.get();
    }
}