#ifndef __LIGHT_HPP__
#define __LIGHT_HPP__ 1
#include <Eigen/Dense>
#include "Color3f.hpp"

class Light
{
private:
        Eigen::Vector3f _position;

        //
        Eigen::Vector3f _ambient;
        Eigen::Vector3f _diffuse;
        Eigen::Vector3f _specular;
public:
        Light ( void ) ;
        virtual ~Light ( void );

        Eigen::Vector3f getPosition ( void ) const;
        Color3f getAmbient ( void ) const;
        Color3f getDiffuse ( void ) const;
        Color3f getSpecular ( void ) const;
        void setPosition ( const Eigen::Vector3f& v );

        //
        void setAmbient(const Eigen::Vector3f& v);
        void setDiffuse(const Eigen::Vector3f& v);
        void setSpecular(const Eigen::Vector3f& v);
};
#endif // __LIGHT_HPP__
