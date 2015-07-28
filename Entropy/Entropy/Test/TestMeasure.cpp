#include "cpulTestHarness.h"
#include "Measure.h"

using namespace entropy;

TEST(constructor01, Measure)
{
    Measure m;
	CHECK_EQUAL( 4, m.getTimeSignature().getNumerator() );
    CHECK_EQUAL( 4, m.getTimeSignature().getDenominator() );
    CHECK_EQUAL( 0, m.getCount() );
}
TEST(constructor02, Measure)
{
    Measure m{ TimeSignature{ 2, 4 } };
	CHECK_EQUAL( 2, m.getTimeSignature().getNumerator() );
    CHECK_EQUAL( 4, m.getTimeSignature().getDenominator() );
    CHECK_EQUAL( 0, m.getCount() );
}
TEST(addNotes, Measure)
{
    Measure m{ TimeSignature{ 2, 4 } };
    m.addNote( Note() );
    m.addNote( Note() );
    try
    {
        m.addNote( Note() );
        CHECK( false )
    }
    catch ( const std::exception& e )
    {
        std::string expected = "cannot add note to measure";
        std::string actual = e.what();
        CHECK_EQUAL( expected, actual );
    }
    CHECK_EQUAL( 2, m.getCount() )
}
TEST(getNotes, Measure)
{
    Measure m{ TimeSignature{ 2, 4 } };
    m.addNote( Note( Pitch( "Ab5" ), Duration( Dur::Eighth ) ) );
    m.addNote( Note( Pitch( "G4" ), Duration( Dur::Quarter ) ) );
    m.addNote( Note( Pitch( "F#5" ), Duration( Dur::Eighth ) ) );
    auto notes = m.getNotes();
    CHECK_EQUAL( 3, notes.size() )
    auto iter = notes.begin();
    std::string expected = "Ab5";
    std::string actual = iter->getPitch().toString();
    CHECK_EQUAL( expected, actual )
    ++iter;
    expected = "G4";
    actual = iter->getPitch().toString();
    CHECK_EQUAL( expected, actual )
    ++iter;
    expected = "F#5";
    actual = iter->getPitch().toString();
    CHECK_EQUAL( expected, actual )
    ++iter;
    CHECK( iter == notes.end() )
}
TEST(removeNote, Measure)
{
    Measure m{ TimeSignature{ 2, 4 } };
    m.addNote( Note( Pitch( "Ab5" ), Duration( Dur::Eighth ) ) );
    m.addNote( Note( Pitch( "G4" ), Duration( Dur::Quarter ) ) );
    m.addNote( Note( Pitch( "F#5" ), Duration( Dur::Eighth ) ) );
    CHECK_EQUAL( 3, m.getNotes().size() )
    
    auto iter = m.getNotes().begin();
    ++iter;
    m.removeNote( iter );
    
    CHECK_EQUAL( 2, m.getNotes().size() )
    
    iter = m.getNotes().begin();
    
    std::string expected = "Ab5";
    std::string actual = iter->getPitch().toString();
    CHECK_EQUAL( expected, actual )
    ++iter;
    
    expected = "F#5";
    actual = iter->getPitch().toString();
    CHECK_EQUAL( expected, actual )
    ++iter;
    
    CHECK( iter == m.getNotes().end() )

}
TEST(setTimeSignature, Measure)
{
    Measure m{ TimeSignature{ 5, 4 } };
	CHECK_EQUAL( 5, m.getTimeSignature().getNumerator() );
    CHECK_EQUAL( 4, m.getTimeSignature().getDenominator() );
    m.setTimeSignature( TimeSignature( 3, 4 ) );
    CHECK_EQUAL( 3, m.getTimeSignature().getNumerator() );
    CHECK_EQUAL( 4, m.getTimeSignature().getDenominator() );
}
TEST(setTimeSignature02, Measure)
{
    Measure m{ TimeSignature{ 5, 4 } };
	m.setTimeSignature( TimeSignature( 3, 4 ) );
    CHECK_EQUAL( 3, m.getTimeSignature().getNumerator() );
    CHECK_EQUAL( 4, m.getTimeSignature().getDenominator() );
    m.addNote( Note( Pitch( "Ab5" ), Duration( Dur::Quarter ) ) );
    m.addNote( Note( Pitch( "G4" ), Duration( Dur::Quarter ) ) );
    m.addNote( Note( Pitch( "F#5" ), Duration( Dur::Quarter ) ) );
    try
    {
        m.setTimeSignature( TimeSignature( 2, 4 ) );
        CHECK( false )
    }
    catch ( std::exception& e )
    {
        std::string expected = "notes will not fit if time signature is changed";
        std::string actual = e.what();
        CHECK_EQUAL( expected, actual )
    }
    
}
TEST( getRemainingDivisions_0, Measure)
{
    Measure m{ TimeSignature{ 2, 4 } };
    m.addNote( Note( Pitch( "Ab5" ), Duration( Dur::Eighth ) ) );
    m.addNote( Note( Pitch( "G4" ), Duration( Dur::Quarter ) ) );
    m.addNote( Note( Pitch( "F#5" ), Duration( Dur::Eighth ) ) );
    CHECK_EQUAL( 0, m.getRemainingDivisions() );
}
TEST( getRemainingDivisions_All, Measure)
{
    Measure m{ TimeSignature{ 2, 4 } };
    Int expected = TimeSignature( 2, 4 ).getDivisionsPerMeasure();
    Int actual = m.getRemainingDivisions();
    CHECK_EQUAL( expected, actual );
}
TEST( getRemainingDivisions, Measure)
{
    Measure m{ TimeSignature{ 3, 4 } };
    Int expected = TimeSignature( 3, 4 ).getDivisionsPerMeasure();
    Int actual = m.getRemainingDivisions();
    CHECK_EQUAL( expected, actual );
    CHECK( expected > 0 )
    
    m.addNote( Note( Pitch( "Ab5" ), Duration( Dur::Eighth ) ) );
    expected -= ( TimeSignature( 3, 4 ).getDivisionsPerMeasure() / 6 );
    actual = m.getRemainingDivisions();
    CHECK_EQUAL( expected, actual );
    
    m.addNote( Note( Pitch( "G4" ), Duration( Dur::Quarter ) ) );
    expected -= ( TimeSignature( 3, 4 ).getDivisionsPerMeasure() / 3 );
    actual = m.getRemainingDivisions();
    CHECK_EQUAL( expected, actual );
    
    m.addNote( Note( Pitch( "F#5" ), Duration( Dur::Eighth ) ) );
    expected -= ( TimeSignature( 3, 4 ).getDivisionsPerMeasure() / 6 );
    actual = m.getRemainingDivisions();
    CHECK_EQUAL( expected, actual );
    
    m.addNote( Note( Pitch( "Db2" ), Duration( Dur::Quarter ) ) );
    expected = 0;
    actual = m.getRemainingDivisions();
    CHECK_EQUAL( expected, actual );
    
}
TEST( getTotalDivisions, Measure)
{
    Measure m{ TimeSignature{ 3, 4 } };
    Int expected = 0;
    Int actual = m.getTotalDivisions();
    CHECK_EQUAL( expected, actual );
    
    m.addNote( Note( Pitch( "Ab5" ), Duration( Dur::Eighth ) ) );
    expected += ( TimeSignature( 3, 4 ).getDivisionsPerMeasure() / 6 );
    actual = m.getTotalDivisions();
    CHECK_EQUAL( expected, actual );
    
    m.addNote( Note( Pitch( "G4" ), Duration( Dur::Quarter ) ) );
    expected += ( TimeSignature( 3, 4 ).getDivisionsPerMeasure() / 3 );
    actual = m.getTotalDivisions();
    CHECK_EQUAL( expected, actual );
    
    m.addNote( Note( Pitch( "F#5" ), Duration( Dur::Eighth ) ) );
    expected += ( TimeSignature( 3, 4 ).getDivisionsPerMeasure() / 6 );
    actual = m.getTotalDivisions();
    CHECK_EQUAL( expected, actual );
    
    m.addNote( Note( Pitch( "Db2" ), Duration( Dur::Quarter ) ) );
    expected = m.getTimeSignature().getDivisionsPerMeasure();
    actual = m.getTotalDivisions();
    CHECK_EQUAL( expected, actual );
    CHECK( m.getTimeSignature().getDivisionsPerMeasure() > 0 )
    
}
TEST( canAdd, Measure)
{
    Measure m{ TimeSignature{ 3, 4 } };
    Note n1( Pitch( "Ab5" ), Duration( Dur::Eighth ) );
    Note n2( Pitch( "Ab5" ), Duration( Dur::Eighth ) );
    Note n3( Pitch( "Ab5" ), Duration( Dur::Eighth ) );
    Note n4( Pitch( "Ab5" ), Duration( Dur::Eighth ) );
    Note n5( Pitch( "Ab5" ), Duration( Dur::Eighth ) );
    Note n6q( Pitch( "Ab5" ), Duration( Dur::Quarter ) );
    Note n6e( Pitch( "Ab5" ), Duration( Dur::Eighth ) );
    m.addNote( n1 );
    m.addNote( n2 );
    m.addNote( n3 );
    m.addNote( n4 );
    m.addNote( n5 );
    CHECK( !m.canAdd( n6q ) )
    CHECK( m.canAdd( n6e ) )
    m.addNote( n6e );
    CHECK( ! m.canAdd( n6e ) )
}
TEST( isOnBeat01, Measure )
{
    Measure m{ TimeSignature{ 4, 4 } };
    CHECK( m.isOnBeat() )
    m.addNote( Note( Pitch{}, Duration( Dur::Quarter ) ) );
    CHECK( m.isOnBeat() )
    m.addNote( Note( Pitch{}, Duration( Dur::Eighth ) ) );\
    CHECK( ! m.isOnBeat() )
}
TEST( canStartTuplet, Measure )
{
    Measure m{ TimeSignature{ 4, 4 } };
    CHECK( m.canStartTuplet( Duration( Dur::Quarter, Tup::Triplet ) ) );
    m.addNote( Note( Pitch{}, Duration( Dur::Quarter, Tup::Triplet ) ) );
    CHECK( ! m.canStartTuplet( Duration( Dur::Quarter, Tup::Triplet ) ) );
    m.addNote( Note( Pitch{}, Duration( Dur::Quarter, Tup::Triplet ) ) );
    CHECK( ! m.isOnBeat() )
    m.addNote( Note( Pitch{}, Duration( Dur::Quarter, Tup::Triplet ) ) );
    CHECK( m.isOnBeat() )
    m.addNote( Note( Pitch{}, Duration( Dur::Quarter ) ) );
    CHECK( ! m.canStartTuplet( Duration( Dur::Quarter, Tup::Triplet ) ) );
}