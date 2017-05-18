// Copyright (c) Matthew James Briggs

#pragma once

#include <string>
#include <map>

#include "EnumMacros.h"

#include "mx/api/ScoreData.h"

namespace entropy
{
    enum class ClefName
    {
        TREBLE,
        ALTO,
        TENOR,
        BASS,
    };

    ENUM_TOSTR_BEGIN( ClefName )
    ENUM_TOSTR_VALUE( ClefName, TREBLE )
    ENUM_TOSTR_VALUE( ClefName, ALTO )
    ENUM_TOSTR_VALUE( ClefName, TENOR )
    ENUM_TOSTR_VALUE( ClefName, BASS )
    ENUM_TOSTR_END;

    ENUM_PARSE_BEGIN( ClefName )
    ENUM_PARSE_VALUE( ClefName, TREBLE )
    ENUM_PARSE_VALUE( ClefName, ALTO )
    ENUM_PARSE_VALUE( ClefName, TENOR )
    ENUM_PARSE_VALUE( ClefName, BASS )
    ENUM_PARSE_END;

    enum class InstrumentTypeID
    {
        VIOLIN,
        VIOLA,
        CELLO,
        DOUBLE_BASS,
    };

    ENUM_TOSTR_BEGIN( InstrumentTypeID )
    ENUM_TOSTR_VALUE( InstrumentTypeID, VIOLIN )
    ENUM_TOSTR_VALUE( InstrumentTypeID, VIOLA )
    ENUM_TOSTR_VALUE( InstrumentTypeID, CELLO )
    ENUM_TOSTR_VALUE( InstrumentTypeID, DOUBLE_BASS )
    ENUM_TOSTR_END;

    ENUM_PARSE_BEGIN( InstrumentTypeID )
    ENUM_PARSE_VALUE( InstrumentTypeID, VIOLIN )
    ENUM_PARSE_VALUE( InstrumentTypeID, VIOLA )
    ENUM_PARSE_VALUE( InstrumentTypeID, CELLO )
    ENUM_PARSE_VALUE( InstrumentTypeID, DOUBLE_BASS )
    ENUM_PARSE_END;

    enum class Step
    {
        C,
        D,
        E,
        F,
        G,
        A,
        B,
        ERROR,
    };

    inline Step convertStep( mx::api::Step inStep )
    {
        switch( inStep )
        {
            case mx::api::Step::c: return entropy::Step::C;
            case mx::api::Step::d: return entropy::Step::D;
            case mx::api::Step::e: return entropy::Step::E;
            case mx::api::Step::f: return entropy::Step::F;
            case mx::api::Step::g: return entropy::Step::G;
            case mx::api::Step::a: return entropy::Step::A;
            case mx::api::Step::b: return entropy::Step::B;
            default: return entropy::Step::ERROR;
        }
    }

    inline mx::api::Step convertStep( entropy::Step inStep )
    {
        switch( inStep )
        {
            case entropy::Step::C: return mx::api::Step::c;
            case entropy::Step::D: return mx::api::Step::d;
            case entropy::Step::E: return mx::api::Step::e;
            case entropy::Step::F: return mx::api::Step::f;
            case entropy::Step::G: return mx::api::Step::g;
            case entropy::Step::A: return mx::api::Step::a;
            case entropy::Step::B: return mx::api::Step::b;
            case entropy::Step::ERROR: return mx::api::Step::c;
            default: return mx::api::Step::c;
        }
    }

    ENUM_TOSTR_BEGIN( Step )
    ENUM_TOSTR_VALUE( Step, C )
    ENUM_TOSTR_VALUE( Step, D )
    ENUM_TOSTR_VALUE( Step, E )
    ENUM_TOSTR_VALUE( Step, F )
    ENUM_TOSTR_VALUE( Step, G )
    ENUM_TOSTR_VALUE( Step, A )
    ENUM_TOSTR_VALUE( Step, B )
    ENUM_TOSTR_END;

