//
// Created by Леонид Соляной on 02.02.2024.
//

#ifndef AVIA_BASEFRAGMENT_H
#define AVIA_BASEFRAGMENT_H

#include <QFrame>
#include <QVBoxLayout>
#include <QWidget>
#include "src/ui/common/navigation/base/basemodel/BaseModel.h"
#include "src/data/db/dbconnector/DBConnector.h"

/**
 * @brief The BaseFragment class
 *
 * Базовый фрагмент приложения.
 */
class BaseFragment: public QFrame {
Q_OBJECT

signals:

    void back();
    void backWhithData(BaseModel* model);

    void navigateTo(QString tag);
    void navigateWhithData(QString tag, BaseModel* model);

    void newRootScreen(QString tag);
    void replace(QString tag);
    void replaceWhithData(QString tag, BaseModel* model);

    void provideThemeChanged();

protected:

    void clearList(QLayout *list);

public:

    BaseFragment();
    ~BaseFragment();

    /**
     * @brief onPause
     *
     * Метод вызывается во время перехода экрана
     * в стэк.
     */
    virtual void onPause();

    /**
     * @brief onResume
     * Метод вызывается при возврашении к эерану
     * из стэка, при появлении на экран.
     */
    virtual void onResume();

    /**
     * @brief bindData
     *
     * Метод вызывается если на экран передаются
     * данные, с предыдущего экрана.
     *
     * @param model модель данных
     */
    virtual void bindData(BaseModel* model);

    virtual void setConnector(DBConnector *connector);
};

#endif //AVIA_BASEFRAGMENT_H
