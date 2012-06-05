#ifndef SHOWVANDFWIDGET_HPP
#define SHOWVANDFWIDGET_HPP

#include <QLabel>
#include <QWidget>

class ShowVandFWidget : public QWidget
{
    Q_OBJECT
private:
    QLabel* _showver;
    QLabel* _showface;
    int vertex;
    int face;
    QString strv;
    QString strf;
public:
    ShowVandFWidget(QWidget *parent = 0);
    void getVandFNumber(int &ver, int &fa);
signals:

public slots:
    
};

#endif // SHOWVANDFWIDGET_HPP
