#include "GetCameraParameterWidget.hpp"
#include <QtGui>
#include <iostream>

GetCameraParameterWidget::GetCameraParameterWidget(int alpha, int beta, int gamma, double xpos, double ypos, double zpos, QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *PosLayout = new QHBoxLayout;
    QLabel *xPosLabel = new QLabel( tr("x") );
    QLabel *yPosLabel = new QLabel( tr("y") );
    QLabel *zPosLabel = new QLabel( tr("z") );
    this->_xPosSpinBox = new QDoubleSpinBox;
    this->_yPosSpinBox = new QDoubleSpinBox;
    this->_zPosSpinBox = new QDoubleSpinBox;

    this->_xPosSpinBox->setRange(-100.0 , 100.0);
    this->_xPosSpinBox->setSingleStep(0.001);
    this->_xPosSpinBox->setDecimals(5);
    this->_yPosSpinBox->setRange(-100.0 , 100.0);
    this->_yPosSpinBox->setSingleStep(0.001);
    this->_yPosSpinBox->setDecimals(5);
    this->_zPosSpinBox->setRange(-100.0 , 100.0);
    this->_zPosSpinBox->setSingleStep(0.001);
    this->_zPosSpinBox->setDecimals(5);

    connect( this->_xPosSpinBox , SIGNAL(valueChanged(double)) , this , SLOT(updateXPos(double)) );
    connect( this->_yPosSpinBox , SIGNAL(valueChanged(double)) , this , SLOT(updateYPos(double)) );
    connect( this->_zPosSpinBox , SIGNAL(valueChanged(double)) , this , SLOT(updateZPos(double)) );

    QHBoxLayout *xPosLayout = new QHBoxLayout;
    QHBoxLayout *yPosLayout = new QHBoxLayout;
    QHBoxLayout *zPosLayout = new QHBoxLayout;

    xPosLayout->addWidget(xPosLabel);
    xPosLayout->addWidget(this->_xPosSpinBox);
    yPosLayout->addWidget(yPosLabel);
    yPosLayout->addWidget(this->_yPosSpinBox);
    zPosLayout->addWidget(zPosLabel);
    zPosLayout->addWidget(this->_zPosSpinBox);

    PosLayout->addLayout( xPosLayout );
    PosLayout->addLayout( yPosLayout );
    PosLayout->addLayout( zPosLayout );

    QGroupBox *PosGroupBox = new QGroupBox( tr ( "Center" ) );

    PosGroupBox->setLayout( PosLayout );

    QVBoxLayout *AngleLayout = new QVBoxLayout;
    QLabel *alphaLabel = new QLabel( tr("X:") );
    QLabel *betaLabel = new QLabel( tr("Y:") );
    QLabel *gammaLabel = new QLabel( tr("Z:") );
    this->_alphaSlider = new QSlider(Qt::Horizontal);
    this->_betaSlider = new QSlider(Qt::Horizontal);
    this->_gammaSlider = new QSlider(Qt::Horizontal);
    this->_alphaSlider->setRange(-89,89);
    this->_betaSlider->setRange(-180,180);
    this->_gammaSlider->setRange(-180,180);
    this->_alphaspin = new QSpinBox;
    this->_betaspin = new QSpinBox;
    this->_gammaspin = new QSpinBox;
    this->_alphaspin->setRange(-89,89);
    this->_betaspin->setRange(-180,180);
    this->_gammaspin->setRange(-180,180);

    QHBoxLayout *alphaLayout = new QHBoxLayout;
    QHBoxLayout *betaLayout = new QHBoxLayout;
    QHBoxLayout *gammaLayout = new QHBoxLayout;

    connect( this->_alphaSlider , SIGNAL(valueChanged(int)) , this , SLOT(updateAlpha(int)) );
    connect( this->_betaSlider , SIGNAL(valueChanged(int)) , this , SLOT( updateBeta(int)) );
    connect( this->_gammaSlider , SIGNAL(valueChanged(int)) , this , SLOT(updateGamma(int)) );
    connect( this->_alphaSlider , SIGNAL(valueChanged(int)) , this->_alphaspin , SLOT(setValue(int)));
    connect( this->_betaSlider , SIGNAL(valueChanged(int)) , this->_betaspin , SLOT(setValue(int)));
    connect( this->_gammaSlider , SIGNAL(valueChanged(int)) , this->_gammaspin , SLOT(setValue(int)));
    connect( this->_alphaspin , SIGNAL(valueChanged(int)) , this->_alphaSlider , SLOT(setValue(int)));
    connect( this->_betaspin , SIGNAL(valueChanged(int)) , this->_betaSlider , SLOT(setValue(int)));
    connect( this->_gammaspin , SIGNAL(valueChanged(int)) , this->_gammaSlider , SLOT(setValue(int)));

    //connect(  this->_alphaSlider,SIGNAL(sliderPressed()) , this , SIGNAL(ParameterChanged()) );
    //connect(  this->_betaSlider,SIGNAL(sliderPressed()) , this , SIGNAL(ParameterChanged()) );
    //connect(  this->_gammaSlider,SIGNAL(sliderPressed()) , this , SIGNAL(ParameterChanged()) );

    this->_parameterChangedByThisWidget = false;
    this->_parameterChangedByOtherWidget = true;

    alphaLayout->addWidget(alphaLabel);
    alphaLayout->addWidget(this->_alphaSlider);
    alphaLayout->addWidget(this->_alphaspin);
    betaLayout->addWidget(betaLabel);
    betaLayout->addWidget(this->_betaSlider);
    betaLayout->addWidget(this->_betaspin);
    gammaLayout->addWidget(gammaLabel);
    gammaLayout->addWidget(this->_gammaSlider);
    gammaLayout->addWidget(this->_gammaspin);

    AngleLayout->addLayout( alphaLayout );
    AngleLayout->addLayout( betaLayout );
    AngleLayout->addLayout( gammaLayout );
    QGroupBox *AngleGroupBox = new QGroupBox( tr ( "Euler Angle" ) );

    AngleGroupBox->setLayout( AngleLayout );

    QVBoxLayout *VBoxLayout = new QVBoxLayout;
    VBoxLayout->addWidget( PosGroupBox );
    VBoxLayout->addWidget( AngleGroupBox );

    this->setLayout( VBoxLayout );

    this->setCameraPosition(xpos,ypos,zpos);
    this->setEulerAngle(alpha,beta,gamma);


}

