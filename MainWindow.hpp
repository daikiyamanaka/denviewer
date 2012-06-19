#ifndef __MAIN_WINDOW_HPP__
#define __MAIN_WINDOW_HPP__ 1
#include <QMainWindow>
#include <Eigen/Core>
QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
class QLabel;
class QMenu;
QT_END_NAMESPACE

#include "GLWidget.hpp"
#include "Model.hpp"
#include "View.hpp"
#include "ChangeColorWidget.hpp"
#include "ChangeWireWidthWidget.h"
#include "ChangeViewAngle.h"
#include "GetCameraParameterWidget.hpp"
#include "ShowVandFWidget.hpp"

class MainWindow : public QMainWindow
{
        Q_OBJECT
private:
        Model& _model;
        View& _view;
        GLWidget* _glwidget;
        ChangeColorWidget* _colorWidget;
        ChangeWireWidthWidget* _wireWidthWidget;
        ChangeViewAngle* _viewWidget;
		GetCameraParameterWidget* _cameraParameterWidget;
        ShowVandFWidget* _VandFWidget;//imamura
public:
        MainWindow ( Model& model, View& view ) ;
protected:
        void contextMenuEvent ( QContextMenuEvent* event );
signals:
        void updated( void );
		void cameraInitialized(void);//Yamauchi Add
private slots:
        void new_file ( void );
        void open ( void );
        void save ( void );
        void openCamera ( void );
        void saveCamera ( void );
        void saveSnapshot( void );
        void polygon_wireframe ( void );
        void polygon_surface ( void );
        void view_fit ( void );
        void view_init ( void );
        void mouse_dragged ( float x, float y );
        void update_surface_color(void);
        void update_wire_width(void);
        void update_perspective_angle(void);
		//Yamauchi
		void update_camera_position(double xpos , double ypos , double zpos);
		void update_euler_angle(int alpha , int beta , int gamma);
		void initialize_camera_position();
		//end
        void file_dropped(QString str);
        void get_ver_face(void);//imamura
        //
        void lightswitch0(bool i);
        void lightswitch1(bool i);
        void lightswitch2(bool i);
        void lightset(void);
private:
        void create_actions ( void );
        void create_menus ( void );
        void create_toolbars ( void );
private:

        QToolBar* _fileToolBar;
        //
        QMenu* _fileMenu;
        QAction* _newAct;
        QAction* _openAct;
        QAction* _saveAct;
        QAction* _exitAct;
        QAction* _openCameraAct;
        QAction* _saveCameraAct;
        QAction* _snapshotAct;
        //
        QMenu* _showmenu;
        QMenu* _rendering;
        QAction* _pointcrowds;
        QAction* _wireflame;
        QAction* _flatshading;
        QMenu* _light;
        QMenu* _camera;

        QMenu* _tool;
};
#endif // __MAIN_WINDOW_HPP__
