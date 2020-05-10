/****************************************************************************
** Meta object code from reading C++ file 'eBaseDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Src/IVRFramework/base_widget/eBaseDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'eBaseDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_IVRFramework__eBaseDialog_t {
    QByteArrayData data[6];
    char stringdata0[74];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_IVRFramework__eBaseDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_IVRFramework__eBaseDialog_t qt_meta_stringdata_IVRFramework__eBaseDialog = {
    {
QT_MOC_LITERAL(0, 0, 25), // "IVRFramework::eBaseDialog"
QT_MOC_LITERAL(1, 26, 15), // "sigDialogClosed"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 8), // "onClosed"
QT_MOC_LITERAL(4, 52, 9), // "onMinSize"
QT_MOC_LITERAL(5, 62, 11) // "onMaxResize"

    },
    "IVRFramework::eBaseDialog\0sigDialogClosed\0"
    "\0onClosed\0onMinSize\0onMaxResize"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IVRFramework__eBaseDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   35,    2, 0x09 /* Protected */,
       4,    0,   36,    2, 0x09 /* Protected */,
       5,    0,   37,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void IVRFramework::eBaseDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        eBaseDialog *_t = static_cast<eBaseDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigDialogClosed(); break;
        case 1: _t->onClosed(); break;
        case 2: _t->onMinSize(); break;
        case 3: _t->onMaxResize(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (eBaseDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&eBaseDialog::sigDialogClosed)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject IVRFramework::eBaseDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_IVRFramework__eBaseDialog.data,
      qt_meta_data_IVRFramework__eBaseDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *IVRFramework::eBaseDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IVRFramework::eBaseDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_IVRFramework__eBaseDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int IVRFramework::eBaseDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void IVRFramework::eBaseDialog::sigDialogClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
