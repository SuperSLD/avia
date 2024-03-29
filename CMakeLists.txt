cmake_minimum_required(VERSION 3.5)

project(Avia VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES x86_64)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

set(CMAKE_PREFIX_PATH "/Users/leonidsolanoj/Qt/5.15.2/clang_64")
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5Svg REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        resc.qrc
        resc/splash.svg
        resc/settings.svg
        resc/routes.svg
        resc/radio_on.svg
        resc/radio_off.svg
        resc/map.svg
        resc/flights.svg
        resc/edit.svg
        resc/db_icon.svg
        resc/chevron_right.svg
        resc/chevron_left.svg
        resc/arrow.svg
        resc/analytics.svg
        resc/splash_dark.svg
        resc/settings_dark.svg
        resc/routes_dark.svg
        resc/map_dark.svg
        resc/flights_dark.svg
        resc/edit_dark.svg
        resc/chevron_right_dark.svg
        resc/chevron_left_dark.svg
        resc/analytics_dark.svg
        resc/close.svg
        main.cpp
        src/mainwindow.cpp
        src/mainwindow.h
        src/ui/common/widgets/slidingstackedwidget/SlidingStackedWidget.cpp src/ui/common/widgets/slidingstackedwidget/SlidingStackedWidget.h src/ui/common/navigation/Router.cpp src/ui/common/navigation/Router.h src/ui/common/navigation/base/basefragment/BaseFragment.cpp src/ui/common/navigation/base/basefragment/BaseFragment.h src/ui/common/navigation/base/basemodel/BaseModel.cpp src/ui/common/navigation/base/basemodel/BaseModel.h src/ui/common/navigation/base/basefragmentfactory/BaseFragmentFactory.cpp src/ui/common/navigation/base/basefragmentfactory/BaseFragmentFactory.h src/ui/screens/splash/SplashFragment.cpp src/ui/screens/splash/SplashFragment.h src/ui/fragmentfactory/FragmentFactoryImpl.cpp src/ui/fragmentfactory/FragmentFactoryImpl.h src/ui/screens/main/MainFragment.cpp src/ui/screens/main/MainFragment.h src/data/settings/SettingsRepository.cpp src/data/settings/SettingsRepository.h src/ui/theme/AppTheme.h src/ui/common/widgets/menutabbutton/MenuTabButton.cpp src/ui/common/widgets/menutabbutton/MenuTabButton.h src/ui/screens/main/settingstab/SettingsTabFragment.cpp src/ui/screens/main/settingstab/SettingsTabFragment.h src/ui/screens/main/flightstab/FlightsTabFragment.cpp src/ui/screens/main/flightstab/FlightsTabFragment.h src/ui/common/widgets/toolbar/Toolbar.cpp src/ui/common/widgets/toolbar/Toolbar.h src/ui/screens/main/routestab/RoutesTabFragment.cpp src/ui/screens/main/routestab/RoutesTabFragment.h src/ui/screens/main/maptab/MapTabFragment.cpp src/ui/screens/main/maptab/MapTabFragment.h src/ui/screens/main/analyticstab/AnalyticsTabFragment.cpp src/ui/screens/main/analyticstab/AnalyticsTabFragment.h src/ui/common/widgets/button/Button.cpp src/ui/common/widgets/button/Button.h src/ui/common/widgets/switcher/Switcher.cpp src/ui/common/widgets/switcher/Switcher.h src/ui/common/widgets/switcher/SwitcherVariant.h src/domain/models/tabopen/TabOpenModel.h src/ui/screens/main/settingstab/changeconnection/ChangeConnectionFragment.cpp src/ui/screens/main/settingstab/changeconnection/ChangeConnectionFragment.h src/ui/common/widgets/textedit/TextEdit.cpp src/ui/common/widgets/textedit/TextEdit.h src/ui/common/widgets/table/Table.cpp src/ui/common/widgets/table/Table.h)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Avia
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(Avia SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Avia
            ${PROJECT_SOURCES}
        )
    endif()
endif()

qt5_import_plugins(${PROJECT_NAME} INCLUDE Qt5::QSvgPlugin)
target_link_libraries(Avia PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Svg)

set_target_properties(Avia PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Avia)
endif()
