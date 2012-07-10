#ifndef __MODEL_HPP__
#define __MODEL_HPP__ 1
#include "Preference.hpp"
#include "Mesh.hpp"
#include "Light.hpp"
#include "Camera.hpp"
#include "CenterArrow.hpp"

class Model
{
private:
        Mesh _mesh;
        Light _light;
        Light _keylight;
        Light _filllight;
        Light _backlight;
        Camera _camera;
        Preference _preference;
        CenterArrow _carrow;


public:
        Model ( void ) ;
        virtual ~Model ( void ) ;

        const Mesh& getMesh ( void );
        const Light& getLight ( void );
        const Light& getLight (const unsigned int number);
        const Camera& getCamera ( void );
        const Preference& getPreference ( void );
        const CenterArrow& getCenterArrow(void);

        bool initMesh ( void );
        bool openMesh ( const std::string& filename );
        bool saveMesh ( const std::string& filename );
        bool openCamera ( const std::string& filename );
        bool saveCamera ( const std::string& filename );
        void setRenderingMode ( const RenderingMode mode );
        void setShadingMode (const ShadingMode shading);
        void viewFit ( void );
        void viewInit ( void );

        void addRotation ( const Eigen::Quaternionf& q );

        // for changing color
        void getSurfaceColor ( int &r, int &g, int &b );
        void setSurfaceColor ( const int r, const int g, const int b );
        void getBackgroundColor ( int &r, int &g, int &b );
        void setBackgroundColor ( const int r, const int g, const int b );
        void getWireColor ( int &r, int &g, int &b );
        void setWireColor ( const int r, const int g, const int b );

        void getLightColor( int &r, int &g, int &b );
        void setLightColor(const int r, const int g, const int b);

        int getWireWidth(void);
        void setWireWidth( const int width );

        void setViewAngle(float _angle);
        float getViewAngle(void);

		//Yamauchi
		void getEulerAngle( int &alpha , int &beta , int &gamma);
		void setEulerAngle( const int alpha , const int beta , const int gamma );
		void getCameraPosition( double &xpos , double &ypos , double &zpos);
		void setCameraPosition( const double xpos , const double ypos , const double zpos);
        void getDistanceToCenter( float &d );
        void setDistanceToCenter( const float d );
        void getDisplayRange( double &near , double &far  );

        //imamura
        void getVertexandFace(int &ver, int &face);
        void setLightPosition(void);
        void changeLightPosition(const unsigned int number, float a, float b, float c);

        void getCenterArrowPos(double &xpos , double &ypos , double &zpos);
        void setCenterArrowPos();
        void ChangeCenterArrow(double xpos, double ypos, double zpos);
};
#endif // __MODEL_HPP__
