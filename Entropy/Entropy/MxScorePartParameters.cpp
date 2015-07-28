#include "MxScorePartParameters.h"

namespace entropy
{
    MxScorePartParameters::MxScorePartParameters()
    :PartID( "" )
    ,PartName( "" )
    ,PartNameDisplay( "" )
    ,PartAbbreviation( "" )
    ,PartAbbreviationDisplay( "" )
    ,PartGroupingString( "" )
    ,ScoreInstrumentID( "" )
    ,InstrumentName( "" )
    ,InstrumentAbbreviation( "" )
    ,InstrumentSound( "" )
    ,SoloOrEnsemble( MxScorePartSoloOrEnsemble::NotSpecified )
    ,MidiDevice( "" )
    ,MidiID( "" )
    ,MidiPort( -1 )
    ,MidiBank( -1 )
    ,MidiChannel( -1 ) /* The midi-channel element specifies a MIDI 1.0 channel numbers ranging from 1 to 16. */
    ,MidiProgram( -1 )
    ,MidiName( "" )
    ,MidiUnpitched( -1 )
    ,MidiVolume( -1 )
    ,MidiPan( -999 )
    ,MidiElevation( -999 )
    ,VirtualInstrumentLibrary( "" )
    ,VirtualInstrumentName( "" )
    {}
    
    MxScorePartParameters::MxScorePartParameters( const InstrumentPtr& instrument )
    :PartID( instrument->getID() )
    ,PartName( instrument->getName() )
    ,PartNameDisplay( "" )
    ,PartAbbreviation( instrument->getAbbreviation() )
    ,PartAbbreviationDisplay( "" )
    ,PartGroupingString( "" )
    ,ScoreInstrumentID( instrument->getID()+"_INSTR" )
    ,InstrumentName( instrument->getName() )
    ,InstrumentAbbreviation( instrument->getAbbreviation() )
    ,InstrumentSound( "" )
    ,SoloOrEnsemble( MxScorePartSoloOrEnsemble::NotSpecified )
    ,MidiDevice( "" )
    ,MidiID( instrument->getID()+"_INSTR" )
    ,MidiPort( -1 )
    ,MidiBank( -1 )
    ,MidiChannel( -1 ) /* The midi-channel element specifies a MIDI 1.0 channel numbers ranging from 1 to 16. */
    ,MidiProgram( -1 )
    ,MidiName( "" )
    ,MidiUnpitched( -1 )
    ,MidiVolume( -1 )
    ,MidiPan( -999 )
    ,MidiElevation( -999 )
    ,VirtualInstrumentLibrary( "" )
    ,VirtualInstrumentName( "" )
    {}
    
    bool MxScorePartParameters::midiDeviveElementHasValues() const
    {
        return MidiID.length() > 0
        || MidiPort > 0
        || MidiDevice.length() > 0;
    }
    bool MxScorePartParameters::midiInstrumentElementHasValues() const
    {
        return MidiBank > 0
        || MidiChannel > 0
        || MidiProgram > 0
        || MidiName.length() > 0
        || MidiUnpitched > 0
        || MidiVolume >= 0
        || ( ( MidiPan > -181 ) && ( MidiPan < 181 ) )
        || ( ( MidiElevation > -181 ) && ( MidiElevation < 181 ) );
    }
    bool MxScorePartParameters::midiGroupHasValues() const
    {
        return midiDeviveElementHasValues() || midiInstrumentElementHasValues();
    }
}