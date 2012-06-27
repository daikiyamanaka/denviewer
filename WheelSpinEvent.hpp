#ifndef WHEELSPINEVENT_HPP
#define WHEELSPINEVENT_HPP
#include <cstdlib>
#include <string>

class WheelSpinEvent
{
private:
        int _width;
        int _height;
        int _x;
        int _y;
        int _step;

public:
        WheelSpinEvent ( const int width, const int height, const int x, const int y , const int step );
        WheelSpinEvent ( const WheelSpinEvent& that );
        WheelSpinEvent& operator = ( const WheelSpinEvent& that );
        virtual ~WheelSpinEvent ( void );

        int x ( void ) const ;
        int y ( void ) const ;
        int width ( void ) const ;
        int height ( void ) const ;
        int step( void ) const;
        std::string toString ( void ) const ;
private:
        void copy ( const WheelSpinEvent &that );
};


#endif // WHEELSPINEVENT_HPP
