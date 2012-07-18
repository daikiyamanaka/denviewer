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
#include "PreferencesDialog.hpp"

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
        PreferencesDialog *_dialog;
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
        void polygon_wireframe ( bool checked );
        void polygon_surface ( bool checked );
        void polygon_point ( bool checked );
        void shading_flat ( void );
        void shading_smooth( void );
        void view_fit ( void );
        void view_init ( void );
        void mouse_dragged ( float x, float y );
        void update_surface_color(void);
        void update_color(void);
        void update_wire_width(void);
        void update_perspective_angle(void);
		//Yamauchi
		void update_camera_position(double xpos , double ypos , double zpos);
		void update_euler_angle(int alpha , int beta , int gamma);
		void initialize_camera_position();
        void wheel_spined( float x , float y , float step );
        void back_camera( void );
        void forward_camera( void );
        void add_now_camera_to_list( void );
        void save_mesh_binary( bool isBinary );
		//end
        void file_dropped(QString str);
        void get_ver_face(void);//imamura
        //
        void lightswitch0(bool i);
        void lightswitch1(bool i);
        void lightswitch2(bool i);
        void lightset(void);

        void changePreference(void);

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
        QAction* preferenceAct;
        //
        QMenu* _showmenu;
        QMenu* _rendering;
        QAction* _pointcrowds;
        QAction* _wireflame;
        QAction* _flatshading;
        QMenu* _light;
        QMenu* _camera;

/*<<<<<<< HEAD
        QMenu* _tool;
=======*/
        QMenu* _viewMenu;
        QMenu* _renderingSubMenu;
        QMenu* _lightSubMenu;
        QMenu* _cameraSubMenu;
        QMenu* _toolMenu;
        QAction* _renderPointAct;
        QAction* _renderWireAct;
        QAction* _renderMeshAct;
        //QRadioButton* _pointRadioButton;
        //QRadioButton* _wireRadioButton;
        //QRadioButton* _surfaceRadioButton;
        QCheckBox* _pointCheckBox;
        QCheckBox* _wireCheckBox;
        QCheckBox* _surfaceCheckBox;

        QRadioButton* _flatRadioButton;
        QRadioButton* _smoothRadioButton;

        QAction* _lightAct1;
        QAction* _lightAct2;
        QAction* _lightAct3;
        QCheckBox* _lightCheckBox1;
        QCheckBox* _lightCheckBox2;
        QCheckBox* _lightCheckBox3;

        QAction* _backCamera;
        QAction* _forwardCamera;

        QRadioButton* _saveMeshBinaryButton;
        QRadioButton* _saveMeshAsciiButton;
        bool _saveBinary;




//>>>>>>> master
};
#endif // __MAIN_WINDOW_HPP__
