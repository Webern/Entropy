#pragma once
#include "defaults.h"
#include "typedefs.h"

namespace entropy
{
    inline bool args(int argc, const char * argv[], String& fpInput, String& fpConfig, String& fpScales)
    {
        if ( ( argc != 1 ) && ( argc != 4 ) )
        {
            std::cout << errorMessageImproperMain() << std::endl;
            return false;
        }
        else if ( argc == 4 )
        {
            fpInput = argv[1];
            fpConfig = argv[2];
            fpScales = argv[3];
            return true;
        }
        else if ( argc == 1 )
        {
            fpInput = inputFilePath();
            fpConfig = configFilePath();
            fpScales = scalesFilePath();
            return true;
        }
        return false;
    }
}