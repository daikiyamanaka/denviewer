#ifndef __MAIN_WINDOW_HPP__
#define __MAIN_WINDOW_HPP__ 1
#include <QMainWindow>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>

QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
class QLabel;
class QMenu;
QT_END_NAMESPACE

#include "GLWidget.hpp"
#include "Model.hpp"
#include "View.hpp"

class MainWindow : public QMainWindow
{
        Q_OBJECT
private:
        Model& _model;
        View& _view;
        GLWidget* _glwidget;
public:
        MainWindow ( Model& model, View& view ) ;
protected:
        void contextMenuEvent ( QContextMenuEvent* event );
signals:
        void updated( void );

private slots:
        void new_file ( void );
        void open ( void );
        void save ( void );
        void openCamera ( void );
        void saveCamera ( void );

        void polygon_wireframe ( void );
        void polygon_surface ( void );
        void polygon_point ( void );
        void polygon_wireframe ( bool );
        void polygon_surface ( bool );
        void polygon_point ( bool );

        void view_fit ( void );
        void view_init ( void );
        void mouse_dragged ( float x, float y );

        void changeModelColor( void );

private:
        void create_actions ( void );
        void create_menus ( void );
        void create_toolbars ( void );
private:

        QToolBar* _fileToolBar;
        QMenu* _fileMenu;
        QAction* _newAct;
        QAction* _openAct;
        QAction* _saveAct;
        QAction* _exitAct;
        QAction* _openCameraAct;
        QAction* _saveCameraAct;

        QSpinBox* spinbox;
        QDoubleSpinBox* _spinbox1;
        QDoubleSpinBox* _spinbox2;
        QDoubleSpinBox* _spinbox3;
        QDoubleSpinBox* _spinbox4;
        QDoubleSpinBox* _spinbox5;
        QDoubleSpinBox* _spinbox6;
        QDoubleSpinBox* _spinbox7;

        QDoubleSpinBox* _colorBox01;
        QDoubleSpinBox* _colorBox02;
        QDoubleSpinBox* _colorBox03;
        QDoubleSpinBox* _colorBox04;
        QDoubleSpinBox* _colorBox05;
        QDoubleSpinBox* _colorBox06;
        QDoubleSpinBox* _colorBox07;
        QDoubleSpinBox* _colorBox08;
        QDoubleSpinBox* _colorBox09;

        QPushButton* _changeingColorButton;

};
#endif // __MAIN_WINDOW_HPP__
