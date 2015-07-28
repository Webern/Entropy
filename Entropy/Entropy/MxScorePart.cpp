#include "MxScorePart.h"
#include <sstream>

namespace entropy
{
    MxScorePart::MxScorePart( const MxScorePartParameters& params )
    :myParams( params )
    {}
    
    MxScorePart::MxScorePart()
    :myParams()
    {}
    
    MxScorePartParameters MxScorePart::getParameters() const
    {
        return myParams;
    }
    void MxScorePart::setParameters( const MxScorePartParameters& params )
    {
        myParams = params;
    }
    
    mx::e::ScorePartPtr MxScorePart::makeScorePart() const
    {
        auto p = mx::e::makeScorePart();

        if ( myParams.PartID.length() > 0 )
        {
            p->getAttributes()->id = mx::t::XsID( myParams.PartID );
        }
        
        if ( myParams.PartName.length() > 0 )
        {
            p->getPartName()->setValue( mx::t::XsString( myParams.PartName ) );
        }
        
        if ( myParams.PartAbbreviation.length() > 0 )
        {
            p->getPartAbbreviation()->setValue( mx::t::XsString( myParams.PartAbbreviation ) );
            p->setHasPartAbbreviation( true );
        }
        if ( myParams.PartNameDisplay.length() > 0 )
        {
            throw new std::runtime_error( "Feature not supported." );
            
        }
        if ( myParams.PartAbbreviationDisplay.length() > 0 )
        {
            throw new std::runtime_error( "Feature not supported." );
        }
        if ( myParams.PartGroupingString.length() > 0 )
        {
            auto grpstr = mx::e::makeGroup();
            grpstr->setValue( myParams.PartGroupingString );
            p->addGroup( grpstr );
        }
        auto si = mx::e::makeScoreInstrument();
        if ( myParams.ScoreInstrumentID.length() > 0 ||
            myParams.InstrumentName.length() > 0 ||
            myParams.InstrumentAbbreviation.length() ||
            myParams.InstrumentSound.length() > 0 ||
            myParams.SoloOrEnsemble != MxScorePartSoloOrEnsemble::NotSpecified )
        {
            p->addScoreInstrument( si );
        }
        
        if ( myParams.ScoreInstrumentID.length() > 0 )
        {
            si->getAttributes()->id = mx::t::XsID( myParams.ScoreInstrumentID );
        }
        
        if ( myParams.InstrumentName.length() > 0 )
        {
            si->getInstrumentName()->setValue( mx::t::XsString( myParams.InstrumentName ) );
        }
        
        if ( myParams.InstrumentAbbreviation.length() > 0 )
        {
            si->getInstrumentAbbreviation()->setValue( mx::t::XsString( myParams.InstrumentAbbreviation ) );
            si->setHasInstrumentAbbreviation( true );
        }
        
        if ( myParams.InstrumentSound.length() != 0 )
        {
            si->getInstrumentSound()->setValue( mx::t::XsString( myParams.InstrumentSound ) );
            si->setHasInstrumentSound( true );
        }
        auto midiDevice = mx::e::makeMidiDevice();
        auto midiInstrument = mx::e::makeMidiInstrument();
        auto midiGroup = mx::e::makeMidiDeviceInstrumentGroup();
        
        if ( myParams.midiGroupHasValues() )
        {
            p->addMidiDeviceInstrumentGroup( midiGroup );
            if ( myParams.midiDeviveElementHasValues() )
            {
                midiGroup->setHasMidiDevice( true );
                midiGroup->setMidiDevice( midiDevice );
                if ( myParams.MidiID.length() > 0 )
                {
                    midiDevice->getAttributes()->id = mx::t::XsIDREF( myParams.MidiID );
                    midiDevice->getAttributes()->hasId = true;
                }
                if ( myParams.MidiPort > 0 )
                {
                    midiDevice->getAttributes()->port = mx::t::Midi16( myParams.MidiPort );
                    midiDevice->getAttributes()->hasPort = true;
                }
                if ( myParams.MidiDevice.length() > 0 )
                {
                    midiDevice->setValue( mx::t::XsString( myParams.MidiDevice ) );
                }
            }
            if ( myParams.midiInstrumentElementHasValues() )
            {
                midiGroup->setHasMidiInstrument( true );
                midiGroup->setMidiInstrument( midiInstrument );
                if ( myParams.MidiBank > 0 )
                {
                    midiInstrument->setHasMidiBank( true );
                    midiInstrument->getMidiBank()->setValue(mx::t::Midi16384( myParams.MidiBank ) );
                }
                if ( myParams.MidiChannel > 0 )
                {
                    midiInstrument->setHasMidiChannel( true );
                    midiInstrument->getMidiChannel()->setValue(mx::t::Midi16( myParams.MidiChannel ) );
                }
                if ( myParams.MidiProgram > 0 )
                {
                    midiInstrument->setHasMidiProgram( true );
                    midiInstrument->getMidiProgram()->setValue( mx::t::Midi128( myParams.MidiProgram ) );
                }
                if ( myParams.MidiName.length() > 0 )
                {
                    midiInstrument->setHasMidiName( true );
                    midiInstrument->getMidiName()->setValue( mx::t::XsString( myParams.MidiName ) );
                }
                if ( myParams.MidiUnpitched > 0 )
                {
                    midiInstrument->setHasMidiUnpitched( true );
                    midiInstrument->getMidiUnpitched()->setValue( mx::t::Midi128( myParams.MidiUnpitched ) );
                }
                if ( myParams.MidiVolume >= 0 )
                {
                    midiInstrument->setHasVolume( true );
                    midiInstrument->getVolume()->setValue( mx::t::Percent( myParams.MidiVolume ));
                }
                if ( myParams.MidiPan > -181 && myParams.MidiPan < 181 )
                {
                    midiInstrument->setHasPan( true );
                    midiInstrument->getPan()->setValue( mx::t::RotationDegrees( myParams.MidiPan ) );
                }
                if ( myParams.MidiElevation > -181 && myParams.MidiElevation < 181 )
                {
                    midiInstrument->setHasElevation( true );
                    midiInstrument->getElevation()->setValue( mx::t::RotationDegrees( myParams.MidiElevation ) );
                }
            }
            if ( myParams.VirtualInstrumentLibrary.length() > 0 ||
                myParams.VirtualInstrumentName.length() > 0 )
            {
                auto vi = mx::e::makeVirtualInstrument();
                si->setHasVirtualInstrument( true );
                si->setVirtualInstrument( vi );
                if ( myParams.VirtualInstrumentName.length() )
                {
                    vi->setHasVirtualName( true );
                    vi->getVirtualName()->setValue( mx::t::XsString( myParams.VirtualInstrumentName ) );
                }
                if ( myParams.VirtualInstrumentLibrary.length() > 0 )
                {
                    vi->setHasVirtualLibrary( true );
                    vi->getVirtualLibrary()->setValue( mx::t::XsString( myParams.VirtualInstrumentLibrary ) );
                }
            }
        }
        return p;
    }
    mx::e::PartGroupOrScorePartPtr MxScorePart::makePartGroupOrScorePart() const
    {
        auto pgosp = mx::e::makePartGroupOrScorePart();
        pgosp->setChoice( mx::e::PartGroupOrScorePart::Choice::scorePart );
        pgosp->setScorePart( makeScorePart() );
        return pgosp;
    }
    
    void addScorePartToPartList( const mx::e::PartListPtr& partList, const Instrument& instrument, bool isFirstInstrument )
    {
        auto part = mx::e::makePartGroupOrScorePart();
        auto scorePartChoice = mx::e::PartGroupOrScorePart::Choice::scorePart;
        part->setChoice( scorePartChoice );
        //part->setScorePart( instrument.makeScorePart() );
        if ( isFirstInstrument )
        {
            partList->setScorePart( part->getScorePart() );
        }
        else
        {
            partList->addPartGroupOrScorePart( part );
        }
    }
    
    
}