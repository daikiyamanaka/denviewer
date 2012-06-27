#include "Translation.hpp"

Translation::Translation(Model& model, const float radius, const float epsilon ) : _model ( model ), _radius ( radius ), _eps ( epsilon )
{
        return;
}

Translation::~Translation(void)
{
    return;
}

void
Translation::setSize(const int width, const int height )
{
        this->_width = width;
        this->_height = height;
}

bool
Translation::mousePressed ( const MouseEvent* event )
{
        if ( !event->isMiddleButtonPressed()) return false;
        this->setSize ( event->width(), event->height() );
        this->_oldp = this->movement_on_screen( event->x(), event->y() );
        return true;
}

bool
Translation::mouseMoved ( const MouseEvent* event )
{
        if ( !event->isMiddleButtonPressed() ) return false;
        const Eigen::Vector3f p0 = this->_oldp;
        const Eigen::Vector3f p1 = this->movement_on_screen ( event->x(), event->y() );
        this->_oldp = p1;
        if ( ( p0 - p1 ).norm() < this->_eps ) return false; // do nothing
        Eigen::Vector3f center = this->_model.getCamera().getCenter();
        center = center + (p1 - p0 );
        this->_model.setCameraPosition( center.x() , center.y() , center.z()  );

        return true;
}

bool
Translation::mouseReleased ( const MouseEvent* event )
{
        event->x();
        return true;
}

Eigen::Vector3f
Translation::project_on_sphere(const int x, const int y) const
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

Eigen::Vector3f
Translation::movement_on_screen ( const int x, const int y ) const
{
        const float cx = static_cast<double>( this->_width / 2 );
        const float cy = static_cast<double>( this->_height / 2 );
        const float sy = this->_model.getCamera().getDistanceToCenter() * std::tan( 0.5 * this->_model.getCamera().getFieldOfViewAngle()*3.14159265/180.0 );
        const float hr = sy/cy;
        const float fx = ( static_cast<float>(x) - cx ) * hr;
        const float fy = ( static_cast<float>(y) - cy ) * hr;

        Eigen::Vector3f result = Eigen::Matrix3f(this->_model.getCamera().getRotation()) * Eigen::Vector3f(fx,fy,0);
        return result;
}
