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
        Preference& getPreference ( void );

        bool initMesh ( void );
        bool openMesh ( const std::string& filename );
        bool saveMesh ( const std::string& filename );
        bool openCamera ( const std::string& filename );
        bool saveCamera ( const std::string& filename );
        void setRenderingMode ( const RenderingMode mode );
        void viewFit ( void );
        void viewInit ( void );

        void addRotation ( const Eigen::Quaternionf& q );
        void moveCenter ( const Eigen::Vector3f& move  );
        //

};
#endif // __MODEL_HPP__
