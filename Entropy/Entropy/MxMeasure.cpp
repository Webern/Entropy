#include "MxMeasure.h"
#include "MxNote.h"
#include "Note.h"
#include <string>
#include "Clef.h"
#include "MxClef.h"

namespace entropy
{
    using namespace mx::e;
    using namespace mx::t;
    using namespace mx::d;
    using namespace std;
    
    void clearMxMeasureAttributes( const mx::e::PartwiseMeasurePtr& m, bool retainMeasureNumber )
    {
        auto attributes = m->getAttributes();
        attributes->hasImplicit = false;
        attributes->hasNonControlling = false;
        attributes->hasWidth = false;
        if ( !retainMeasureNumber )
        {
            attributes->number = XsToken( "" );
        }
    }
    void clearMxMeasureContents( const mx::e::PartwiseMeasurePtr& m )
    {
        m->setMusicDataGroup( makeMusicDataGroup() );
    }
    void fillMxMeasure( const mx::e::PartwiseMeasurePtr& mxmeasure, const Measure& measure )
    {
        clearMxMeasureAttributes( mxmeasure, true );
        clearMxMeasureContents( mxmeasure );
        setMxMeasureDivisions( mxmeasure, measure.getTimeSignature().getDivisionsPerQuarter() );
        setMxMeasureTimeSignature( mxmeasure, measure.getTimeSignature() );
        Clf clef = inferClef( measure.getNotes().cbegin(), measure.getNotes().cend(), measure.getInstrument() );
        setMxMeasureClef( mxmeasure, clef );
        
        bool inTuplet = false;
        Tup tup = Tup::Simple;
        Int tupletTotalDivisionsToComplete = 0;
        Int tupletDivisionsEncountered = 0;
        std::vector<Pitch> alteredPitches;
        for ( auto n = measure.getNotes().begin(); n != measure.getNotes().end(); ++n )
        {
            //TODO: Refactor a Ton
            MxNote note{ *n };
            auto newNoteMdc = note.getMusicDataChoice();
            auto newNote = newNoteMdc->getNote();
            
            tup = n->getDuration().getTup();
            
            if ( tup != Tup::Simple ) // begin tuplet parsing
            {
                auto tuplet = makeTuplet();
                auto tupletNotationChoice = makeNotationsChoice();
                bool found = false;
                for ( auto notationsSetIter = newNote->getNotationsSet().begin();
                     notationsSetIter != newNote->getNotationsSet().end();
                     ++notationsSetIter)
                {
                    for ( auto notationsChoiceSetIter = (*notationsSetIter)->getNotationsChoiceSet().begin();
                         notationsChoiceSetIter != (*notationsSetIter)->getNotationsChoiceSet().end();
                         ++notationsChoiceSetIter )
                    {
                        tupletNotationChoice = *notationsChoiceSetIter;
                        found = true;
                    }
                }
                if ( !found )
                {
                    auto newnotations = makeNotations();
                    newnotations->addNotationsChoice( tupletNotationChoice );
                    newNote->addNotations( newnotations );
                }
                tupletNotationChoice->setChoice( NotationsChoice::Choice::tuplet );
                tupletNotationChoice->setTuplet( tuplet );
                
                if ( ! inTuplet )
                {
                    tupletTotalDivisionsToComplete = n->getDuration().getDivisionsToCompleteTuplet();
                    tupletDivisionsEncountered = n->getDuration().getDivisions();
                    tuplet->getAttributes()->hasNumber = false;
                    tuplet->getAttributes()->hasPlacement = false;
                    tuplet->getAttributes()->hasBracket = false;
                    tuplet->getAttributes()->type = StartStop::start;
                    inTuplet = true;
                    
                }
                else
                {
                    tupletDivisionsEncountered += n->getDuration().getDivisions();
                    if ( tupletDivisionsEncountered > tupletTotalDivisionsToComplete )
                    {
                        // throw ( new std::runtime_error( "tuplet overflow" ) );
                    }
                    else if ( tupletDivisionsEncountered == tupletTotalDivisionsToComplete )
                    {
                        // end the tuplet
                        auto tupletAttributes = tuplet->getAttributes();
                        tupletAttributes->hasNumber = false;
                        tupletAttributes->hasPlacement = false;
                        tupletAttributes->hasBracket = false;
                        tupletAttributes->type = StartStop::stop;
                        inTuplet = false;
                        tupletDivisionsEncountered = 0;
                        tupletTotalDivisionsToComplete = 0;
                    }
                    else
                    {
                        // tuplet continues
                        // remove any tuplet definitions
                        for ( auto notationsSetIter = newNote->getNotationsSet().begin();
                             notationsSetIter != newNote->getNotationsSet().end();
                             ++notationsSetIter)
                        {
                            auto ncsBeg = (*notationsSetIter)->getNotationsChoiceSet().begin();
                            auto ncsEnd = (*notationsSetIter)->getNotationsChoiceSet().end();
                            auto ncsFound = ncsBeg;
                            while ( ncsFound != ncsEnd )
                            {
                                ncsFound = std::find_if( ncsBeg, ncsEnd, [](const NotationsChoicePtr& inside)
                                {
                                    return inside->getChoice() == NotationsChoice::Choice::tuplet;
                                
                                } );
                                if( ncsFound != ncsEnd )
                                {
                                    (*notationsSetIter)->removeNotationsChoice( ncsFound );
                                    ncsBeg = (*notationsSetIter)->getNotationsChoiceSet().begin();
                                    ncsEnd = (*notationsSetIter)->getNotationsChoiceSet().end();
                                    ncsFound = ncsBeg;
                                }
                            }
                        }
                    }
                }
            } // end tuplet parsing
            
            
            /* deal with altered pitches */
            if( ! n->getIsRest() )
            {
                auto alteredBeg = alteredPitches.cbegin();
                auto alteredEnd = alteredPitches.cend();
                auto alteredFnd = alteredEnd;
                alteredFnd = std::find_if( alteredBeg, alteredEnd, [&n](const Pitch& inside)
                                          {
                                              return ( inside.getNoteName().getStep() == n->getPitch().getNoteName().getStep() )
                                              &&
                                              ( inside.getOctave() == n->getPitch().getOctave() );
                                          } );
                if ( alteredFnd != alteredEnd )
                {
                    /* this step has been altered before */
                    if ( alteredFnd->getNoteName().getAlter() == n->getPitch().getNoteName().getAlter() )
                    {
                        hideAccidental( newNote );
                    }
                    else
                    {
                        showAccidental( newNote );
                        alteredPitches.erase( alteredFnd );
                        alteredPitches.push_back( n->getPitch() );
                    }
                }
                else
                {
                    if ( n->getPitch().getNoteName().getAlter() != 0 )
                    {
                        showAccidental( newNote );
                        alteredPitches.push_back( n->getPitch() );
                    }
                    
                }
            }
            // wtf why can't i get a rest?
            if ( n->getIsRest() )
            {
                newNoteMdc->getNote()->getNoteChoice()->getNormalNoteGroup()->getFullNoteGroup()->getFullNoteTypeChoice()->setChoice( FullNoteTypeChoice::Choice::rest );
            }
            mxmeasure->getMusicDataGroup()->addMusicDataChoice( newNoteMdc );
        } // end loop - for each note
    }
    void fillMxMeasure( const mx::e::PartwiseMeasurePtr& mxmeasure, const Measure& measure, Int measureNumber )
    {
        mxmeasure->getAttributes()->number = XsToken( to_string( measureNumber ) );
        fillMxMeasure( mxmeasure, measure );
    }
    void setMxMeasureDivisions( const mx::e::PartwiseMeasurePtr& m, const Int divisions )
    {
        auto mdcBeg = m->getMusicDataGroup()->getMusicDataChoiceSet().begin();
        auto mdcEnd = m->getMusicDataGroup()->getMusicDataChoiceSet().end();
        auto iterToProperties = std::find_if( mdcBeg, mdcEnd, [](const MusicDataChoicePtr& inside){ return inside->getChoice() == MusicDataChoice::Choice::properties; } );
        auto properties = makeProperties();
        if ( iterToProperties != mdcEnd )
        {
            properties = (*iterToProperties)->getProperties();
        }
        else
        {
            auto newMdc = makeMusicDataChoice();
            newMdc->setChoice( MusicDataChoice::Choice::properties );
            newMdc->setProperties( properties );
            m->getMusicDataGroup()->addMusicDataChoice( newMdc );
        }
        properties->setHasDivisions( true );
        properties->getDivisions()->setValue( PositiveDivisionsValue( divisions ) );
    }
    void setMxMeasureTimeSignature( const mx::e::PartwiseMeasurePtr& m, const TimeSignature& timeSignature )
    {
        auto mdcBeg = m->getMusicDataGroup()->getMusicDataChoiceSet().begin();
        auto mdcEnd = m->getMusicDataGroup()->getMusicDataChoiceSet().end();
        auto iterToProperties = std::find_if( mdcBeg, mdcEnd, [](const MusicDataChoicePtr& inside){ return inside->getChoice() == MusicDataChoice::Choice::properties; } );
        auto properties = makeProperties();
        if ( iterToProperties != mdcEnd )
        {
            properties = (*iterToProperties)->getProperties();
        }
        else
        {
            auto newMdc = makeMusicDataChoice();
            newMdc->setChoice( MusicDataChoice::Choice::properties );
            newMdc->setProperties( properties );
            m->getMusicDataGroup()->addMusicDataChoice( newMdc );
        }
        properties->clearTimeSet();
        auto time = makeTime();
        time->getTimeChoice()->setChoice( TimeChoice::Choice::timeSignature );
        auto timeSig = time->getTimeChoice()->getTimeSignature();
        timeSig->getBeats()->setValue( XsString( to_string( timeSignature.getNumerator() ) ) );
        timeSig->getBeatType()->setValue( XsString( to_string( timeSignature.getDenominator() ) ) );
        properties->addTime( time );
    }
    
    
    
    
    
    
    
    
    
