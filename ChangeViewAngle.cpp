#include "ChangeViewAngle.h"
#include<QtGui>

ChangeViewAngle::ChangeViewAngle(float _angle, QWidget *parent):QWidget(parent)
{
    QHBoxLayout *hBoxLayout1 = new QHBoxLayout;
    this->change_view_label = new QLabel;
    this->change_view_label->setText(QString("View Angle"));

    this->change_view_spin_box = new QSpinBox;
    //this->change_view_spin_box->text("View Angle");
    this->change_view_spin_box->setMinimum(this->MINIMUM_ANGLE);
    this->change_view_spin_box->setMaximum(this->MAXIMUM_ANGLE);
    this->change_view_spin_box->setSingleStep(1);
    //printf("%lf\n", _angle);
    this->change_view_spin_box->setValue(int(_angle));

    connect(this->change_view_spin_box, SIGNAL(valueChanged(int)), this, SLOT(viewAngleIsUpdated()));

    hBoxLayout1->addWidget(this->change_view_label);
    hBoxLayout1->addWidget(this->change_view_spin_box);

    this->setLayout(hBoxLayout1);
    return;
}

int ChangeViewAngle::getViewAngle(void){
    return this->change_view_spin_box->value();
}

void ChangeViewAngle::viewAngleIsUpdated(){
    //change_view_spin_box->setValue(_angle);
    emit updated();
}
