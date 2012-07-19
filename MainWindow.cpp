#include "MainWindow.hpp"
#include "GLWidget.hpp"
#include <QtGui>
#include <iostream>

MainWindow::MainWindow ( Model& model, View& view ) : _model ( model ), _view ( view )
{



    QWidget* widget = new QWidget;
    widget->setContentsMargins ( 5,5,5,5 );

    this->setCentralWidget ( widget );
    this->_glwidget = new GLWidget ( this->_model,  this->_view, widget );
    connect ( this->_glwidget, SIGNAL ( mouseDragged ( float, float ) ), this, SLOT ( mouse_dragged ( float, float ) ) );
    connect ( this->_glwidget, SIGNAL ( fileDropped ( QString ) ), this, SLOT ( file_dropped(QString)));
    connect ( this->_glwidget, SIGNAL ( wheelSpined(float,float,float) ), this , SLOT(wheel_spined(float,float,float) ) );

    //Rendering Mode
    this->_pointCheckBox = new QCheckBox(tr("Points"));
    this->_pointCheckBox->setChecked(false);
    this->_wireCheckBox = new QCheckBox(tr("Wireframe"));
    this->_wireCheckBox->setChecked(false);
    this->_surfaceCheckBox = new QCheckBox(tr("Surface"));
    this->_surfaceCheckBox->setChecked(true);

    QVBoxLayout *boxLayout1 = new QVBoxLayout;

    boxLayout1->addWidget(this->_pointCheckBox);
    boxLayout1->addWidget(this->_wireCheckBox);
    boxLayout1->addWidget(this->_surfaceCheckBox);
    boxLayout1->addStretch ( 1 );

    QGroupBox *groupBox1 = new QGroupBox ( tr ( "Rendering Mode" ) );
    groupBox1->setLayout ( boxLayout1 );

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

    //view
    QPushButton *button1 = new QPushButton ( tr ( "View Fit" ) ) ;
    QPushButton *button2 = new QPushButton ( tr ( "View Init" ) ) ;
    connect ( button1, SIGNAL ( pressed() ), this, SLOT ( view_fit() ) );
    connect ( button2, SIGNAL ( pressed() ), this, SLOT ( view_init() ) );


	int r,g,b;
	this->_model.getSurfaceColor ( r,g,b );
    QColor face(r,g,b);
    this->_model.getBackgroundColor(r, g, b);
    QColor background(r, g, b);
    this->_model.getWireColor(r, g, b);
    QColor wire(r, g, b);
    this->_model.getVertexColor(r, g, b);
    QColor vertex(r, g, b);
    this->_model.getLightColor(r, g, b);
    QColor light(r, g, b);
    this->_colorWidget = new ChangeColorWidget(face, background, wire, vertex, light);
    connect ( this->_colorWidget, SIGNAL(updated()), this, SLOT(update_color()));

    int wirewidth = this->_model.getWireWidth();
    this->_wireWidthWidget = new ChangeWireWidthWidget(wirewidth);
    connect( this->_wireWidthWidget, SIGNAL(updated()), this, SLOT(update_wire_width()));
	
    float angle = this->_model.getViewAngle();
    this->_viewWidget = new ChangeViewAngle(angle);
    connect(this->_viewWidget, SIGNAL(updated()), this, SLOT(update_perspective_angle()));



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

    QVBoxLayout *boxLayout2 = new QVBoxLayout;
    boxLayout2->addWidget ( this->_lightCheckBox1 );
    boxLayout2->addWidget ( this->_lightCheckBox2 );
    boxLayout2->addWidget ( this->_lightCheckBox3 );
    boxLayout2->addWidget ( lightbutton );
    boxLayout2->addStretch ( 1 );

    QGroupBox *groupBox2 = new QGroupBox ( tr ( "Light" ) );
    groupBox2->setLayout ( boxLayout2 );

    this->_VandFWidget = new ShowVandFWidget();//imamura

    //ViewTab—p
    QVBoxLayout *boxLayout3 = new QVBoxLayout;
    boxLayout3->addWidget ( groupBox1 );
    boxLayout3->addWidget ( groupBox_shading );
    boxLayout3->addWidget ( button1 );
    boxLayout3->addWidget ( button2 );
    boxLayout3->addWidget ( this->_colorWidget);
    boxLayout3->addStretch ( 1 );

    QVBoxLayout *boxLayout4 = new QVBoxLayout;
    boxLayout4->addWidget(groupBox2);
    boxLayout4->addWidget(this->_cameraParameterWidget);
    boxLayout4->addWidget(this->_viewWidget);

    boxLayout4->addStretch( 1 );

    QVBoxLayout *boxLayout5 = new QVBoxLayout;
	boxLayout5->addWidget ( this->_VandFWidget);//imamura
    boxLayout5->addWidget(this->_wireWidthWidget);
    boxLayout5->addStretch( 1 );

    QWidget* widget1 = new QWidget;
    widget1->setLayout(boxLayout3);

    QWidget* widget2 = new QWidget;
    widget2->setLayout(boxLayout4);
    QWidget* widget3 = new QWidget;
    widget3->setLayout(boxLayout5);

    QTabWidget* tabWidget1 = new QTabWidget;
    tabWidget1->addTab ( widget1, tr ( "Views" ) );

    tabWidget1->addTab(widget2 ,tr("Camera") );
    tabWidget1->addTab(widget3 ,tr("MeshInfo") );

    tabWidget1->setMinimumWidth ( 250 );

    QTabWidget* tabWidget2 = new QTabWidget;
    modelLayerWidget = new ModelLayerWidget;
    tabWidget2->addTab ( modelLayerWidget, tr ( "ModelLayer" ) );
    tabWidget2->setMinimumWidth ( 200 );

    connect(this->modelLayerWidget, SIGNAL(updated()), this, SLOT(changeModelLayer()));

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin ( 5 );
    layout->addWidget ( tabWidget2 );
    layout->addWidget ( this->_glwidget );
    layout->addWidget ( tabWidget1 );

    widget->setLayout ( layout );

    QString message = tr ( "A context menu is not available by right-clicking" );

    this->statusBar()->showMessage ( message );

    this->create_actions();
    this->create_menus();
    this->create_toolbars();
    this->setWindowTitle ( tr ( "Viewer" ) );
    this->setMinimumSize ( 1000, 600 );
    this->resize ( 1000, 600 );

    connect ( this, SIGNAL ( updated() ), this->_glwidget, SLOT ( updateGL() ) );

    //Preference Dialog
    _dialog = new PreferencesDialog(this, this->_model.getPreference());
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

        this->_backCamera = new QAction( tr("Back Camera") , this );
        this->_backCamera->setShortcut(QKeySequence::Undo);
        this->_backCamera->setStatusTip ( "Back Camera." );
        connect ( this->_backCamera, SIGNAL ( triggered() ), this , SLOT(back_camera()) );

        this->_forwardCamera = new QAction( tr("Forward Camera") , this );
        this->_forwardCamera->setShortcut(QKeySequence::Redo);
        this->_forwardCamera->setStatusTip ( "Forward Camera." );
        connect ( this->_forwardCamera, SIGNAL ( triggered() ), this , SLOT(forward_camera()) );


/*<<<<<<< HEAD
        //rendering
        this->_rendering = new QMenu ( tr ( "Rendering" ));
        this->_pointcrowds = new QAction (tr("Point crouds"), this);
        this->_wireflame = new QAction ( tr ( "wire flame" ), this );
        this->_flatshading = new QAction ( tr ( "flat shading" ), this );
        this->_rendering->addAction(_pointcrowds);
        this->_rendering->addAction(_wireflame);
        this->_rendering->addAction(_flatshading);

        //light
        this->_light = new QMenu( tr ("LIght"));

        //camera
        this->_camera = new QMenu(tr ("Camera"));
=======*/
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




//>>>>>>> master

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

/*<<<<<<< HEAD
    this->_showmenu = menuBar()->addMenu( tr ( "&Show" ) );
    this->_showmenu->addMenu(this->_rendering);
    this->_showmenu->addMenu(this->_light);
    this->_showmenu->addMenu(this->_camera);

    this->_tool = menuBar()->addMenu( tr ( "&Tools" ) );

=======*/
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
    this->_cameraSubMenu->addAction(this->_backCamera);
    this->_cameraSubMenu->addAction(this->_forwardCamera);
    this->_toolMenu = menuBar()->addMenu(tr("&Tools"));
//>>>>>>> master
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
        this->_fileToolBar->addAction( this->preferenceAct);
        return ;
}

