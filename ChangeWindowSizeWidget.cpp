#include "ChangeWindowSizeWidget.hpp"

ChangeWindowSizeWidget::ChangeWindowSizeWidget(int width, int height, QWidget *parent) :
    QWidget(parent)
{
    this->_width = width;
    this->_height = height;
    QVBoxLayout *vBoxLayout1 = new QVBoxLayout;

    this->spinheight = new QSpinBox;
    this->spinheight->setMinimum(100);
    this->spinheight->setMaximum(2500);
    this->spinheight->setValue(height);
    QLabel *labelheight = new QLabel(tr("Window Height"));

    connect(this->spinheight, SIGNAL(valueChanged(int)), this, SLOT(set_window_height(int)));

    this->spinwidth = new QSpinBox;
    this->spinwidth->setMinimum(100);
    this->spinwidth->setMaximum(2500);
    this->spinwidth->setValue(width);
    QLabel *labelwidth = new QLabel(tr("Window Width"));

    connect(this->spinwidth, SIGNAL(valueChanged(int)), this, SLOT(set_window_width(int)));

    QHBoxLayout *heightbox = new QHBoxLayout;
    QHBoxLayout *widthbox = new QHBoxLayout;

    widthbox->addWidget(labelwidth);
    widthbox->addWidget(this->spinwidth);
    heightbox->addWidget(labelheight);
    heightbox->addWidget(this->spinheight);

    vBoxLayout1->addLayout(widthbox);
    vBoxLayout1->addLayout(heightbox);

    this->setLayout(vBoxLayout1);
    return;
}

void
ChangeWindowSizeWidget::set_window_height(int height)
{
    this->_height = height;
    emit updated(this->_width, this->_height);
    return;
}

void
ChangeWindowSizeWidget::set_window_width(int width)
{
    this->_width = width;
    emit updated(this->_width, this->_height);
    return;
}

int
ChangeWindowSizeWidget::getWindowHeight(void)
{
    return this->spinheight->value();
}

int
ChangeWindowSizeWidget::getWindowWidth(void)
{
    return this->spinwidth->value();
}

void
ChangeWindowSizeWidget::ResizeEvent(QResizeEvent *event)
{

    event->size();
    //this->_width = event->size().width();
    //this->_height = event->size().height();
    return;
}
