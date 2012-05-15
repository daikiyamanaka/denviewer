#ifndef VIRTUALPAN_H
#define VIRTUALPAN_H
#include "Model.hpp"
#include "MouseListener.hpp"
#include <Eigen/Geometry>
#include <fstream>

class VirtualPan : public MouseListener
{
private:
        Model& _model;
        int _width;
        int _height;
        float _radius;
        float _eps;
        std::ofstream fout;
        Eigen::Vector3f _oldp;

public:
        VirtualPan(Model& model, const float radius = 0.8, const float epsilon = 1.0e-10);
        virtual ~VirtualPan();
        void setSize ( const int width, const int height );
        virtual bool mousePressed ( const MouseEvent* event );
        virtual bool mouseMoved ( const MouseEvent* event );
        virtual bool mouseReleased ( const MouseEvent* event );
private:
        Eigen::Vector3f project_on_sphere ( const int x, const int y ) const;
};

#endif // VIRTUALPAN_H
