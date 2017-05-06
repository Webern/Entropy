// Copyright (c) Matthew James Briggs

#include "Duration.h"
#include "Constants.h"
#include "Throw.h"

namespace entropy
{
    Duration::Duration()
    : myDuration{}
    {
        myDuration.durationName = mx::api::DurationName::quarter;
        setTicks();
    }


    mx::api::DurationData Duration::getDurationData() const
    {
        return myDuration;
    }


    Tuplet Duration::getTuplet() const
    {
        Tuplet result;
        result.normal = myDuration.timeModificationNormalNotes;
        result.actual = myDuration.timeModificationActualNotes;
        return result;
    }


    void Duration::setTuplet(Tuplet inTuplet)
    {
        myDuration.timeModificationActualNotes = inTuplet.actual;
        myDuration.timeModificationNormalNotes = inTuplet.normal;
        setTicks();
    }


    void Duration::clearTuplet()
    {
        myDuration.timeModificationActualNotes = 0;
        myDuration.timeModificationNormalNotes = 0;
        setTicks();
    }


    int Duration::getTicks() const
    {
        return myDuration.durationTimeTicks;
    }


    const std::vector<const int>& Duration::getDurationSizes()
    {
        static const std::vector<const int> durationSizes =
        {
            TICKS_PER_WHOLE,
            TICKS_PER_HALF,
            TICKS_PER_QUARTER,
            TICKS_PER_8TH,
            TICKS_PER_16TH,
            TICKS_PER_32ND,
            TICKS_PER_64TH,
        };

        return durationSizes;
    }


    const std::map<const int, const Duration>&
    Duration::getDurationPrototypes()
    {
        static std::map<const int, const Duration> prototypes;

        const auto& sizes = getDurationSizes();

        // loop once for zero and single-dotted durations without tuplets
        for( const auto& durBase : sizes )
        {
            for( int dots = 0; dots <= 1; ++dots )
            {
                const int ticks = applyDots( durBase, dots );
                mx::api::DurationData mxdur{};
                mxdur.durationName = getDurationNames().at( durBase );
                mxdur.durationTimeTicks = ticks;
                mxdur.durationDots = dots;
                Duration dur{};
                dur.myDuration = mxdur;
                std::pair<const int, const Duration> pair{ ticks, dur };
                prototypes.insert( std::move( pair ) );
            }
        }

        // loop once for triplets with no dots
        for( const auto& durBase : sizes )
        {
            Tuplet tup;
            tup.actual = 3;
            tup.normal = 2;
            const int ticks = applyTuplet( durBase, tup );
            mx::api::DurationData mxdur{};
            mxdur.durationName = getDurationNames().at( durBase );
            mxdur.durationTimeTicks = ticks;
            mxdur.durationDots = 0;
            mxdur.timeModificationActualNotes = 3;
            mxdur.timeModificationNormalNotes = 2;
            Duration dur{};
            dur.myDuration = mxdur;
            std::pair<const int, const Duration> pair{ ticks, dur };
            prototypes.insert( std::move( pair ) );
        }

        // loop again for normal-ish tuplets without dots
        const std::vector<int> normalishTupletBases = { 2, 4, 8, 16, 32 };

        for( const auto& durBase : sizes )
        {
            Tuplet tup;

            for( tup.actual = 2; tup.actual <= MAX_TUPLET_ACTUAL; ++tup.actual )
            {
                for( const auto& tupBase : normalishTupletBases )
                {
                    if ( tupBase > MAX_TUPLET_NORMAL )
                    {
                        continue;
                    }

                    const int currentMaxActual = tupBase * 2;

                    if ( tup.actual >= currentMaxActual )
                    {
                        continue;
                    }

                    tup.normal = tupBase;

                    if( tup.actual == tup.normal )
                    {
                        continue;
                    }

                    if( tup.actual == 1 || tup.normal == 1 )
                    {
                        continue;
                    }

                    const int ticks = applyTuplet( durBase, tup );
                    mx::api::DurationData mxdur{};
                    mxdur.durationName = getDurationNames().at( durBase );
                    mxdur.durationTimeTicks = ticks;
                    mxdur.durationDots = 0;
                    mxdur.timeModificationActualNotes = tup.actual;
                    mxdur.timeModificationNormalNotes = tup.normal;
                    Duration dur{};
                    dur.myDuration = mxdur;
                    std::pair<const int, const Duration> pair{ ticks, dur };
                    if( prototypes.find( ticks ) == prototypes.end() )
                    {
                        prototypes.insert( std::move( pair ) );
                    }
                }
            }
        }


        // loop again for normal-ish tuplets with one dot
        for( const auto& durBase : sizes )
        {
            Tuplet tup;

            for( tup.actual = 2; tup.actual <= MAX_TUPLET_ACTUAL; ++tup.actual )
            {
                for( const auto& tupBase : normalishTupletBases )
                {
                    const int dots = 1;
                    if ( tupBase > MAX_TUPLET_NORMAL )
                    {
                        continue;
                    }

                    const int currentMaxActual = tupBase * 2;

                    if ( tup.actual >= currentMaxActual )
                    {
                        continue;
                    }

                    tup.normal = tupBase;

                    if( tup.actual == tup.normal )
                    {
                        continue;
                    }

                    if( tup.actual == 1 || tup.normal == 1 )
                    {
                        continue;
                    }

                    const int ticks = applyTuplet( applyDots( durBase, dots ), tup );
                    mx::api::DurationData mxdur{};
                    mxdur.durationName = getDurationNames().at( durBase );
                    mxdur.durationTimeTicks = ticks;
                    mxdur.durationDots = dots;
                    mxdur.timeModificationActualNotes = tup.actual;
                    mxdur.timeModificationNormalNotes = tup.normal;
                    Duration dur{};
                    dur.myDuration = mxdur;
                    std::pair<const int, const Duration> pair{ ticks, dur };
                    if( prototypes.find( ticks ) == prototypes.end() )
                    {
                        prototypes.insert( std::move( pair ) );
                    }
                }
            }
        }

        // loop again for everything
        for( const auto& durBase : sizes )
        {
            Tuplet tup;

            for( tup.actual = 2; tup.actual <= MAX_TUPLET_ACTUAL; ++tup.actual )
            {
                for( tup.normal = 2; tup.normal <= MAX_TUPLET_NORMAL; ++tup.normal )
                {
                    for( int dots = 0; dots <= MAX_DOTS; ++dots )
                    {
                        const int currentMaxActual = tup.normal * 2;

                        if ( tup.actual >= currentMaxActual )
                        {
                            continue;
                        }

                        if( tup.actual == tup.normal )
                        {
                            continue;
                        }

                        if( tup.actual == 1 || tup.normal == 1 )
                        {
                            continue;
                        }

                        const int ticks = applyTuplet( applyDots( durBase, dots ), tup );
                        mx::api::DurationData mxdur{};
                        mxdur.durationName = getDurationNames().at( durBase );
                        mxdur.durationTimeTicks = ticks;
                        mxdur.durationDots = dots;
                        mxdur.timeModificationActualNotes = tup.actual;
                        mxdur.timeModificationNormalNotes = tup.normal;
                        Duration dur{};
                        dur.myDuration = mxdur;
                        std::pair<const int, const Duration> pair{ ticks, dur };
                        if( prototypes.find( ticks ) == prototypes.end() )
                        {
                            prototypes.insert( std::move( pair ) );
                        }
                    }
                }
            }
        }

        return prototypes;
    }


