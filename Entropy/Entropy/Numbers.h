#pragma once
#include <iostream>
#include "typedefs.h"

namespace entropy
{
    class Numbers
    {
    public:
        Numbers( const Int columns );
        ~Numbers() = default;
        Numbers& operator=( const Numbers& other ) = default;
        void addRow();
        void removeRow( const Int row_number );
        void setValue( const Int row_number, const Int column_number, const Float value );
        Float getValue( const Int row_number, const Int column_number ) const;
        Int getValueInt( const Int row_number, const Int column_number ) const;
        Int getColumnCount() const;
        Int getRowCount() const;
        
        TableIter begin();
        TableIterConst cbegin() const;
        TableIter end();
        TableIterConst cend() const;
        
        TableIter findRow( const Int row_number );
        TableIterConst findRowConst( const Int row_number ) const;
        RowIterCost findFieldConst( const Int row_number, const Int column_number ) const;
        RowIter findField( const Int row_number, const Int column_number );
        static Numbers parse( const String filepath );
        Float findMinimum() const;
        Float findMaximum() const;
        Numbers scale( Int newRowCount ) const;
    private:
        Int myColumns;
        Table myTable; 
    };
}