    ENUM_PARSE_BEGIN( Step )
    ENUM_PARSE_VALUE( Step, A )
    ENUM_PARSE_VALUE( Step, B )
    ENUM_PARSE_VALUE( Step, C )
    ENUM_PARSE_VALUE( Step, D )
    ENUM_PARSE_VALUE( Step, E )
    ENUM_PARSE_VALUE( Step, F )
    ENUM_PARSE_VALUE( Step, G )
    ENUM_PARSE_VALUE( Step, A )
    ENUM_PARSE_VALUE( Step, B )
    ENUM_PARSE_END;

    inline int intStep( Step inValue )
    {
        switch ( inValue )
        {
            case Step::C: return 0;
            case Step::D: return 2;
            case Step::E: return 4;
            case Step::F: return 5;
            case Step::G: return 7;
            case Step::A: return 9;
            case Step::B: return 11;
            default: return 0;
        }
    }

    inline Step intStep( int inValue )
    {
        switch ( inValue )
        {
            case 0: return Step::C;
            case 2: return Step::D;
            case 4: return Step::E;
            case 5: return Step::F;
            case 7: return Step::G;
            case 9: return Step::A;
            case 11: return Step::B;
            default: return Step::ERROR;
        }
    }

    enum class Alter
    {
        NATURAL,
        SHARP,
        FLAT,
        DOUBLE_SHARP,
        DOUBLE_FLAT,
        ERROR,
    };

    ENUM_TOSTR_BEGIN( Alter )
    ENUM_TOSTR_VALUE( Alter, NATURAL )
    ENUM_TOSTR_VALUE( Alter, SHARP )
    ENUM_TOSTR_VALUE( Alter, FLAT )
    ENUM_TOSTR_VALUE( Alter, DOUBLE_SHARP )
    ENUM_TOSTR_VALUE( Alter, DOUBLE_FLAT )
    ENUM_TOSTR_END;

    ENUM_PARSE_BEGIN( Alter )
    ENUM_PARSE_VALUE( Alter, NATURAL )
    ENUM_PARSE_VALUE( Alter, SHARP )
    ENUM_PARSE_VALUE( Alter, FLAT )
    ENUM_PARSE_VALUE( Alter, DOUBLE_SHARP )
    ENUM_PARSE_VALUE( Alter, DOUBLE_FLAT )
    ENUM_PARSE_END;

    inline int intAlter( Alter inValue )
    {
        switch ( inValue )
        {
            case Alter::NATURAL: return 0;
            case Alter::SHARP: return 1;
            case Alter::FLAT: return -1;
            case Alter::DOUBLE_SHARP: return 2;
            case Alter::DOUBLE_FLAT: return -2;
            default: return 0;
        }
    }

    inline Alter intAlter( int inValue )
    {
        switch ( inValue )
        {
            case 0: return Alter::NATURAL;
            case 1: return Alter::SHARP;
            case -1: return Alter::FLAT;
            case 2: return Alter::DOUBLE_SHARP;
            case -2: return Alter::DOUBLE_FLAT;
            default: return Alter::ERROR;
        }
    }

    inline mx::api::Accidental convertAlter( Alter inAlter )
    {
        switch( inAlter )
        {
            case entropy::Alter::NATURAL: return mx::api::Accidental::natural;
            case entropy::Alter::SHARP: return mx::api::Accidental::sharp;
            case entropy::Alter::FLAT: return mx::api::Accidental::flat;
            case entropy::Alter::DOUBLE_SHARP: return mx::api::Accidental::doubleSharp;
            case entropy::Alter::DOUBLE_FLAT: return mx::api::Accidental::flatFlat;
            case entropy::Alter::ERROR: return mx::api::Accidental::none;
            default: return mx::api::Accidental::none;
        }
    }