void
GetCameraParameterWidget::setEulerAngle(int alpha , int beta , int gamma )
{
    this->_parameterChangedByThisWidget = false;
    this->_parameterChangedByOtherWidget = true;
    this->_angleSliderChanged = false;
    this->_alpha = alpha;
    this->_beta = beta;
    this->_gamma = gamma;
    this->_alphaSlider->setValue(this->_alpha);
    this->_betaSlider->setValue(this->_beta);
    this->_gammaSlider->setValue(this->_gamma);
    this->_angleSliderChanged = true;
    this->_parameterChangedByOtherWidget = false;

    return;
}

void
GetCameraParameterWidget::setCameraPosition( double xpos , double ypos , double zpos )
{
    this->_parameterChangedByThisWidget = false;
    this->_parameterChangedByOtherWidget = true;
    this->_xpos = xpos;
    this->_ypos = ypos;
    this->_zpos = zpos;
    this->_xPosSpinBox->setValue(this->_xpos);
    this->_yPosSpinBox->setValue(this->_ypos);
    this->_zPosSpinBox->setValue(this->_zpos);
    this->_parameterChangedByOtherWidget = false;


    return;
}

void
GetCameraParameterWidget::updateAlpha(int alpha)
{
    if( !this->_parameterChangedByThisWidget && !this->_parameterChangedByOtherWidget ) {
        this->_parameterChangedByThisWidget = true;
        emit this->ParameterChanged();
    }
    if( this->_angleSliderChanged )emit this->EulerAngleUpdated(alpha , this->_beta , this->_gamma);
    this->_alpha = alpha;
}

void
GetCameraParameterWidget::updateBeta(int beta)
{
    if( !this->_parameterChangedByThisWidget && !this->_parameterChangedByOtherWidget ) {
        this->_parameterChangedByThisWidget = true;
        emit this->ParameterChanged();
    }
    if( this->_angleSliderChanged )emit this->EulerAngleUpdated(this->_alpha , beta , this->_gamma);
    this->_beta = beta;

}

void
GetCameraParameterWidget::updateGamma(int gamma)
{
    if( !this->_parameterChangedByThisWidget && !this->_parameterChangedByOtherWidget ) {
        this->_parameterChangedByThisWidget = true;
        emit this->ParameterChanged();
    }
    if( this->_angleSliderChanged )emit this->EulerAngleUpdated(this->_alpha , this->_beta , gamma);
    this->_gamma = gamma;

}

void
GetCameraParameterWidget::updateXPos(double xPos)
{
    if( !this->_parameterChangedByThisWidget && !this->_parameterChangedByOtherWidget ) {
        this->_parameterChangedByThisWidget = true;
        emit this->ParameterChanged();
    }
    this->_xpos = xPos;
    emit this->CameraPositionUpdated(this->_xpos,this->_ypos,this->_zpos);
}

void
GetCameraParameterWidget::updateYPos(double yPos)
{
    if( !this->_parameterChangedByThisWidget && !this->_parameterChangedByOtherWidget ) {
        this->_parameterChangedByThisWidget = true;
        emit this->ParameterChanged();
    }
    this->_ypos = yPos;
    emit this->CameraPositionUpdated(this->_xpos,this->_ypos,this->_zpos);
}

void
GetCameraParameterWidget::updateZPos(double zPos)
{
    if( !this->_parameterChangedByThisWidget && !this->_parameterChangedByOtherWidget ) {
        this->_parameterChangedByThisWidget = true;
        emit this->ParameterChanged();
    }
    this->_zpos = zPos;
    emit this->CameraPositionUpdated(this->_xpos,this->_ypos,this->_zpos);
}
