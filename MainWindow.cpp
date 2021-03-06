#include "MainWindow.hpp"
#include "GLWidget.hpp"
#include <QtGui>
#include <iostream>

MainWindow::MainWindow ( Model& model, View& view, QApplication &app ) : _model ( model ), _view ( view )
{
    QWidget* widget = new QWidget;
    widget->setContentsMargins ( 5,5,5,5 );

    this->setCentralWidget ( widget );
    this->_glwidget = new GLWidget ( this->_model,  this->_view, widget );
    connect ( this->_glwidget, SIGNAL ( mouseDragged ( float, float ) ), this, SLOT ( mouse_dragged ( float, float ) ) );
    connect ( this->_glwidget, SIGNAL ( fileDropped ( QStringList ) ), this, SLOT ( file_dropped(QStringList)));
    connect ( this->_glwidget, SIGNAL ( wheelSpined(float,float,float) ), this , SLOT(wheel_spined(float,float,float) ) );

    //Rendering Mode
    this->_pointCheckBox = new QCheckBox(tr("Points"));
    this->_pointCheckBox->setChecked(false);
    this->_wireCheckBox = new QCheckBox(tr("Wireframe"));
    this->_wireCheckBox->setChecked(false);
    this->_surfaceCheckBox = new QCheckBox(tr("Surface"));
    this->_surfaceCheckBox->setChecked(true);

    int wirewidth = this->_model.getWireWidth();
    this->_wireWidthWidget = new ChangeWireWidthWidget(wirewidth);
    connect( this->_wireWidthWidget, SIGNAL(updated()), this, SLOT(update_wire_width()));
    this->_pointSizeWidget = new ChangePointSizeWidget(1);
    connect( this->_pointSizeWidget, SIGNAL(updated()), this, SLOT(update_point_size()));

    float nLength = this->_model.getVectorLength();
    this->_normalDisplayWidget = new NormalDisplayWidget(nLength);
    connect(this->_normalDisplayWidget, SIGNAL(updated()), this, SLOT(update_normal_display()));

    bool perspective = this->_view.getPerspective();
    this->_projectionModeWidget = new ProjectionModeWidget(perspective);
    connect(this->_projectionModeWidget, SIGNAL(updated()), this,SLOT(update_projection_mode()));

    QGridLayout *renderModeGridLayout = new QGridLayout;

    renderModeGridLayout->addWidget(this->_pointCheckBox,0,0,Qt::AlignLeft);
    renderModeGridLayout->addWidget(this->_wireCheckBox,1,0,Qt::AlignLeft);
    renderModeGridLayout->addWidget(this->_surfaceCheckBox,2,0,Qt::AlignLeft);
    renderModeGridLayout->addWidget(this->_pointSizeWidget,0,1,Qt::AlignRight);
    renderModeGridLayout->addWidget(this->_wireWidthWidget,1,1,Qt::AlignRight);


    QGroupBox *groupBox_renderingMode = new QGroupBox ( tr ( "Rendering Mode" ) );
    groupBox_renderingMode->setLayout ( renderModeGridLayout );

    //Shading Mode
    this->_flatRadioButton = new QRadioButton( tr("Flat") );
    this->_smoothRadioButton = new QRadioButton( tr("Smooth") );
    this->_smoothRadioButton->setChecked(true);
    connect (this->_flatRadioButton, SIGNAL(pressed()), this , SLOT(shading_flat()) );
    connect (this->_smoothRadioButton, SIGNAL(pressed()), this , SLOT(shading_smooth()) );

    QVBoxLayout *boxLayout_shading = new QVBoxLayout;
    boxLayout_shading->addWidget ( this->_flatRadioButton );
    boxLayout_shading->addWidget( this->_smoothRadioButton);
    boxLayout_shading->addStretch(1);

    QGroupBox *groupBox_shading = new QGroupBox(tr("Shading Mode"));
    groupBox_shading->setLayout(boxLayout_shading);

    //Normal display
    QGroupBox *groupBox_normal = new QGroupBox(tr("Normal"));
    QVBoxLayout *boxLayout_normal = new QVBoxLayout;
    boxLayout_normal->addWidget(this->_normalDisplayWidget);
    groupBox_normal->setLayout(boxLayout_normal);

    //view
    QPushButton *button1 = new QPushButton ( tr ( "View Fit" ) ) ;
    QPushButton *button2 = new QPushButton ( tr ( "View Init" ) ) ;
    connect ( button1, SIGNAL ( pressed() ), this, SLOT ( view_fit() ) );
    connect ( button2, SIGNAL ( pressed() ), this, SLOT ( view_init() ) );

    //color
	int r,g,b;
    this->_model.getSurfaceColor (0, r,g,b );
    QColor face(r,g,b);
    this->_model.getBackgroundColor(0,r, g, b);
    QColor background(r, g, b);
    this->_model.getWireColor(0,r, g, b);
    QColor wire(r, g, b);
    this->_model.getVertexColor(0,r, g, b);
    QColor vertex(r, g, b);
    this->_model.getLightColor(r, g, b);
    QColor light(r, g, b);
    this->_colorWidget = new ChangeColorWidget(face, background, wire, vertex, light);
    connect ( this->_colorWidget, SIGNAL(updated()), this, SLOT(update_color()));
    QGroupBox *groupBox_color = new QGroupBox(tr("Colors"));
    QVBoxLayout *boxLayout_color = new QVBoxLayout;
    boxLayout_color->addWidget(this->_colorWidget);
    groupBox_color->setLayout(boxLayout_color);


    //view angle
    float angle = this->_model.getViewAngle();
    this->_viewWidget = new ChangeViewAngle(angle);
    connect(this->_viewWidget, SIGNAL(updated()), this, SLOT(update_perspective_angle()));


    //windowsize
    /*int width = 800;
    int height = 600;
    this->_windowWidget = new ChangeWindowSizeWidget(width, height);
    connect(this->_windowWidget, SIGNAL(updated(int,int)), this, SLOT(update_window_size(int,  int)));
    connect (this->_windowWidget, SIGNAL(sizechanged(int,int)), this, SLOT(set_width_height(int,int)));
*/
    QCheckBox* _centerarrow = new QCheckBox(tr("Center Arrow"));
    connect(_centerarrow, SIGNAL(toggled(bool)), this, SLOT(set_carrow(bool)));
    _centerarrow->setChecked(true);

    //camera
	int alpha , beta , gamma;
    double xpos , ypos , zpos;
    this->_model.getEulerAngle(alpha , beta , gamma);
    this->_model.getCameraPosition(xpos,ypos,zpos);
    this->_cameraParameterWidget = new GetCameraParameterWidget( alpha , beta , gamma , xpos , ypos, zpos );
    connect(this->_cameraParameterWidget, SIGNAL(CameraPositionUpdated(double,double,double)) ,
            this , SLOT(update_camera_position(double,double,double)));
    connect(this , SIGNAL(cameraInitialized()) , this , SLOT(initialize_camera_position()));
    connect(this->_cameraParameterWidget,SIGNAL(EulerAngleUpdated(int,int,int)),
            this , SLOT(update_euler_angle(int,int,int)));

    connect(this->_cameraParameterWidget, SIGNAL(ParameterChanged()) , this , SLOT(add_now_camera_to_list()));

    //light
    this->_lightCheckBox1 = new QCheckBox(tr ( "Key Light" ));
    this->_lightCheckBox2 = new QCheckBox(tr ( "Fill Light" ));
    this->_lightCheckBox3 = new QCheckBox(tr ( "Back Light" ));
    connect ( this->_lightCheckBox1, SIGNAL ( toggled(bool) ), this, SLOT ( lightswitch0(bool) ) );
    connect ( this->_lightCheckBox2, SIGNAL ( toggled(bool) ), this, SLOT ( lightswitch1(bool) ) );
    connect ( this->_lightCheckBox3, SIGNAL ( toggled(bool) ), this, SLOT ( lightswitch2(bool) ) );
    this->_lightCheckBox1->setChecked(true);
    this->_lightCheckBox2->setChecked(true);
    this->_lightCheckBox3->setChecked(true);

    QPushButton *lightbutton = new QPushButton ( tr ( "Light Fit" ) ) ;
    connect ( lightbutton, SIGNAL ( pressed() ), this, SLOT ( lightset() ) );

    QVBoxLayout *boxLayout_lightCheckBox = new QVBoxLayout;
    boxLayout_lightCheckBox->addWidget ( this->_lightCheckBox1 );
    boxLayout_lightCheckBox->addWidget ( this->_lightCheckBox2 );
    boxLayout_lightCheckBox->addWidget ( this->_lightCheckBox3 );
    boxLayout_lightCheckBox->addWidget ( lightbutton );
    boxLayout_lightCheckBox->addStretch ( 1 );

    QGroupBox *groupBox_light = new QGroupBox ( tr ( "Light" ) );
    groupBox_light->setLayout ( boxLayout_lightCheckBox );

    this->_VandFWidget = new ShowVandFWidget();//imamura

    //ViewTab�p
    QVBoxLayout *boxLayout_viewTab = new QVBoxLayout;
    boxLayout_viewTab->addWidget ( groupBox_renderingMode );
    boxLayout_viewTab->addWidget ( groupBox_shading );
    boxLayout_viewTab->addWidget(groupBox_normal);
    boxLayout_viewTab->addWidget(this->_projectionModeWidget);
    boxLayout_viewTab->addWidget ( button1 );
    boxLayout_viewTab->addWidget ( button2 );
    //boxLayout_viewTab->addWidget ( this->_colorWidget);
    boxLayout_viewTab->addWidget ( _centerarrow );
    boxLayout_viewTab->addStretch ( 1 );

    //cameraTab�p
    QVBoxLayout *boxLayout_cameraTab = new QVBoxLayout;
    boxLayout_cameraTab->addWidget(this->_cameraParameterWidget);
    boxLayout_cameraTab->addWidget(this->_viewWidget);
    boxLayout_cameraTab->addStretch( 1 );

    //MeshInfoTab�p
    QVBoxLayout *boxLayout_infoTab = new QVBoxLayout;
    boxLayout_infoTab->addWidget(groupBox_color);
    boxLayout_infoTab->addWidget ( this->_VandFWidget);//imamura
    //boxLayout_infoTab->addWidget(_centerarrow);
    //boxLayout_infoTab->addWidget(this->_normalDisplayWidget);
    boxLayout_infoTab->addStretch( 1 );

    //LightTab�p

    //
    QWidget* widget_vewTab = new QWidget;
    widget_vewTab->setLayout(boxLayout_viewTab);

    QWidget* widget_cameraTab = new QWidget;
    widget_cameraTab->setLayout(boxLayout_cameraTab);

    QWidget* widget_infoTab = new QWidget;
    widget_infoTab->setLayout(boxLayout_infoTab);

    QWidget* widget_lightTab = new QWidget;
    widget_lightTab->setLayout(boxLayout_lightCheckBox);

    QTabWidget* tabwidget_propaties = new QTabWidget;
    tabwidget_propaties->addTab ( widget_vewTab, tr ( "Views" ) );
    tabwidget_propaties->addTab(widget_cameraTab ,tr("Camera") );
    tabwidget_propaties->addTab(widget_infoTab ,tr("Mesh") );
    tabwidget_propaties->addTab(widget_lightTab, tr("Light"));
    tabwidget_propaties->setMinimumWidth ( 250 );

    QTabWidget* tabwidget_model = new QTabWidget;
    modelLayerWidget = new ModelLayerWidget;
    tabwidget_model->addTab ( modelLayerWidget, tr ( "ModelLayer" ) );
    tabwidget_model->setMinimumWidth ( 200 );

    connect(this->modelLayerWidget, SIGNAL(updated()), this, SLOT(changeModelLayer()));
    connect(this->modelLayerWidget, SIGNAL(selectedItemChanged()) , this , SLOT(change_active_mesh_index()));

        //connect ( this, SIGNAL ( updated() ), this->_glwidget, SLOT ( updateGL() ) );
        //std::cerr << "w =" << this->size().width() << " h = " <<this->size().height() << std::endl;


    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin ( 5 );
    layout->addWidget ( tabwidget_model );
    layout->addWidget ( this->_glwidget );
    layout->addWidget ( tabwidget_propaties );

    widget->setLayout ( layout );

    QString message = tr ( "A context menu is not available by right-clicking" );

    this->statusBar()->showMessage ( message );

    this->create_actions();
    this->create_menus();
    this->create_toolbars();
    this->setWindowTitle ( tr ( "Viewer" ) );
    this->setMinimumSize ( 1000, 700 );
    this->resize ( 1000, 700 );

    connect ( this, SIGNAL ( updated() ), this->_glwidget, SLOT ( updateGL() ) );

    //Preference Dialog
    _dialog = new PreferencesDialog(this, this->_model.getPreferences().at(0));

    if( app.argc() != 1){

        for( int i = 1 ; i < app.argc() ; i++ ){
            std::string filename( app.argv()[i]);
            if( !this->_model.openMesh ( filename ) ){
                QString message ( tr ( "Open failed." ) );
                statusBar()->showMessage ( message );
            }else{
                emit updated();
                emit cameraInitialized();
                this->modelLayerWidget->addList(filename);
                this->get_ver_face();
                //this->_view.createDisplayList();
                this->_view.addDrawMeshList(this->_model.getMesh().size()-1);
                this->_model.setActiveMeshIndex( this->_model.getMesh().size()-1 );
                this->change_pallet_color_to_Id_mesh( this->_model.getMesh().size()-1 );

            }
        }

    }

    return;

}