    enum class Spelling
    {
        Cn,    ///< C-natural
        Dn,    ///< D-natural
        En,    ///< E-natural
        Fn,    ///< F-natural
        Gn,    ///< G-natural
        An,    ///< A-natural
        Bn,    ///< B-natural
        Cs,    ///< C-sharp
        Ds,    ///< D-sharp
        Es,    ///< E-sharp
        Fs,    ///< F-sharp
        Gs,    ///< G-sharp
        As,    ///< A-sharp
        Bs,    ///< B-sharp
        Cb,    ///< C-flat
        Db,    ///< D-flat
        Eb,    ///< E-flat
        Fb,    ///< F-flat
        Gb,    ///< G-flat
        Ab,    ///< A-flat
        Bb,    ///< B-flat
        Cx,    ///< C-double-sharp
        Dx,    ///< D-double-sharp
        Ex,    ///< E-double-sharp
        Fx,    ///< F-double-sharp
        Gx,    ///< G-double-sharp
        Ax,    ///< A-double-sharp
        Bx,    ///< B-double-sharp
        Cd,    ///< C-double-flat
        Dd,    ///< D-double-flat
        Ed,    ///< E-double-flat
        Fd,    ///< F-double-flat
        Gd,    ///< G-double-flat
        Ad,    ///< A-double-flat
        Bd,    ///< B-double-flat
        ERROR, ///< Bad State
    };


    inline std::string stringSpelling( Spelling inValue )
    {
        switch ( inValue )
        {
            case Spelling::Cn: return "C";
            case Spelling::Dn: return "D";
            case Spelling::En: return "E";
            case Spelling::Fn: return "F";
            case Spelling::Gn: return "G";
            case Spelling::An: return "A";
            case Spelling::Bn: return "B";
            case Spelling::Cs: return "C#";
            case Spelling::Ds: return "D#";
            case Spelling::Es: return "E#";
            case Spelling::Fs: return "F#";
            case Spelling::Gs: return "G#";
            case Spelling::As: return "A#";
            case Spelling::Bs: return "B#";
            case Spelling::Cb: return "Cb";
            case Spelling::Db: return "Db";
            case Spelling::Eb: return "Eb";
            case Spelling::Fb: return "Fb";
            case Spelling::Gb: return "Gb";
            case Spelling::Ab: return "Ab";
            case Spelling::Bb: return "Bb";
            case Spelling::Cx: return "Cx";
            case Spelling::Dx: return "Dx";
            case Spelling::Ex: return "Ex";
            case Spelling::Fx: return "Fx";
            case Spelling::Gx: return "Gx";
            case Spelling::Ax: return "Ax";
            case Spelling::Bx: return "Bx";
            case Spelling::Cd: return "Cd";
            case Spelling::Dd: return "Dd";
            case Spelling::Ed: return "Ed";
            case Spelling::Fd: return "Fd";
            case Spelling::Gd: return "Gd";
            case Spelling::Ad: return "Ad";
            case Spelling::Bd: return "Bd";
            default: return "ERROR";
        }
    }


