/****************************************************************************
** Meta object code from reading C++ file 'MainFragment.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/ui/screens/main/MainFragment.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainFragment.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainFragment_t {
    QByteArrayData data[6];
    char stringdata0[75];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainFragment_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainFragment_t qt_meta_stringdata_MainFragment = {
    {
QT_MOC_LITERAL(0, 0, 12), // "MainFragment"
QT_MOC_LITERAL(1, 13, 18), // "onTabButtonClicked"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 2), // "id"
QT_MOC_LITERAL(4, 36, 15), // "onThemeSwitched"
QT_MOC_LITERAL(5, 52, 22) // "onOpenChangeConnection"

    },
    "MainFragment\0onTabButtonClicked\0\0id\0"
    "onThemeSwitched\0onOpenChangeConnection"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainFragment[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x08 /* Private */,
       4,    0,   32,    2, 0x08 /* Private */,
       5,    0,   33,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainFragment::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainFragment *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onTabButtonClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->onThemeSwitched(); break;
        case 2: _t->onOpenChangeConnection(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainFragment::staticMetaObject = { {
    QMetaObject::SuperData::link<BaseFragment::staticMetaObject>(),
    qt_meta_stringdata_MainFragment.data,
    qt_meta_data_MainFragment,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainFragment::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainFragment::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainFragment.stringdata0))
        return static_cast<void*>(this);
    return BaseFragment::qt_metacast(_clname);
}

int MainFragment::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseFragment::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
