#include "ChangeWireWidthWidget.h"

ChangeWireWidthWidget::ChangeWireWidthWidget(const int wireWidth, QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *hBoxLayout1 = new QHBoxLayout;
    this->spinBox1 = new QSpinBox;
    this->spinBox1->setMinimum(1);
    this->spinBox1->setValue(wireWidth);
    QLabel *label1 = new QLabel(tr("Wire width"));

    connect(this->spinBox1, SIGNAL(valueChanged(int)),this, SLOT(set_wire_width(int)));

    hBoxLayout1->addWidget(label1);
    hBoxLayout1->addWidget(this->spinBox1);

    this->setLayout(hBoxLayout1);
    return;
}

void
ChangeWireWidthWidget::set_wire_width( int value )
{
    emit updated();
    return;
}

int
ChangeWireWidthWidget::getWireWidth( void )
{
    return this->spinBox1->value();
}
