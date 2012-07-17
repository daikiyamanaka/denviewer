#include "CenterArrow.hpp"

CenterArrow::CenterArrow()
{
}

void
CenterArrow::setCenterVec(const Eigen::Vector3f modelcenter, const float max)
{
    Eigen::Vector3f x(1.0, 0.0, 0.0);
    Eigen::Vector3f y(0.0, 1.0, 0.0);
    Eigen::Vector3f z(0.0, 0.0, 1.0);
    this->_center = modelcenter;
    /*this->_yvec = upvec;
    this->_zvec = modelcenter - camcenter;
    this->_zvec.normalize();
    this->_xvec = _yvec.cross(_zvec);
    this->_xvec.normalize();*/
    this->_yvec = y;
    this->_xvec = x;
    this->_zvec = z;
    this->_scale = max;
    return;
}

void
CenterArrow::setCenter(double xpos, double ypos, double zpos)
{
    Eigen::Vector3f center(xpos, ypos, zpos);
    this->_center = center;
    return;
}

Eigen::Vector3f
CenterArrow::GetCenter(void) const
{
    return this->_center;
}

Eigen::Vector3f
CenterArrow::GetXvec(void) const
{
    return this->_xvec;
}

Eigen::Vector3f
CenterArrow::GetYvec(void) const
{
    return this->_yvec;
}

Eigen::Vector3f
CenterArrow::GetZvec(void) const
{
    return this->_zvec;
}

float
CenterArrow::GetScale(void) const
{
    return this->_scale;
}
