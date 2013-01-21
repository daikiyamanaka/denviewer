#include "NormalDisplayWidget.hpp"

NormalDisplayWidget::NormalDisplayWidget(const float nlength, QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *hBoxLayout1 = new QHBoxLayout;
    this->_spinbox1 = new QDoubleSpinBox;
    this->_spinbox1->setMinimum(0.0);
    this->_spinbox1->setMaximum(10.0);
    this->_spinbox1->setSingleStep(0.1);
    this->_spinbox1->setValue(nlength);
    QLabel *label1 = new QLabel(tr("Length"));

    connect(this->_spinbox1, SIGNAL(valueChanged(double)),this, SIGNAL(updated()));

    hBoxLayout1->addWidget(label1);
    hBoxLayout1->addWidget(this->_spinbox1);

    QHBoxLayout *hBoxLayout2 = new QHBoxLayout;
    this->_checkbox1 = new QCheckBox;
    this->_checkbox1->setChecked(false);

    connect(this->_checkbox1, SIGNAL(clicked()), this, SIGNAL(updated()));
    QLabel *label2 = new QLabel(tr("Both Side"));
    hBoxLayout2->addWidget(this->_checkbox1);
    hBoxLayout2->addWidget(label2);


    QHBoxLayout *hBoxLayout3 = new QHBoxLayout;
    this->_checkbox2 = new QCheckBox;
    this->_checkbox2->setChecked(true);
    connect(this->_checkbox2, SIGNAL(clicked()), this, SIGNAL(updated()));
    QLabel *label3 = new QLabel(tr("Show"));
    hBoxLayout3->addWidget(this->_checkbox2);
    hBoxLayout3->addWidget(label3);


/*
    QVBoxLayout *vBoxLayout1 = new QVBoxLayout;
    vBoxLayout1->addLayout(hBoxLayout4);
    vBoxLayout1->addLayout(hBoxLayout2);
    */
    QGridLayout *renderModeGridLayout = new QGridLayout;
    renderModeGridLayout->addLayout(hBoxLayout3,0,0,Qt::AlignLeft);
    renderModeGridLayout->addLayout(hBoxLayout1,0,1,Qt::AlignRight);
    renderModeGridLayout->addLayout(hBoxLayout2,1,0,Qt::AlignLeft);

    this->setLayout(renderModeGridLayout);
    //this->setLayout(vBoxLayout1);
    return;
}

float
NormalDisplayWidget::getNormalLength( void )
{
    return this->_spinbox1->value();
}

bool
NormalDisplayWidget::RenderAtCenter( void )
{
    return this->_checkbox1->isChecked();
}

bool
NormalDisplayWidget::RenderNormal( void )
{
    return this->_checkbox2->isChecked();
}


//void
//NormalDisplayWidget::set_normal_length(double l)
//{
 //   emit updated();
  //  return;
//}
