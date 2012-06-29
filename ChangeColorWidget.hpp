#ifndef __CHANGE_COLOR_WIDGET_HPP__
#define __CHANGE_COLOR_WIDGET_HPP__ 1
#include <QLabel>
#include <QWidget>
class ChangeColorWidget : public QWidget
{
Q_OBJECT
private:
    QLabel* _faceColorLabel;
    QLabel* _backgroundColorLabel;
    QLabel* _wireColorLabel;
    QLabel* _vertexColorLabel;
public:
    ChangeColorWidget( QColor faceColor, QColor backgroundColor, QColor wireColor,  QWidget *parent = 0);
    QColor getSurfaceColor( void ) const ;
    QColor getBackgroundColor(void);
    QColor getWireColor(void);
    QColor getVertexColor(void);
public slots : 
    void set_surface_color( void ) ;
    void setBackgroundColor( void);
    void setWireColor(void);
    void setVertexColor(void);
signals :
	void updated();
};
#endif //__CHANGE_COLOR_WIDGET_HPP__
