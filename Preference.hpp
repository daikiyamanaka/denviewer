#ifndef __PREFERENCE_HPP__
#define __PREFERENCE_HPP__ 1

#include <cstdlib>
#include "Color3f.hpp"
enum RenderingMode {
        WIRE = 0,
        SURFACE = 1,
        POINTCLOUD = 2
};

class Preference
{
private:
        Color3f _background;
        Color3f _wire;
        Color3f _surface;
        Color3f _pointcloud;

        bool _surfaceRendering;
        bool _wireRendering;
        bool _pointCloudRendering;


        RenderingMode _status;

public:
        Preference ( void ) ;
        virtual ~Preference ( void );

        void setBackgroundColor ( const Color3f c );
        void setWireColor ( const Color3f c );
        void setSurfaceColor ( const Color3f c );
        void setPointcloudColor ( const Color3f c);

        void setSurfaceRendering( const bool b);
        void setWireRendering( const bool b);
        void setPointCloudRendering( const bool b);

        void setRenderingMode ( const RenderingMode status );

        Color3f getBackgroundColor ( void ) const;
        Color3f getWireColor ( void ) const;
        Color3f getSurfaceColor ( void ) const;
        Color3f getPointcloudColor ( void ) const;

        bool getSurfaceRenderingMode( void ) const;
        bool getWireRenderingMode( void ) const;
        bool getPointCloudRenderingMode( void ) const;


        RenderingMode getRenderingMode ( void ) const;
};
#endif // __PREFERENCE_HPP__