//Pop-up menu
/*
void
MainWindow::contextMenuEvent ( QContextMenuEvent* event )
{
        QMenu menu ( this );
        menu.addAction ( this->_newAct );
        menu.addAction ( this->_openAct );
        menu.addAction ( this->_saveAct );
        menu.exec ( event->globalPos() );
        return;
}*/

void
MainWindow::create_actions ( void )
{
        //New
        this->_newAct = new QAction ( QIcon ( ":/resources/new.png" ),tr ( "&New" ), this );
        this->_newAct->setShortcuts ( QKeySequence::New );
        this->_newAct->setStatusTip ( "Create a new file" );
        connect ( this->_newAct, SIGNAL ( triggered() ), this, SLOT ( new_file() ) );
        connect ( this->_newAct, SIGNAL ( triggered() ), this->_glwidget, SLOT ( updateGL() ) );

        //Open
        this->_openAct = new QAction ( QIcon ( ":/resources/open.png" ),tr ( "&Open" ), this );
        this->_openAct->setShortcuts ( QKeySequence::Open );
        this->_openAct->setStatusTip ( "Open a file" );
        connect ( this->_openAct, SIGNAL ( triggered() ), this, SLOT ( open() ) );
        connect ( this->_openAct, SIGNAL ( triggered() ), this->_glwidget, SLOT ( updateGL() ) );

        //Save
        this->_saveAct = new QAction ( QIcon ( ":/resources/save.png" ),tr ( "&Save" ), this );
        this->_saveAct->setShortcuts ( QKeySequence::Save );
        this->_saveAct->setStatusTip ( "Save a file" );
        connect ( this->_saveAct, SIGNAL ( triggered() ), this, SLOT ( save() ) );

        //Open
        this->_openCameraAct = new QAction ( QIcon ( ":/resources/openCamera.png" ),tr ( "Open Camera" ), this );
        this->_openCameraAct->setStatusTip ( "Open a camera file" );
        connect ( this->_openCameraAct, SIGNAL ( triggered() ), this, SLOT ( openCamera() ) );
        connect ( this->_openCameraAct, SIGNAL ( triggered() ), this->_glwidget, SLOT ( updateGL() ) );

        //Save
        this->_saveCameraAct = new QAction ( QIcon ( ":/resources/saveCamera.png" ),tr ( "Save Camera" ), this );
        this->_saveCameraAct->setStatusTip ( "Save a camera file" );
        connect ( this->_saveCameraAct, SIGNAL ( triggered() ), this, SLOT ( saveCamera() ) );

        //Save
        this->_snapshotAct = new QAction ( QIcon ( ":/resources/save.png" ),tr ( "Snapshot" ), this );
        this->_snapshotAct->setStatusTip ( "Snapshot" );
        connect ( this->_snapshotAct, SIGNAL ( triggered() ), this, SLOT ( saveSnapshot() ) );

        //Exit
        this->_exitAct = new QAction ( tr ( "E&xit" ), this );
        this->_exitAct->setShortcuts ( QKeySequence::Quit );
        this->_exitAct->setStatusTip ( "Exit this application." );
        connect ( this->_exitAct, SIGNAL ( triggered() ), this, SLOT ( close() ) );

        //Preference
        this->preferenceAct = new QAction( QIcon ( ":/resources/preference.png" ), tr("&Preferences"), this);
        connect(this->preferenceAct, SIGNAL(triggered()), this, SLOT( changePreference()));

        this->_backCameraAct = new QAction( QIcon ( ":/resources/camera_back.png" ),tr("Back Camera") , this );
        this->_backCameraAct->setShortcut(QKeySequence::Undo);
        this->_backCameraAct->setStatusTip ( "Back Camera." );
        connect ( this->_backCameraAct, SIGNAL ( triggered() ), this , SLOT(back_camera()) );

        this->_forwardCameraAct = new QAction( QIcon ( ":/resources/camera_forward.png" ), tr("Forward Camera") , this );
        this->_forwardCameraAct->setShortcut(QKeySequence::Redo);
        this->_forwardCameraAct->setStatusTip ( "Forward Camera." );
        connect ( this->_forwardCameraAct, SIGNAL ( triggered() ), this , SLOT(forward_camera()) );

        this->_forwardCameraAct = new QAction( QIcon ( ":/resources/camera_forward.png" ), tr("Forward Camera") , this );
        this->_forwardCameraAct->setShortcut(QKeySequence::Redo);
        this->_forwardCameraAct->setStatusTip ( "Forward Camera." );
        connect ( this->_forwardCameraAct, SIGNAL ( triggered() ), this , SLOT(forward_camera()) );

        this->_viewFitAct = new QAction( QIcon ( ":/resources/view_fit.png" ), tr("View Fit") , this );
        this->_viewFitAct->setShortcut(QKeySequence::Redo);
        this->_viewFitAct->setStatusTip ( "View Fit." );
        connect ( this->_viewFitAct, SIGNAL ( triggered() ), this , SLOT(view_fit()) );

        this->_viewInitAct = new QAction( QIcon ( ":/resources/view_init.png" ), tr("View Init") , this );
        this->_viewInitAct->setShortcut(QKeySequence::Redo);
        this->_viewInitAct->setStatusTip ( "View Init." );
        connect ( this->_viewInitAct, SIGNAL ( triggered() ), this , SLOT(view_init()) );


        this->_viewFitAct = new QAction( QIcon ( ":/resources/view_fit.png" ), tr("View Fit") , this );
        this->_viewFitAct->setShortcut(QKeySequence::Redo);
        this->_viewFitAct->setStatusTip ( "View Fit." );
        connect ( this->_viewFitAct, SIGNAL ( triggered() ), this , SLOT(view_fit()) );

        this->_viewInitAct = new QAction( QIcon ( ":/resources/view_init.png" ), tr("View Init") , this );
        this->_viewInitAct->setShortcut(QKeySequence::Redo);
        this->_viewInitAct->setStatusTip ( "View Init." );
        connect ( this->_viewInitAct, SIGNAL ( triggered() ), this , SLOT(view_init()) );

        this->_renderPointAct = new QAction( tr("&Point") , this );
        this->_renderPointAct->setStatusTip("Rendering Points");
        this->_renderPointAct->setCheckable(true);
        //this->_renderPointAct->toggled();
        connect(this->_renderPointAct , SIGNAL(toggled(bool)), this , SLOT(polygon_point(bool)));
        //connect(this->_renderPointAct , SIGNAL(toggled(bool)), this->_pointRadioButton , SLOT(setChecked(bool)));
        //connect(this->_pointRadioButton , SIGNAL(toggled(bool)), this->_renderPointAct , SLOT(setChecked(bool)));
        connect(this->_renderPointAct , SIGNAL(toggled(bool)), this->_pointCheckBox , SLOT(setChecked(bool)));
        connect(this->_pointCheckBox, SIGNAL(toggled(bool)), this->_renderPointAct, SLOT(setChecked(bool)));

        this->_renderWireAct = new QAction( tr("&Wire") , this );
        this->_renderWireAct->setStatusTip("Rendering Wireflame");
        this->_renderWireAct->setCheckable(true);
        connect(this->_renderWireAct , SIGNAL(toggled(bool)), this , SLOT(polygon_wireframe(bool)));
        //connect(this->_renderWireAct , SIGNAL(toggled(bool)), this->_wireRadioButton , SLOT(setChecked(bool)));
        //connect( this->_wireRadioButton , SIGNAL(toggled(bool)), this->_renderWireAct , SLOT(setChecked(bool)));
        connect(this->_renderWireAct , SIGNAL(toggled(bool)), this->_wireCheckBox , SLOT(setChecked(bool)));
        connect( this->_wireCheckBox , SIGNAL(toggled(bool)), this->_renderWireAct , SLOT(setChecked(bool)));

        this->_renderMeshAct = new QAction( tr("&Surface") , this );
        this->_renderMeshAct->setStatusTip("Rendering Surface");
        this->_renderMeshAct->setCheckable(true);
        this->_renderMeshAct->setChecked(true);
        connect(this->_renderMeshAct , SIGNAL(toggled(bool)), this , SLOT(polygon_surface(bool)));
        //connect(this->_renderMeshAct, SIGNAL(toggled(bool)), this->_surfaceRadioButton , SLOT(setChecked(bool)));
        //connect(this->_surfaceRadioButton, SIGNAL(toggled(bool)), this->_renderMeshAct , SLOT(setChecked(bool)));
        connect(this->_renderMeshAct, SIGNAL(toggled(bool)), this->_surfaceCheckBox , SLOT(setChecked(bool)));
        connect( this->_surfaceCheckBox , SIGNAL(toggled(bool)), this->_renderMeshAct , SLOT(setChecked(bool)));

        this->_lightAct1 = new QAction( tr("Key Light"), this);
        this->_lightAct1->setCheckable(true);
        this->_lightAct1->setChecked(true);
        connect(this->_lightAct1 , SIGNAL(triggered(bool)), this->_lightCheckBox1 , SLOT(setChecked(bool)));
        connect(this->_lightCheckBox1 , SIGNAL(toggled(bool)) , this->_lightAct1 , SLOT(setChecked(bool)));

        this->_lightAct2 = new QAction( tr("Fill Light"), this);
        this->_lightAct2->setCheckable(true);
        this->_lightAct2->setChecked(true);
        connect(this->_lightAct2 , SIGNAL(triggered(bool)), this->_lightCheckBox2 , SLOT(setChecked(bool)));
        connect(this->_lightCheckBox2 , SIGNAL(toggled(bool)) , this->_lightAct2 , SLOT(setChecked(bool)));

        this->_lightAct3 = new QAction( tr("Back Light"), this);
        this->_lightAct3->setCheckable(true);
        this->_lightAct3->setChecked(true);
        connect(this->_lightAct3 , SIGNAL(triggered(bool)), this->_lightCheckBox3 , SLOT(setChecked(bool)));
        connect(this->_lightCheckBox3 , SIGNAL(toggled(bool)) , this->_lightAct3 , SLOT(setChecked(bool)));

        //Tool
        this->_swapXYAct = new QAction ( tr("Swap XY Axis"), this );
        connect(this->_swapXYAct, SIGNAL( triggered()), this, SLOT(swap_xy()) );
        this->_swapYZAct = new QAction ( tr("Swap YZ Axis"), this );
        connect(this->_swapYZAct, SIGNAL( triggered()), this, SLOT(swap_yz()) );
        this->_swapZXAct = new QAction ( tr("Swap ZX Axis"), this );
        connect(this->_swapZXAct, SIGNAL( triggered()), this, SLOT(swap_zx()) );
        this->_flipXAct = new QAction ( tr("Flip X Axis"), this );
        connect(this->_flipXAct, SIGNAL(triggered()), this, SLOT(flip_x()) );
        this->_flipYAct = new QAction ( tr("Flip Y Axis"), this );
        connect(this->_flipYAct, SIGNAL(triggered()), this, SLOT(flip_y()) );
        this->_flipZAct = new QAction ( tr("Flip Z Axis"), this );
        connect(this->_flipZAct, SIGNAL(triggered()), this, SLOT(flip_z()) );

        return;
}
void
MainWindow::create_menus ( void )
{
    this->_fileMenu = menuBar()->addMenu ( tr ( "&File" ) );
    this->_fileMenu->addAction ( this->_newAct );
    this->_fileMenu->addAction ( this->_openAct );
    this->_fileMenu->addAction ( this->_saveAct );
    this->_fileMenu->addAction ( this->_openCameraAct );
    this->_fileMenu->addAction ( this->_saveCameraAct );
    this->_fileMenu->addAction ( this->_snapshotAct );
    this->_fileMenu->addSeparator();
    this->_fileMenu->addAction ( this->_exitAct );

    this->_viewMenu = menuBar()->addMenu( tr("&View")  );
    this->_renderingSubMenu = this->_viewMenu->addMenu(tr("&Rendering Mode"));
    this->_renderingSubMenu->addAction(this->_renderPointAct);
    this->_renderingSubMenu->addAction(this->_renderWireAct);
    this->_renderingSubMenu->addAction(this->_renderMeshAct);
    this->_lightSubMenu = this->_viewMenu->addMenu(tr("light"));
    this->_lightSubMenu->addAction(this->_lightAct1);
    this->_lightSubMenu->addAction(this->_lightAct2);
    this->_lightSubMenu->addAction(this->_lightAct3);
    this->_cameraSubMenu = this->_viewMenu->addMenu(tr("camera"));
    this->_cameraSubMenu->addAction(this->_backCameraAct);
    this->_cameraSubMenu->addAction(this->_forwardCameraAct);

    this->_toolMenu = menuBar()->addMenu(tr("&Tools"));
    this->_flipToolSubMenu = this->_toolMenu->addMenu(tr("Flip"));
    this->_flipToolSubMenu->addAction(this->_flipXAct);
    this->_flipToolSubMenu->addAction(this->_flipYAct);
    this->_flipToolSubMenu->addAction(this->_flipZAct);
    this->_swapToolSubMenu = this->_toolMenu->addMenu(tr("Swap"));
    this->_swapToolSubMenu->addAction(this->_swapXYAct);
    this->_swapToolSubMenu->addAction(this->_swapYZAct);
    this->_swapToolSubMenu->addAction(this->_swapZXAct);


     return;
}

