#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__ 1
#include <Eigen/Dense>
#include <Eigen/Geometry>
#define EIGEN_DONT_ALIGN_STATICALLY

class Camera
{
private:
        Eigen::Vector3f _center;
        float  _distanceToCenter;
        float    _fieldOfViewAngle;
        Eigen::Quaternionf _rotation;
public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW

        Camera ( const Eigen::Vector3f center = Eigen::Vector3f(), const float distanceToCenter = 10, const float fieldOfViewAngle = 60 );
        Camera ( const Camera& that );
        Camera& operator = ( const Camera& that );
        virtual ~Camera ( void ) ;

        void fitPosition ( const Eigen::Vector3f& center,  const float radius , const Eigen::Quaternionf& q );

        float getFieldOfViewAngle ( void ) const;
        float getDistanceToCenter (void ) const;
        Eigen::Vector3f getEye ( void ) const;
        Eigen::Vector3f getCenter ( void ) const;
        Eigen::Vector3f getUpVector ( void ) const;
        Eigen::Quaternionf getRotation ( void ) const;
        void setFieldOfViewAngle ( const float fov );
        void setCenter ( const Eigen::Vector3f& move );
        void setRotation ( const Eigen::Quaternionf& rot );
        void setDistanceToCenter( const float d );
        void multiplyRotation ( const Eigen::Quaternionf& rotation );

private:
        void copy ( const Camera& that );
};
#endif // __CAMERA_HPP__
