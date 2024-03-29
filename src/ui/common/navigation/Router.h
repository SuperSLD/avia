//
// Created by Леонид Соляной on 02.02.2024.
//

#ifndef AVIA_ROUTER_H
#define AVIA_ROUTER_H


#include <QObject>
#include "src/ui/common/widgets/slidingstackedwidget/SlidingStackedWidget.h"
#include "src/ui/common/navigation/base/basefragmentfactory/BaseFragmentFactory.h"

/**
 * @brief The Navigator class
 *
 * Навигация в риложении и логика замены экранов.
 *
 * <p>Экраны лежат в списке и мы можем выполнить
 * переход дальше по цепочке, заменить текущий экран
 * или перейти назад по цепочке.</p>
 */
class Router: public QObject {
    Q_OBJECT
private:
    SlidingStackedWidget *currentContainer;
    BaseFragmentFactory *screensFactory;
    QList<BaseFragment*> stack;

    /**
     * @brief createAndConnect
     * @param tag тэг создаваемого фрагмента.
     *
     * Создание фрагмента по тегу и его
     * прикрепление к навигатору.
     *
     * @return фрагмент приконекченный к слотам навигатора.
     */
    BaseFragment* createAndConnect(QString tag);

    /**
     * @brief connectFragment
     * @param fragment фрагмент который переходит
     *        в активное состояние.
     *
     * Прикрепление текущего фрагмента
     * к слотам навигатора для быстрого
     * и удобного перехода между экранами.
     *
     */
    void connectFragment(BaseFragment *fragment);

    /**
     * @brief disconnectFragment
     * @param fragment
     *
     * Отключение сигналов от фрагмента.
     */
    void disconnectFragment(BaseFragment *fragment);

public:
    Router(
            SlidingStackedWidget *container,
            BaseFragmentFactory *screensFactory
    );
    ~Router();
    BaseFragment* getStartScreen();

public slots:
    /**
     * @brief navigateTo
     * @param tag имя следующего экрана.
     *
     * Переход к следующему экрану.
     */
    void navigateTo(QString tag);

    /**
     * @brief back
     *
     * Переход назад по цепочке.
     */
    void back();

    /**
     * @brief replace
     * @param tag имя экрана на который
     *        произойдет замена.
     *
     * Замена текущего экрана с сохранением
     * предыдущей цепочки.
     */
    void replace(QString tag);

    /**
     * @brief newRootScreen
     * @param tag имя экрана на который
     *        произойдет замена.
     *
     * Замена текущего экрана на новый и сброс
     * всей цепочки экранов.
     */
    void newRootScreen(QString tag);

    /**
     * @brief backWhithData
     * @param model
     *
     * Тот же бэк но с данными.
     */
    void backWhithData(BaseModel* model);

    /**
     * @brief navigateWhithData
     * @param model
     *
     * Тот же navigateTo но с данными.
     */
    void navigateWhithData(QString tag, BaseModel* model);


    /**
     * @brief removeOnFinishLast
     *
     * Удаление последнего элемента после анимации.
     */
    void removeOnFinishLast();

    /**
     * @brief removeOnReplace
     *
     * Удаление после замены текущего экрана
     */
    void removeOnReplace();

    /**
     * @brief removeOnReplace
     *
     * Удаление после создания новой цепочки
     */
    void removeOnRoot();

    /**
     * @brief navigateWhithData
     * @param model
     *
     * Тот же replace но с данными.
     */
    void replaceWhithData(QString tag, BaseModel* model);

    /**
     * @brief provideThemeChanged
     *
     * Перебрасывает событие сммены темы до главного окна.
     */
    void provideThemeChanged();

signals:

    void onThemeChanged();

};;


#endif //AVIA_ROUTER_H
