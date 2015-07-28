/* MusicXML Class Library v0.1.0
 Copyright (c) 2015 by Matthew James Briggs */

#pragma once
#include <iostream>
#include <memory>
#include "Elements.h"

namespace mx
{
    namespace d
    {
        class DocumentTimewise;
        using DocumentTimewisePtr = std::shared_ptr<DocumentTimewise>;
        
        class DocumentPartwise;
        using DocumentPartwisePtr = std::shared_ptr<DocumentPartwise>;
        inline DocumentPartwisePtr makeDocumentPartwise() { return std::make_shared<DocumentPartwise>(); }
        class DocumentPartwise
        {
        public:
            DocumentPartwise();
            /* _________ ScorePartwise minOccurs = 1, maxOccurs = 1 _________ */
            e::ScorePartwisePtr getScorePartwise() const;
            void setScorePartwise( const e::ScorePartwisePtr& value );
            std::ostream& toStream( std::ostream& os ) const;
            static DocumentPartwisePtr convert( const DocumentTimewisePtr& input );
        private:
            mx::e::ScorePartwisePtr myScorePartwise;
        };
    }
}