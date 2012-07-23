#include "PreferencesDialog.hpp"

PreferencesDialog::PreferencesDialog(QWidget *parent, const Preference &preference): QDialog( parent)
{
    this->setMinimumSize(400, 300);
    QPushButton *initButton = new QPushButton(this);
    initButton->setText(tr("Init"));
    QPushButton *applyButton = new QPushButton(this);
    applyButton->setText(tr("Apply"));

    Color3f c = preference.getSurfaceColor();
    QPushButton *faceColorButton = new QPushButton(tr("Face Color"));
    QLabel *_faceColorLabel = new QLabel;
    _faceColorLabel->setFrameStyle ( QFrame::Sunken | QFrame::Panel );
    _faceColorLabel->setPalette ( QColor(c[0]*255, c[1]*255, c[2]*255));
    _faceColorLabel->setAutoFillBackground ( true );

    c = preference.getBackgroundColor();
    QPushButton *backgroundColorButton = new QPushButton(tr("Background Color"));
    QLabel *_backgroundColorLabel = new QLabel;
    _backgroundColorLabel->setFrameStyle(QFrame::Sunken | QFrame::Panel);
    _backgroundColorLabel->setPalette( QColor(c[0]*255, c[1]*255, c[2]*255));
    _backgroundColorLabel->setAutoFillBackground(true);

    c = preference.getWireColor();
    QPushButton *wireColorButton = new QPushButton(tr("Wire Color"));
    QLabel *_wireColorLabel = new QLabel;
    _wireColorLabel->setFrameStyle(QFrame::Sunken | QFrame::Panel);
    _wireColorLabel->setPalette( QColor(c[0]*255, c[1]*255, c[2]*255));
    _wireColorLabel->setAutoFillBackground(true);

    /*
    QPushButton *vertexColorButton = new QPushButton(tr("Vertex Color"));
    this->_vertexColorLabel = new QLabel;
    this->_vertexColorLabel->setFrameStyle(QFrame::Sunken | QFrame::Panel);
    this->_faceColorLabel->setPalette( faceColor);
    this->_faceColorLabel->setAutoFillBackground(true);
    */

/*
    QPushButton *lightColorButton = new QPushButton(tr("Light Color"));
    QLabel *_lightColorLabel = new QLabel;
    _lightColorLabel->setFrameStyle(QFrame::Sunken | QFrame::Panel);
    _lightColorLabel->setPalette( );
    _lightColorLabel->setAutoFillBackground(true);
*/

    QGridLayout *layout = new QGridLayout;
    layout->addWidget( faceColorButton, 0, 0);
    layout->addWidget(_faceColorLabel, 0, 1);
    layout->addWidget( backgroundColorButton, 1, 0);
    layout->addWidget(_backgroundColorLabel, 1, 1);
    layout->addWidget( wireColorButton, 2, 0);
    layout->addWidget(_wireColorLabel, 2, 1);
    //gridlayout->addWidget( vertexColorButton, 3, 0);
    //gridlayout->addWidget(this->_vertexColorLabel, 3, 1);
    //layout->addWidget( lightColorButton, 3, 0);
    //layout->addWidget(_lightColorLabel, 3, 1);
    layout->addWidget(initButton, 4, 0);
    layout->addWidget(applyButton, 4, 1);
    //layout->addStretch ( 1 );

    this->setLayout(layout);
}

void PreferencesDialog::initialize(){

}
