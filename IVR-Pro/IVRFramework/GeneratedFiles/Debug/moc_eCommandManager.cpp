/****************************************************************************
** Meta object code from reading C++ file 'eCommandManager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Src/IVRFramework/command/eCommandManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'eCommandManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_IVRFramework__eCommandManager_t {
    QByteArrayData data[6];
    char stringdata0[91];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_IVRFramework__eCommandManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_IVRFramework__eCommandManager_t qt_meta_stringdata_IVRFramework__eCommandManager = {
    {
QT_MOC_LITERAL(0, 0, 29), // "IVRFramework::eCommandManager"
QT_MOC_LITERAL(1, 30, 13), // "OnUpdateState"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 18), // "OnCommandTriggered"
QT_MOC_LITERAL(4, 64, 21), // "OnCombCurIndexChanged"
QT_MOC_LITERAL(5, 86, 4) // "text"

    },
    "IVRFramework::eCommandManager\0"
    "OnUpdateState\0\0OnCommandTriggered\0"
    "OnCombCurIndexChanged\0text"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IVRFramework__eCommandManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x08 /* Private */,
       3,    0,   30,    2, 0x08 /* Private */,
       4,    1,   31,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,

       0        // eod
};

void IVRFramework::eCommandManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        eCommandManager *_t = static_cast<eCommandManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OnUpdateState(); break;
        case 1: _t->OnCommandTriggered(); break;
        case 2: _t->OnCombCurIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject IVRFramework::eCommandManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_IVRFramework__eCommandManager.data,
      qt_meta_data_IVRFramework__eCommandManager,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *IVRFramework::eCommandManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IVRFramework::eCommandManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_IVRFramework__eCommandManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int IVRFramework::eCommandManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
