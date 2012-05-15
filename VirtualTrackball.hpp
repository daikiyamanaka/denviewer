#ifndef __VIRTUAL_TRACKBALL_HPP__
#define __VIRTUAL_TRACKBALL_HPP__ 1
#include "Model.hpp"
#include "MouseListener.hpp"
#include <Eigen/Geometry>
#include <Eigen/Dense>
#include <fstream>
class VirtualTrackball : public MouseListener
{
private:
        Model& _model;
        int _width;
        int _height;
        float _radius;
        float _eps;
        std::ofstream fout;
        Eigen::Vector3f _oldp;
        int _oldx;
        int _oldy;



public:
        VirtualTrackball ( Model& model, const float radius = 0.8, const float epsilon = 1.0e-10 );
        virtual ~VirtualTrackball ( void ) ;
        void setSize ( const int width, const int height );
        virtual bool mousePressed ( const MouseEvent* event );
        virtual bool mouseMoved ( const MouseEvent* event );
        virtual bool mouseReleased ( const MouseEvent* event );
        virtual bool middleButtonPressed ( const MouseEvent* event);
        virtual bool middleButtonMoved ( const MouseEvent* event);
        virtual bool middleButtonReleased ( const MouseEvent* event);

private:
        Eigen::Vector3f project_on_sphere ( const int x, const int y ) const;
};

#endif// __VIRTUAL_TRACKBALL_HPP__
