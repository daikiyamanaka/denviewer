#ifndef NORMALDISPLAYWIDGET_HPP
#define NORMALDISPLAYWIDGET_HPP

#include <QWidget>
#include <QtGui>

class NormalDisplayWidget : public QWidget
{
    Q_OBJECT
private:
    QDoubleSpinBox *_spinbox1;
    QCheckBox *_checkbox1;
    QCheckBox *_checkbox2;

public:
    explicit NormalDisplayWidget(const float nlength, QWidget *parent = 0);
    float getNormalLength( void );
    bool  RenderAtCenter( void );
    bool  RenderNormal( void );

signals:
    void updated();
    
public slots:
    //void set_normal_length( double l );
    
};

#endif // NORMALDISPLAYWIDGET_HPP
