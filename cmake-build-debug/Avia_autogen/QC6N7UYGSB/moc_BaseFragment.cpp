/****************************************************************************
** Meta object code from reading C++ file 'BaseFragment.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/ui/common/navigation/base/basefragment/BaseFragment.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BaseFragment.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BaseFragment_t {
    QByteArrayData data[12];
    char stringdata0[122];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BaseFragment_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BaseFragment_t qt_meta_stringdata_BaseFragment = {
    {
QT_MOC_LITERAL(0, 0, 12), // "BaseFragment"
QT_MOC_LITERAL(1, 13, 4), // "back"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 13), // "backWhithData"
QT_MOC_LITERAL(4, 33, 10), // "BaseModel*"
QT_MOC_LITERAL(5, 44, 5), // "model"
QT_MOC_LITERAL(6, 50, 10), // "navigateTo"
QT_MOC_LITERAL(7, 61, 3), // "tag"
QT_MOC_LITERAL(8, 65, 17), // "navigateWhithData"
QT_MOC_LITERAL(9, 83, 13), // "newRootScreen"
QT_MOC_LITERAL(10, 97, 7), // "replace"
QT_MOC_LITERAL(11, 105, 16) // "replaceWhithData"

    },
    "BaseFragment\0back\0\0backWhithData\0"
    "BaseModel*\0model\0navigateTo\0tag\0"
    "navigateWhithData\0newRootScreen\0replace\0"
    "replaceWhithData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BaseFragment[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    1,   50,    2, 0x06 /* Public */,
       6,    1,   53,    2, 0x06 /* Public */,
       8,    2,   56,    2, 0x06 /* Public */,
       9,    1,   61,    2, 0x06 /* Public */,
      10,    1,   64,    2, 0x06 /* Public */,
      11,    2,   67,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 4,    7,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 4,    7,    5,

       0        // eod
};

void BaseFragment::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BaseFragment *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->back(); break;
        case 1: _t->backWhithData((*reinterpret_cast< BaseModel*(*)>(_a[1]))); break;
        case 2: _t->navigateTo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->navigateWhithData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< BaseModel*(*)>(_a[2]))); break;
        case 4: _t->newRootScreen((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->replace((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->replaceWhithData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< BaseModel*(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (BaseFragment::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BaseFragment::back)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (BaseFragment::*)(BaseModel * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BaseFragment::backWhithData)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (BaseFragment::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BaseFragment::navigateTo)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (BaseFragment::*)(QString , BaseModel * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BaseFragment::navigateWhithData)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (BaseFragment::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BaseFragment::newRootScreen)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (BaseFragment::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BaseFragment::replace)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (BaseFragment::*)(QString , BaseModel * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BaseFragment::replaceWhithData)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject BaseFragment::staticMetaObject = { {
    QMetaObject::SuperData::link<QFrame::staticMetaObject>(),
    qt_meta_stringdata_BaseFragment.data,
    qt_meta_data_BaseFragment,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *BaseFragment::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BaseFragment::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BaseFragment.stringdata0))
        return static_cast<void*>(this);
    return QFrame::qt_metacast(_clname);
}

int BaseFragment::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void BaseFragment::back()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void BaseFragment::backWhithData(BaseModel * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void BaseFragment::navigateTo(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void BaseFragment::navigateWhithData(QString _t1, BaseModel * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void BaseFragment::newRootScreen(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void BaseFragment::replace(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void BaseFragment::replaceWhithData(QString _t1, BaseModel * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
