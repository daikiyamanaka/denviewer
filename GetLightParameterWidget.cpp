#include "GetLightParameterWidget.hpp"

GetLightParameterWidget::GetLightParameterWidget(double xpos, double ypos, double zpos, QWidget *parent) :
    QWidget(parent)
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

    this->setLightPosition(xpos, ypos, zpos);
}

void
GetLightParameterWidget::setLightPosition(double xpos, double ypos, double zpos)
{
    this->_xpos = xpos;
    this->_ypos = ypos;
    this->_zpos = zpos;
    this->_xPosSpinBox->setValue(this->_xpos);
    this->_yPosSpinBox->setValue(this->_ypos);
    this->_zPosSpinBox->setValue(this->_zpos);

    return;
}

void
GetLightParameterWidget::updateXPos(double xPos)
{
    this->_xpos = xPos;
    emit this->Light0PositionUpdated(this->_xpos,this->_ypos,this->_zpos);
}

void
GetLightParameterWidget::updateYPos(double yPos)
{
    this->_ypos = yPos;
    emit this->Light0PositionUpdated(this->_xpos,this->_ypos,this->_zpos);
}

void
GetLightParameterWidget::updateZPos(double zPos)
{
    this->_zpos = zPos;
    emit this->Light0PositionUpdated(this->_xpos,this->_ypos,this->_zpos);
}
