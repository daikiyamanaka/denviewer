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
#include "ChangePointSizeWidget.hpp"
#include "ChangeViewAngle.h"
#include "GetCameraParameterWidget.hpp"
#include "GetLightParameterWidget.hpp"
#include "ShowVandFWidget.hpp"
//#include "ChangeWindowSizeWidget.hpp"//imamura
#include "PreferencesDialog.hpp"
#include "ModelLayerWidget.hpp"
#include "NormalDisplayWidget.hpp"
#include "projectionmodewidget.h"

class MainWindow : public QMainWindow
{
        Q_OBJECT
private:
        Model& _model;
        View& _view;
        GLWidget* _glwidget;
        ChangeColorWidget* _colorWidget;
        ChangeWireWidthWidget* _wireWidthWidget;
        ChangePointSizeWidget* _pointSizeWidget;
        ChangeViewAngle* _viewWidget;
		GetCameraParameterWidget* _cameraParameterWidget;
        GetLightParameterWidget* _lightParameterWidget;
        ShowVandFWidget* _VandFWidget;//imamura

        NormalDisplayWidget* _normalDisplayWidget;
        ProjectionModeWidget* _projectionModeWidget;

        //ChangeWindowSizeWidget* _windowWidget;
        //int oldw, oldh;
        PreferencesDialog *_dialog;
        ModelLayerWidget* modelLayerWidget;


public:
        MainWindow ( Model& model, View& view, QApplication& app ) ;
protected:
        //void contextMenuEvent ( QContextMenuEvent* event );
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
        void update_point_size(void);
        void update_perspective_angle(void);
		//Yamauchi
		void update_camera_position(double xpos , double ypos , double zpos);
		void update_euler_angle(int alpha , int beta , int gamma);
		void initialize_camera_position();
        void wheel_spined( float x , float y , float step );
        void back_camera( void );
        void forward_camera( void );
        void add_now_camera_to_list( void );
        void update_normal_display( void );
        void update_projection_mode( void );
		//end
        void file_dropped(QStringList strs);
        void get_ver_face(void);//imamura
        //
        void lightswitch0(bool i);
        void lightswitch1(bool i);
        void lightswitch2(bool i);
        void lightset(void);

        void update_window_size(int width, int height);
        void set_width_height(int width, int height);
        void set_carrow(bool i);

        void changePreference(void);
        void changeModelLayer(void);

        void checkBinary(QString str);

        void save_mesh_binary(bool isBinary);
        void change_active_mesh_index( void );
        void change_pallet_color_to_Id_mesh( int id );

        void swap_xy( void );
        void swap_yz( void );
        void swap_zx( void );
        void flip_x(void);
        void flip_y(void);
        void flip_z(void);

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

        QMenu* _viewMenu;
        QMenu* _renderingSubMenu;
        QMenu* _lightSubMenu;
        QMenu* _cameraSubMenu;
        QMenu* _toolMenu;
        QMenu* _swapToolSubMenu;
        QMenu* _flipToolSubMenu;

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

        QAction* _backCameraAct;
        QAction* _forwardCameraAct;

        QAction* _viewInitAct;
        QAction* _viewFitAct;

        QAction* _swapXYAct;
        QAction* _swapYZAct;
        QAction* _swapZXAct;
        QAction* _flipXAct;
        QAction* _flipYAct;
        QAction* _flipZAct;


        bool _saveBinary;

};
#endif // __MAIN_WINDOW_HPP__
