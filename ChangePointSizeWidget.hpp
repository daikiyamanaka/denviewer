#ifndef CHANGEPOINTSIZEWIDGET_HPP
#define CHANGEPOINTSIZEWIDGET_HPP

#endif // CHANGEPOINTSIZEWIDGET_HPP

#include <QWidget>
#include <QtGui>

class ChangePointSizeWidget : public QWidget
{
    Q_OBJECT
private:
    QSpinBox *spinBox1;
public:
    explicit ChangePointSizeWidget( int pointSize, QWidget *parent = 0);
    int getPointSize( void );
signals:
    void updated();
public slots:
    void set_point_size( int value );
};

