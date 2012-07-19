#include "ModelLayerWidget.hpp"

#include <iostream>

ModelLayerWidget::ModelLayerWidget(QWidget *parent ) : QWidget(parent)
{
    modelList = new QListWidget(this);
    //modelList->addItem(QString("test"));

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(modelList);
    this->setLayout(layout);

    connect(modelList, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(changeItemsState(QListWidgetItem*)));
}


void ModelLayerWidget::addList(const std::string &filename){
    QListWidgetItem *item = new QListWidgetItem;
    item->setText(QString(filename.c_str()));
    item->setFlags(item->flags()| Qt::ItemIsUserCheckable | Qt::ItemIsEnabled |Qt::ItemIsSelectable);
    item->setCheckState(Qt::Checked);
    checked.push_back(true);
    modelList->addItem(item);
    modelList->repaint();

}

int ModelLayerWidget::getSelectedIndex(){
    int index = 0;
    for(int i=0; i<modelList->count(); i++){
        if(modelList->item(i)->isSelected()){
            index = i;
            break;
        }
    }
    return index;
}

std::vector<bool> ModelLayerWidget::getCheckState(){
    return checked;
}

void ModelLayerWidget::deleteItem(int index){

}

void ModelLayerWidget::deleteAll(){

}

void ModelLayerWidget::changeItemsState(QListWidgetItem* item){
    //std::cout << "change items state" << std::endl;

    for(int i=0; i<modelList->count(); i++){
        if(modelList->item(i)->checkState() == Qt::Checked){
            checked[i] = true;
            //std::cout << "true" << std::endl;
        }
        else{
            checked[i] = false;
            //std::cout << "false" << std::endl;
        }
        //checked[i] = Qt::Checked & modelList->item(i)->checkState();
    }

    emit updated();
}
