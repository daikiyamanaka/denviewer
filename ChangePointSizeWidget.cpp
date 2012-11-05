#include "ChangePointSizeWidget.hpp"

ChangePointSizeWidget::ChangePointSizeWidget(const int pointsize, QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *hBoxLayout1 = new QHBoxLayout;
    this->spinBox1 = new QSpinBox;
    this->spinBox1->setMinimum(1);
    this->spinBox1->setValue(pointsize);
    QLabel *label1 = new QLabel(tr("Radius"));

    connect(this->spinBox1, SIGNAL(valueChanged(int)),this, SLOT(set_point_size(int)));

    hBoxLayout1->addWidget(label1);
    hBoxLayout1->addWidget(this->spinBox1);

    this->setLayout(hBoxLayout1);
    return;
}

void
ChangePointSizeWidget::set_point_size( int value )
{
    emit updated();
    return;
}

int
ChangePointSizeWidget::getPointSize( void )
{
    return this->spinBox1->value();
}

