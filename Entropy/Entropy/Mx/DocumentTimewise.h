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
        class DocumentPartwise;
        using DocumentPartwisePtr = std::shared_ptr<DocumentPartwise>;
        
        class DocumentTimewise;
        using DocumentTimewisePtr = std::shared_ptr<DocumentTimewise>;
        inline DocumentTimewisePtr makeDocumentTimewise() { return std::make_shared<DocumentTimewise>(); }
        
        class DocumentTimewise
        {
        public:
            DocumentTimewise();
            /* _________ ScoreTimewise minOccurs = 1, maxOccurs = 1 _________ */
            e::ScoreTimewisePtr getScoreTimewise() const;
            void setScoreTimewise( const e::ScoreTimewisePtr& value );
            std::ostream& toStream( std::ostream& os ) const;
            static DocumentTimewisePtr convert( const DocumentPartwisePtr& input );
        private:
            mx::e::ScoreTimewisePtr myScoreTimewise;
        };
    }
}