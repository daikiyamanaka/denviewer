#ifndef PROJECTIONMODEWIDGET_H
#define PROJECTIONMODEWIDGET_H

#include <QWidget>
#include <QtGui>

class ProjectionModeWidget : public QWidget
{
    Q_OBJECT
private:
    QRadioButton *_radiobutton1;
    QRadioButton *_radiobutton2;

public:
    explicit ProjectionModeWidget(const bool perspective, QWidget *parent = 0);
    bool projectionMode( void );

signals:
    void updated();
    
public slots:
    void set_projection_mode( bool p);

    
};

#endif // PROJECTIONMODEWIDGET_H
