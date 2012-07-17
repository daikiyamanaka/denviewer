#ifndef CENTERARROW_HPP
#define CENTERARROW_HPP
#include <Eigen/Dense>
#include <Eigen/Geometry>

class CenterArrow
{
private:
    Eigen::Vector3f _center;
    Eigen::Vector3f _xvec;
    Eigen::Vector3f _yvec;
    Eigen::Vector3f _zvec;
    float _scale;
public:
    CenterArrow();
    void setCenterVec(const Eigen::Vector3f modelcenter, const float max);
    void setCenter(double xpos, double ypos, double zpos);
    Eigen::Vector3f GetCenter(void) const;
    Eigen::Vector3f GetXvec(void) const;
    Eigen::Vector3f GetYvec(void) const;
    Eigen::Vector3f GetZvec(void) const;
    float GetScale(void) const;
};

#endif // CENTERARROW_HPP
