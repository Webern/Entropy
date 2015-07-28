#include "RhythmList.h"
#define VERSION2

namespace entropy
{
#ifdef VERSION1
    RhythmBook makeRhythmBook()
    {
        RhythmBook book;
        RhythmList list0 =
        {
            Duration{ Dur::Whole },
        };
        RhythmList list1 =
        {
            //Duration{ Dur::Quarter, Tup::Quintuplet },
            Duration{ Dur::Whole },
            //Duration{ Dur::Quarter, Tup::Quintuplet },
            //Duration{ Dur::Eighth, 1 },
            //Duration{ Dur::Sixteenth },
            //Duration{ Dur::Quarter },
            //Duration{ Dur::Half }
        };
        RhythmList list2 =
        {
            //Duration{ Dur::Quarter, Tup::Quintuplet },
            Duration{ Dur::Whole },
            //Duration{ Dur::Quarter, Tup::Quintuplet },
            //Duration{ Dur::Eighth, 1 },
            //Duration{ Dur::Sixteenth },
            //Duration{ Dur::Quarter },
            //Duration{ Dur::Half }
        };
        RhythmList list3 =
        {
            //Duration{ Dur::Quarter, Tup::Quintuplet },
            Duration{ Dur::Whole },
            //Duration{ Dur::Quarter, Tup::Quintuplet },
            //Duration{ Dur::Eighth, 1 },
            //Duration{ Dur::Sixteenth },
            //Duration{ Dur::Quarter },
            Duration{ Dur::Half }
        };
        RhythmList list4 =
        {
            //Duration{ Dur::Quarter, Tup::Quintuplet },
            Duration{ Dur::Whole },
            //Duration{ Dur::Quarter, Tup::Quintuplet },
            //Duration{ Dur::Eighth, 1 },
            //Duration{ Dur::Sixteenth },
            Duration{ Dur::Quarter },
            Duration{ Dur::Half }
        };
        RhythmList list5 =
        {
            //Duration{ Dur::Quarter, Tup::Quintuplet },
            Duration{ Dur::Whole },
            //Duration{ Dur::Quarter, Tup::Quintuplet },
            //Duration{ Dur::Eighth, 1 },
            //Duration{ Dur::Sixteenth },
            Duration{ Dur::Quarter },
            Duration{ Dur::Half }
        };
        RhythmList list6 =
        {
            //Duration{ Dur::Quarter, Tup::Quintuplet },
            Duration{ Dur::Quarter, Tup::Triplet },
            //Duration{ Dur::Quarter, Tup::Quintuplet },
            //Duration{ Dur::Eighth, 1 },
            //Duration{ Dur::Sixteenth },
            Duration{ Dur::Quarter },
            Duration{ Dur::Half }
        };
        RhythmList list7 =
        {
            Duration{ Dur::Quarter, Tup::Quintuplet },
            Duration{ Dur::Quarter, Tup::Triplet },
            //Duration{ Dur::Quarter, Tup::Quintuplet },
            //Duration{ Dur::Eighth, 1 },
            //Duration{ Dur::Sixteenth },
            Duration{ Dur::Quarter }
        };
        RhythmList list8 =
        {
            Duration{ Dur::Quarter, Tup::Quintuplet },
            Duration{ Dur::Quarter, Tup::Triplet },
            Duration{ Dur::Quarter, Tup::Quintuplet },
            //Duration{ Dur::Eighth, 1 },
            //Duration{ Dur::Sixteenth },
            Duration{ Dur::Quarter }
        };
        RhythmList list9 =
        {
            Duration{ Dur::Quarter, Tup::Quintuplet },
            Duration{ Dur::Eighth, Tup::Triplet },
            Duration{ Dur::Quarter, Tup::Quintuplet },
            //Duration{ Dur::Eighth, 1 },
            //Duration{ Dur::Sixteenth },
            Duration{ Dur::Quarter }
        };
        RhythmList list10 =
        {
            Duration{ Dur::Quarter, Tup::Quintuplet },
            Duration{ Dur::Eighth, Tup::Triplet },
            Duration{ Dur::Eighth, Tup::Quintuplet },
            Duration{ Dur::Eighth, 1 },
            Duration{ Dur::Sixteenth },
            Duration{ Dur::Quarter }
        };
        RhythmList list11 =
        {
            Duration{ Dur::Quarter, Tup::Quintuplet },
            Duration{ Dur::Eighth, Tup::Triplet },
            Duration{ Dur::Eighth, Tup::Quintuplet },
            Duration{ Dur::Eighth, 1 },
            Duration{ Dur::Sixteenth },
            Duration{ Dur::Quarter }
        };
        RhythmList list12 =
        {
            Duration{ Dur::Quarter, Tup::Quintuplet },
            Duration{ Dur::Eighth, Tup::Triplet },
            Duration{ Dur::Eighth, Tup::Quintuplet },
            Duration{ Dur::Eighth, 1 },
            Duration{ Dur::Sixteenth },
            Duration{ Dur::Quarter }
            //Duration{ Dur::Sixteenth },
            //Duration{ Dur::Sixteenth, Tup::Quintuplet },
            //Duration{ Dur::Sixteenth, Tup::Sextuplet }
        };
        
        book.push_back( list0 );
        book.push_back( list1 );
        book.push_back( list2 );
        book.push_back( list3 );
        book.push_back( list4 );
        book.push_back( list5 );
        book.push_back( list6 );
        book.push_back( list7 );
        book.push_back( list8 );
        book.push_back( list9 );
        book.push_back( list10 );
        book.push_back( list11 );
        book.push_back( list12 );
        
        return book;
    }
#endif
    Duration getRhythm( const Int listIndex, const Int rhythmIndex )
    {
        return Duration{};
    }
    
#ifdef VERSION2
    RhythmBook makeRhythmBook()
    {
        RhythmBook book;
        RhythmList list0 =
        {
            Duration{ Dur::Whole },
            Duration{ Dur::Half, 1 }
        };
        RhythmList list1 =
        {
            Duration{ Dur::Whole },
            Duration{ Dur::Half },
            Duration{ Dur::Half, 1 }
        };
        RhythmList list2 =
        {
            Duration{ Dur::Whole },
            Duration{ Dur::Half },
            Duration{ Dur::Half, 1 },
            Duration{ Dur::Quarter }
        };
        RhythmList list3 =
        {
            Duration{ Dur::Half },
            Duration{ Dur::Half, 1 },
            Duration{ Dur::Quarter }
        };
        RhythmList list4 =
        {
            Duration{ Dur::Half },
            Duration{ Dur::Half, 1 },
            Duration{ Dur::Quarter },
            Duration{ Dur::Eighth }
        };
        RhythmList list5 =
        {
            Duration{ Dur::Half },
            Duration{ Dur::Half, 1 },
            Duration{ Dur::Quarter },
            Duration{ Dur::Eighth },
            Duration{ Dur::Eighth, 1 },
            Duration{ Dur::Sixteenth }
        };
        RhythmList list6 =
        {
            Duration{ Dur::Half },
            Duration{ Dur::Quarter },
            Duration{ Dur::Eighth },
            Duration{ Dur::Eighth, 1 },
            Duration{ Dur::Sixteenth }
        };
        RhythmList list7 =
        {
            Duration{ Dur::Quarter },
            Duration{ Dur::Eighth },
            Duration{ Dur::Eighth, 1 },
            Duration{ Dur::Sixteenth }
        };
        RhythmList list8 =
        {
            Duration{ Dur::Eighth },
            Duration{ Dur::Eighth, 1 },
            Duration{ Dur::Sixteenth }
        };
        RhythmList list9 =
        {
            Duration{ Dur::Eighth },
            Duration{ Dur::Sixteenth }
        };
        RhythmList list10 =
        {
            Duration{ Dur::Eighth },
            Duration{ Dur::Sixteenth }
        };
        RhythmList list11 =
        {
            Duration{ Dur::Sixteenth }
        };
        RhythmList list12 =
        {
            Duration{ Dur::Sixteenth }
        };
        
        book.push_back( list0 );
        book.push_back( list1 );
        book.push_back( list2 );
        book.push_back( list3 );
        book.push_back( list4 );
        book.push_back( list5 );
        book.push_back( list6 );
        book.push_back( list7 );
        book.push_back( list8 );
        book.push_back( list9 );
        book.push_back( list10 );
        book.push_back( list11 );
        book.push_back( list12 );
        
        return book;
    }
#endif
}