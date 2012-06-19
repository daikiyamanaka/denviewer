#include "MainWindow.hpp"
#include "GLWidget.hpp"
#include <QtGui>
MainWindow::MainWindow ( Model& model, View& view ) : _model ( model ), _view ( view )
{
        QWidget* widget = new QWidget;
        widget->setContentsMargins ( 5,5,5,5 );

        this->setCentralWidget ( widget );
        this->_glwidget = new GLWidget ( this->_model,  this->_view, widget );
        connect ( this->_glwidget, SIGNAL ( mouseDragged ( float, float ) ), this, SLOT ( mouse_dragged ( float, float ) ) );
        connect ( this->_glwidget, SIGNAL ( fileDropped ( QString ) ), this, SLOT ( file_dropped(QString)));
        QRadioButton *radioButton1 = new QRadioButton ( tr ( "Wireframe" ) );
        QRadioButton *radioButton2 = new QRadioButton ( tr ( "Surface" ) );
        radioButton2->setChecked ( true );
        connect ( radioButton1, SIGNAL ( pressed() ), this, SLOT ( polygon_wireframe() ) );
        connect ( radioButton2, SIGNAL ( pressed() ), this, SLOT ( polygon_surface() ) );

        QVBoxLayout *boxLayout1 = new QVBoxLayout;
        boxLayout1->addWidget ( radioButton1 );
        boxLayout1->addWidget ( radioButton2 );
        boxLayout1->addStretch ( 1 );

        QGroupBox *groupBox1 = new QGroupBox ( tr ( "Rendering Mode" ) );
        groupBox1->setLayout ( boxLayout1 );

        QPushButton *button1 = new QPushButton ( tr ( "View Fit" ) ) ;
        QPushButton *button2 = new QPushButton ( tr ( "View Init" ) ) ;
        connect ( button1, SIGNAL ( pressed() ), this, SLOT ( view_fit() ) );
        connect ( button2, SIGNAL ( pressed() ), this, SLOT ( view_init() ) );


	int r,g,b;
	this->_model.getSurfaceColor ( r,g,b );
	QColor col(r,g,b);
	this->_colorWidget = new ChangeColorWidget(col);
	connect ( this->_colorWidget, SIGNAL(updated()), this, SLOT(update_surface_color()));

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

    this->_VandFWidget = new ShowVandFWidget();//imamura

        //ViewTab—p
        QVBoxLayout *boxLayout3 = new QVBoxLayout;
        boxLayout3->addWidget ( groupBox1 );
        boxLayout3->addWidget ( button1 );
        boxLayout3->addWidget ( button2 );
        boxLayout3->addWidget ( this->_colorWidget);
        boxLayout3->addWidget ( this->_wireWidthWidget);
        boxLayout3->addWidget ( this->_VandFWidget);//imamura
        boxLayout3->addStretch ( 1 );

        //CameraTab—p
        QVBoxLayout *boxLayout4 = new QVBoxLayout;
        boxLayout4->addWidget ( this->_cameraParameterWidget );
        boxLayout4->addWidget ( this->_viewWidget );
        boxLayout4->addStretch ( 1 );
	
        //LightTab—p
        QVBoxLayout *boxLayout5 = new QVBoxLayout;

        QCheckBox *button3 = new QCheckBox ( tr ( "Light1" ) ) ;
        QCheckBox *button4 = new QCheckBox ( tr ( "Light2" ) ) ;
        QCheckBox *button5 = new QCheckBox ( tr ( "Light3" ) ) ;
        connect ( button3, SIGNAL ( clicked(bool) ), this, SLOT ( lightswitch0(bool) ) );
        connect ( button3, SIGNAL ( clicked(bool) ), this, SLOT ( lightswitch0(bool) ) );
        connect ( button4, SIGNAL ( clicked(bool) ), this, SLOT ( lightswitch1(bool) ) );
        connect ( button4, SIGNAL ( clicked(bool) ), this, SLOT ( lightswitch1(bool) ) );
        connect ( button5, SIGNAL ( clicked(bool) ), this, SLOT ( lightswitch2(bool) ) );
        connect ( button5, SIGNAL ( clicked(bool) ), this, SLOT ( lightswitch2(bool) ) );
        button3->setChecked(true);
        button4->setChecked(true);
        button5->setChecked(true);
        boxLayout5->addWidget(button3);
        boxLayout5->addWidget(button4);
        boxLayout5->addWidget(button5);
        boxLayout5->addStretch ( 1 );

        QGroupBox *groupBox2 = new QGroupBox ( tr ( "Light Number" ) );
        groupBox2->setLayout ( boxLayout5 );

        QPushButton *lightbutton = new QPushButton ( tr ( "Light Fit" ) ) ;
        connect ( lightbutton, SIGNAL ( pressed() ), this, SLOT ( lightset() ) );

        QVBoxLayout *boxLayout6 = new QVBoxLayout;
        boxLayout6->addWidget(groupBox2);
        boxLayout6->addWidget(lightbutton);
        boxLayout6->addStretch(1);

        QWidget* widget1 = new QWidget;
        widget1->setLayout(boxLayout3);
        QTabWidget* tabWidget1 = new QTabWidget;
        tabWidget1->addTab ( widget1, tr ( "Views" ) );
        tabWidget1->setMinimumWidth ( 250 );
        QWidget* widget2 = new QWidget;
        widget2->setLayout(boxLayout4);
        tabWidget1->addTab( widget2, tr ( "Camera" ) );
        tabWidget1->setMinimumWidth( 250 );
        QWidget* widget3 = new QWidget;
        widget3->setLayout(boxLayout6);
        tabWidget1->addTab( widget3, tr ( "Light" ) );
        tabWidget1->setMinimumWidth( 250 );

        QHBoxLayout *layout = new QHBoxLayout;
        layout->setMargin ( 5 );
        layout->addWidget ( this->_glwidget );
        layout->addWidget ( tabWidget1 );
        //layout->addWidget ( tabWidget2 );
        widget->setLayout ( layout );

        QString message = tr ( "A context menu is available by right-clicking" );
        this->statusBar()->showMessage ( message );

        this->create_actions();
        this->create_menus();
        this->create_toolbars();
        this->setWindowTitle ( tr ( "Viewer" ) );
        this->setMinimumSize ( 800, 600 );
        this->resize ( 800, 600 );
        connect ( this, SIGNAL ( updated() ), this->_glwidget, SLOT ( updateGL() ) );




        return;
}

