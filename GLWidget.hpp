#ifndef __GL_WIDGET_HPP__
#define __GL_WIDGET_HPP__ 1
#include <QMouseEvent>
#include <QGLWidget>
#include "View.hpp"
#include "GLWidget.hpp"
#include "VirtualTrackball.hpp"

enum ChangingViewMode{
    TRACKBALL = 0,
    PAN = 1
};

class GLWidget : public QGLWidget
{
        Q_OBJECT
private:
        Model& _model;
        View& _view;
        MouseListener *_ball;
        //VirtualTrackball* _ball;

        ChangingViewMode status;
public:
        GLWidget ( Model& model, View& view, QWidget *parent = 0 );
        virtual ~GLWidget ( void );
        QSize minimumSizeHint ( void ) const ;
        QSize sizeHint ( void ) const;
        void setChangingViewMode ( const ChangingViewMode status );
        ChangingViewMode getChangingViewMode ( void ) const;

public slots:
signals:
        void mouseDragged ( float x, float y );
protected:
        void initializeGL ( void  );
        void paintGL ( void ) ;
        void resizeGL ( int width, int height );
        void mousePressEvent ( QMouseEvent* event );
        void mouseMoveEvent ( QMouseEvent* event );
        void mouseReleaseEvent ( QMouseEvent* event );
        void middleButtonPressEvent ( QMouseEvent* event);
        void middleButtonMoveEvent ( QMouseEvent* event);
        void middleButtonReleaseEvent ( QMouseEvent* event);
private:
        MouseEvent convert_qmouse_event ( QMouseEvent* event );

};
#endif //__GL_WIDGET_HPP__
