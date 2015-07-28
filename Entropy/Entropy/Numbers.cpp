#include "Numbers.h"
#include <string>
#include <fstream>
#include <sstream>
#include "parse.h"
#include <cmath>

namespace entropy
{
    Numbers::Numbers( const Int columns )
    :myColumns( columns )
    {}
    void Numbers::addRow()
    {
        Row r;
        for ( int i=0; i<myColumns; ++i)
        {
            r.push_back( 0 );
        }
        myTable.push_back( r );
    }
    void Numbers::removeRow( const Int row_number )
    {
        myTable.erase( findRow( row_number ) );
    }
    void Numbers::setValue( const Int row_number, const Int column_number, const Float value )
    {
        auto field = findField( row_number, column_number );
        *field = value;
    }
    Float Numbers::getValue( const Int row_number, const Int column_number ) const
    {
        auto field = findFieldConst( row_number, column_number );
        return *field;
    }
    Int Numbers::getValueInt( const Int row_number, const Int column_number ) const
    {
        auto fVal = getValue( row_number, column_number );
        return (Int)std::round( fVal );
    }
    Int Numbers::getColumnCount() const
    {
        return myColumns;
    }
    Int Numbers::getRowCount() const
    {
        return (Int) myTable.size();
    }
    
    TableIter Numbers::begin()
    {
        return myTable.begin();
    }
    TableIterConst Numbers::cbegin() const
    {
        return myTable.cbegin();
    }
    TableIter Numbers::end()
    {
        return myTable.end();
    }
    TableIterConst Numbers::cend() const
    {
        return myTable.cend();
    }
    
    
    TableIterConst Numbers::findRowConst( const Int row_number ) const
    {
        TableIterConst row;
        if ( row_number < 0 || row_number > myTable.size() - 1 )
        {
            throw new std::out_of_range( "entropy::Numbers::findRow - bad index" );
        }
        else
        {
            row = myTable.begin();
            for ( int i=0;
                  i < row_number && ( row != myTable.end() );
                  ++i, ++row )
            { ; }
        }
        return row;
    }
    RowIterCost Numbers::findFieldConst( const Int row_number, const Int column_number ) const
    {
        RowIterCost field;
        if ( column_number < 0 || column_number > myColumns - 1 )
        {
            throw new std::out_of_range( "entropy::Numbers::findFieldConst - bad index" );
        }
        else
        {
            auto row = findRowConst( row_number );
            field = row->begin();
            for ( int i=0;
                 i < column_number && ( field != row->end() );
                 ++i, ++field )
            { ; }
        }
        return field;
    }
    TableIter Numbers::findRow( const Int row_number )
    {
        TableIterConst crow = findRowConst( row_number );
        return myTable.erase( crow, crow );
    }
    RowIter Numbers::findField( const Int row_number, const Int column_number )
    {
        RowIter field;
        if ( column_number < 0 || column_number > myColumns - 1 )
        {
            throw new std::out_of_range( "entropy::Numbers::findField - bad index" );
        }
        else
        {
            auto row = findRow( row_number );
            field = row->begin();
            for ( int i=0;
                 i < column_number && ( field != row->end() );
                 ++i, ++field )
            { ; }
        }
        return field;
    }
    Numbers Numbers::parse( const String filepath )
    {
        
        Int columns{ 0 };
        String line;
        std::ifstream file( filepath );
        if ( file.is_open() )
        {
            while ( getline( file, line ) )
            {
                Int commaCount{ 1 };
                for ( auto c = line.begin(); c != line.end(); ++c )
                {
                    if ( *c == ',' )
                    {
                        ++commaCount;
                    }
                }
                if ( commaCount > columns )
                {
                    columns = commaCount;
                }
            }
            file.close();
            file = std::ifstream{ filepath };
            if ( file.is_open() )
            {
                line = "";
                String validChars{ "-.0123456789" };
                std::stringstream accumulate;
                Int currentColum{ 0 };
                Int currentRow{ 0 };
                Numbers OUTPUT( columns );
                
                while ( getline( file, line ) )
                {
                    OUTPUT.addRow();
                    auto c = line.cbegin();
                    while ( c != line.cend() )
                    {
                        Float currentValue{ 0 };
                        currentValue = getNextFloat( c, line.end() );
                        OUTPUT.setValue( currentRow, currentColum, currentValue );
                        ++currentColum;
                    }
                    currentColum = 0;
                    ++currentRow;
                }
                return OUTPUT;
            }
            else
            {
                throw std::runtime_error("Error opening file." );
            }
        }
        else
        {
            throw std::runtime_error("Error opening file." );
        }
    }
    Float Numbers::findMinimum() const
    {
        Float val = 0;
        if ( getRowCount() > 0 )
        {
            if ( getColumnCount() > 0 )
            {
                val = getValue( 0, 0);
            }
        }
        for ( int row = 0; row < getRowCount(); ++row )
        {
            for ( int field = 0; field < getColumnCount(); ++field )
            {
                Int currVal = getValue( row, field );
                if ( currVal < val )
                {
                    val = currVal;
                }
            }
        }
        return val;
    }
    Float Numbers::findMaximum() const
    {
        Float val = 0;
        if ( getRowCount() > 0 )
        {
            if ( getColumnCount() > 0 )
            {
                val = getValue( 0, 0);
            }
        }
        for ( int row = 0; row < getRowCount(); ++row )
        {
            for ( int field = 0; field < getColumnCount(); ++field )
            {
                Int currVal = getValue( row, field );
                if ( currVal > val )
                {
                    val = currVal;
                }
            }
        }
        return val;
    }
    Numbers Numbers::scale( Int newRowCount ) const
    {
        Numbers out{ getColumnCount() };
        if ( getRowCount() == 0 || newRowCount <= 0 )
        {
            return out;
        }
        Float scaleFact = ((Float)getRowCount()) / ((Float)newRowCount);
        Int scaleFactInt = (Int)std::round( scaleFact );
        if ( scaleFact < 0 )
        {
            return out;
        }
        for ( Int row = 0; row < getRowCount(); ++row )
        {
            Int scaledRow = (Int)(row/scaleFact);
            for ( Int column = 0; column < getColumnCount(); ++column )
            {
                Float accumulate = 0;
                Float divideby = 0;
                for ( Int i = row-scaleFactInt; i <= row; ++i )
                {
                    if ( i >=0 )
                    {
                        accumulate += getValue( i, column );
                        divideby += 1;
                    }
                }
                if ( divideby > 0.9 )
                {
                    while ( out.getRowCount() < scaledRow+1 )
                    {
                        out.addRow();
                    }
                    out.setValue( scaledRow, column, accumulate/divideby );
                }
            }
        }
        return out;
    }
}