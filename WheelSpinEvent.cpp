#include "WheelSpinEvent.hpp"
#include <sstream>
WheelSpinEvent::WheelSpinEvent ( const int width, const int height, const int x, const int y, const int step ) : _width ( width ), _height ( height ), _x ( x ), _y ( y ), _step ( step )
{
        return;
}
WheelSpinEvent::WheelSpinEvent ( const WheelSpinEvent& that )
{
        this->copy ( that );
        return;
}
WheelSpinEvent&
WheelSpinEvent::operator = ( const WheelSpinEvent& that )
{
        this->copy ( that );
        return *this;
}
WheelSpinEvent::~WheelSpinEvent ( void )
{
        return;
}

int
WheelSpinEvent::x ( void ) const
{
        return this->_x;
}
int
WheelSpinEvent::y ( void ) const
{
        return this->_y;
}

int
WheelSpinEvent::width ( void ) const
{
        return this->_width;
}

int
WheelSpinEvent::height ( void ) const
{
        return this->_height;
}

int
WheelSpinEvent::step ( void ) const
{
    return this->_step;
}

std::string
WheelSpinEvent::toString ( void ) const
{
        std::stringstream ss;
        ss<<"("<<this->width() <<", "<<this->height() <<")";
        ss<<"("<<this->x() <<", "<<this->y() <<")";
        return ss.str();
}

void
WheelSpinEvent::copy ( const WheelSpinEvent &that )
{
        this->_x = that._x;
        this->_y = that._y;
        this->_width = that._width;
        this->_height = that._height;
        this->_step = that._step;
        return;
}

