#include "VirtualTrackball.hpp"

VirtualTrackball::VirtualTrackball ( Model& model, const float radius, const float epsilon ) : _model ( model ), _radius ( radius ), _eps ( epsilon )
{
        return;
}

VirtualTrackball::~VirtualTrackball ( void )
{
        return;
}
void
VirtualTrackball::setSize ( const int width, const int height )
{
        this->_width = width;
        this->_height = height;
}
bool
VirtualTrackball::mousePressed ( const MouseEvent* event )
{
        if ( !event->isLeftButtonPressed() ) return false;
        this->setSize ( event->width(), event->height() );
        this->_oldp = this->project_on_sphere ( event->x(), event->y() );
        return true;
}
bool
VirtualTrackball::mouseMoved ( const MouseEvent* event )
{
        if ( !event->isLeftButtonPressed() ) return false;
        const Eigen::Vector3f p0 = this->_oldp;
        const Eigen::Vector3f p1 = this->project_on_sphere ( event->x(), event->y() );
        this->_oldp = p1;
        if ( ( p0 - p1 ).norm() < this->_eps ) return false; // do nothing
		//�����Ԉ���Ă����Ȃ̂Œ������Ă݂�
        float radian = std::acos( p0.dot ( p1 ) )*0.5;
        const float cost = std::cos(radian);
        const float sint = std::sin(radian);
        //const float cost = p0.dot ( p1 );
        //const float sint = std::sqrt ( 1 - cost * cost );
        const Eigen::Vector3f axis = p0.cross ( p1 ).normalized();
        const Eigen::Quaternionf q ( -cost, sint * axis.x(), sint * axis.y(), sint * axis.z() );
        const Eigen::Quaternionf q2 ( -cost, -sint * axis.x(), -sint * axis.y(), -sint * axis.z() );

        Eigen::Vector3f bmin , bmax;
        Mesh mesh;
        mesh = this->_model.getMesh();
        mesh.getBoundingBox(bmin,bmax);
        Eigen::Vector3f mc = (bmin + bmax)*0.5;
        Eigen::Vector3f c = Eigen::Matrix3f(q2) * ( this->_model.getCamera().getCenter() - mc ) + mc ;

        this->_model.addRotation ( q );
        this->_model.setCameraPosition(c.x(),c.y(),c.z());
        return true;
}
bool
VirtualTrackball::mouseReleased ( const MouseEvent* event )
{
        event->x();
        return true;
}

Eigen::Vector3f
VirtualTrackball::project_on_sphere ( const int x, const int y ) const
{
        const int cx = this->_width / 2;
        const int cy = this->_height / 2;
        const int base = std::min ( cx,cy );
        const float fx = ( x - cx ) * 1.0 / base / _radius;
        const float fy = ( y - cy ) * 1.0 / base / _radius;

        Eigen::Vector3f result ( fx, fy, 0 );
        const float d = fx * fx + fy * fy;
        if ( d < 1.0f ) result.z() = std::sqrt ( 1.0f - d );
        result.normalize();
        return result;
}


