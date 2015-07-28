#include "MxClef.h"

namespace entropy
{
    mx::e::ClefPtr makeMxClef( const Clf clef )
    {
        using namespace mx::e;
        using namespace mx::t;
        using namespace std;
        
        auto c = makeClef();
        switch ( clef )
        {
            case Clf::Treble:
            {
                c->getSign()->setValue( ClefSign::g );
                c->setHasLine( true );
                c->getLine()->setValue( StaffLine( 2 ) );
            }
                break;
            case Clf::Bass:
            {
                c->getSign()->setValue( ClefSign::f );
                c->setHasLine( true );
                c->getLine()->setValue( StaffLine( 4 ) );
            }
                break;
            case Clf::Viola:
            {
                c->getSign()->setValue( ClefSign::c );
                c->setHasLine( true );
                c->getLine()->setValue( StaffLine( 3 ) );
            }
                break;
                
            default:
                break;
        }
        return c;
    }
}