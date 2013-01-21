#include "projectionmodewidget.h"

ProjectionModeWidget::ProjectionModeWidget(const bool perspective, QWidget *parent) :
    QWidget(parent)
{
    QGroupBox *gbox = new QGroupBox(tr("Projection Mode"));
    QVBoxLayout *vbox = new QVBoxLayout;
    this->_radiobutton1 = new QRadioButton(tr("Perspective"));
    this->_radiobutton2 = new QRadioButton(tr("Orthographic"));
    vbox->addWidget(this->_radiobutton1);
    vbox->addWidget(this->_radiobutton2);
    vbox->addStretch(1);
    gbox->setLayout(vbox);

    this->_radiobutton1->setChecked(perspective);
    connect(this->_radiobutton1,SIGNAL(clicked()),this,SIGNAL(updated()));
    connect(this->_radiobutton2,SIGNAL(clicked()),this,SIGNAL(updated()));

    QVBoxLayout *vbox2 = new QVBoxLayout;
    vbox2->addWidget(gbox);
    this->setLayout(vbox2);
}

bool
ProjectionModeWidget::projectionMode(void)
{
    return this->_radiobutton1->isChecked();
}

void
ProjectionModeWidget::set_projection_mode(bool p)
{
    this->_radiobutton1->setChecked(p);
    emit updated();
}