void
MainWindow::create_toolbars ( void )
{
    this->_fileToolBar = addToolBar ( tr ( "File" ) );
    this->_fileToolBar->addAction ( this->_newAct );
    this->_fileToolBar->addAction ( this->_openAct );
    this->_fileToolBar->addAction ( this->_saveAct );
    this->_fileToolBar->addAction ( this->_openCameraAct );
    this->_fileToolBar->addAction ( this->_saveCameraAct );

    this->_fileToolBar->addSeparator();
    this->_fileToolBar->addAction ( this->_backCameraAct);
    this->_fileToolBar->addAction ( this->_forwardCameraAct);
    this->_fileToolBar->addAction( this->_viewFitAct);
    this->_fileToolBar->addAction( this->_viewInitAct);

    this->_fileToolBar->addSeparator();
    this->_fileToolBar->addAction( this->preferenceAct);
    return ;
}

void
MainWindow::new_file ( void )
{
    this->_model.initMesh();
    this->_view.deleteAllDrawMeshList();
    this->_view.init();
    this->modelLayerWidget->deleteAll();
    QString message = tr ( "Initialized." );
    statusBar()->showMessage ( message );
    emit updated();
    emit cameraInitialized();
    return;
}

void
MainWindow::open ( void )
{
    QStringList fileFilterList;
    fileFilterList += tr("Supported File(*.stl *.obj *.pcd)");
    fileFilterList += tr("STL File(*.stl)");
    fileFilterList += tr("OBJ File(*.obj)");
    fileFilterList += tr("PCD File(*.pcd)");
    fileFilterList += tr("All files(*.*)");

    QFileDialog *openDlg = new QFileDialog( this , tr("Open File"),".");
    openDlg->setNameFilters(fileFilterList);
    openDlg->setAcceptMode(QFileDialog::AcceptOpen);
    QStringList fileNames;
    if( openDlg->exec() ){
        fileNames = openDlg->selectedFiles();
    }

    //QString filename = QFileDialog::getOpenFileName ( this, tr ( "Open file from" ), ".", tr ( "STL File (*.stl)" ) );
    for(int i = 0 ; i < fileNames.size() ; i++){
        if ( !this->_model.openMesh ( fileNames.at(i).toStdString() ) ) {
                QString message ( tr ( "Open failed." ) );
                statusBar()->showMessage ( message );
                return;
        } else {
            emit updated();
            emit cameraInitialized();
            this->modelLayerWidget->addList(QFileInfo(fileNames.at(i)).fileName().toStdString());
            this->get_ver_face();
            //this->_view.createDisplayList();
            this->_view.addDrawMeshList(this->_model.getMesh().size()-1);
            this->_model.setActiveMeshIndex( this->_model.getMesh().size()-1 );
            this->change_pallet_color_to_Id_mesh( this->_model.getMesh().size()-1 );
        }

    }
//    if ( fileNames.size()==0 || !this->_model.openMesh ( fileNames.at(0).toStdString() ) ) {
//            QString message ( tr ( "Open failed." ) );
//            statusBar()->showMessage ( message );
//            return;
//    } else {
//        emit updated();
//        emit cameraInitialized();
//        this->modelLayerWidget->addList(QFileInfo(fileNames.at(0)).fileName().toStdString());
//        this->get_ver_face();
//        //this->_view.createDisplayList();
//        this->_view.addDrawMeshList(this->_model.getMesh().size()-1);
//        this->_model.setActiveMeshIndex( this->_model.getMesh().size()-1 );
//        this->change_pallet_color_to_Id_mesh( this->_model.getMesh().size()-1 );
//    }
    return;
}

