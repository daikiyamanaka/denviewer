#ifndef MODELLAYERWIDGET_H
#define MODELLAYERWIDGET_H
#include <QWidget>
#include <QtGui>

class ModelLayerWidget : public QWidget
{
    Q_OBJECT
public:
    ModelLayerWidget(QWidget *parent=0);
    int getSelectedIndex();
    std::vector<bool> getCheckState();
    void deleteItem(int index);
    void deleteAll();



private:
    QListWidget *modelList;
    std::vector<bool> checked;

signals:
    void updated();
    void selectedItemChanged(void);

public slots:
    void addList(const std::string &filename);
    void changeItemsState(QListWidgetItem *item);

};

#endif // MODELLAYERWIDGET_H
