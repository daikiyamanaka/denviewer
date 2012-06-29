#include "ChangeColorWidget.hpp"
#include <QtGui>
#include <QGridLayout>


ChangeColorWidget::ChangeColorWidget(const QColor faceColor,  QWidget *parent ) : QWidget(parent) {
    QHBoxLayout *hBoxLayout1 = new QHBoxLayout;
    QGridLayout * gridlayout = new QGridLayout;
    QPushButton *button3 = new QPushButton ( tr ( "Face Color" ) ) ;


    this->_faceColorLabel = new QLabel;
    this->_faceColorLabel->setFrameStyle ( QFrame::Sunken | QFrame::Panel );
    this->_faceColorLabel->setPalette ( faceColor );
    this->_faceColorLabel->setAutoFillBackground ( true );

    QPushButton *backgroundColorButton = new QPushButton(tr("Background Color"));
    this->_backgroundColorLabel = new QLabel;
    this->_backgroundColorLabel->setFrameStyle(QFrame::Sunken | QFrame::Panel);
    this->_backgroundColorLabel->setPalette( faceColor);
    this->_backgroundColorLabel->setAutoFillBackground(true);

    QPushButton *wireColorButton = new QPushButton(tr("Wire Color"));
    this->_wireColorLabel = new QLabel;
    this->_wireColorLabel->setFrameStyle(QFrame::Sunken | QFrame::Panel);
    this->_wireColorLabel->setPalette( faceColor);
    this->_wireColorLabel->setAutoFillBackground(true);

    /*
    QPushButton *vertexColorButton = new QPushButton(tr("Vertex Color"));
    this->_vertexColorLabel = new QLabel;
    this->_vertexColorLabel->setFrameStyle(QFrame::Sunken | QFrame::Panel);
    this->_faceColorLabel->setPalette( faceColor);
    this->_faceColorLabel->setAutoFillBackground(true);
    */

    connect (button3, SIGNAL(pressed()), this, SLOT(set_surface_color()));
    connect (backgroundColorButton, SIGNAL(pressed()), this, SLOT(setBackgroundColor()));
    connect (wireColorButton, SIGNAL(pressed()), this, SLOT(setWireColor()));
//    connect (vertexColorButton, SIGNAL(pressed()), this, SLOT(setVertexColor()));

    gridlayout->addWidget(button3, 0, 0);
    gridlayout->addWidget(this->_faceColorLabel, 0, 1);
    gridlayout->addWidget( backgroundColorButton, 1, 0);
    gridlayout->addWidget(this->_backgroundColorLabel, 1, 1);
    gridlayout->addWidget( wireColorButton, 2, 0);
    gridlayout->addWidget(this->_wireColorLabel, 2, 1);
    //gridlayout->addWidget( vertexColorButton, 3, 0);
    //gridlayout->addWidget(this->_vertexColorLabel, 3, 1);



    //this->setLayout(hBoxLayout1);
    this->setLayout(gridlayout);
    return;
}

void
ChangeColorWidget::set_surface_color( void ) {
    QColor color = QColorDialog::getColor ( this->getSurfaceColor(), this );
    if ( color.isValid() ) {
        this->_faceColorLabel->setPalette ( QPalette ( color ) );
        this->_faceColorLabel->setAutoFillBackground ( true );
        emit updated();
    }
    return;
}

void ChangeColorWidget::setBackgroundColor(void){
    QColor color = QColorDialog::getColor(this->getBackgroundColor(), this);
    if(color.isValid()){
        this->_backgroundColorLabel->setPalette(QPalette(color));
        this->_backgroundColorLabel->setAutoFillBackground(true);
        emit updated();
    }
    return;
}

void ChangeColorWidget::setWireColor(void){
    QColor color = QColorDialog::getColor(this->getWireColor(), this);
    if(color.isValid()){
        this->_wireColorLabel->setPalette(QPalette(color));
        this->_wireColorLabel->setAutoFillBackground(true);
        emit updated();
    }
    return;
}

void ChangeColorWidget::setVertexColor(void){
    QColor color = QColorDialog::getColor(this->getVertexColor(), this);
    if(color.isValid()){
        this->_vertexColorLabel->setPalette(QPalette(color));
        this->_vertexColorLabel->setAutoFillBackground(true);
        emit updated();
    }
    return;
}

QColor
ChangeColorWidget::getSurfaceColor( void ) const {
    return this->_faceColorLabel->palette().color(QPalette::Window);
}

QColor ChangeColorWidget::getBackgroundColor(){
    return this->_backgroundColorLabel->palette().color(QPalette::Window);
}

QColor ChangeColorWidget::getWireColor(){
    return this->_wireColorLabel->palette().color(QPalette::Window);
}

QColor ChangeColorWidget::getVertexColor(){
    return this->_vertexColorLabel->palette().color(QPalette::Window);
}
