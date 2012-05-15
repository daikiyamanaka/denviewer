#include "Preference.hpp"

Preference::Preference ( void )
{
        this->setBackgroundColor ( Color3f ( 1,1,1 ) );
        this->setWireColor ( Color3f ( 0,0,0 ) );
        this->setPointcloudColor ( Color3f ( 0,0,0.5f) );
        this->setSurfaceColor ( Color3f ( 0.7f, 0, 0 ) );
        this->setRenderingMode ( SURFACE );
        this->_pointCloudRendering = false;
        this->_surfaceRendering = true;
        this->_wireRendering = false;
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
Preference::setPointcloudColor ( const Color3f c)
{
        this->_pointcloud = c;
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
Color3f
Preference::getPointcloudColor ( void ) const
{
        return _pointcloud;
}

RenderingMode
Preference::getRenderingMode ( void ) const
{
        return this->_status;
}

void
Preference::setSurfaceRendering(const bool b)
{
    this->_surfaceRendering = b;
}

void
Preference::setWireRendering(const bool b)
{
    this->_wireRendering = b;
}
void
Preference::setPointCloudRendering(const bool b)
{
    this->_pointCloudRendering = b;
}

bool
Preference::getPointCloudRenderingMode() const
{
    return this->_pointCloudRendering;
}

bool
Preference::getSurfaceRenderingMode() const
{
    return this->_surfaceRendering;
}

bool
Preference::getWireRenderingMode() const
{
    return this->_wireRendering;
}


