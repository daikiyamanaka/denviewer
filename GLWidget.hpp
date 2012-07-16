#ifndef __GL_WIDGET_HPP__
#define __GL_WIDGET_HPP__ 1
#include <QMouseEvent>
#include <QGLWidget>
#include "View.hpp"
#include "GLWidget.hpp"
#include "VirtualTrackball.hpp"
#include "Translation.hpp"
#include "WheelSpinEvent.hpp"

class GLWidget : public QGLWidget
{
        Q_OBJECT
private:
        Model& _model;
        View& _view;
        MouseListener *_ball;
        MouseListener *_move;
        //ChangeWindowSizeWidget* _changewh;
        //VirtualTrackball* _ball;
public:
        GLWidget ( Model& model, View& view, QWidget *parent = 0 );
        virtual ~GLWidget ( void );
        QSize minimumSizeHint ( void ) const ;
        QSize sizeHint ( void ) const;
public slots:
signals:
        void mouseDragged ( float x, float y );
        void fileDropped ( QString file);
        void wheelSpined ( float x , float y , float step );
        void resizedWindow(int width, int height);
protected:
        void initializeGL ( void  );
        void paintGL ( void ) ;
        void resizeGL ( int width, int height );
        void mousePressEvent ( QMouseEvent* event );
        void mouseMoveEvent ( QMouseEvent* event );
        void mouseReleaseEvent ( QMouseEvent* event );
        void dragEnterEvent(QDragEnterEvent *event);
        void dragLeaveEvent(QDragEnterEvent *event);
        void dropEvent(QDropEvent *event);
        void wheelEvent(QWheelEvent *event);
private:
        MouseEvent convert_qmouse_event ( QMouseEvent* event );
        WheelSpinEvent convert_qwheel_event ( QWheelEvent* event );

};
#endif //__GL_WIDGET_HPP__
