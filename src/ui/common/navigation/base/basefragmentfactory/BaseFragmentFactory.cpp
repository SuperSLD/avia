//
// Created by Леонид Соляной on 02.02.2024.
//

#include "BaseFragmentFactory.h"

BaseFragmentFactory::BaseFragmentFactory() {

}

BaseFragmentFactory::~BaseFragmentFactory() {

}

BaseFragment* BaseFragmentFactory::create(QString tag) {return nullptr;}

QString BaseFragmentFactory::createStart() {return nullptr;}