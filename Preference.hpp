#ifndef __PREFERENCE_HPP__
#define __PREFERENCE_HPP__ 1

#include <cstdlib>
#include "Color3f.hpp"
enum RenderingMode {
        WIRE = 0x01,
        SURFACE = 0x02,
        POINTCLOUD = 0x04
};

enum ShadingMode {
    FLAT = 0,
    SMOOTH = 1
};

class Preference
{
private:
        Color3f _background;
        Color3f _wire;
        Color3f _surface;
        Color3f _point;

        int _wire_width;
        int _point_radius;

        //RenderingMode _status;
        int renderingMode;
        ShadingMode _shading;

public:
        Preference ( void ) ;
        virtual ~Preference ( void );

        void setBackgroundColor ( const Color3f c );
        void setWireColor ( const Color3f c );
        void setSurfaceColor ( const Color3f c );
        void setVertexColor ( const Color3f c );
        void setWireWidth( const int width );
        void setPointRadius( const int radius );
        //void setRenderingMode ( const RenderingMode status );
        void setRenderingMode(const int status);
        void setShadingMode( const ShadingMode shading);

        Color3f getBackgroundColor ( void ) const;
        Color3f getWireColor ( void ) const;
        Color3f getSurfaceColor ( void ) const;
        Color3f getVertexColor ( void ) const;
        int getWireWidth( void ) const;
        int getPointRadius( void ) const;
        //RenderingMode getRenderingMode ( void ) const;
        int getRenderingMode(void) const;
        ShadingMode getShadingMode( void ) const;
};
#endif // __PREFERENCE_HPP__
