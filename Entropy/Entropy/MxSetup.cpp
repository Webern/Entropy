#include "MxSetup.h"
#include "defaults.h"
#include "Mx/Elements.h"
#include "Instrument.h"
#include "MxPartGroup.h"
#include "MxScorePart.h"
#include "MxScorePartParameters.h"
#include "MxScorePart.h"
#include <string>

namespace entropy
{
    mx::d::DocumentPartwisePtr createMxDocument( const Config& config, const InstrumentListPtr& instrumentList )
    {
        auto doc = mx::d::makeDocumentPartwise();
        mxdocfuncs::addDocumentMetadata( doc, config );
        mxdocfuncs::addDefaults( doc );
        mxdocfuncs::addParts( doc, config, instrumentList );
        mxdocfuncs::addMeasures( doc, config );
        return doc;
    }
    
    namespace mxdocfuncs
    {
        void addDocumentMetadata( const mx::d::DocumentPartwisePtr& doc, const Config& config )
        {
            mxdocfuncs::addMusicXmlVersion( doc, "3.0" );
            mxdocfuncs::addComposer( doc, config.getComposer() );
            mxdocfuncs::addEncodingSoftware( doc, appName() );
            mxdocfuncs::addWorkTitle( doc, config.getTitle() );
        }
        
        void addMusicXmlVersion( const mx::d::DocumentPartwisePtr& doc, const String& version )
        {
            auto score = doc->getScorePartwise();
            score->getAttributes()->hasVersion = true;
            score->getAttributes()->version = mx::t::XsToken( version );
        }
        mx::e::DefaultsPtr addDefaults( const mx::d::DocumentPartwisePtr& doc )
        {
            auto def = mx::e::makeDefaults();
            doc->getScorePartwise()->getScoreHeaderGroup()->setDefaults( def );
            doc->getScorePartwise()->getScoreHeaderGroup()->setHasDefaults( true );
            addDefaultMillimeters( def, 5.3516 );
            addDefaultTenths( def, 40 );
            addDefaultPageSize( def, 2088, 3227); /* width, height */
            addDefaultPageMargins( def, 95, 95, 95, 95 ); /* L, R, Top, Bottom */
            addDefaultSystemMargins( def, 95, 0 ); /* L, R */
            addDefaultSystemDistance( def, 163 ); /* ? */
            addDefaultTopSystemDistance( def, 120 ); /* ? */
            addDefaultStaffDistance( def, 105 ); /* ? */
            
            return def;
        }
        mx::e::DefaultsPtr addDefaultMillimeters( const mx::e::DefaultsPtr& d, const Float mm )
        {
            d->setHasScaling( true );
            d->getScaling()->getMillimeters()->setValue( mx::t::MillimetersValue( mm ) );
            return d;
        }
        mx::e::DefaultsPtr addDefaultTenths( const mx::e::DefaultsPtr& d, const Int tenths )
        {
            d->setHasScaling( true );
            d->getScaling()->getTenths()->setValue( mx::t::TenthsValue( tenths ) );
            return d;
        }
        mx::e::DefaultsPtr addDefaultPageSize( const mx::e::DefaultsPtr& d, const Int width, const Int height )
        {
            d->setHasAppearance( true );
            d->getLayoutGroup()->setHasPageLayout( true );
            d->getLayoutGroup()->getPageLayout()->getPageWidth()->setValue( mx::t::TenthsValue( width ) );
            d->getLayoutGroup()->getPageLayout()->getPageHeight()->setValue( mx::t::TenthsValue( height ) );
            return d;
        }
        mx::e::DefaultsPtr addDefaultPageMargins( const mx::e::DefaultsPtr& d, const Int left, const Int right, const Int top, const Int bottom )
        {
            d->setHasAppearance( true );
            d->getLayoutGroup()->setHasPageLayout( true );
            auto margins = mx::e::makePageMargins();
            margins->getAttributes()->type = mx::t::MarginType::both;
            margins->getTopMargin()->setValue( mx::t::TenthsValue( top ) );
            margins->getBottomMargin()->setValue( mx::t::TenthsValue( bottom ) );
            margins->getLeftMargin()->setValue( mx::t::TenthsValue( left ) );
            margins->getRightMargin()->setValue( mx::t::TenthsValue( right ) );
            d->getLayoutGroup()->getPageLayout()->addPageMargins( margins );
            return d;
        }
        mx::e::DefaultsPtr addDefaultSystemMargins( const mx::e::DefaultsPtr& d, const Int left, const Int right )
        {
            d->getLayoutGroup()->setHasSystemLayout( true );
            d->getLayoutGroup()->getSystemLayout()->setHasSystemMargins( true );
            auto margins = d->getLayoutGroup()->getSystemLayout()->getSystemMargins();
            margins->getLeftMargin()->setValue( mx::t::TenthsValue( left ) );
            margins->getRightMargin()->setValue( mx::t::TenthsValue( right ) );
            return d;
        }
        mx::e::DefaultsPtr addDefaultSystemDistance( const mx::e::DefaultsPtr& d, const Int value )
        {
            d->getLayoutGroup()->setHasSystemLayout( true );
            auto layout = d->getLayoutGroup()->getSystemLayout();
            layout->setHasSystemDistance( true );
            layout->getSystemDistance()->setValue( mx::t::TenthsValue( value ) );
            return d;
        }
        mx::e::DefaultsPtr addDefaultTopSystemDistance( const mx::e::DefaultsPtr& d, const Int value )
        {
            d->getLayoutGroup()->setHasSystemLayout( true );
            auto layout = d->getLayoutGroup()->getSystemLayout();
            layout->setHasTopSystemDistance( true );
            layout->getTopSystemDistance()->setValue( mx::t::TenthsValue( value ) );
            return d;
        }
        mx::e::DefaultsPtr addDefaultStaffDistance( const mx::e::DefaultsPtr& d, const Int value )
        {
            auto staffLayout = mx::e::makeStaffLayout();
            staffLayout->setHasStaffDistance( true );
            staffLayout->getStaffDistance()->setValue( mx::t::TenthsValue( value ) );
            d->getLayoutGroup()->addStaffLayout( staffLayout );
            return d;
        }
        void addComposer( const mx::d::DocumentPartwisePtr& doc, const String& composerName )
        {
            auto score = doc->getScorePartwise();
            auto header = score->getScoreHeaderGroup();
            auto composer = mx::e::makeCreator();
            auto ident = header->getIdentification();
            composer->getAttributes()->hasType = true;
            composer->getAttributes()->type = mx::t::XsToken( "composer" );
            composer->setValue( composerName );
            ident->addCreator( composer );
            header->setHasIdentification( true );
        }
        