    inline Spelling stringSpelling( const std::string& inValue )
    {
        if ( inValue == "C" ) { return Spelling::Cn; }
        if ( inValue == "D" ) { return Spelling::Dn; }
        if ( inValue == "E" ) { return Spelling::En; }
        if ( inValue == "F" ) { return Spelling::Fn; }
        if ( inValue == "G" ) { return Spelling::Gn; }
        if ( inValue == "A" ) { return Spelling::An; }
        if ( inValue == "B" ) { return Spelling::Bn; }
        if ( inValue == "C" ) { return Spelling::Cs; }
        if ( inValue == "D" ) { return Spelling::Ds; }
        if ( inValue == "E" ) { return Spelling::Es; }
        if ( inValue == "F" ) { return Spelling::Fs; }
        if ( inValue == "G" ) { return Spelling::Gs; }
        if ( inValue == "A" ) { return Spelling::As; }
        if ( inValue == "B" ) { return Spelling::Bs; }
        if ( inValue == "Cb" ) { return Spelling::Cb; }
        if ( inValue == "Db" ) { return Spelling::Db; }
        if ( inValue == "Eb" ) { return Spelling::Eb; }
        if ( inValue == "Fb" ) { return Spelling::Fb; }
        if ( inValue == "Gb" ) { return Spelling::Gb; }
        if ( inValue == "Ab" ) { return Spelling::Ab; }
        if ( inValue == "Bb" ) { return Spelling::Bb; }
        if ( inValue == "Cx" ) { return Spelling::Cx; }
        if ( inValue == "Dx" ) { return Spelling::Dx; }
        if ( inValue == "Ex" ) { return Spelling::Ex; }
        if ( inValue == "Fx" ) { return Spelling::Fx; }
        if ( inValue == "Gx" ) { return Spelling::Gx; }
        if ( inValue == "Ax" ) { return Spelling::Ax; }
        if ( inValue == "Bx" ) { return Spelling::Bx; }
        if ( inValue == "Cd" ) { return Spelling::Cd; }
        if ( inValue == "Dd" ) { return Spelling::Dd; }
        if ( inValue == "Ed" ) { return Spelling::Ed; }
        if ( inValue == "Fd" ) { return Spelling::Fd; }
        if ( inValue == "Gd" ) { return Spelling::Gd; }
        if ( inValue == "Ad" ) { return Spelling::Ad; }
        if ( inValue == "Bd" ) { return Spelling::Bd; }
        return Spelling::ERROR;
    }

    struct SpellingTables
    {
        static const std::map<const Spelling, const int>& getPitchClassMap()
        {
            static std::map<const Spelling, const int> pitchClassMap =
            {
                { Spelling::Cn, 0  },
                { Spelling::Dn, 2  },
                { Spelling::En, 4  },
                { Spelling::Fn, 5  },
                { Spelling::Gn, 7  },
                { Spelling::An, 9  },
                { Spelling::Bn, 11 },
                { Spelling::Cs, 1  },
                { Spelling::Ds, 3  },
                { Spelling::Es, 5  },
                { Spelling::Fs, 6  },
                { Spelling::Gs, 8  },
                { Spelling::As, 10 },
                { Spelling::Bs, 0  },
                { Spelling::Cb, 11 },
                { Spelling::Db, 1  },
                { Spelling::Eb, 3  },
                { Spelling::Fb, 4  },
                { Spelling::Gb, 6  },
                { Spelling::Ab, 8  },
                { Spelling::Bb, 10 },
                { Spelling::Cx, 2  },
                { Spelling::Dx, 4  },
                { Spelling::Ex, 6  },
                { Spelling::Fx, 7  },
                { Spelling::Gx, 9  },
                { Spelling::Ax, 11 },
                { Spelling::Bx, 1  },
                { Spelling::Cd, 10 },
                { Spelling::Dd, 0  },
                { Spelling::Ed, 2  },
                { Spelling::Fd, 3  },
                { Spelling::Gd, 5  },
                { Spelling::Ad, 7  },
                { Spelling::Bd, 9  },
            };

            return pitchClassMap;
        }

        static const std::map<const int, const Spelling>& getDefaultSpellingMap()
        {
            static std::map<const int, const Spelling> defaultSpellingMap =
            {
                { 0 , Spelling::Cn },
                { 1 , Spelling::Cs },
                { 2 , Spelling::Dn },
                { 3 , Spelling::Eb },
                { 4 , Spelling::En },
                { 5 , Spelling::Fn },
                { 6 , Spelling::Fs },
                { 7 , Spelling::Gn },
                { 8 , Spelling::Ab },
                { 9 , Spelling::An },
                { 10, Spelling::Bb },
                { 11, Spelling::Bn },
            };

            return defaultSpellingMap;
        }