void
MainWindow::save ( void )
{
    QStringList fileFilterList;
    fileFilterList += tr("STL File Ascii(*.stl)");
    fileFilterList += tr("STL File Binary(*.stl)");
    fileFilterList += tr("OBJ File(*.obj)");

    QFileDialog *saveDlg = new QFileDialog( this , tr("Save File"),".");
    saveDlg->setNameFilters(fileFilterList);
    saveDlg->setAcceptMode(QFileDialog::AcceptSave);
    saveDlg->setConfirmOverwrite(true);
    this->_saveBinary = false;

    connect(saveDlg , SIGNAL(filterSelected(QString)) , this , SLOT(checkBinary(QString)) );

    QStringList fileNames;
    if(saveDlg->exec()){
        fileNames = saveDlg->selectedFiles();
    }
    if ( fileNames.size()==0 || !this->_model.saveMesh ( fileNames.at(0).toStdString() , this->_saveBinary , this->modelLayerWidget->getSelectedIndex() ) ) {
            QString message ( tr ( "Save failed." ) );
            statusBar()->showMessage ( message );
            return;
    }

    return;
}

void
MainWindow::openCamera ( void )
{
    QString filename = QFileDialog::getOpenFileName ( this, tr ( "Open camera file from" ), ".", tr ( "CAM File (*.cam)" ) );
    if ( !this->_model.openCamera ( filename.toStdString() ) ) {
            QString message ( tr ( "Open failed." ) );
            statusBar()->showMessage ( message );
    } else emit updated(); emit cameraInitialized();
    return;
}

