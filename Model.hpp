#ifndef __MODEL_HPP__
#define __MODEL_HPP__ 1
#include "Preference.hpp"
#include "Mesh.hpp"
#include "Light.hpp"
#include "Camera.hpp"

class Model
{
private:
        Mesh _mesh;
        Light _light;
        Camera _camera;
        Preference _preference;


public:
        Model ( void ) ;
        virtual ~Model ( void ) ;

        const Mesh& getMesh ( void );
        const Light& getLight ( void );
        const Camera& getCamera ( void );
        const Preference& getPreference ( void );

        bool initMesh ( void );
        bool openMesh ( const std::string& filename );
        bool saveMesh ( const std::string& filename );
        bool openCamera ( const std::string& filename );
        bool saveCamera ( const std::string& filename );
        void setRenderingMode ( const RenderingMode mode );
        void viewFit ( void );
        void viewInit ( void );

        void addRotation ( const Eigen::Quaternionf& q );
        //
        void getSurfaceColor ( int &r, int &g, int &b );
        void setSurfaceColor ( const int r, const int g, const int b );

        int getWireWidth(void);
        void setWireWidth( const int width );

        void setViewAngle(float _angle);
        float getViewAngle(void);

		//Yamauchi
		void getEulerAngle( int &alpha , int &beta , int &gamma);
		void setEulerAngle( const int alpha , const int beta , const int gamma );
		void getCameraPosition( double &xpos , double &ypos , double &zpos);
		void setCameraPosition( const double xpos , const double ypos , const double zpos);

        //imamura
        void getVertexandFace(int &ver, int &face);
};
#endif // __MODEL_HPP__
