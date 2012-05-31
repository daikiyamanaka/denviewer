#include "Preference.hpp"

Preference::Preference ( void )
{
        this->setBackgroundColor ( Color3f ( 1,1,1 ) );
        this->setWireColor ( Color3f ( 0,0,0 ) );
        this->setSurfaceColor ( Color3f ( 0.7f, 0, 0 ) );
        this->setWireWidth(1);
        this->setRenderingMode ( SURFACE );
        return;
}
Preference:: ~Preference ( void )
{
        return;
}

void
Preference::setBackgroundColor ( const Color3f c )
{
        this->_background = c;
        return;
}

void
Preference::setWireColor ( const Color3f c )
{
        this->_wire = c;
        return;
}

void
Preference::setSurfaceColor ( const Color3f c )
{
        this->_surface = c;
        return;
}

void
Preference::setWireWidth( const int width )
{
    this->_wire_width = width;
    return;
}

void
Preference::setRenderingMode ( const RenderingMode status )
{
        this->_status = status;
}
Color3f
Preference::getBackgroundColor ( void ) const
{
        return _background;
}
Color3f
Preference::getWireColor ( void ) const
{
        return _wire;
}
Color3f
Preference::getSurfaceColor ( void ) const
{
        return _surface;
}

int
Preference::getWireWidth( void ) const//<-add
{
    return _wire_width;
}

RenderingMode
Preference::getRenderingMode ( void ) const
{
        return this->_status;
}