void
MainWindow::saveCamera ( void )
{
    QString filename = QFileDialog::getSaveFileName ( this, tr ( "Save camera file to" ), ".", tr ( "CAM File (*.cam)" ) );
    if ( !this->_model.saveCamera ( filename.toStdString() ) ) {
            QString  message ( tr ( "Save failed." ) );
            statusBar()->showMessage ( message );
    }
    return;
}

void
MainWindow::polygon_wireframe ( bool checked)
{
    this->_model.setRenderingMode(this->_model.getRenderingMode() | WIRE);
    if(!checked) this->_model.setRenderingMode(this->_model.getRenderingMode() ^ WIRE);
    QString  message ( tr ( "Wireframe mode" ) );
    statusBar()->showMessage ( message );
    emit updated();
    return;
}

void
MainWindow::polygon_surface ( bool checked)
{
    this->_model.setRenderingMode (this->_model.getRenderingMode() | SURFACE);
    if(!checked) this->_model.setRenderingMode (this->_model.getRenderingMode() ^ SURFACE);
    QString  message ( tr ( "Surface mode" ) );
    statusBar()->showMessage ( message );
    emit updated();
    return;
}

void
MainWindow::polygon_point( bool checked)
{
    this->_model.setRenderingMode (this->_model.getRenderingMode() | POINTCLOUD);
    if(!checked) this->_model.setRenderingMode (this->_model.getRenderingMode() ^ POINTCLOUD);
    QString  message ( tr ( "Point mode" ) );
    statusBar()->showMessage ( message );
    emit updated();
    return;
}

