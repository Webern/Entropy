// Copyright (c) Matthew James Briggs

#include "impl/PugiAttribute.h"
#include "EazyXml/XDoc.h"
#include "impl/PugiAttributeIterImpl.h"

namespace ezx
{
    PugiAttribute::PugiAttribute()
    : myAttribute()
    , myParentElement()
    , myXDoc()
    {

    }


    PugiAttribute::PugiAttribute(
        const pugi::xml_attribute& attribute,
        const pugi::xml_node& parentElement,
        const XDocCPtr& parentXDoc )
    : myAttribute( attribute )
    , myParentElement( parentElement )
    , myXDoc( parentXDoc )
    {

    }


    bool PugiAttribute::getIsNull() const
    {
        auto ptr = myXDoc.lock();

        if( !ptr )
        {
            return true;
        }

        if( myParentElement.type() != pugi::node_element )
        {
            return true;
        }

        return false;
    }


    std::string PugiAttribute::getName() const
    {
        return myAttribute.name();
    }


    std::string PugiAttribute::getValue() const
    {
        return myAttribute.value();
    }


    void PugiAttribute::setName( const std::string& name )
    {
        myAttribute.set_name( name.c_str() );
    }


    void PugiAttribute::setValue( const std::string& value )
    {
        myAttribute.set_value( value.c_str() );
    }
}
