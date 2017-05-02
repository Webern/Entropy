// Copyright (c) Matthew James Briggs

#include "EazyXml/XFactory.h"
#include "impl/PugiDoc.h"
#include "impl/PugiElement.h"

namespace ezx
{
    XDocPtr XFactory::makeXDoc()
    {
        return XDocPtr{ new PugiDoc{} };
    }
    
    XElementPtr XFactory::makeXElement()
    {
        return XElementPtr{ new PugiElement{} };
    }
}