void
MainWindow::shading_flat( void )
{
    this->_model.setShadingMode(FLAT);
    QString  message ( tr ( "Flat shading" ) );
    statusBar()->showMessage ( message );
    //this->_view.createDisplayList();
    emit updated();
    return;
}

void
MainWindow::shading_smooth( void )
{
    this->_model.setShadingMode(SMOOTH);
    QString  message ( tr ( "Smooth shading" ) );
    statusBar()->showMessage ( message );
    //this->_view.createDisplayList();
    emit updated();
    return;
}

void
MainWindow::view_fit ( void )
{

    if(!this->_model.viewFit()){
        return;
    }

    QString  message ( tr ( "View fit" ) );
    statusBar()->showMessage ( message );
    emit updated();
    emit cameraInitialized();
    return;
}

void
MainWindow::view_init ( void )
{
    if(!this->_model.viewInit()){
        return;
    }
    QString  message ( tr ( "View init" ) );
    statusBar()->showMessage ( message );

    this->_cameraParameterWidget->setCameraPosition(this->_model.getCamera().getCenter().x(),
                                                       this->_model.getCamera().getCenter().y(),
                                                       this->_model.getCamera().getCenter().z());

    emit updated();
    emit cameraInitialized();
    return;
}

void
MainWindow::mouse_dragged ( float x, float y )
{

    QString  message ( tr ( "MouseDragging (" ) );
    QString strx;
    strx.setNum ( x );
    message += strx;
    message += tr ( ", " );
    QString stry;
    stry.setNum ( y );
    message += stry;
    message += tr ( ") " );

    int alpha , beta , gamma;
    this->_model.getEulerAngle(alpha , beta , gamma);
    this->_cameraParameterWidget->setEulerAngle(alpha,beta,gamma);

    double xpos , ypos , zpos;
    this->_model.getCameraPosition(xpos,ypos,zpos);
    this->_cameraParameterWidget->setCameraPosition(xpos,ypos,zpos);
    //double cx, cy, cz;
    //this->_model.getCenterArrowPos(cx, cy, cz);
    this->_model.ChangeCenterArrow(xpos, ypos, zpos);
    double cx , cy , cz;
    this->_model.getCenterArrowPos(cx, cy, cz);

    statusBar()->showMessage ( message );
    return;

}

void
MainWindow::wheel_spined(float x, float y, float step)
{
    QString  message ( tr ( "Wheel Spining (" ) );
    QString strx;
    strx.setNum ( x );
    message += strx;
    message += tr ( ", " );
    QString stry;
    stry.setNum ( y );
    message += stry;
    message += tr ( ", " );
    QString strs;
    strs.setNum ( step );
    message += strs;
    message += tr ( ") " );

    statusBar()->showMessage(message);
    return;

}


