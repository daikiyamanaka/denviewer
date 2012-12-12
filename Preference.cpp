#include "Preference.hpp"

Preference::Preference ( void )
{
        this->setBackgroundColor ( Color3f ( 1,1,1 ) );
        this->setWireColor ( Color3f ( 0,0,0 ) );
        this->setSurfaceColor ( Color3f ( 0.7f, 0, 0 ) );
        this->setVertexColor( Color3f(0 , 0 , 0.7f) );
        this->setWireWidth(1);
        this->setPointSize(1);
        this->setVectorLength(1.0f);
        this->_viewNormal = true;
        this->_vecAtCenter = false;
        this->setRenderingMode ( SURFACE );
        this->setShadingMode( SMOOTH );
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
Preference::setVertexColor(const Color3f c)
{
    this->_point = c;
    return;
}

void
Preference::setWireWidth( const int width )
{
    this->_wire_width = width;
    return;
}

void
Preference::setVectorLength(const float length)
{
    this->_vectorLength = length;
    return;
}

void
Preference::setPointSize(const int size)
{
    this->_point_size = size;
    return;
}

void
Preference::setRenderAtCenter(const bool center)
{
    this->_vecAtCenter = center;
}

void
Preference::setViewNormal(const bool view)
{
    this->_viewNormal = view;
}

void
Preference::setRenderingMode(const int status){
    this->renderingMode = status;
}

/*
void
Preference::setRenderingMode ( const RenderingMode status )
{
        this->_status = status;
}
*/
void
Preference::setShadingMode( const ShadingMode shading)
{
    this->_shading = shading;
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

Color3f
Preference::getVertexColor( void ) const
{
    return _point;
}

int
Preference::getWireWidth( void ) const//<-add
{
    return _wire_width;
}

int
Preference::getPointSize( void ) const
{
    return _point_size;
}

float
Preference::getVectorLength( void ) const
{
    return this->_vectorLength;
}

bool
Preference::getRenderAtCenter( void ) const
{
    return this->_vecAtCenter;
}

bool
Preference::getViewNormal( void ) const
{
    return this->_viewNormal;
}

/*
RenderingMode
Preference::getRenderingMode ( void ) const
{
        return this->_status;
}
*/
int
Preference::getRenderingMode ( void ) const
{
    return this->renderingMode;
}
ShadingMode
Preference::getShadingMode( void ) const
{
    return this->_shading;
}
