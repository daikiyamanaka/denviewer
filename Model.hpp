#ifndef __MODEL_HPP__
#define __MODEL_HPP__ 1
#include "Preference.hpp"
#include "Mesh.hpp"
#include "Light.hpp"
#include "Camera.hpp"
#include "CenterArrow.hpp"
#include "deque"


class Model
{
private:
        std::vector<Mesh> _mesh;
        //std::vector<bool> _selected;
        std::vector<bool> _checked;
        Light _light;
        Light _keylight;
        Light _filllight;
        Light _backlight;

        Camera _camera;
        CenterArrow _carrow;

        std::deque<Camera, Eigen::aligned_allocator<Camera> > _cameraList;
        int _NowCameraId;
        int _activeMeshId;

        std::vector<Preference, Eigen::aligned_allocator<Preference> > _Preferences;


public:
        Model ( void ) ;
        virtual ~Model ( void ) ;

        const std::vector<Mesh>& getMesh ( void );
        const Light& getLight ( void );
        const Light& getLight (const unsigned int number);
        const Camera& getCamera ( void );

        const CenterArrow& getCenterArrow(void);
        const std::vector< Preference, Eigen::aligned_allocator<Preference> > &getPreferences( void );

        bool initMesh ( void );
        bool openMesh ( const std::string& filename );
        bool saveMesh ( const std::string& filename , bool isBinary = false , size_t id = 0 );
        bool openCamera ( const std::string& filename );
        bool saveCamera ( const std::string& filename );
        //void setRenderingMode ( const RenderingMode mode );
        void setRenderingMode(const int mode);
        int getRenderingMode();
        void setShadingMode (const ShadingMode shading);
        void viewFit ( void );
        void viewInit ( void );

        int getActiveMeshIndex();
        void setActiveMeshIndex( int id );

        void addRotation ( const Eigen::Quaternionf& q );

        // for changing color
        void getSurfaceColor ( const int id , int &r, int &g, int &b );
        void setSurfaceColor ( const int id, const int r, const int g, const int b );
        void getBackgroundColor ( const int id, int &r, int &g, int &b );
        void setBackgroundColor ( const int id, const int r, const int g, const int b );
        void getWireColor ( const int id, int &r, int &g, int &b );
        void setWireColor ( const int id, const int r, const int g, const int b );
        void getVertexColor( const int id, int &r, int &g, int &b );
        void setVertexColor( const int id, const int r, const int g, const int b );

        void getLightColor( int &r, int &g, int &b );
        void setLightColor(const int r, const int g, const int b);

        int getWireWidth(void);
        void setWireWidth( const int width );

        void setViewAngle(float _angle);
        float getViewAngle(void);

        void setMeshCheckState(std::vector<bool> checked);
        std::vector<bool> getMeshCheckState();

		//Yamauchi
		void getEulerAngle( int &alpha , int &beta , int &gamma);
		void setEulerAngle( const int alpha , const int beta , const int gamma );
		void getCameraPosition( double &xpos , double &ypos , double &zpos);
		void setCameraPosition( const double xpos , const double ypos , const double zpos);
        void getDistanceToCenter( float &d );
        void setDistanceToCenter( const float d );
        void getDisplayRange( double &near , double &far  );
        void addNowCameraToList( void );
        void backCamera( void );
        void forwardCamera( void );

        //imamura
        void getVertexandFace(int &ver, int &face);
        void setLightPosition(void);
        void changeLightPosition(const unsigned int number, float a, float b, float c);

        void getCenterArrowPos(double &xpos , double &ypos , double &zpos);
        void setCenterArrowPos();
        void ChangeCenterArrow(double xpos, double ypos, double zpos);
};
#endif // __MODEL_HPP__
