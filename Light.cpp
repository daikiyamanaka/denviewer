#include "Light.hpp"


Light::Light ( void )
{
        return;
}

Light::~Light ( void )
{
        return;
}

Eigen::Vector3f
Light::getPosition ( void ) const
{
        return this->_position;
}
Color3f
Light::getAmbient ( void ) const
{
    return this->_ambient;
        //return Color3f ( 0.1, 0.1, 0.1 );
}
Color3f
Light::getDiffuse ( void ) const
{
        //return Color3f ( 0.8, 0.8, 0.8 );
        return this->_diffuse;
}

Color3f
Light::getSpecular ( void ) const
{
        //return Color3f ( 0.1, 0.1, 0.1 );
        return this->_specular;
}

void
Light::setPosition ( const Eigen::Vector3f& v )
{
        this->_position = v;
}

void Light::setAmbient(const Eigen::Vector3f &v){

    this->_ambient = v;
}

void Light::setDiffuse(const Eigen::Vector3f &v){

    this->_diffuse = v;
}

void Light::setSpecular(const Eigen::Vector3f &v){

    this->_specular = v;
}
