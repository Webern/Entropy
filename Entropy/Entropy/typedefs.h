#pragma once
#include <iostream>
#include <string>
#include <vector>

namespace entropy
{
    using Float = double;
    using Int = int;
    using String = std::string;
    
    using Row = std::vector<Float>;
    using RowIter = Row::iterator;
    using RowIterCost = Row::const_iterator;
    
    using Table = std::vector<Row>;
    using TableIter = Table::iterator;
    using TableIterConst = Table::const_iterator;
    
    using StringRow = std::vector<String>;
    using StringTable = std::vector<StringRow>;
}