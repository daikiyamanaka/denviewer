#include "MouseListener.hpp"
MouseListener::MouseListener ( void )
{

};
MouseListener::~MouseListener ( void )
{

}
bool
MouseListener::mousePressed ( const MouseEvent* event )
{

        return true;
}
bool
MouseListener::mouseMoved ( const MouseEvent* event )
{

        return true;
}
bool
MouseListener::mouseReleased ( const MouseEvent* event )
{
        return true;
}

bool
MouseListener::middleButtonPressed(const MouseEvent *event)
{
        return true;
}
bool
MouseListener::middleButtonMoved(const MouseEvent *event)
{
    return true;
}
bool
MouseListener::middleButtonReleased(const MouseEvent *event)
{
    return true;
}