        void addEncodingSoftware( const mx::d::DocumentPartwisePtr& doc, const String& softwareName )
        {
            auto score = doc->getScorePartwise();
            auto header = score->getScoreHeaderGroup();
            auto ident = header->getIdentification();
            ident->getEncoding()->setChoice( mx::e::Encoding::Choice::software );
            ident->getEncoding()->getSoftware()->setValue( mx::t::XsString( softwareName ) );
            ident->setHasEncoding( true );
            header->setHasIdentification( true );
        }
        
        void addWorkTitle(  const mx::d::DocumentPartwisePtr& doc, const String& workTitle )
        {
            auto score = doc->getScorePartwise();
            auto header = score->getScoreHeaderGroup();
            header->setHasWork( true );
            header->getWork()->setHasWorkTitle( true );
            header->getWork()->getWorkTitle()->setValue( mx::t::XsString( workTitle ) );
        }
        
        void addParts( const mx::d::DocumentPartwisePtr& doc, const Config& config, const InstrumentListPtr& instrumentList )
        {
            auto score = doc->getScorePartwise();
            auto partList = score->getScoreHeaderGroup()->getPartList();
            auto grpBeg = instrumentList->getScoreGroups().cbegin();
            auto grpEnd = instrumentList->getScoreGroups().cend();
            int grpNumber = 1;
            for ( auto grp = grpBeg; grp != grpEnd; ++grp )
            {
                if ( grp == grpBeg )
                {
                    /* add the start of the very first group */
                    partList->addPartGroup( makePartGroupStart( grpNumber ) );
                    
                }
                else
                {
                    /* this is not the very first group,
                     but is a start of a subsequent score group */
                    partList->addPartGroupOrScorePart( makePartGroupStart( grpNumber, true ) );
                }
                auto iBeg = (*grp)->getInstruments().cbegin();
                auto iEnd = (*grp)->getInstruments().cend();
                for ( auto i=iBeg; i != iEnd; ++i )
                {
                    auto mxParams = MxScorePartParameters{ (*i) };
                    auto mxPart = MxScorePart{ mxParams };
                    if ( grp == grpBeg && i == iBeg )
                    {
                        
                        partList->setScorePart( mxPart.makeScorePart() );
                        
                        /* add the first part */
                        auto firstPart = score->getPartwisePart( score->getPartwisePartSet().begin() );
                        firstPart->getAttributes()->id = mx::t::XsID( (*i)->getID() );
                    }
                    else
                    {
                        
                        
                        
                        partList->addPartGroupOrScorePart( mxPart.makePartGroupOrScorePart() );
                        auto newPart = mx::e::makePartwisePart();
                        newPart->getAttributes()->id = mx::t::XsID( (*i)->getID() );
                        score->addPartwisePart( newPart );
                    }
                }
                /* close the group */
                partList->addPartGroupOrScorePart( makePartGroupStop( grpNumber, true ) );
                ++grpNumber;
            }
        }
        
