#ifndef CHANGEWINDOWSIZEWIDGET_HPP
#define CHANGEWINDOWSIZEWIDGET_HPP

#include <QWidget>
#include <QtGui>
#include <QResizeEvent>

class ChangeWindowSizeWidget : public QWidget
{
    Q_OBJECT
private:
    QSpinBox *spinwidth;
    QSpinBox *spinheight;
    int _width, _height;
public:
    explicit ChangeWindowSizeWidget(int width, int height, QWidget *parent = 0);
    int getWindowWidth(void);
    int getWindowHeight(void);
    void setWindowWidth(int width);
    void setWindowHeight(int height);
signals:
    void updated(int width, int height);
    void sizechanged(int width, int height);
public slots:
    void set_window_height(int height);
    void set_window_width(int width);
protected:
    void resizeEvent(QResizeEvent* event);

};

#endif // CHANGEWINDOWSIZEWIDGET_HPP
