#pragma once
#include "typedefs.h"
#include "Numbers.h"

namespace entropy
{
    inline Numbers equanta( const Numbers& input, const Int measureCount )
    {
        Numbers temp = input.scale( measureCount );
        Numbers equanta{ temp.getColumnCount() };
        Quantizer q{ temp.findMinimum(), temp.findMaximum(), 13 };
        for ( Int row = 0; row < temp.getRowCount(); ++row )
        {
            equanta.addRow();
            for ( Int column = 0; column < temp.getColumnCount(); ++column )
            {
                equanta.setValue( row, column, q.getQuantumState( temp.getValue( row, column ) ) );
            }
        }
    return std::move( equanta );
    }
}