void 
MainWindow::saveSnapshot( void ){
        QString filename = QFileDialog::getSaveFileName ( this, tr ( "Save snapshot to" ), ".", tr ( "Image File (*.png)" ) );

	QImage image = this->_glwidget->grabFrameBuffer(true);
        if ( !image.save(filename, 0, 100)){
                QString  message ( tr ( "Save failed." ) );
                statusBar()->showMessage ( message );
        }
        return;
}
void 
MainWindow::update_surface_color(void) {
	QColor color = this->_colorWidget->getSurfaceColor();
    this->_model.setSurfaceColor (this->_model.getActiveMeshIndex() , color.red(),color.green(),color.blue() );
	emit updated();
}

void
MainWindow::update_color(void) {
    QColor color = this->_colorWidget->getSurfaceColor();
    this->_model.setSurfaceColor (this->_model.getActiveMeshIndex(), color.red(),color.green(),color.blue() );

    color = this->_colorWidget->getBackgroundColor();
    this->_model.setBackgroundColor(this->_model.getActiveMeshIndex() ,color.red(), color.green(), color.blue());

    color = this->_colorWidget->getWireColor();
    this->_model.setWireColor(this->_model.getActiveMeshIndex() ,color.red(), color.green(), color.blue());

    color = this->_colorWidget->getVertexColor();
    this->_model.setVertexColor(this->_model.getActiveMeshIndex() ,color.red(), color.green(), color.blue());

    color = this->_colorWidget->getLightColor();
    this->_model.setLightColor(color.red(), color.green(), color.blue());

    delete this->_dialog;
    this->_dialog = new PreferencesDialog(this , this->_model.getPreferences().at(this->_model.getActiveMeshIndex()));
    emit updated();
}


void
MainWindow::update_wire_width( void )
{
    int width = this->_wireWidthWidget->getWireWidth();
    this->_model.setWireWidth(width);
    emit updated();
}

void
MainWindow::update_point_size( void )
{
    int size = this->_pointSizeWidget->getPointSize();
    this->_model.setPointSize(size);
    emit updated();
}

void MainWindow::update_perspective_angle(void){
    this->_model.setViewAngle(this->_viewWidget->getViewAngle());
    //printf("%d", this->_viewWidget->getViewAngle());
    emit updated();
}

void
MainWindow::update_camera_position(double xpos, double ypos, double zpos)
{
    this->_model.setCameraPosition(xpos, ypos, zpos);
    this->_model.ChangeCenterArrow(xpos, ypos, zpos);
    emit updated();
}

void
MainWindow::update_euler_angle(int alpha, int beta, int gamma)
{
    this->_model.setEulerAngle(alpha,beta,gamma);
    emit updated();
}

void
MainWindow::update_window_size(int width, int height)
{
    int h = size().height();
    //this->resize(oldw+width, height);
    //oldh = height;
    //this->_view.resize(width, height);
    this->_glwidget->resize(width, height);
    emit updated();
}

void
MainWindow::update_normal_display( void )
{
    float l = this->_normalDisplayWidget->getNormalLength();
    bool  rac = this->_normalDisplayWidget->RenderAtCenter();
    bool  rv  = this->_normalDisplayWidget->RenderNormal();
    this->_model.setVectorLength(l);
    this->_model.setRenderAtCenter(rac);
    this->_model.setViewNormal(rv);
    this->_view.updateDrawMeshList(this->_model.getActiveMeshIndex());

    emit updated();
}
void
MainWindow::update_projection_mode(void)
{
    bool perspective = this->_projectionModeWidget->projectionMode();
    this->_view.setPerspective(perspective);

    emit updated();
}

void
MainWindow::initialize_camera_position()
{
    this->_cameraParameterWidget->setCameraPosition(this->_model.getCamera().getCenter().x(),
                                                       this->_model.getCamera().getCenter().y(),
                                                       this->_model.getCamera().getCenter().z());
    int alpha , beta , gamma;
    this->_model.getEulerAngle(alpha,beta,gamma);
    this->_cameraParameterWidget->setEulerAngle(alpha,beta,gamma);
    this->_model.setCenterArrowPos();
    return;
}

void
MainWindow::back_camera(void)
{
    QString  message ( tr ( "Back Camera" ) );
    this->_model.backCamera();
    emit updated();
    statusBar()->showMessage ( message );
}

void
MainWindow::forward_camera()
{
    QString  message ( tr ( "Forward Camera" ) );
    this->_model.forwardCamera();
    emit updated();
    statusBar()->showMessage(message);
}

void
MainWindow::add_now_camera_to_list()
{
    this->_model.addNowCameraToList();
}

void
MainWindow::file_dropped(QStringList strs){
    for(size_t i = 0 ; i < strs.size() ; i++){
        QString  message  = strs.at(i) +  QString( tr ( " reading...." ) );
        statusBar()->showMessage ( message );
        if ( !this->_model.openMesh (strs.at(i).toStdString() ) ) {
                QString message ( tr ( "Open failed." ) );
                statusBar()->showMessage ( message );
        } else {
            QString  message  = strs.at(i) +  QString( tr ( " reading  done." ) );
                statusBar()->showMessage ( message );
                //this->_view.createDisplayList();
                this->_view.addDrawMeshList(this->_model.getMesh().size()-1);
                this->_model.setActiveMeshIndex( this->_model.getMesh().size()-1 );
                emit updated();
                emit cameraInitialized();
                //this->modelLayerWidget->addList(str.toStdString());
                this->modelLayerWidget->addList(QFileInfo(strs.at(i)).fileName().toStdString());
                this->get_ver_face();
                this->change_pallet_color_to_Id_mesh( this->_model.getMesh().size()-1 );
        }


    }

//    QString  message  = strs.at(0) +  QString( tr ( " reading...." ) );
//    statusBar()->showMessage ( message );
//        if ( !this->_model.openMesh (str.toStdString() ) ) {
//                QString message ( tr ( "Open failed." ) );
//                statusBar()->showMessage ( message );
//        } else {
//        QString  message  = str +  QString( tr ( " reading  done." ) );
//                statusBar()->showMessage ( message );
//                //this->_view.createDisplayList();
//                this->_view.addDrawMeshList(this->_model.getMesh().size()-1);
//                this->_model.setActiveMeshIndex( this->_model.getMesh().size()-1 );
//                emit updated();
//                emit cameraInitialized();
//                //this->modelLayerWidget->addList(str.toStdString());
//                this->modelLayerWidget->addList(QFileInfo(str).fileName().toStdString());
//                this->get_ver_face();
//                this->change_pallet_color_to_Id_mesh( this->_model.getMesh().size()-1 );
//        }

        return;
}
//imamura
void
MainWindow::get_ver_face(void){
    int ver, face;
    this->_model.getVertexandFace(ver, face);
    this->_VandFWidget->getVandFNumber(ver, face);
    emit updated();
}

