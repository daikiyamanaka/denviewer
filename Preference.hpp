#ifndef __PREFERENCE_HPP__
#define __PREFERENCE_HPP__ 1

#include <cstdlib>
#include "Color3f.hpp"
enum RenderingMode {
        WIRE = 0,
        SURFACE = 1
};

class Preference
{
private:
        Color3f _background;
        Color3f _wire;
        Color3f _surface;

        int _wire_width;

        RenderingMode _status;

public:
        Preference ( void ) ;
        virtual ~Preference ( void );

        void setBackgroundColor ( const Color3f c );
        void setWireColor ( const Color3f c );
        void setSurfaceColor ( const Color3f c );
        void setWireWidth( const int width );
        void setRenderingMode ( const RenderingMode status );

        Color3f getBackgroundColor ( void ) const;
        Color3f getWireColor ( void ) const;
        Color3f getSurfaceColor ( void ) const;
        int getWireWidth( void ) const;
        RenderingMode getRenderingMode ( void ) const;
};
#endif // __PREFERENCE_HPP__
