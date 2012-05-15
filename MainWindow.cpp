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
        QCheckBox *checkBox1 = new QCheckBox ( tr( "Wireframe" ) );
        QCheckBox *checkBox2 = new QCheckBox ( tr( "Surface" ) );
        QCheckBox *checkBox3 = new QCheckBox ( tr( "Point" ) );
        checkBox2->setChecked(true);
        connect( checkBox1 , SIGNAL( toggled(bool) ) , this , SLOT ( polygon_wireframe(bool) ) );
        connect( checkBox2 , SIGNAL( toggled(bool) ) , this , SLOT ( polygon_surface(bool) ) );
        connect( checkBox3 , SIGNAL( toggled(bool) ) , this , SLOT ( polygon_point(bool) ) );


        QRadioButton *radioButton1 = new QRadioButton ( tr ( "Wireframe" ) );
        QRadioButton *radioButton2 = new QRadioButton ( tr ( "Surface" ) );
        QRadioButton *radioButton3 = new QRadioButton ( tr( "Point" ) );
        radioButton2->setChecked ( true );
        //connect ( radioButton1, SIGNAL ( pressed() ), this->_glwidget, SLOT ( updateGL() ) );
        //connect ( radioButton2, SIGNAL ( pressed() ), this->_glwidget, SLOT ( updateGL() ) );
        //connect ( radioButton3, SIGNAL ( pressed() ), this->_glwidget, SLOT ( updateGL() ) );
        connect ( radioButton1, SIGNAL ( pressed() ), this, SLOT ( polygon_wireframe() ) );
        connect ( radioButton2, SIGNAL ( pressed() ), this, SLOT ( polygon_surface() ) );
        connect ( radioButton3, SIGNAL ( pressed() ), this, SLOT ( polygon_point() ) );

        QVBoxLayout *boxLayout1 = new QVBoxLayout;
        boxLayout1->addWidget ( checkBox1 );
        boxLayout1->addWidget ( checkBox2 );
        boxLayout1->addWidget ( checkBox3 );


        /*
        boxLayout1->addWidget ( radioButton1 );
        boxLayout1->addWidget ( radioButton2 );
        boxLayout1->addWidget ( radioButton3 );
        */
        boxLayout1->addStretch ( 1 );

        QGroupBox *groupBox1 = new QGroupBox ( tr ( "Rendering Mode" ) );
        groupBox1->setLayout ( boxLayout1 );

        QRadioButton *radioButton4 = new QRadioButton ( tr( "Rotation" ) );
        QRadioButton *radioButton5 = new QRadioButton ( tr( "Pan" ) );//ƒXƒyƒ‹‚ª”÷–­
        radioButton4->setChecked( true );

        QVBoxLayout *boxLayout2 = new QVBoxLayout;
        boxLayout2->addWidget( radioButton4 );
        boxLayout2->addWidget( radioButton5 );
        boxLayout2->addStretch( 1 );

        QGroupBox *groupBox2 = new QGroupBox ( tr ( "View Change Mode" ) );
        groupBox2->setLayout ( boxLayout2 );

        QPushButton *button1 = new QPushButton ( tr ( "View Fit" ) ) ;
        QPushButton *button2 = new QPushButton ( tr ( "View Init" ) ) ;
        connect ( button1, SIGNAL ( pressed() ), this->_glwidget, SLOT ( updateGL() ) );
        connect ( button2, SIGNAL ( pressed() ), this->_glwidget, SLOT ( updateGL() ) );
        connect ( button1, SIGNAL ( pressed() ), this, SLOT ( view_fit() ) );
        connect ( button2, SIGNAL ( pressed() ), this, SLOT ( view_init() ) );


        QVBoxLayout *boxLayout3 = new QVBoxLayout;
        boxLayout3->addWidget ( groupBox1 );
        boxLayout3->addWidget ( groupBox2 );
        boxLayout3->addWidget ( button1 );
        boxLayout3->addWidget ( button2 );
        boxLayout3->addStretch ( 1 );

        QWidget* widget1 = new QWidget;
        widget1->setLayout ( boxLayout3 );

        QTabWidget* tabWidget1 = new QTabWidget;
        tabWidget1->addTab ( widget1, tr ( "Views" ) );
        tabWidget1->setMinimumWidth ( 250 );

        //‚±‚±‚©‚ç‚à‚¤ˆê‚Â‚ÌTab
        QHBoxLayout *boxLayout_C1 = new QHBoxLayout;
        QLabel *label_R1 = new QLabel( tr("  R"));
        QLabel *label_G1 = new QLabel( tr("  G"));
        QLabel *label_B1 = new QLabel( tr("  B"));
        _colorBox01 = new QDoubleSpinBox;
        _colorBox01->setSingleStep( 0.05 );
        _colorBox01->setValue( this->_model.getPreference().getWireColor().x() );
        _colorBox01->setRange(0.0 , 1.0);
        _colorBox02 = new QDoubleSpinBox;
        _colorBox02->setSingleStep( 0.05 );
        _colorBox02->setValue( this->_model.getPreference().getWireColor().y() );
        _colorBox02->setRange(0.0 , 1.0);
        _colorBox03 = new QDoubleSpinBox;
        _colorBox03->setSingleStep( 0.05 );
        _colorBox03->setValue( this->_model.getPreference().getWireColor().z() );
        _colorBox03->setRange(0.0 , 1.0);
        boxLayout_C1->addWidget(label_R1);
        boxLayout_C1->addWidget(_colorBox01);
        boxLayout_C1->addWidget(label_G1);
        boxLayout_C1->addWidget(_colorBox02);
        boxLayout_C1->addWidget(label_B1);
        boxLayout_C1->addWidget(_colorBox03);
        QGroupBox* groupBoxC1 = new QGroupBox(tr("Wire Color"));
        groupBoxC1->setLayout(boxLayout_C1);

        /*
        QImage qi1 = new QImage(20 , 30 , QImage::Format_RGB32);
        QRgb value1;
        value1 = QRgb( (int)(255.0*_colorBox01->value()) , (int)(255.0*_colorBox02->value()) , (int)(255.0*_colorBox03->value()) );
        for( int i = 0 ; i < 20 ; i++ ){
            for( int j = 0 ; j < 30 ; j++ ){
                qi1.setPixel(i,j,value1);
            }
        }
        */

        QHBoxLayout *boxLayout_C2 = new QHBoxLayout;
        QLabel *label_R2 = new QLabel( tr("  R"));
        QLabel *label_G2 = new QLabel( tr("  G"));
        QLabel *label_B2 = new QLabel( tr("  B"));
        _colorBox04 = new QDoubleSpinBox;
        _colorBox04->setSingleStep( 0.05 );
        _colorBox04->setValue( this->_model.getPreference().getSurfaceColor().x() );
        _colorBox04->setRange(0.0 , 1.0);
        _colorBox05 = new QDoubleSpinBox;
        _colorBox05->setSingleStep( 0.05 );
        _colorBox05->setValue( this->_model.getPreference().getSurfaceColor().y() );
        _colorBox05->setRange(0.0 , 1.0);
        _colorBox06 = new QDoubleSpinBox;
        _colorBox06->setSingleStep( 0.05 );
        _colorBox06->setValue( this->_model.getPreference().getSurfaceColor().z() );
        _colorBox06->setRange(0.0 , 1.0);
        boxLayout_C2->addWidget(label_R2);
        boxLayout_C2->addWidget(_colorBox04);
        boxLayout_C2->addWidget(label_G2);
        boxLayout_C2->addWidget(_colorBox05);
        boxLayout_C2->addWidget(label_B2);
        boxLayout_C2->addWidget(_colorBox06);
        QGroupBox* groupBoxC2 = new QGroupBox(tr("Mesh Color"));
        groupBoxC2->setLayout(boxLayout_C2);

        QHBoxLayout *boxLayout_C3 = new QHBoxLayout;
        QLabel *label_R3 = new QLabel( tr("  R"));
        QLabel *label_G3 = new QLabel( tr("  G"));
        QLabel *label_B3 = new QLabel( tr("  B"));
        _colorBox07 = new QDoubleSpinBox;
        _colorBox07->setSingleStep( 0.05 );
        _colorBox07->setValue( this->_model.getPreference().getPointcloudColor().x() );
        _colorBox07->setRange(0.0 , 1.0);
        _colorBox08 = new QDoubleSpinBox;
        _colorBox08->setSingleStep( 0.05 );
        _colorBox08->setValue( this->_model.getPreference().getPointcloudColor().y() );
        _colorBox08->setRange(0.0 , 1.0);
        _colorBox09 = new QDoubleSpinBox;
        _colorBox09->setSingleStep( 0.05 );
        _colorBox09->setValue( this->_model.getPreference().getPointcloudColor().z() );
        _colorBox09->setRange(0.0 , 1.0);
        boxLayout_C3->addWidget(label_R3);
        boxLayout_C3->addWidget(_colorBox07);
        boxLayout_C3->addWidget(label_G3);
        boxLayout_C3->addWidget(_colorBox08);
        boxLayout_C3->addWidget(label_B3);
        boxLayout_C3->addWidget(_colorBox09);
        QGroupBox* groupBoxC3 = new QGroupBox(tr("PointCloud Color"));
        groupBoxC3->setLayout(boxLayout_C3);

        _changeingColorButton = new QPushButton();
        _changeingColorButton->setText( tr("Change Colors") );
        connect(_changeingColorButton , SIGNAL( pressed() ) , this , SLOT( changeModelColor() ) );

        QVBoxLayout* boxLayout_C = new QVBoxLayout;
        boxLayout_C->addWidget(groupBoxC1);
        boxLayout_C->addWidget(groupBoxC2);
        boxLayout_C->addWidget(groupBoxC3);
        boxLayout_C->addWidget( _changeingColorButton );

        QWidget* widget2 = new QWidget;
        widget2->setLayout(boxLayout_C);
        tabWidget1->addTab( widget2 , tr("Colors") );
