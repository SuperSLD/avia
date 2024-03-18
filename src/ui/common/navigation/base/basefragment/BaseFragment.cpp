//
// Created by Леонид Соляной on 02.02.2024.
//

#include "BaseFragment.h"
#include "src/ui/common/navigation/base/basemodel/BaseModel.h"
#include <QVBoxLayout>

BaseFragment::BaseFragment() {}
BaseFragment::~BaseFragment() {}
void BaseFragment::onPause() {}
void BaseFragment::onResume() {}
void BaseFragment::bindData(BaseModel* model) {}

void BaseFragment::clearList(QLayout *list) {
    QLayoutItem* child;
    while(list->count()!=0) {
        child = list->takeAt(0);
        if(child->layout() != 0) {
            clearList(child->layout());
        }
        else if(child->widget() != 0) {
            delete child->widget();
        }
        delete child;
    }
}