        void addMeasures( const mx::d::DocumentPartwisePtr& doc, const Config& config )
        {
            auto total = config.getMeasureCount();
            for ( auto part = doc->getScorePartwise()->getPartwisePartSet().begin();
                 part != doc->getScorePartwise()->getPartwisePartSet().end();
                 ++part )
            {
                for ( Int m = 1; m <= total; ++m )
                {
                    mx::e::PartwiseMeasurePtr measure;

                    /* because we start with an existing measure
                     which cannot be removed... */
                    if ( m == 1 )
                    {
                        measure = (*(*part)->getPartwiseMeasureSet().begin());
                    }
                    else
                    {
                        measure = mx::e::makePartwiseMeasure();
                        (*part)->addPartwiseMeasure( measure );
                    }
                    measure->getAttributes()->number = mx::t::XsToken( std::to_string( m ) );
                    addTimeSignature( measure, config.getBeatsPerMeasure(), 4 );
                }
            }
        }
        void addTimeSignature( const mx::e::PartwiseMeasurePtr& measure, const Int beats, const Int beattype )
        {
            auto musicdata = measure->getMusicDataGroup();
            auto musicdatachoice = mx::e::makeMusicDataChoice();
            musicdatachoice->setChoice( mx::e::MusicDataChoice::Choice::properties );
            musicdata->addMusicDataChoice( musicdatachoice );
            auto measureproperties = musicdatachoice->getProperties();
            auto time = mx::e::makeTime();
            auto timeChoice = mx::e::makeTimeChoice();
            time->setTimeChoice( timeChoice );
            timeChoice->setChoice( mx::e::TimeChoice::Choice::timeSignature );
            timeChoice->getTimeSignature()->getBeats()->setValue( mx::t::XsString( std::to_string( beats ) ) );
            timeChoice->getTimeSignature()->getBeatType()->setValue( mx::t::XsString( std::to_string( beattype ) ) );
            measureproperties->addTime( time );
        }
    }
}