        static const std::map<const Spelling, const Step>& getStepMap()
        {
            static std::map<const Spelling, const Step> pitchStepMap =
            {
                { Spelling::Cn, Step::C },
                { Spelling::Dn, Step::D },
                { Spelling::En, Step::E },
                { Spelling::Fn, Step::F },
                { Spelling::Gn, Step::G },
                { Spelling::An, Step::A },
                { Spelling::Bn, Step::B },
                { Spelling::Cs, Step::C },
                { Spelling::Ds, Step::D },
                { Spelling::Es, Step::E },
                { Spelling::Fs, Step::F },
                { Spelling::Gs, Step::G },
                { Spelling::As, Step::A },
                { Spelling::Bs, Step::B },
                { Spelling::Cb, Step::C },
                { Spelling::Db, Step::D },
                { Spelling::Eb, Step::E },
                { Spelling::Fb, Step::F },
                { Spelling::Gb, Step::G },
                { Spelling::Ab, Step::A },
                { Spelling::Bb, Step::B },
                { Spelling::Cx, Step::C },
                { Spelling::Dx, Step::D },
                { Spelling::Ex, Step::E },
                { Spelling::Fx, Step::F },
                { Spelling::Gx, Step::G },
                { Spelling::Ax, Step::A },
                { Spelling::Bx, Step::B },
                { Spelling::Cd, Step::C },
                { Spelling::Dd, Step::D },
                { Spelling::Ed, Step::E },
                { Spelling::Fd, Step::F },
                { Spelling::Gd, Step::G },
                { Spelling::Ad, Step::A },
                { Spelling::Bd, Step::B },
            };

            return pitchStepMap;
        }

        static const std::map<const Spelling, const Alter>& getAlterMap()
        {
            static std::map<const Spelling, const Alter> pitchAlterMap =
            {
                { Spelling::Cn, Alter::NATURAL },
                { Spelling::Dn, Alter::NATURAL },
                { Spelling::En, Alter::NATURAL },
                { Spelling::Fn, Alter::NATURAL },
                { Spelling::Gn, Alter::NATURAL },
                { Spelling::An, Alter::NATURAL },
                { Spelling::Bn, Alter::NATURAL },
                { Spelling::Cs, Alter::SHARP },
                { Spelling::Ds, Alter::SHARP },
                { Spelling::Es, Alter::SHARP },
                { Spelling::Fs, Alter::SHARP },
                { Spelling::Gs, Alter::SHARP },
                { Spelling::As, Alter::SHARP },
                { Spelling::Bs, Alter::SHARP },
                { Spelling::Cb, Alter::FLAT },
                { Spelling::Db, Alter::FLAT },
                { Spelling::Eb, Alter::FLAT },
                { Spelling::Fb, Alter::FLAT },
                { Spelling::Gb, Alter::FLAT },
                { Spelling::Ab, Alter::FLAT },
                { Spelling::Bb, Alter::FLAT },
                { Spelling::Cx, Alter::DOUBLE_SHARP },
                { Spelling::Dx, Alter::DOUBLE_SHARP },
                { Spelling::Ex, Alter::DOUBLE_SHARP },
                { Spelling::Fx, Alter::DOUBLE_SHARP },
                { Spelling::Gx, Alter::DOUBLE_SHARP },
                { Spelling::Ax, Alter::DOUBLE_SHARP },
                { Spelling::Bx, Alter::DOUBLE_SHARP },
                { Spelling::Cd, Alter::DOUBLE_FLAT },
                { Spelling::Dd, Alter::DOUBLE_FLAT },
                { Spelling::Ed, Alter::DOUBLE_FLAT },
                { Spelling::Fd, Alter::DOUBLE_FLAT },
                { Spelling::Gd, Alter::DOUBLE_FLAT },
                { Spelling::Ad, Alter::DOUBLE_FLAT },
                { Spelling::Bd, Alter::DOUBLE_FLAT },
            };
            
            return pitchAlterMap;
        }
    };

