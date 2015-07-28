#include "Duration.h"

namespace entropy
{
    const DurationStrings DurationStringsLookup = {
        { "Sixteenth", Duration{ Dur::Sixteenth } },
        { "Eighth", Duration{ Dur::Eighth } },
        { "Quarter", Duration{ Dur::Quarter } },
        { "Half", Duration{ Dur::Half } },
        { "Whole", Duration{ Dur::Whole } },
        // { "Sixteenth.", Duration{ Dur::Sixteenth, 1 } },
        { "Eighth.", Duration{ Dur::Eighth, 1 } },
        { "Quarter.", Duration{ Dur::Quarter, 1 } },
        { "Half.", Duration{ Dur::Half, 1 } },
        { "Whole.", Duration{ Dur::Whole, 1 } },
        // { "Sixteenth..", Duration{ Dur::Sixteenth, 2 } },
        // { "Eighth..", Duration{ Dur::Eighth, 2 } },
        { "Quarter..", Duration{ Dur::Quarter, 2 } },
        { "Half..", Duration{ Dur::Half, 2 } },
        { "Whole..", Duration{ Dur::Whole, 2 } },
        { "TripletSixteenth", Duration{ Dur::Sixteenth, Tup::Triplet } },
        { "TripletEighth", Duration{ Dur::Eighth, Tup::Triplet } },
        { "TripletQuarter", Duration{ Dur::Quarter, Tup::Triplet } },
        { "TripletHalf", Duration{ Dur::Half, Tup::Triplet } },
        { "TripletWhole", Duration{ Dur::Whole, Tup::Triplet } },
        { "QuintupletSixteenth", Duration{ Dur::Sixteenth, Tup::Quintuplet } },
        { "QuintupletEighth", Duration{ Dur::Eighth, Tup::Quintuplet } },
        { "QuintupletQuarter", Duration{ Dur::Quarter, Tup::Quintuplet } },
        { "QuintupletHalf", Duration{ Dur::Half, Tup::Quintuplet } },
        { "QuintupletWhole", Duration{ Dur::Whole, Tup::Quintuplet } },
        { "SextupletSixteenth", Duration{ Dur::Sixteenth, Tup::Sextuplet } },
        { "SextupletEighth", Duration{ Dur::Eighth, Tup::Sextuplet } },
        { "SextupletQuarter", Duration{ Dur::Quarter, Tup::Sextuplet } },
        { "SextupletHalf", Duration{ Dur::Half, Tup::Sextuplet } },
        { "SextupletWhole", Duration{ Dur::Whole, Tup::Sextuplet } },
    };
    
    Duration::Duration()
    :myDur( Dur::Quarter )
    ,myTup( Tup::Simple )
    ,myDots( 0 )
    ,myDivisions( DIVISIONS )
    {}
    
    Duration::Duration( const Dur dur )
    :myDur( dur )
    ,myTup( Tup::Simple )
    ,myDots( 0 )
    ,myDivisions( DIVISIONS )
    {}
    
    Duration::Duration( const Dur dur, const Tup tup )
    :myDur( dur )
    ,myTup( tup )
    ,myDots( 0 )
    ,myDivisions( DIVISIONS )
    {}
    
    Duration::Duration( const Dur dur, const Int dots )
    :myDur( dur )
    ,myTup( Tup::Simple )
    ,myDots( dots )
    ,myDivisions( DIVISIONS )
    { setDots( dots ); }
    
    Duration::Duration( const Dur dur, const Int dots, const Tup tup )
    :myDur( dur )
    ,myTup( tup )
    ,myDots( dots )
    ,myDivisions( DIVISIONS )
    { setDots( dots ); }
    
    /* get / set */
    Dur Duration::getDur() const
    {
        return myDur;
    }
    
    Tup Duration::getTup() const
    {
        return myTup;
    }
    
    Int Duration::getDots() const
    {
        return myDots;
    }
    
    Int Duration::getQuarterDivisions() const
    {
        return myDivisions;
    }
    
