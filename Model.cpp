#include "Model.hpp"
#include "ImporterMesh.hpp"
#include "ExporterMesh.hpp"
#include "ImporterCamera.hpp"
#include "ExporterCamera.hpp"

#include "ImporterMeshStlBinary.hpp"
#include "ImporterMeshObj.hpp"

#include "Tokenizer.hpp"

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

const Light&
Model::getLight( const unsigned int number){
    if(number == 0){
        return this->_keylight;
    }else if(number == 1){
        return this->_filllight;
    }else if(number == 2){
        return this->_backlight;
    }else{
        return this->_light;
    }
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

const CenterArrow&
Model::getCenterArrow(void)
{
    return this->_carrow;
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
    ImporterMesh *importer = NULL;
    Tokenizer tok(filename, ".");
    std::string ext = tok.get( tok.size() - 1);
    if( ext == std::string("stl") ){
        importer = new ImporterMeshStlBinary(this->_mesh);
    }
    else if ( ext == std::string("obj") ){
        importer = new ImporterMeshObj(this->_mesh);
    }
    else {
        return false;
    }
    this->initMesh();
        bool result = importer->read ( filename );
        this->viewInit();
    delete importer;
        return result;
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
Model::setShadingMode(const ShadingMode shading)
{
    this->_preference.setShadingMode(shading);
    return;
}


void
Model::viewFit ( void )
{
        Eigen::Vector3f bmin, bmax;
        this->_mesh.getBoundingBox ( bmin, bmax );

        Eigen::Vector3f center;
        center = ( bmax+bmin )/2;

        //const Eigen::Vector3f center = this->_camera.getCenter();
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

        this->setLightPosition();

        Eigen::Vector3f keyamb(0.1, 0.1, 0.1);
        Eigen::Vector3f keydif = 8.0*keyamb;
        this->_keylight.setAmbient(keyamb);
        this->_keylight.setDiffuse(keydif);
        this->_keylight.setSpecular(keyamb);

        this->_filllight.setAmbient( 0.5*keyamb);
        this->_filllight.setDiffuse(0.5*keydif);
        this->_filllight.setSpecular(0.0*keyamb);

        this->_backlight.setAmbient(0.50*keyamb);
        this->_backlight.setDiffuse(0.50*keydif);
        this->_backlight.setSpecular(0.0*keyamb);
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

void
Model::getBackgroundColor ( int &r, int &g, int &b )
{
    const Color3f c = this->getPreference().getBackgroundColor();
    r = static_cast<int> ( 255 * c.x() );
    g = static_cast<int> ( 255 * c.y() );
    b = static_cast<int> ( 255 * c.z() );

}
void
Model::setBackgroundColor ( const int r, const int g, const int b )
{
    Color3f c;
    c.x() = r * 1.0 / 255;
    c.y() = g * 1.0 / 255;
    c.z() = b * 1.0 / 255;
    this->_preference.setBackgroundColor ( c );
}
void
Model::getWireColor ( int &r, int &g, int &b )
{
    const Color3f c = this->getPreference().getWireColor();
    r = static_cast<int> ( 255 * c.x() );
    g = static_cast<int> ( 255 * c.y() );
    b = static_cast<int> ( 255 * c.z() );

}
void
Model::setWireColor ( const int r, const int g, const int b )
{
    Color3f c;
    c.x() = r * 1.0 / 255;
    c.y() = g * 1.0 / 255;
    c.z() = b * 1.0 / 255;
    this->_preference.setWireColor ( c );
}

void
Model::getLightColor ( int &r, int &g, int &b )
{
    const Color3f c = this->_light.getColor();
    r = static_cast<int> ( 255 * c.x() );
    g = static_cast<int> ( 255 * c.y() );
    b = static_cast<int> ( 255 * c.z() );

}
void
Model::setLightColor ( const int r, const int g, const int b )
{
    Color3f c;
    c.x() = r * 1.0 / 255;
    c.y() = g * 1.0 / 255;
    c.z() = b * 1.0 / 255;
    //this->_preference.setWireColor ( c );
    this->_light.setColor(c);
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

void
Model::getDisplayRange(double &near, double &far)
{
    if( this->_mesh.getNumFaces() == 0 ){
        near = 0.001;
        far = 100000.0;
        return;
    }
    Eigen::Vector3f bmin , bmax , bcenter;
    this->_mesh.getBoundingBox(bmin , bmax);
    bcenter = (bmin+bmax)*0.5;
    float r = (bmax - bmin).norm()*0.5;
    Eigen::Vector3f eyeLine = ( this->getCamera().getCenter() - this->getCamera().getEye() ).normalized();
    near = ( bcenter-this->getCamera().getEye() ).dot(eyeLine) - r;
    far  = ( bcenter-this->getCamera().getEye() ).dot(eyeLine) + r;
    if(near < 0.001) near = 0.001;
}

//imamura
void
Model::getVertexandFace(int &ver, int &face){

    face = this->_mesh.getNumFaces();
    ver = face*3;
}

void
Model::setLightPosition(void){

    Eigen::Vector3f bmin, bmax;
    this->_mesh.getBoundingBox ( bmin, bmax );

    float x = 0.5*(bmin[0]+bmax[0]);
    float y = 1.0*(bmin[1]+bmax[1]);

    Eigen::Vector3f eye = this->_camera.getEye();
    Eigen::Vector3f center = this->_camera.getCenter();
    Eigen::Vector3f tocenterv = center - eye;
    float e = tocenterv.norm();
    Eigen::Vector3f tocentere = tocenterv/e;
    Eigen::Vector3f up = this->_camera.getUpVector();
    Eigen::Vector3f side = up.cross(tocentere);
    Eigen::Vector3f lightpos = this->_camera.getEye() + 2.0*y*up + x*side;
    Eigen::Vector3f flightpos = this->_camera.getEye() - 0.5*y*up - x*side;
    Eigen::Vector3f blightpos = this->_camera.getEye() + 2.0*tocenterv;
    /*if(bmin[0]+bmax[0] >= 0.0){
        lightpos[0] -= 0.5*(bmin[0]+bmax[0]);
        flightpos[0] += 0.75*(bmin[0]+bmax[0]);
    }else{
        lightpos[0] += 0.5*(bmin[0]+bmax[0]);
        flightpos[0] -= 0.75*(bmin[0]+bmax[0]);
    }
    if(bmin[1]+bmax[1] >= 0.0){
        lightpos[1] += 1.0*(bmin[1]+bmax[1]);
        flightpos[1] -= 0.75*(bmin[1]+bmax[1]);
    }else{
        lightpos[1] -= 1.0*(bmin[1]+bmax[1]);
        flightpos[1] += 0.75*(bmin[1]+bmax[1]);
    }
    if(bmin[2]+bmax[2] >= 0.0){
        blightpos[2] -= 100.0*(bmin[2]+bmax[2]);
    }else{
        blightpos[2] += 100.0*(bmin[2]+bmax[2]);
    }*/
    this->_keylight.setPosition ( lightpos );
    this->_filllight.setPosition( flightpos );
    this->_backlight.setPosition( blightpos );
    return;
}

void Model::changeLightPosition(const unsigned int number, float a, float b, float c){

    Eigen::Vector3f lightpos;
    Eigen::Vector3f eye = this->_camera.getEye();
    Eigen::Vector3f center = this->_camera.getCenter();
    Eigen::Vector3f tocenterv = center - eye;
    float e = tocenterv.norm();
    Eigen::Vector3f tocentere = tocenterv/e;
    Eigen::Vector3f up = this->_camera.getUpVector();
    Eigen::Vector3f side = up.cross(tocentere);

    /*if(number == 0){
        lightpos = this->_keylight.getLight(number) + a*up + b*side + c*tocentere;
        this->_keylight.setPosition(lightpos);
    }else if(number == 1){
        lightpos = this->_filllight.getLight(number) + a*up + b*side + c*tocentere;
        this->_filllight.setPosition(lightpos);
    }else if(number == 2){
        lightpos = this->_backlight.getLight(number) + a*up + b*side + c*tocentere;
        this->_backlight.setPosition(lightpos);
    }*/
}

void
Model::getCenterArrowPos(double &xpos , double &ypos , double &zpos)
{
    Eigen::Vector3f center = this->_carrow.GetCenter();
    xpos = center(0);
    ypos = center(1);
    zpos = center(2);

    return;
}

void
Model::setCenterArrowPos()
{
    Eigen::Vector3f bmin  , bmax;
    this->_mesh.getBoundingBox(bmin , bmax);
    Eigen::Vector3f modelCenter = (bmin + bmax)*0.5;
    this->_camera.getCenter();
    this->_carrow.setCenterVec(modelCenter,
                               this->_camera.getUpVector(),
                               this->_camera.getEye(),
                               this->_camera.getDistanceToCenter()*0.5);
    return;
}

void
Model::ChangeCenterArrow(double xpos, double ypos, double zpos)
{
    this->_carrow.setCenter(xpos, ypos, zpos);
    return;
}