void
MainWindow::new_file ( void )
{
        this->_model.initMesh();
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
        if ( fileNames.size()==0 || !this->_model.openMesh ( fileNames.at(0).toStdString() ) ) {
                QString message ( tr ( "Open failed." ) );
                statusBar()->showMessage ( message );
                return;
        } else {
            emit updated();
            emit cameraInitialized();
            this->modelLayerWidget->addList(QFileInfo(fileNames.at(0)).fileName().toStdString());
            this->get_ver_face();
            this->_view.createDisplayList();
        }
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

    connect(saveDlg , SIGNAL(filterSelected(QString)) , this , SLOT(checkBinary(QString)) );

    QStringList fileNames;
    if(saveDlg->exec()){
        fileNames = saveDlg->selectedFiles();
    }
    if ( fileNames.size()==0 || !this->_model.saveMesh ( fileNames.at(0).toStdString() , this->_saveBinary ) ) {
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
    if(checked){
        this->_model.setRenderingMode (this->_model.getRenderingMode() | WIRE);
        //std::cout << "wire: checked" << std::endl;
    }
    else{
        this->_model.setRenderingMode (this->_model.getRenderingMode() ^ WIRE);
        //std::cout << "wire: unchecked" << std::endl;
    }
        QString  message ( tr ( "Wireframe mode" ) );
        statusBar()->showMessage ( message );
        emit updated();
        return;
}

void
MainWindow::polygon_surface ( bool checked)
{
    if(checked){
        this->_model.setRenderingMode (this->_model.getRenderingMode() | SURFACE);
        //std::cout << "surface: checked" << std::endl;
    }
    else{
        this->_model.setRenderingMode (this->_model.getRenderingMode() ^ SURFACE);
        //std::cout << "surface: unchecked" << std::endl;
    }

        QString  message ( tr ( "Surface mode" ) );
        statusBar()->showMessage ( message );
        emit updated();
        return;
}

void
MainWindow::polygon_point( bool checked)
{
    if(checked){
        this->_model.setRenderingMode (this->_model.getRenderingMode() | POINTCLOUD);
    }
    else{
        this->_model.setRenderingMode (this->_model.getRenderingMode() ^ POINTCLOUD);
    }

    //this->_model.setRenderingMode(this->_model.getRenderingMode() | POINTCLOUD);
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
    this->_view.createDisplayList();
    emit updated();
    return;
}

void
MainWindow::shading_smooth( void )
{
    this->_model.setShadingMode(SMOOTH);
    QString  message ( tr ( "Smooth shading" ) );
    statusBar()->showMessage ( message );
    this->_view.createDisplayList();
    emit updated();
    return;
}

void
MainWindow::view_fit ( void )
{
        this->_model.viewFit();
        QString  message ( tr ( "View fit" ) );
        statusBar()->showMessage ( message );
        emit updated();
		emit cameraInitialized();
        return;
}

void
MainWindow::view_init ( void )
{
        this->_model.viewInit();
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
	this->_model.setSurfaceColor ( color.red(),color.green(),color.blue() );
	emit updated();
}

void
MainWindow::update_color(void) {
    QColor color = this->_colorWidget->getSurfaceColor();
    this->_model.setSurfaceColor ( color.red(),color.green(),color.blue() );

    color = this->_colorWidget->getBackgroundColor();
    this->_model.setBackgroundColor(color.red(), color.green(), color.blue());

    color = this->_colorWidget->getWireColor();
    this->_model.setWireColor(color.red(), color.green(), color.blue());

    color = this->_colorWidget->getVertexColor();
    this->_model.setVertexColor(color.red(), color.green(), color.blue());

    color = this->_colorWidget->getLightColor();
    this->_model.setLightColor(color.red(), color.green(), color.blue());

    emit updated();
}


void
MainWindow::update_wire_width( void )
{
    int width = this->_wireWidthWidget->getWireWidth();
    this->_model.setWireWidth(width);
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
    this->_model.setCameraPosition(xpos,ypos,zpos);
    emit updated();
}

void
MainWindow::update_euler_angle(int alpha, int beta, int gamma)
{
    this->_model.setEulerAngle(alpha,beta,gamma);
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
MainWindow::file_dropped(QString str){
    QString  message  = str +  QString( tr ( " reading...." ) );
    statusBar()->showMessage ( message );
        if ( !this->_model.openMesh (str.toStdString() ) ) {
                QString message ( tr ( "Open failed." ) );
                statusBar()->showMessage ( message );
        } else {
        QString  message  = str +  QString( tr ( " reading  done." ) );
                statusBar()->showMessage ( message );
        this->_view.createDisplayList();
        emit updated();
        emit cameraInitialized();
        //this->modelLayerWidget->addList(str.toStdString());
        this->modelLayerWidget->addList(QFileInfo(str).fileName().toStdString());
        this->get_ver_face();
    }

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

<<<<<<< HEAD
void MainWindow::checkBinary(QString str){
    if( str.contains("binary" , Qt::CaseInsensitive ) ) this->_saveBinary = true;
    else this->_saveBinary = false;
	return;
}

void MainWindow::changeModelLayer(void){
    std::cout << "changeModelLayer" << std::endl;
    this->_model.setMeshCheckState(this->modelLayerWidget->getCheckState());
    this->_view.createDisplayList();
    emit updated();
}