//
  //
        QLabel *label1 = new QLabel( tr("Field of View Angle") );
        //QLabel *label2 = new QLabel( tr("Distance to Center") );
        QLabel *label3 = new QLabel( tr("Center") );
        QLabel *label4 = new QLabel( tr("Rotation") );
        QString str1( tr("Field of View Angle") );
        spinbox = new QSpinBox;
        QTextStream(&str1)<<" "<<this->_model.getCamera().getFieldOfViewAngle();
        spinbox->setRange(10,170);
        spinbox->setValue(static_cast<int>( this->_model.getCamera().getFieldOfViewAngle() ) );
        QHBoxLayout* hboxLayout1 = new QHBoxLayout;
        hboxLayout1->addWidget(label1);
        hboxLayout1->addWidget(spinbox);
        //QString str3( tr("Center") );
        //QTextStream(&str3)<<" "<<this->_model.getCamera().getCenter().x()<<" "<<this->_model.getCamera().getCenter().y()<<" "<<this->_model.getCamera().getCenter().z();

        _spinbox1 = new QDoubleSpinBox;
        _spinbox2 = new QDoubleSpinBox;
        _spinbox3 = new QDoubleSpinBox;
        _spinbox1->setSingleStep( 0.01 );
        _spinbox2->setSingleStep( 0.01 );
        _spinbox3->setSingleStep( 0.01 );
        _spinbox1->setValue( this->_model.getCamera().getCenter().x() );
        _spinbox2->setValue( this->_model.getCamera().getCenter().y() );
        _spinbox3->setValue( this->_model.getCamera().getCenter().z() );

        QHBoxLayout* hboxLayout2 = new QHBoxLayout;
        hboxLayout2->addWidget(label3);
        hboxLayout2->addWidget(_spinbox1);
        hboxLayout2->addWidget(_spinbox2);
        hboxLayout2->addWidget(_spinbox3);

        _spinbox4 = new QDoubleSpinBox;
        _spinbox5 = new QDoubleSpinBox;
        _spinbox6 = new QDoubleSpinBox;
        _spinbox7 = new QDoubleSpinBox;
        _spinbox4->setSingleStep( 0.01 );
        _spinbox5->setSingleStep( 0.01 );
        _spinbox6->setSingleStep( 0.01 );
        _spinbox7->setSingleStep( 0.01 );
        _spinbox4->setValue( this->_model.getCamera().getRotation().w() );
        _spinbox5->setValue( this->_model.getCamera().getRotation().x() );
        _spinbox6->setValue( this->_model.getCamera().getRotation().y() );
        _spinbox7->setValue( this->_model.getCamera().getRotation().z() );
        QHBoxLayout* hboxLayout3 = new QHBoxLayout;
        hboxLayout3->addWidget( label4 );
        hboxLayout3->addWidget(_spinbox4);
        hboxLayout3->addWidget(_spinbox5);
        hboxLayout3->addWidget(_spinbox6);
        hboxLayout3->addWidget(_spinbox7);

        QVBoxLayout *boxLayout4 = new QVBoxLayout;
        boxLayout4->addLayout(hboxLayout1);
        boxLayout4->addLayout(hboxLayout2);
        boxLayout4->addLayout(hboxLayout3);

        QGroupBox *groupBox3 = new QGroupBox( tr("Camera Paremeters") );
        groupBox3->setLayout( boxLayout4 );

        QVBoxLayout *boxLayout5 = new QVBoxLayout;
        boxLayout5->addWidget( tabWidget1 );
        boxLayout5->addWidget( groupBox3 );

        QHBoxLayout *layout = new QHBoxLayout;
        layout->setMargin ( 5 );
        layout->addWidget ( this->_glwidget );
        layout->addLayout ( boxLayout5 );
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

        //Exit
        this->_exitAct = new QAction ( tr ( "E&xit" ), this );
        this->_exitAct->setShortcuts ( QKeySequence::Quit );
        this->_exitAct->setStatusTip ( "Exit this application." );
        connect ( this->_exitAct, SIGNAL ( triggered() ), this, SLOT ( close() ) );

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
        this->_fileMenu->addSeparator();
        this->_fileMenu->addAction ( this->_exitAct );
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
        return;
}