    const std::map<const int, const mx::api::DurationName>&
    Duration::getDurationNames()
    {
        static const std::map<const int, const mx::api::DurationName> names =
        {
            { TICKS_PER_WHOLE, mx::api::DurationName::whole },
            { TICKS_PER_HALF, mx::api::DurationName::half },
            { TICKS_PER_QUARTER, mx::api::DurationName::quarter },
            { TICKS_PER_8TH, mx::api::DurationName::eighth },
            { TICKS_PER_16TH, mx::api::DurationName::dur16th },
            { TICKS_PER_32ND, mx::api::DurationName::dur32nd },
            { TICKS_PER_64TH, mx::api::DurationName::dur64th },
        };

        return names;
    }


    int Duration::applyDots(int inTicks, int inDots)
    {
        int result = inTicks;
        int add = inTicks / 2;

        for( int i = 0; i < inDots; ++i )
        {
            result += add;
            add /= 2;
        }

        return result;
    }


    int Duration::applyTuplet(int inTicks, Tuplet inTuplet)
    {
        ENTROPY_ASSERT( inTuplet.actual != 0 );
        return ( inTicks * inTuplet.normal ) / inTuplet.actual;
    }

    void Duration::setTicks()
    {
        const auto& names = getDurationNames();

        const auto pred = [&]( const std::pair<const int, const mx::api::DurationName>& inPair )
        {
            return inPair.second == myDuration.durationName;
        };

        auto iter = std::find_if( std::begin(names), std::end(names), pred );
        ENTROPY_ASSERT( iter != std::end( names ) );
        auto ticks = iter->first;
        ticks = applyDots( ticks, myDuration.durationDots );
        Tuplet tuplet;
        tuplet.actual = myDuration.timeModificationActualNotes;
        tuplet.normal = myDuration.timeModificationNormalNotes;
        ticks = applyTuplet( ticks, tuplet );
        myDuration.durationTimeTicks = ticks;
    }
}
