#pragma once
#include "typedefs.h"
#include "Mx/DocumentPartwise.h"
#include "Config.h"
#include "Mx/Elements.h"
#include "InstrumentList.h"

namespace entropy
{
    mx::d::DocumentPartwisePtr createMxDocument( const Config& config, const InstrumentListPtr& instrumentList );
    namespace mxdocfuncs
    {
        void addDocumentMetadata( const mx::d::DocumentPartwisePtr& doc, const Config& config );
        void addMusicXmlVersion( const mx::d::DocumentPartwisePtr& doc, const String& version );
        mx::e::DefaultsPtr addDefaults( const mx::d::DocumentPartwisePtr& doc );
        mx::e::DefaultsPtr addDefaultMillimeters( const mx::e::DefaultsPtr& d, const Float mm );
        mx::e::DefaultsPtr addDefaultTenths( const mx::e::DefaultsPtr& d, const Int tenths );
        mx::e::DefaultsPtr addDefaultPageSize( const mx::e::DefaultsPtr& d, const Int width, const Int height ); /* width, height */
        mx::e::DefaultsPtr addDefaultPageMargins( const mx::e::DefaultsPtr& d, const Int left, const Int right, const Int top, const Int bottom ); /* L, R, Top, Bottom */
        mx::e::DefaultsPtr addDefaultSystemMargins( const mx::e::DefaultsPtr& d, const Int left, const Int right ); /* L, R */
        mx::e::DefaultsPtr addDefaultSystemDistance( const mx::e::DefaultsPtr& d, const Int value ); /* ? */
        mx::e::DefaultsPtr addDefaultTopSystemDistance( const mx::e::DefaultsPtr& d, const Int value ); /* ? */
        mx::e::DefaultsPtr addDefaultStaffDistance( const mx::e::DefaultsPtr& d, const Int value ); /* ? */
        
        void addDocumentVersion( const mx::d::DocumentPartwisePtr& doc );
        void addComposer( const mx::d::DocumentPartwisePtr& doc, const String& composer );
        void addEncodingSoftware( const mx::d::DocumentPartwisePtr& doc, const String& softwareName );
        void addWorkTitle(  const mx::d::DocumentPartwisePtr& doc, const String& workTitle );
        void addParts( const mx::d::DocumentPartwisePtr& doc, const Config& config, const InstrumentListPtr& instrumentList );
        void addMeasures( const mx::d::DocumentPartwisePtr& doc, const Config& config );
        void addTimeSignature( const mx::e::PartwiseMeasurePtr& measure, const Int beats, const Int beattype );
    }
}
/*
<defaults>
<scaling>
<millimeters>5.3516</millimeters>
<tenths>40</tenths>
</scaling>
<page-layout>
<page-height>3227</page-height>
<page-width>2088</page-width>
<page-margins type="both">
<left-margin>190</left-margin>
<right-margin>95</right-margin>
<top-margin>95</top-margin>
<bottom-margin>95</bottom-margin>
</page-margins>
</page-layout>
<system-layout>
<system-margins>
<left-margin>0</left-margin>
<right-margin>0</right-margin>
</system-margins>
<system-distance>163</system-distance>
<top-system-distance>95</top-system-distance>
</system-layout>
<staff-layout>
<staff-distance>80</staff-distance>
</staff-layout>
<appearance>
<line-width type="stem">0.7487</line-width>
<line-width type="beam">5</line-width>
<line-width type="staff">0.7487</line-width>
<line-width type="light barline">0.7487</line-width>
<line-width type="heavy barline">5</line-width>
<line-width type="leger">0.7487</line-width>
<line-width type="ending">0.7487</line-width>
<line-width type="wedge">0.7487</line-width>
<line-width type="enclosure">0.7487</line-width>
<line-width type="tuplet bracket">0.7487</line-width>
<note-size type="grace">60</note-size>
<note-size type="cue">60</note-size>
<distance type="hyphen">120</distance>
<distance type="beam">8</distance>
</appearance>
<music-font font-family="Maestro,engraved" font-size="15.2"/>
<word-font font-family="Times New Roman" font-size="7.6"/>
</defaults>
*/