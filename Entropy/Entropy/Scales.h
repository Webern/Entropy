#pragma once
#include <iostream>
#include <vector>
#include "typedefs.h"
#include "Scale.h"

namespace entropy
{
    using Scales = std::vector<Scale>;
    using ScalesIter = Scales::iterator;
    using ScalesIterConst = Scales::const_iterator;
    
    Scales parseScales( const String& filepath );
}