//Pop-up menu
void
MainWindow::contextMenuEvent ( QContextMenuEvent* event )
{
        QMenu menu ( this );
        menu.addAction ( this->_newAct );
        menu.addAction ( this->_openAct );
        menu.addAction ( this->_saveAct );
        menu.exec ( event->globalPos() );
        return;
}

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

    this->_showmenu = menuBar()->addMenu( tr ( "&Show" ) );
    this->_showmenu->addMenu(this->_rendering);
    this->_showmenu->addMenu(this->_light);
    this->_showmenu->addMenu(this->_camera);

    this->_tool = menuBar()->addMenu( tr ( "&Tools" ) );

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
        QString filename = QFileDialog::getOpenFileName ( this, tr ( "Open file from" ), ".", tr ( "STL File (*.stl)" ) );
        if ( !this->_model.openMesh ( filename.toStdString() ) ) {
                QString message ( tr ( "Open failed." ) );
                statusBar()->showMessage ( message );
        } else {
            emit updated();
            emit cameraInitialized();
            int ver, fa;
            this->_model.getVertexandFace(ver, fa);
            this->_VandFWidget->getVandFNumber(ver, fa);
        }
        return;
}

void
MainWindow::save ( void )
{
        QString filename = QFileDialog::getSaveFileName ( this, tr ( "Save file to" ), ".", tr ( "STL File (*.stl)" ) );
        if ( !this->_model.saveMesh ( filename.toStdString() ) ) {
                QString  message ( tr ( "Save failed." ) );
                statusBar()->showMessage ( message );
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
MainWindow::polygon_wireframe ( void )
{
        this->_model.setRenderingMode ( WIRE );
        QString  message ( tr ( "Wireframe mode" ) );
        statusBar()->showMessage ( message );
        emit updated();
        return;
}

void
MainWindow::polygon_surface ( void )
{
        this->_model.setRenderingMode ( SURFACE );
        QString  message ( tr ( "Surface mode" ) );
        statusBar()->showMessage ( message );
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

        statusBar()->showMessage ( message );
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
MainWindow::file_dropped(QString str){
    QString  message  = str +  QString( tr ( " reading...." ) );
    statusBar()->showMessage ( message );
        if ( !this->_model.openMesh (str.toStdString() ) ) {
                QString message ( tr ( "Open failed." ) );
                statusBar()->showMessage ( message );
        } else {
        QString  message  = str +  QString( tr ( " reading  done." ) );
                statusBar()->showMessage ( message );
        emit updated();
        emit cameraInitialized();
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