void
MainWindow::open ( void )
{
        QString filename = QFileDialog::getOpenFileName ( this, tr ( "Open file from" ), ".", tr ( "STL File (*.stl)" ) );
        if ( !this->_model.openMesh ( filename.toStdString() ) ) {
                QString message ( tr ( "Open failed." ) );
                statusBar()->showMessage ( message );
        }
        else emit updated();
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
        }
        else emit updated();
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
MainWindow::polygon_wireframe ( bool b )
{
    this->_model.getPreference().setWireRendering(b);
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
MainWindow::polygon_surface ( bool b )
{
    this->_model.getPreference().setSurfaceRendering(b);
    QString  message ( tr ( "Surface mode" ) );
    statusBar()->showMessage ( message );
    emit updated();
    return;
}

void
MainWindow::polygon_point ( void )
{
        this->_model.setRenderingMode ( POINTCLOUD );
        QString message ( tr( "Point Mode" ) );
        statusBar()->showMessage( message );
        emit updated();
        return;
}

void
MainWindow::polygon_point ( bool b )
{
    this->_model.getPreference().setPointCloudRendering(b);
    QString  message ( tr ( "Point mode" ) );
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
        return;
}

void
MainWindow::view_init ( void )
{
        this->_model.viewInit();
        QString  message ( tr ( "View init" ) );
        statusBar()->showMessage ( message );
        emit updated();
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
        statusBar()->showMessage ( message );

        spinbox->setValue( static_cast<int>( this->_model.getCamera().getFieldOfViewAngle() ) );
        _spinbox1->setValue( this->_model.getCamera().getCenter().x() );
        _spinbox2->setValue( this->_model.getCamera().getCenter().y() );
        _spinbox3->setValue( this->_model.getCamera().getCenter().z() );
        _spinbox4->setValue( this->_model.getCamera().getRotation().w() );
        _spinbox5->setValue( this->_model.getCamera().getRotation().x() );
        _spinbox6->setValue( this->_model.getCamera().getRotation().y() );
        _spinbox7->setValue( this->_model.getCamera().getRotation().z() );

       // this->_model.getPreference().getPointcloudColor();

        return;

}

void
MainWindow::changeModelColor( void )
{
    Color3f c1( _colorBox01->value(),_colorBox02->value(),_colorBox03->value() );
    Color3f c2( _colorBox04->value(),_colorBox05->value(),_colorBox06->value() );
    Color3f c3( _colorBox07->value(),_colorBox08->value(),_colorBox09->value() );

    this->_model.getPreference().setWireColor( c1 );
    this->_model.getPreference().setSurfaceColor( c2 );
    this->_model.getPreference().setPointcloudColor( c3 );

    emit updated();

    return;
}

