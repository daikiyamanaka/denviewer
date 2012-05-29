#ifndef CHANGEVIEWANGLE_H
#define CHANGEVIEWANGLE_H

#include <QWidget>
#include <QtGui>

class ChangeViewAngle : public QWidget
{
    Q_OBJECT
public:
    ChangeViewAngle(float _angle, QWidget *parent = 0);
    int getViewAngle(void);

private:
    QLabel *change_view_label;
    QSpinBox *change_view_spin_box;
    static const int MINIMUM_ANGLE = 1;
    static const int MAXIMUM_ANGLE = 89;

public slots:
    //void setViewAngle(int _angle);
    void viewAngleIsUpdated();
signals:
    void updated();

};

#endif // CHANGEVIEWANGLE_H