    /****************************************************************************************************/
    MxMeasureIterator::MxMeasureIterator( DocumentPartwisePtr& doc, PartwisePartPtr& part )
    :myDoc( doc )
    ,myPart( part )
    ,myMeasure( makePartwiseMeasure() )
    ,myIsEnd( true )
    {
        if( ! doc )
        {
            throw std::runtime_error( "invalid DocumentPartwisePtr" );
        }
        if ( ! part )
        {
            throw std::runtime_error( "invalid ParwisePartPtr" );
        }
        if ( ! setBegin() )
        {
            throw std::runtime_error( "the part has no measures" );
        }
    }

    bool MxMeasureIterator::isBegin() const
    {
        return getMeasureNumber() == 1;
    }
    bool MxMeasureIterator::isEnd() const
    {
        return myIsEnd;
    }
    bool MxMeasureIterator::isValid() const
    {
        if ( myPart )
        {
            if ( myDoc )
            {
                if ( myMeasure )
                {
                    if ( myPart->getPartwiseMeasureSet().size() > 0 )
                    {
                        if ( ! myIsEnd )
                        {
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }
    bool MxMeasureIterator::next()
    {
        auto iter = getIteratorToCurrentMeasure();
        ++iter;
        if ( iter == myPart->getPartwiseMeasureSet().end() )
        {
            myIsEnd = true;
        }
        else
        {
            myMeasure = *iter;
            myIsEnd = false;
        }
        return ! myIsEnd;
    }
    bool MxMeasureIterator::previous()
    {
        auto iter = getIteratorToCurrentMeasure();
        if ( iter == myPart->getPartwiseMeasureSet().begin() )
        {
            return false;
        }
        --iter;
        myMeasure = *iter;
        return true;
    }
    bool MxMeasureIterator::setBegin()
    {
        if ( !myPart )
        {
            throw std::runtime_error( "invalid ParwisePartPtr" );
        }
        if( myPart->getPartwiseMeasureSet().size() == 0 )
        {
            return false;
        }
        myMeasure = *( myPart->getPartwiseMeasureSet().begin() );
        myIsEnd = false;
        return true;
    }
    void MxMeasureIterator::jump( const Int measureNumber )
    {
        auto beg = myPart->getPartwiseMeasureSet().cbegin();
        auto end = myPart->getPartwiseMeasureSet().cend();
        auto iter = std::find_if( beg, end, [&measureNumber](const PartwiseMeasurePtr& inside){ return measureNumber == std::stoi( inside->getAttributes()->number.getValue() ); } );
        if ( iter == end )
        {
            throw new std::runtime_error( "could not find the measure (index out of range)" );
        }
    }
    Int MxMeasureIterator::getMeasureNumber() const
    {
        checkValid();
        return (Int)std::stoi( myMeasure->getAttributes()->number.getValue() );
    }
    const mx::e::PartwiseMeasurePtr& MxMeasureIterator::operator*() const
    {
        return myMeasure;
    }
    mx::e::PartwiseMeasurePtr MxMeasureIterator::operator*()
    {
        return myMeasure;
    }
    const mx::e::PartwiseMeasurePtr& MxMeasureIterator::operator->() const
    {
        return myMeasure;
    }
    mx::e::PartwiseMeasurePtr MxMeasureIterator::operator->()
    {
        return myMeasure;
    }
    PartwiseMeasureSetIterConst MxMeasureIterator::getIteratorToCurrentMeasure() const
    {
        checkValid();
        auto beg = myPart->getPartwiseMeasureSet().cbegin();
        auto end = myPart->getPartwiseMeasureSet().cend();
        auto current = std::find_if( beg, end, [this](const PartwiseMeasurePtr& inside){ return this->getMeasureNumber() == std::stoi( inside->getAttributes()->number.getValue() ); } );
        if ( current == end )
        {
            throw new std::runtime_error( "getIteratorToCurrentMeasure() encountered a problem" );
        }
        return current;
    }
    void MxMeasureIterator::checkValid() const
    {
        if ( !isValid() )
        {
            throw std::runtime_error( "attempt to do something illegal with an invalid measure iterator" );
        }
    }
    mx::e::PartwiseMeasurePtr getMeasure( const mx::d::DocumentPartwisePtr& doc, const String& partID, const Int measureNumber )
    {
        using namespace mx::e;
        using namespace mx::d;
        
        auto measure = makePartwiseMeasure();
        auto partBeg = doc->getScorePartwise()->getPartwisePartSet().cbegin();
        auto partEnd = doc->getScorePartwise()->getPartwisePartSet().cend();
        auto partIter = std::find_if( partBeg, partEnd, [&partID](const PartwisePartPtr& inside){ return inside->getAttributes()->id.getValue() == partID;});
        if ( partIter == partEnd )
        {
            throw std::runtime_error( "invalid partID" );
        }
        auto part = *partIter;
        if( !part )
        {
            throw std::runtime_error( "part not found" );
        }
        measure = getMeasure( doc, part, measureNumber );
        if ( ! measure )
        {
            throw std::runtime_error( "measure not found" );
        }
        return measure;
    }
    mx::e::PartwiseMeasurePtr getMeasure( const mx::d::DocumentPartwisePtr& doc, const mx::e::PartwisePartPtr& part, const Int measureNumber )
    {
        using namespace mx::e;
        using namespace mx::d;
        
        auto measure = makePartwiseMeasure();
        auto measures = part->getPartwiseMeasureSet();
        auto mBeg = measures.cbegin();
        auto mEnd = measures.cend();
        auto mIter = mBeg;
        Int mCount = 1;
        
        /* find the measure by counting
         assume first measure = m1
         and that all measures increment by 1 */
        for ( ; mIter != mEnd && mCount < measureNumber; ++mIter, ++mCount )
        { ; }
        
        /* assign */
        if ( mIter != mEnd )
        {
            measure = *mIter;
        }
        
        /* verify the measure is correct */
        if ( std::stoi( measure->getAttributes()->number.getValue() ) != measureNumber )
        {
            throw new std::runtime_error( "problem finding measure" );
        }
        
        return measure;
    }
//    void addNote( const mx::e::PartwiseMeasurePtr& measure, const Note& note  )
//    {
//        using namespace mx::d;
//        using namespace mx::e;
//        using namespace mx::t;
//        
//        auto mContents = measure->getMusicDataGroup()->getMusicDataChoiceSet();
//        
//        /* find measure properties if they exist */
//        auto mProperties = makeMusicDataChoice();
//        auto foundProperties = std::find_if( mContents.cbegin(), mContents.cend(), [](const MusicDataChoicePtr& inside){ return inside->getChoice() == MusicDataChoice::Choice::properties; });
//        if ( foundProperties != mContents.end() )
//        {
//            /* properties found */
//            mProperties = *foundProperties;
//            
//        }
//        else
//        {
//            /* properties did not exist and need to be added */
//            mProperties->setChoice( MusicDataChoice::Choice::properties );
//            measure->getMusicDataGroup()->addMusicDataChoice( mProperties );
//        }
//        mProperties->getProperties()->getDivisions()->setValue( PositiveDivisionsValue( note.getDuration().getQuarterDivisions() ) );
//        mProperties->getProperties()->setHasDivisions( true );
//        
//        /* create the note that will be added */
//        MxNote mxnotefactory{ note };
//        auto newNoteDataChoice = mxnotefactory.getMusicDataChoice();
//        measure->getMusicDataGroup()->addMusicDataChoice( newNoteDataChoice );
//    }
    void setMxMeasureClef( const mx::e::PartwiseMeasurePtr& measure, Clf clef )
    {
        using namespace mx::d;
        using namespace mx::e;
        using namespace mx::t;
        
        auto mContents = measure->getMusicDataGroup()->getMusicDataChoiceSet();
        
        /* find measure properties if they exist */
        auto mProperties = makeMusicDataChoice();
        auto foundProperties = std::find_if( mContents.cbegin(), mContents.cend(), [](const MusicDataChoicePtr& inside){ return inside->getChoice() == MusicDataChoice::Choice::properties; });
        if ( foundProperties != mContents.end() )
        {
            /* properties found */
            mProperties = *foundProperties;
            
        }
        else
        {
            /* properties did not exist and need to be added */
            mProperties->setChoice( MusicDataChoice::Choice::properties );
            measure->getMusicDataGroup()->addMusicDataChoice( mProperties );
        }
        auto mxclef = makeMxClef( clef );
        if ( mProperties->getProperties()->getClefSet().size() > 0 )
        {
            mxclef = *( mProperties->getProperties()->getClefSet().cbegin() );
        }
        else
        {
            mProperties->getProperties()->addClef( mxclef );
        }
    }
//    void addRest( const mx::e::PartwiseMeasurePtr& measure, const Duration& duration )
//    {
//        using namespace mx::d;
//        using namespace mx::e;
//        using namespace mx::t;
//        
//        auto mContents = measure->getMusicDataGroup()->getMusicDataChoiceSet();
//        
//        /* find measure properties if they exist */
//        auto mProperties = makeMusicDataChoice();
//        auto foundProperties = std::find_if( mContents.cbegin(), mContents.cend(), [](const MusicDataChoicePtr& inside){ return inside->getChoice() == MusicDataChoice::Choice::properties; });
//        if ( foundProperties != mContents.end() )
//        {
//            /* properties found */
//            mProperties = *foundProperties;
//            
//        }
//        else
//        {
//            /* properties did not exist and need to be added */
//            mProperties->setChoice( MusicDataChoice::Choice::properties );
//            measure->getMusicDataGroup()->addMusicDataChoice( mProperties );
//        }
//        mProperties->getProperties()->getDivisions()->setValue( PositiveDivisionsValue( duration.getQuarterDivisions() ) );
//        mProperties->getProperties()->setHasDivisions( true );
//        auto rest = makeRest();
//        
//        auto mdc = makeMusicDataChoice();
//        mdc->setChoice( MusicDataChoice::Choice::note );
//        mdc->getNote()->getNoteChoice()->setChoice( NoteChoice::Choice::normal );
//        mdc->getNote()->getNoteChoice()->getNormalNoteGroup()->getFullNoteGroup()->getFullNoteTypeChoice()->setChoice( FullNoteTypeChoice::Choice::rest );
//        mdc->getNote()->getNoteChoice()->getNormalNoteGroup()->getDuration()->setValue( PositiveDivisionsValue( duration.getDivisions() ) );
//        mdc->getNote()->getType()->setValue( convert(duration.getDur() ) );
//        mdc->getNote()->setHasType( true );
//        measure->getMusicDataGroup()->addMusicDataChoice( mdc );
//    }
}