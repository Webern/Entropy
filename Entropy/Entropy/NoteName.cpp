#include "NoteName.h"

namespace entropy
{
    NoteName::NoteName( const mx::t::StepEnum step, const Int alter )
    :myStep( step )
    ,myAlter( alter )
    {
        setAlter( alter );
    }
    NoteName::NoteName()
    :myStep( mx::t::StepEnum::c )
    ,myAlter( 0 )
    {}
    NoteName::NoteName( const String& name )
    :myStep( mx::t::StepEnum::c )
    ,myAlter( 0 )
    {
        parse( name );
    }
    void NoteName::setAlter( const Int value )
    {
        if ( value < -2 || value > 2 )
        {
            throw new std::runtime_error( "Alter value must be between -2 and 2" );
        }
        else
        {
            myAlter = value;
        }
    }
    void NoteName::setStep( const mx::t::StepEnum value )
    {
        myStep = value;
    }
    Int NoteName::getAlter() const
    {
        return myAlter;
    }
    Step NoteName::getStep() const
    {
        return myStep;
    }
    void NoteName::parse( const String& value )
    {
        auto len = value.length();
        mx::t::StepEnum step{ mx::t::StepEnum::c };
        Int alter = 0;
        if ( len < 1 || len > 3 )
        {
            throw std::runtime_error( "Error parsing note name" );
        }
        else
        {
            auto c = value.begin();
            switch ( *c )
            {
                case 'A':
                    step = mx::t::StepEnum::a;
                    break;
                case 'B':
                    step = mx::t::StepEnum::b;
                    break;
                case 'C':
                    step = mx::t::StepEnum::c;
                    break;
                case 'D':
                    step = mx::t::StepEnum::d;
                    break;
                case 'E':
                    step = mx::t::StepEnum::e;
                    break;
                case 'F':
                    step = mx::t::StepEnum::f;
                    break;
                case 'G':
                    step = mx::t::StepEnum::g;
                    break;
                default:
                    throw std::runtime_error( "Error parsing note name" );
                    break;
            }
            ++c;
            if ( c != value.end() )
            {
                switch ( *c )
                {
                    case 'b':
                    {
                        alter = -1;
                        ++c;
                        if ( c != value.end() )
                        {
                            if ( *c == 'b' )
                            {
                                alter = -2;
                            }
                            else
                            {
                                throw std::runtime_error( "Error parsing note name" );
                            }
                        }
                        break;
                    }
                    case '#':
                    {
                        alter = 1;
                        if ( len != 2 )
                        {
                            throw std::runtime_error( "Error parsing note name" );
                        }
                    }
                        break;
                    case 'x':
                    {
                        alter = 2;
                        if ( len != 2 )
                        {
                            throw std::runtime_error( "Error parsing note name" );
                        }
                    }
                        break;
                    default:
                        throw std::runtime_error( "Error parsing note name" );
                        break;
                }
            }
        }
        myStep = step;
        myAlter = alter;
    }
    String NoteName::toString() const
    {
        String output;
        switch ( myStep )
        {
            case mx::t::StepEnum::a:
                output = "A";
                break;
            case mx::t::StepEnum::b:
                output = "B";
                break;
            case mx::t::StepEnum::c:
                output = "C";
                break;
            case mx::t::StepEnum::d:
                output = "D";
                break;
            case mx::t::StepEnum::e:
                output = "E";
                break;
            case mx::t::StepEnum::f:
                output = "F";
                break;
            case mx::t::StepEnum::g:
                output = "G";
                break;
            default:
                throw std::runtime_error( "Funky internal error." );
                break;
        }
        switch ( myAlter )
        {
            case -2:
                output += "bb";
                break;
            case -1:
                output += "b";
                break;
            case 0:
                ;
                break;
            case 1:
                output += "#";
                break;
            case 2:
                output += "x";
                break;
            default:
                throw std::runtime_error( "Funky internal error." );
                break;
        }
        return output;
    }
    Int NoteName::getPitchClass() const
    {
        Int step = 0;
        switch ( myStep )
        {
            case mx::t::StepEnum::a:
                step = 9;
                break;
            case mx::t::StepEnum::b:
                step = 11;
                break;
            case mx::t::StepEnum::c:
                step = 0;
                break;
            case mx::t::StepEnum::d:
                step = 2;
                break;
            case mx::t::StepEnum::e:
                step = 4;
                break;
            case mx::t::StepEnum::f:
                step = 5;
                break;
            case mx::t::StepEnum::g:
                step = 7;
                break;
            default:
                throw std::runtime_error( "Funky internal error." );
                break;
        }
        Int pitchClass = step + myAlter;
        if ( pitchClass < 0 )
        {
            pitchClass += 12;
        }
        else if ( pitchClass >= 12 )
        {
            pitchClass %= 12;
        }
        return pitchClass;
    }
    void NoteName::setPitchClass( const Int pitchClass )
    {
        if ( pitchClass < 0 || pitchClass > 11 )
        {
            throw std::out_of_range( "pitch class must be between 0 and 11" );
        }
        switch ( pitchClass )
        {
            case 0:
            {
                myStep = convert( mx::t::StepEnum::c );
                myAlter = 0;
            }
                break;
            case 1:
            {
                myStep = convert( mx::t::StepEnum::c );
                myAlter = 1;
            }
                break;
            case 2:
            {
                myStep = convert( mx::t::StepEnum::d );
                myAlter = 0;
            }
                break;
            case 3:
            {
                myStep = convert( mx::t::StepEnum::e );
                myAlter = -1;
            }
                break;
            case 4:
            {
                myStep = convert( mx::t::StepEnum::e );
                myAlter = 0;
            }
                break;
            case 5:
            {
                myStep = convert( mx::t::StepEnum::f );
                myAlter = 0;
            }
                break;
            case 6:
            {
                myStep = convert( mx::t::StepEnum::f );
                myAlter = 1;
            }
                break;
            case 7:
            {
                myStep = convert( mx::t::StepEnum::g );
                myAlter = 0;
            }
                break;
            case 8:
            {
                myStep = convert( mx::t::StepEnum::a );
                myAlter = -1;
            }
                break;
            case 9:
            {
                myStep = convert( mx::t::StepEnum::a );
                myAlter = 0;
            }
                break;
            case 10:
            {
                myStep = convert( mx::t::StepEnum::b );
                myAlter = -1;
            }
                break;
            case 11:
            {
                myStep = convert( mx::t::StepEnum::b );
                myAlter = 0;
            }
                break;  
            default:
                throw std::out_of_range( "pitch class must be between 0 and 11" );
                break;
        }
    }
    bool operator==( const NoteName& l, const NoteName& r )
    {
        return l.getPitchClass() == r.getPitchClass();
    }
    bool operator!=( const NoteName& l, const NoteName& r )
    {
        return ! ( l == r );
    }
    bool operator>( const NoteName& l, const NoteName& r )
    {
        return r < l;
    }
    bool operator<( const NoteName& l, const NoteName& r )
    {
        return l.getPitchClass() < r.getPitchClass();
    }
    
    bool operator>=( const NoteName& l, const NoteName& r )
    {
        return ( l > r ) || ( l == r );
    }
    bool operator<=( const NoteName& l, const NoteName& r )
    {
        return ( l < r ) || ( l == r );
    }
    Step convert( const Step value )
    {
        return value;
    }
}