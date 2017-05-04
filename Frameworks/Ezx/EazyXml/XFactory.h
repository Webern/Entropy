// Copyright (c) Matthew James Briggs

#pragma once

#include "EazyXml/XDoc.h"
#include <memory>

namespace ezx
{
    class XFactory
    {
    public:
        static XDocPtr makeXDoc();
        static XElementPtr makeXElement();
    };
}
