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
    QByteArrayData data[15];
    char stringdata0[164];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Router_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Router_t qt_meta_stringdata_Router = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Router"
QT_MOC_LITERAL(1, 7, 10), // "navigateTo"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 3), // "tag"
QT_MOC_LITERAL(4, 23, 4), // "back"
QT_MOC_LITERAL(5, 28, 7), // "replace"
QT_MOC_LITERAL(6, 36, 13), // "newRootScreen"
QT_MOC_LITERAL(7, 50, 13), // "backWhithData"
QT_MOC_LITERAL(8, 64, 10), // "BaseModel*"
QT_MOC_LITERAL(9, 75, 5), // "model"
QT_MOC_LITERAL(10, 81, 17), // "navigateWhithData"
QT_MOC_LITERAL(11, 99, 18), // "removeOnFinishLast"
QT_MOC_LITERAL(12, 118, 15), // "removeOnReplace"
QT_MOC_LITERAL(13, 134, 12), // "removeOnRoot"
QT_MOC_LITERAL(14, 147, 16) // "replaceWhithData"

    },
    "Router\0navigateTo\0\0tag\0back\0replace\0"
    "newRootScreen\0backWhithData\0BaseModel*\0"
    "model\0navigateWhithData\0removeOnFinishLast\0"
    "removeOnReplace\0removeOnRoot\0"
    "replaceWhithData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Router[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x0a /* Public */,
       4,    0,   67,    2, 0x0a /* Public */,
       5,    1,   68,    2, 0x0a /* Public */,
       6,    1,   71,    2, 0x0a /* Public */,
       7,    1,   74,    2, 0x0a /* Public */,
      10,    2,   77,    2, 0x0a /* Public */,
      11,    0,   82,    2, 0x0a /* Public */,
      12,    0,   83,    2, 0x0a /* Public */,
      13,    0,   84,    2, 0x0a /* Public */,
      14,    2,   85,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 8,    3,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 8,    3,    9,

       0        // eod
};

void Router::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Router *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->navigateTo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->back(); break;
        case 2: _t->replace((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->newRootScreen((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->backWhithData((*reinterpret_cast< BaseModel*(*)>(_a[1]))); break;
        case 5: _t->navigateWhithData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< BaseModel*(*)>(_a[2]))); break;
        case 6: _t->removeOnFinishLast(); break;
        case 7: _t->removeOnReplace(); break;
        case 8: _t->removeOnRoot(); break;
        case 9: _t->replaceWhithData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< BaseModel*(*)>(_a[2]))); break;
        default: ;
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
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
