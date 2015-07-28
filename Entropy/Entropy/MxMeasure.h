#pragma once
#include "typedefs.h"
#include "Mx/Elements.h"
#include "Mx/DocumentPartwise.h"
#include "Note.h"
#include "Measure.h"
#include "Clef.h"

namespace entropy
{
    void clearMxMeasureAttributes( const mx::e::PartwiseMeasurePtr& m, bool retainMeasureNumber = true );
    void clearMxMeasureContents( const mx::e::PartwiseMeasurePtr& m );
    void fillMxMeasure( const mx::e::PartwiseMeasurePtr& mxmeasure, const Measure& measure );
    void fillMxMeasure( const mx::e::PartwiseMeasurePtr& mxmeasure, const Measure& measure, Int meausreNumber );
    void setMxMeasureDivisions( const mx::e::PartwiseMeasurePtr& m, const Int divisions );
    void setMxMeasureTimeSignature( const mx::e::PartwiseMeasurePtr& m, const TimeSignature& timeSignature );
    void setMxMeasureClef( const mx::e::PartwiseMeasurePtr& mxmeasure, Clf clef );
    
    class MxMeasureIterator
    {
    public:
        MxMeasureIterator( mx::d::DocumentPartwisePtr& doc, mx::e::PartwisePartPtr& part );
        bool isBegin() const;
        bool isEnd() const;
        bool isValid() const;
        bool next();
        bool previous();
        bool setBegin();
        void jump( const Int measureNumber );
        Int getMeasureNumber() const;
        const mx::e::PartwiseMeasurePtr& operator*() const;
        mx::e::PartwiseMeasurePtr operator*();
        const mx::e::PartwiseMeasurePtr& operator->() const;
        mx::e::PartwiseMeasurePtr operator->();
    private:
        mx::d::DocumentPartwisePtr myDoc;
        mx::e::PartwisePartPtr myPart;
        mx::e::PartwiseMeasurePtr myMeasure;
        bool myIsEnd;
        mx::e::PartwiseMeasureSetIterConst getIteratorToCurrentMeasure() const;
        void checkValid() const;
        
    };
    mx::e::PartwiseMeasurePtr getMeasure( const mx::d::DocumentPartwisePtr& doc, const String& partID, const Int measureNumber );
    mx::e::PartwiseMeasurePtr getMeasure( const mx::d::DocumentPartwisePtr& doc, const mx::e::PartwisePartPtr& part, const Int measureNumber );
    void addNote( const mx::e::PartwiseMeasurePtr& measure, const Note& note  );
    void addRest( const mx::e::PartwiseMeasurePtr& measure, const Duration& duration );
}