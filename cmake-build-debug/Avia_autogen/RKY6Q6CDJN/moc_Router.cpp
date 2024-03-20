/****************************************************************************
** Meta object code from reading C++ file 'Router.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/ui/common/navigation/Router.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Router.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Router_t {
    QByteArrayData data[17];
    char stringdata0[199];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Router_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Router_t qt_meta_stringdata_Router = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Router"
QT_MOC_LITERAL(1, 7, 14), // "onThemeChanged"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 10), // "navigateTo"
QT_MOC_LITERAL(4, 34, 3), // "tag"
QT_MOC_LITERAL(5, 38, 4), // "back"
QT_MOC_LITERAL(6, 43, 7), // "replace"
QT_MOC_LITERAL(7, 51, 13), // "newRootScreen"
QT_MOC_LITERAL(8, 65, 13), // "backWhithData"
QT_MOC_LITERAL(9, 79, 10), // "BaseModel*"
QT_MOC_LITERAL(10, 90, 5), // "model"
QT_MOC_LITERAL(11, 96, 17), // "navigateWhithData"
QT_MOC_LITERAL(12, 114, 18), // "removeOnFinishLast"
QT_MOC_LITERAL(13, 133, 15), // "removeOnReplace"
QT_MOC_LITERAL(14, 149, 12), // "removeOnRoot"
QT_MOC_LITERAL(15, 162, 16), // "replaceWhithData"
QT_MOC_LITERAL(16, 179, 19) // "provideThemeChanged"

    },
    "Router\0onThemeChanged\0\0navigateTo\0tag\0"
    "back\0replace\0newRootScreen\0backWhithData\0"
    "BaseModel*\0model\0navigateWhithData\0"
    "removeOnFinishLast\0removeOnReplace\0"
    "removeOnRoot\0replaceWhithData\0"
    "provideThemeChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Router[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   75,    2, 0x0a /* Public */,
       5,    0,   78,    2, 0x0a /* Public */,
       6,    1,   79,    2, 0x0a /* Public */,
       7,    1,   82,    2, 0x0a /* Public */,
       8,    1,   85,    2, 0x0a /* Public */,
      11,    2,   88,    2, 0x0a /* Public */,
      12,    0,   93,    2, 0x0a /* Public */,
      13,    0,   94,    2, 0x0a /* Public */,
      14,    0,   95,    2, 0x0a /* Public */,
      15,    2,   96,    2, 0x0a /* Public */,
      16,    0,  101,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 9,    4,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 9,    4,   10,
    QMetaType::Void,

       0        // eod
};

void Router::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Router *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onThemeChanged(); break;
        case 1: _t->navigateTo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->back(); break;
        case 3: _t->replace((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->newRootScreen((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->backWhithData((*reinterpret_cast< BaseModel*(*)>(_a[1]))); break;
        case 6: _t->navigateWhithData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< BaseModel*(*)>(_a[2]))); break;
        case 7: _t->removeOnFinishLast(); break;
        case 8: _t->removeOnReplace(); break;
        case 9: _t->removeOnRoot(); break;
        case 10: _t->replaceWhithData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< BaseModel*(*)>(_a[2]))); break;
        case 11: _t->provideThemeChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Router::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Router::onThemeChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Router::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Router.data,
    qt_meta_data_Router,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Router::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Router::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Router.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Router::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void Router::onThemeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