    inline int intSpelling( Spelling inValue )
    {
        ENTROPY_ASSERT( static_cast<int>( inValue ) >= static_cast<int>( Spelling::Cn ) );
        ENTROPY_ASSERT( static_cast<int>( inValue ) < static_cast<int>( Spelling::ERROR ) );
        return SpellingTables::getPitchClassMap().at( inValue );
    }

    inline Spelling intSpelling( int inValue )
    {
        if( inValue < 0 || inValue > 11 )
        {
            return Spelling::ERROR;
        }

        return SpellingTables::getDefaultSpellingMap().at( inValue );
    }


    inline Spelling spell( Step inStep, Alter inAlter )
    {
        switch ( inStep )
        {
            case Step::C:
            {
                switch ( inAlter )
                {
                    case Alter::NATURAL: return Spelling::Cn;
                    case Alter::SHARP: return Spelling::Cs;
                    case Alter::FLAT: return Spelling::Cb;
                    case Alter::DOUBLE_SHARP: return Spelling::Cx;
                    case Alter::DOUBLE_FLAT: return Spelling::Cd;
                    default: return Spelling::ERROR;
                }
            }
                break;
            case Step::D:
            {
                switch ( inAlter )
                {
                    case Alter::NATURAL: return Spelling::Dn;
                    case Alter::SHARP: return Spelling::Ds;
                    case Alter::FLAT: return Spelling::Db;
                    case Alter::DOUBLE_SHARP: return Spelling::Dx;
                    case Alter::DOUBLE_FLAT: return Spelling::Dd;
                    default: return Spelling::ERROR;
                }
            }
                break;
            case Step::E:
            {
                switch ( inAlter )
                {
                    case Alter::NATURAL: return Spelling::En;
                    case Alter::SHARP: return Spelling::Es;
                    case Alter::FLAT: return Spelling::Eb;
                    case Alter::DOUBLE_SHARP: return Spelling::Ex;
                    case Alter::DOUBLE_FLAT: return Spelling::Ed;
                    default: return Spelling::ERROR;
                }
            }
                break;
            case Step::F:
            {
                switch ( inAlter )
                {
                    case Alter::NATURAL: return Spelling::Fn;
                    case Alter::SHARP: return Spelling::Fs;
                    case Alter::FLAT: return Spelling::Fb;
                    case Alter::DOUBLE_SHARP: return Spelling::Fx;
                    case Alter::DOUBLE_FLAT: return Spelling::Fd;
                    default: return Spelling::ERROR;
                }
            }
                break;
            case Step::G:
            {
                switch ( inAlter )
                {
                    case Alter::NATURAL: return Spelling::Gn;
                    case Alter::SHARP: return Spelling::Gs;
                    case Alter::FLAT: return Spelling::Gb;
                    case Alter::DOUBLE_SHARP: return Spelling::Gx;
                    case Alter::DOUBLE_FLAT: return Spelling::Gd;
                    default: return Spelling::ERROR;
                }
            }
                break;
            case Step::A:
            {
                switch ( inAlter )
                {
                    case Alter::NATURAL: return Spelling::An;
                    case Alter::SHARP: return Spelling::As;
                    case Alter::FLAT: return Spelling::Ab;
                    case Alter::DOUBLE_SHARP: return Spelling::Ax;
                    case Alter::DOUBLE_FLAT: return Spelling::Ad;
                    default: return Spelling::ERROR;
                }
            }
                break;
            case Step::B:
            {
                switch ( inAlter )
                {
                    case Alter::NATURAL: return Spelling::Bn;
                    case Alter::SHARP: return Spelling::Bs;
                    case Alter::FLAT: return Spelling::Bb;
                    case Alter::DOUBLE_SHARP: return Spelling::Bx;
                    case Alter::DOUBLE_FLAT: return Spelling::Bd;
                    default: return Spelling::ERROR;
                }
            }
                break;

            default:
                return Spelling::ERROR;
                break;
        }
    }
}
