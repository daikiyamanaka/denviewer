#include "ShowVandFWidget.hpp"
#include <QtGui>

ShowVandFWidget::ShowVandFWidget(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *hboxlayout1 = new QHBoxLayout;
    QLabel *label1 = new QLabel( tr ( "Vertex : " ) );
    this->_showver = new QLabel( tr( " 0 " ) );
    hboxlayout1->addWidget( label1 );
    hboxlayout1->addWidget( this->_showver );

    QHBoxLayout *hboxlayout2 = new QHBoxLayout;
    QLabel *label3 = new QLabel( tr ( "Face : " ) );
    this->_showface = new QLabel( tr( " 0 " ) );
    hboxlayout2->addWidget( label3 );
    hboxlayout2->addWidget( this->_showface );

    QVBoxLayout *vboxLayout = new QVBoxLayout;
    vboxLayout->addLayout( hboxlayout1 );
    vboxLayout->addLayout( hboxlayout2 );

    this->setLayout(vboxLayout);
    return;
}

void
ShowVandFWidget::getVandFNumber(int &ver, int &fa){
    vertex = ver;
    face = fa;
    strv.setNum(vertex);
    strf.setNum(face);
    this->_showver->setText( strv );
    this->_showface->setText( strf );
}
