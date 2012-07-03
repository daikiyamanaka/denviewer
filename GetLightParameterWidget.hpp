#ifndef GETLIGHTPARAMETERWIDGET_HPP
#define GETLIGHTPARAMETERWIDGET_HPP

#include <QWidget>
#include <QtGui>

class GetLightParameterWidget : public QWidget
{
    Q_OBJECT
private:
    QDoubleSpinBox* _xPosSpinBox;
    QDoubleSpinBox* _yPosSpinBox;
    QDoubleSpinBox* _zPosSpinBox;

    double _xpos, _ypos, _zpos;

public:
    explicit GetLightParameterWidget(double xpos , double ypos , double zpos, QWidget *parent = 0);
    void setLightPosition( double xpos , double ypos , double zpos );
signals:
    void Light0PositionUpdated(double xpos , double ypos , double zpos);
    
public slots:
    void updateXPos( double xPos );
    void updateYPos( double yPos );
    void updateZPos( double zPos );
};

#endif // GETLIGHTPARAMETERWIDGET_HPP