    void Duration::setDur( const Dur value )
    {
        myDur = value;
    }
    
    void Duration::setTup( const Tup value )
    {
        myTup = value;
    }
    
    void Duration::setDots( const Int value )
    {
        myDots = value;
    }
    
    void Duration::setQuarterDivisions( const Int value )
    {
        if ( value >= 0 && value <= 2 )
        {
            myDivisions = value;
        }
        else
        {
            throw std::out_of_range( "dots value must by 0, 1 or 2" );
        }
    }
    
    
    /* calculations */
    Int Duration::getDivisions() const
    {
        Int value = myDivisions;
        switch ( myDur )
        {
            case Dur::Sixteenth:
            {
                value /= 4;
            }
                break;
            case Dur::Eighth:
            {
                value /= 2;
            }
                break;
            case Dur::Quarter:
            {
                ;
            }
                break;
            case Dur::Half:
            {
                value *= 2;
            }
                break;
            case Dur::Whole:
            {
                value *= 4;
            }
                break;
            default:
                break;
        }
        switch ( myTup )
        {
            case Tup::Simple:
            {
                ;
            }
                break;
            case Tup::Triplet:
            {
                value = ( value * 2 ) / 3;
            }
                break;
            case Tup::Quintuplet:
            {
                value = ( value * 4 ) / 5;
            }
                break;
            case Tup::Sextuplet:
            {
                value = ( value * 4 ) / 6;
            }
                break;
            default:
                break;
        }
        switch ( myDots )
        {
            case 0:
            {
                ;
            }
                break;
            case 1:
            {
                value += ( value / 2 );
            }
                break;
            case 2:
            {
                value += ( ( value / 2 ) + ( value / 4 ) );
            }
                break;
            default:
            {
                throw std::out_of_range( "dots value must by 0, 1 or 2" );
            }
                break;
        }
        return value;
    }
    
    bool operator==( const Duration& l, const Duration& r )
    {
        return ( l.getDur() == r.getDur() ) &&
        ( l.getTup() == r.getTup() ) &&
        ( l.getDots() == r.getDots() );
    }
    
    String Duration::toString() const
    {
        String value{ "string not found" };
        auto iter = std::find_if(
                                 DurationStringLookup.cbegin(),
                                 DurationStringLookup.cend(),
                                 [this](const DurationString& inside){
                                     return (*this) == inside.duration;
                                 } );
        if( iter != DurationStringLookup.cend() )
        {
            value = iter->name;
        }
        return value;
    }
    bool operator==( const DurationString& l, const DurationString& r )
    {
        return l.name == r.name;
    }
    bool operator!=( const DurationString& l, const DurationString& r )
    {
        return l.name != r.name;
    }
    bool operator<( const DurationString& l, const DurationString& r )
    {
        return l.name < r.name;
    }
    bool operator>( const DurationString& l, const DurationString& r )
    {
        return l.name > r.name;
    }
    bool operator<=( const DurationString& l, const DurationString& r )
    {
        return l.name <= r.name;
    }
    bool operator>=( const DurationString& l, const DurationString& r )
    {
        return l.name >= r.name;
    }
    
    Duration parseDuration( const String& value )
    {
        auto iter = std::find_if(
            DurationStringLookup.cbegin(),
            DurationStringLookup.cend(),
            [&value](const DurationString& inside){ return value == inside.name; } );
        if( iter == DurationStringLookup.cend() )
        {
            throw std::runtime_error( "unparseable duration string" );
        }
        return iter->duration;
    }
    Int Duration::getDivisionsToCompleteTuplet() const
    {
        switch ( myTup )
        {
            case Tup::Simple:
                return 0;
                break;
            case Tup::Triplet:
                return 3 * getDivisions();
                break;
            case Tup::Quintuplet:
                return 5 * getDivisions();
                break;
            case Tup::Sextuplet:
                return 6 * getDivisions();
                break;
            default:
                break;
        }
    }
}