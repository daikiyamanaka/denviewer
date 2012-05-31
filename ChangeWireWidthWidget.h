#ifndef CHANGEWIREWIDTHWIDGET_H
#define CHANGEWIREWIDTHWIDGET_H

#include <QWidget>
#include <QtGui>

class ChangeWireWidthWidget : public QWidget
{
    Q_OBJECT
private:
    QSpinBox *spinBox1;
public:
    explicit ChangeWireWidthWidget( int wireWidth, QWidget *parent = 0);
    int getWireWidth( void );
signals:
    void updated();
public slots:
    void set_wire_width( int value );
};

#endif // CHANGEWIREWIDTHWIDGET_H
