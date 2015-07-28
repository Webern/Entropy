#pragma once
#include <iostream>
#include <string>
#include "typedefs.h"
#include "Mx/Elements.h"
#include "Pitch.h"
#include "Instrument.h"

namespace entropy
{
    enum class MxScorePartSoloOrEnsemble
    {
        Solo = 0,
        Ensemble = 1,
        NotSpecified = 2
    };
    struct MxScorePartParameters
    {
    public:
        MxScorePartParameters();
        MxScorePartParameters( const InstrumentPtr& instrument );
        bool midiDeviveElementHasValues() const;
        bool midiInstrumentElementHasValues() const;
        bool midiGroupHasValues() const;
        
        /* Part */
        String PartID;
        String PartName;
        String PartNameDisplay;
        String PartAbbreviation;
        String PartAbbreviationDisplay;
        String PartGroupingString; /* The group element allows the use of different versions of the part for different purposes. Typical values include score, parts, sound, and data. Ordering information that is directly encoded in MuseData can be derived from the ordering within a MusicXML score or opus. */
        
        /* Score Instrument */
        String ScoreInstrumentID;
        String InstrumentName;
        String InstrumentAbbreviation;
        String InstrumentSound; /* The instrument-sound element describes the default timbre of the score-instrument. This description is independent of a particular virtual or MIDI instrument specification and allows playback to be shared more easily between applications and libraries. */
        MxScorePartSoloOrEnsemble SoloOrEnsemble; /* InstrumentSoloOrEnsemble */
        
        /* MidiDevice */
        String MidiDevice; /* MidiDevice The midi-device type corresponds to the DeviceName meta event in Standard MIDI Files. Unlike the DeviceName meta event, there can be multiple midi-device elements per MusicXML part starting in MusicXML 3.0.  If missing, the device assignment affects all score-instrument elements in the score-part. */
        String MidiID; /*  The optional id attribute refers to the score-instrument assigned to this device.  */
        Int MidiPort; /* The optional port attribute is a number from 1 to 16 that can be used with the unofficial MIDI port (or cable) meta event. */
        
        /* MidiInstrument */
        Int MidiBank; /* The midi-bank element specified a MIDI 1.0 bank number ranging from 1 to 16,384. */
        Int MidiChannel; /* The midi-channel element specifies a MIDI 1.0 channel numbers ranging from 1 to 16. */
        Int MidiProgram; /* The midi-program element specifies a MIDI 1.0 program number ranging from 1 to 128. */
        String MidiName; /* The midi-name element corresponds to a ProgramName meta-event within a Standard MIDI File. */
        Int MidiUnpitched; /* For unpitched instruments, the midi-unpitched element specifies a MIDI 1.0 note number ranging from 1 to 128. It is usually used with MIDI banks for percussion. Note that MIDI 1.0 note numbers are generally specified from 0 to 127 rather than the 1 to 128 numbering used in this element. */
        Float MidiVolume; /* The volume element value is a percentage of the maximum ranging from 0 to 100, with decimal values allowed. This corresponds to a scaling value for the MIDI 1.0 channel volume controller. */
        Float MidiPan; /* The pan and elevation elements allow placing of sound in a 3-D space relative to the listener. Both are expressed in degrees ranging from -180 to 180. For pan, 0 is straight ahead, -90 is hard left, 90 is hard right, and -180 and 180 are directly behind the listener. */
        Float MidiElevation; /* The elevation and pan elements allow placing of sound in a 3-D space relative to the listener. Both are expressed in degrees ranging from -180 to 180. For elevation, 0 is level with the listener, 90 is directly above, and -90 is directly below. */
        
        /* Virtual Instrument */
        String VirtualInstrumentLibrary;
        String VirtualInstrumentName;
        /*
         myParams.MidiID.length() > 0 ||
         ( ( myParams.MidiPort > 0 )&&( myParams.MidiPort < 17 ) ) ||
         ( (myParams.MidiChannel > 0)&&(myParams.MidiChannel < 17) ) ||
         myParams.MidiName.length() > 0 ||
         myParams.MidiBank > 0 ||
         myParams.MidiProgram > 0 ||
         myParams.MidiUnpitched > 0 ||
         myParams.MidiVolume > 0 ||
         ( (myParams.MidiPan >= -181) && (myParams.MidiPan) <= 181 ) ||
         ( (myParams.MidiElevation >= -181) && (myParams.MidiElevation <= 181) )*/
    };
}