void MainWindow::lightswitch0(bool i){
    if(i == true){
        this->_view.onLight(GL_LIGHT0);
    }else{
        this->_view.offLight(GL_LIGHT0);
    }
    emit updated();
}

void MainWindow::lightswitch1(bool i){
    if(i == true){
        this->_view.onLight(GL_LIGHT1);
    }else{
        this->_view.offLight(GL_LIGHT1);
    }
    emit updated();
}

void MainWindow::lightswitch2(bool i){
    if(i == true){
        this->_view.onLight(GL_LIGHT2);
    }else{
        this->_view.offLight(GL_LIGHT2);
    }
    emit updated();
}

void MainWindow::lightset(void){
    this->_model.setLightPosition();
    emit updated();
}

void
MainWindow::set_width_height(int width, int height)
{

   // this->_windowWidget->setWindowHeight(height);
   // this->_windowWidget->setWindowWidth(width);
    emit updated();
    //return;
}

void
MainWindow::set_carrow(bool i)
{
    this->_view.carrow(i);
    emit updated();
}

void MainWindow::changePreference(void){
    //std::cout << "preference is pressed" << std::endl;
    /*
    if (!_dialog) {
        _dialog = new PreferencesDialog(this);
        //connect(findDialog, SIGNAL(findNext()), this, SLOT(findNext()));
    }

    _dialog->show();
*/
    _dialog->exec();
    //_dialog->raise();
   // _dialog->activateWindow();
}

void MainWindow::checkBinary(QString str){
    if( str.contains("binary" , Qt::CaseInsensitive ) ) this->_saveBinary = true;
    else this->_saveBinary = false;
	return;
}

void MainWindow::changeModelLayer(void){
    //std::cout << "changeModelLayer" << std::endl;
    this->_model.setMeshCheckState(this->modelLayerWidget->getCheckState());
    //this->_view.createDisplayList();

    emit updated();
}

void
MainWindow::save_mesh_binary(bool isBinary)
{
    this->_saveBinary = isBinary;
    return;
}

void
MainWindow::change_active_mesh_index(void)
{
    int id = this->modelLayerWidget->getSelectedIndex();
    this->_model.setActiveMeshIndex(id);
    //this->view_fit();
	this->_wireWidthWidget->set_wire_width(this->_model.getWireWidth());
    this->_pointSizeWidget->set_point_size(this->_model.getPointSize());
    this->_normalDisplayWidget->set_normal_length(this->_model.getPreferences().at(id).getVectorLength());
    this->change_pallet_color_to_Id_mesh(id);
    emit updated();
}

void
MainWindow::change_pallet_color_to_Id_mesh(int id)
{
    int r,g,b;
    this->_model.getSurfaceColor (id, r,g,b );
    QColor face(r,g,b);
    this->_model.getBackgroundColor(id,r, g, b);
    QColor background(r, g, b);
    this->_model.getWireColor(id,r, g, b);
    QColor wire(r, g, b);
    this->_model.getVertexColor(id,r, g, b);
    QColor vertex(r, g, b);
    this->_model.getLightColor(r, g, b);
    QColor light(r, g, b);
    this->_colorWidget->setColorsToPallet(face,background,wire,vertex,light);

    if( this->_model.getPreferences().at(id).getShadingMode() == SMOOTH ) this->_smoothRadioButton->setChecked(true);
    else this->_flatRadioButton->setChecked(true);

    this->get_ver_face();


    int mode = this->_model.getPreferences().at(id).getRenderingMode();
    this->_surfaceCheckBox->setChecked(mode & SURFACE);
    this->_wireCheckBox->setChecked(mode & WIRE);
    this->_pointCheckBox->setChecked(mode & POINTCLOUD);

    delete this->_dialog;
    this->_dialog = new PreferencesDialog(this, this->_model.getPreferences().at(id));

}

void
MainWindow::swap_xy( void )
{
    if(!this->_model.swapAxis(0,1)){
        return;
    }
    this->_view.updateDrawMeshList(this->_model.getActiveMeshIndex());
    emit updated();
    return;
}
void
MainWindow::swap_yz( void )
{
    if(!this->_model.swapAxis(1,2)){
        return;
    }
    this->_view.updateDrawMeshList(this->_model.getActiveMeshIndex());
    emit updated();
    return;
}
void
MainWindow::swap_zx( void )
{
    if(!this->_model.swapAxis(2,0)){
        return;
    }
    this->_view.updateDrawMeshList(this->_model.getActiveMeshIndex());
    emit updated();
    return;
}

void
MainWindow::flip_x(void)
{
    if(!this->_model.flipAxis(0)){
        return;
    }
    this->_view.updateDrawMeshList(this->_model.getActiveMeshIndex());
    emit updated();
    return;
}
void
MainWindow::flip_y(void)
{
    if(!this->_model.flipAxis(1)){
        return;
    }
    this->_view.updateDrawMeshList(this->_model.getActiveMeshIndex());
    emit updated();
    return;
}
void
MainWindow::flip_z(void)
{
    if(!this->_model.flipAxis(2)){
        return;
    }
    this->_view.updateDrawMeshList(this->_model.getActiveMeshIndex());
    emit updated();
    return;
}
//>>>>>>> master
