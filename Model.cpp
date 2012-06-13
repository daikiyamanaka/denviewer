#include "Model.hpp"
#include "ImporterMesh.hpp"
#include "ExporterMesh.hpp"
#include "ImporterCamera.hpp"
#include "ExporterCamera.hpp"

Model::Model ( void )
{
        return;
}

Model::~Model ( void )
{
        return;
}

const Mesh&
Model::getMesh ( void )
{
        return this->_mesh;
}

const Light&
Model::getLight ( void )
{
        return this->_light;
}

const Camera&
Model::getCamera ( void )
{
        return this->_camera;
}

const Preference&
Model::getPreference ( void )
{
        return this->_preference;
}

bool
Model::initMesh ( void )
{
        this->_mesh.clear();
        return true;
}

bool
Model::openMesh ( const std::string& filename )
{
        ImporterMesh importer ( this->_mesh );
        if ( !importer.read ( filename ) ) return false;
        this->viewInit();
        return true;
}
bool
Model::saveMesh ( const std::string& filename )
{
        ExporterMesh exporter ( this->_mesh );
        return exporter.write ( filename );
}
bool
Model::openCamera ( const std::string& filename )
{
        ImporterCamera importer ( this->_camera );
        if ( !importer.read ( filename ) ) return false;
        this->_light.setPosition ( this->_camera.getEye() );
        return true;
}
bool
Model::saveCamera ( const std::string& filename )
{
        ExporterCamera exporter ( this->_camera );
        return exporter.write ( filename );
}


void
Model::setRenderingMode ( const RenderingMode mode )
{
        this->_preference.setRenderingMode ( mode );
        return;
}


void
Model::viewFit ( void )
{
        Eigen::Vector3f bmin, bmax;
        this->_mesh.getBoundingBox ( bmin, bmax );
        const Eigen::Vector3f center = this->_camera.getCenter();;
        const float radius = 1.25 * std::min ( ( bmax - center ).norm(), ( bmin - center ).norm() );
        const Eigen::Quaternionf q = this->_camera.getRotation();
        this->_camera.fitPosition ( center, radius, q );
        this->_light.setPosition ( this->_camera.getEye() );
        return;
}
void
Model::viewInit ( void )
{
        Eigen::Vector3f bmin, bmax;
        this->_mesh.getBoundingBox ( bmin, bmax );

        const Eigen::Vector3f center = 0.5 * ( bmin + bmax );
        const float radius = 1.25 * 0.5 * ( bmax - bmin ).norm();
        const Eigen::Quaternionf q ( 1,0,0,0 );
        this->_camera.fitPosition ( center, radius, q );
        this->_light.setPosition ( this->_camera.getEye() );
        return;
}

void
Model::addRotation ( const Eigen::Quaternionf& q )
{
        this->_camera.multiplyRotation ( q );
        this->_light.setPosition ( this->_camera.getEye() );
        return;
}

void
Model::getSurfaceColor ( int &r, int &g, int &b )
{
	const Color3f c = this->getPreference().getSurfaceColor();
	r = static_cast<int> ( 255 * c.x() );
	g = static_cast<int> ( 255 * c.y() );
	b = static_cast<int> ( 255 * c.z() );

}
void
Model::setSurfaceColor ( const int r, const int g, const int b )
{
	Color3f c;
	c.x() = r * 1.0 / 255;
	c.y() = g * 1.0 / 255;
	c.z() = b * 1.0 / 255;
	this->_preference.setSurfaceColor ( c );
}

int
Model::getWireWidth( void )
{
    return this->getPreference().getWireWidth();
}

void
Model::setWireWidth(const int width)
{
    this->_preference.setWireWidth(width);
}

void Model::setViewAngle(float _angle){
    this->_camera.setFieldOfViewAngle(_angle);
}
float Model::getViewAngle(void){
    return this->_camera.getFieldOfViewAngle();
}

void
Model::getEulerAngle( int &alpha , int &beta , int &gamma  )
{
    Eigen::Matrix3f m;
    m = this->_camera.getRotation().matrix();
    double a , b , c;
    //Z>X>Y‚Ì‡‚Å‰ñ“]
    if( 1.0f - std::abs( m(2,1) ) > 1.0e-10 ){
        a = std::asin( m(2,1) );
        c = std::atan2( -m(0,1) , m(1,1) );
        b = std::atan2( -m(2,0) , m(2,2) );
    }else if( m(2,1) > 0.0 ){
        a = 3.1415926535 * 0.5;
        b  = 0.0;
        c = std::atan2( m(1,0),m(0,0) );
    }else{
        a = -3.1415926535 * 0.5;
        b  = 0.0;
        c = std::atan2( m(1,0),m(0,0) );
    }
    alpha = static_cast<int>( a*180.0/3.1415926535 );
    beta =  static_cast<int>( b*180.0/3.1415926535 );
    gamma = static_cast<int>( c*180.0/3.1415926535 );

    return;
}

void
Model::setEulerAngle(const int alpha, const int beta, const int gamma)
{
    double a = alpha*3.1415926535/360.0;
    double b = beta*3.1415926535/360.0;
    double c = gamma*3.1415926535/360.0;

    Eigen::Quaternionf qz ( std::cos(c), 0.0f , 0.0f , std::sin(c) );
    Eigen::Quaternionf qx ( std::cos(a), std::sin(a) , 0.0f , 0.0f );
    Eigen::Quaternionf qy ( std::cos(b), 0.0f , std::sin(b) , 0.0f );
    Eigen::Quaternionf q;
    q = qz*qx*qy;//Z>X>Y‚Ì‡‚Å‰ñ“]
    this->_camera.setRotation(q);
    this->_light.setPosition ( this->_camera.getEye() );
    return;
}

void
Model::getCameraPosition( double &xpos , double &ypos , double &zpos)
{
    xpos = this->_camera.getCenter().x();
    ypos = this->_camera.getCenter().y();
    zpos = this->_camera.getCenter().z();

    return;
}

void
Model::setCameraPosition(const double xpos, const double ypos, const double zpos)
{
    Eigen::Vector3f pos(xpos,ypos,zpos);
    this->_camera.setCenter(pos);
    return;
}

void
Model::getDistanceToCenter(float &d)
{
    d = this->_camera.getDistanceToCenter();
    return;
}

void
Model::setDistanceToCenter(const float d)
{
    this->_camera.setDistanceToCenter(d);
    return;
}

//imamura
void
Model::getVertexandFace(int &ver, int &face){

    face = this->_mesh.getNumFaces();
    ver = face*3;
}
