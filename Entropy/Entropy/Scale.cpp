#include "Scale.h"
#include "parse.h"

namespace entropy
{
    Scale::Scale()
    :myNotes()
    ,myCurrent( 0 )
    {}
    Int Scale::size() const
    {
        return (Int)myNotes.size();
    }
    void Scale::addNoteName( const NoteName& value )
    {
        if ( std::find( myNotes.begin(), myNotes.end(), value ) != myNotes.end() )
        {
            throw new std::runtime_error( "Attempted to create a scale with duplicate enharmonic notes." );
        }
        myNotes.push_back( value );
    }
    void Scale::removeNoteName( const NoteName& value )
    {
        auto rem = std::find( myNotes.begin(), myNotes.end(), value );
        if ( rem == myNotes.end() )
        {
            throw new std::runtime_error( "Attempted to remove a note that is not in the scale." );
        }
        myNotes.erase( rem );
        if ( myCurrent > size()-1 )
        {
            setCurrent( size()-1 );
        }
    }
    NoteName Scale::getNoteName( const Int whichNote ) const
    {
        if ( whichNote < 0 || whichNote > size() - 1 )
        {
            throw std::out_of_range( "index out of range" );
        }
        auto iter = myNotes.cbegin();
        for ( Int i = 0;
             ( iter != myNotes.cend() ) && ( i < whichNote );
             ++i, ++iter)
        { ; }
        return *iter;
    }
    NoteName Scale::getCurrent() const
    {
        return getNoteName( myCurrent );
    }
    void Scale::setCurrent( const Int value )
    {
        if ( value < 0 || value > size()-1 )
        {
            throw std::out_of_range( "index out of range" );
        }
        myCurrent = value;
    }
    Scale& Scale::increment()
    {
        if ( myCurrent == size() - 1 )
        {
            myCurrent = 0;
        }
        else
        {
            ++myCurrent;
        }
        return *this;
    }
    Scale& Scale::decrement()
    {
        if ( myCurrent == 0 )
        {
            myCurrent = size()-1;
        }
        else
        {
            --myCurrent;
        }
        return *this;
    }
    Scale& Scale::increment( const Int scaleDegrees )
    {
        if ( scaleDegrees > 0 )
        {
            for ( Int i = 0; i < scaleDegrees; ++i )
            {
                increment();
            }
        }
        else if ( scaleDegrees < 0 )
        {
            for ( Int i = scaleDegrees; i < 0; ++i )
            {
                decrement();
            }
        }
        return *this;
    }
    void Scale::parse( const String& str )
    {
        myNotes.clear();
        auto c = str.cbegin();
        auto e = str.cend();
        String note;
        String valid = "ABCDEFGAbx#";
        char delim = ',';
        while ( c != e )
        {
            note = readToNextDelim( c, e, delim, valid );
            NoteName newNoteName( note );
            addNoteName( note );
        }
        
    }
    String Scale::toString() const
    {
        std::stringstream ss;
        for ( auto n = myNotes.cbegin(); n != myNotes.cend(); ++n )
        {
            if ( n != myNotes.cbegin() )
            {
                ss << ",";
            }
            ss << n->toString();
        }
        return ss.str();
    }
    Int Scale::findScaleDegree( const NoteName& notename ) const
    {
        auto beg = myNotes.cbegin();
        auto end = myNotes.cend();
        auto itr = beg;
        for (; itr != end; ++itr )
        {
            if ( itr->getPitchClass() == notename.getPitchClass() )
            {
                return (Int)std::distance( beg, itr );
            }
        }
        for ( Int semitones = 1; semitones < 12; ++semitones )
        {
            for (itr = beg; itr != end; ++itr )
            {
                if ( std::abs( itr->getPitchClass() - notename.getPitchClass() ) < semitones )
                {
                    return (Int)std::distance( beg, itr );
                }
            }
        }
        return 0;
    }
    Int Scale::getCurrentScaleDegree() const
    {
        return myCurrent;
    }
}