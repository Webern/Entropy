#include "mainSandbox.h"
#include "Measure.h"
#include "Note.h"
#include "Duration.h"
#include "MxMeasure.h"
#include <fstream>
#include "Quantizer.h"
#include <cstdlib>
#include <string>
#include "Rand.h"
#include "RhythmList.h"
#include "goUp.h"
#include "skipSize.h"
#include "writeMxMeasures.h"
#include "setTupletCountdown.h"
#include "isDurationOk.h"
#include "setDuration.h"
#include "initializePitch.h"
#include "setPitch.h"
#include "rest.h"

namespace entropy
{
    using namespace std;
    
    void mainSandbox( const mx::d::DocumentPartwisePtr& doc, const Config& conf, const Numbers& quanta, const Scales& scales, const InstrumentListPtr& instrumentList )
    {
        
        auto rhythmBook = makeRhythmBook();
        auto grpBeg = instrumentList->getLogicGroups().begin();
        auto grpEnd = instrumentList->getLogicGroups().end();
        auto grpNumber = 0;
        auto grpItr = grpBeg;
        Rand dirRand{ 0, 12 };
        for ( ; grpItr != grpEnd; ++grpItr )
        {
            auto grp = *grpItr;
            auto instrBeg = grp->getInstruments().begin();
            auto instrEnd = grp->getInstruments().end();
            auto instrItr = instrBeg;
            for ( ; instrItr != instrEnd; ++instrItr )
            {
                auto instr = *instrItr;
                Int currScaleDegree = 0;
                Int prevScaleDegree = 0;
                Pitch currPitch;
                Pitch prevPitch;
                Int currOctave = 0;
                Int prevOctave = 0;
                Duration currDur;
                Duration prevDur;
                Int tupletCountdown = 0;

                for( Int measureNumber = 1; measureNumber <= conf.getMeasureCount(); ++measureNumber )
                {
                    bool safetyTripped = false;
                    Measure newMeasure{ instr, TimeSignature{ conf.getBeatsPerMeasure(), 4 } };
                    while ( newMeasure.getRemainingDivisions() > 0 )
                    {
                        Int e = quanta.getValueInt( measureNumber-1, grpNumber );
                        auto scale = scales[e];
                        Rand scalerand{ 0, (Int)(scale.size()-1) };

                        
                        const auto rhythmList = rhythmBook[e];
                        Rand rhythrand{ 0, (Int)(rhythmList.size()-1) };
                        if ( measureNumber == 1 )
                        {
                            currPitch = prevPitch = initializePitch( scale, scalerand, instr, e );
                        }
                        else
                        {
                            setPitch( scalerand, scale, instr, e, dirRand, currPitch, prevPitch );
                        }
                        
                        /* find an appropriate durations */
                        currDur = setDuration( prevDur, rhythrand, rhythmList, newMeasure, tupletCountdown, safetyTripped );

                        Note newNote{ currPitch, currDur };
                        prevPitch = currPitch;
                        prevScaleDegree = currScaleDegree;
                        prevOctave = currOctave;
                        newNote.setIsRest( rest( e, dirRand ) );
                        if ( ! instr->getRange().isInRange( newNote.getPitch() ) )
                        {
                            std::cout << "out of range note encountered: " << instr->getID() << " ";
                            std::cout << newNote.getPitch() << " measure " << measureNumber << std::endl;
                        }
                        if ( newMeasure.canAdd( newNote ) )
                        {
                            newMeasure.addNote( newNote );
                        }
                        else
                        {
                            break;
                        }
                    }
                    instr->addMeasure( newMeasure );
                } // for each meausre
            } // for each instrument
            ++grpNumber;
        } // for each group
    
        /* now add the measures to the doc */
        writeMxMeasures( doc, instrumentList );
    }
}