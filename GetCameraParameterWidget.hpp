#ifndef GETCAMERAPARAMETERWIDGET_HPP
#define GETCAMERAPARAMETERWIDGET_HPP 1

#include <QWidget>
#include <QtGui>

class GetCameraParameterWidget : public QWidget
{
Q_OBJECT
private:
    QDoubleSpinBox *_xPosSpinBox;
    QDoubleSpinBox *_yPosSpinBox;
    QDoubleSpinBox *_zPosSpinBox;
    QSlider *_alphaSlider;
    QSlider *_betaSlider;
    QSlider *_gammaSlider;
    QSpinBox *_alphaspin;
    QSpinBox *_betaspin;
    QSpinBox *_gammaspin;

    int _alpha , _beta , _gamma;
    double _xpos , _ypos , _zpos;//posX

    bool _angleSliderChanged;
    bool _parameterChangedByThisWidget;//aimaimemine
    bool _parameterChangedByOtherWidget;//

public:
    explicit GetCameraParameterWidget(int alpha , int beta , int gamma, double xpos , double ypos , double zpos , QWidget *parent = 0);
    void setEulerAngle( int alpha , int beta , int gamma  );
    void setCameraPosition( double xpos , double ypos , double zpos );
signals:
    void CameraPositionUpdated(double xPos , double yPos , double zPos  );//
    void EulerAngleUpdated( int alpha , int beta , int gamma  );
    void ParameterChanged( void );

public slots:
    void updateAlpha( int alpha );//updateEulerAngleAlpha
    void updateBeta( int beta );
    void updateGamma( int gamma );
    void updateXPos( double xPos );//updatePosition
    void updateYPos( double yPos );
    void updateZPos( double zPos );

    
};

#endif // GETCAMERAPARAMETERWIDGET_H
