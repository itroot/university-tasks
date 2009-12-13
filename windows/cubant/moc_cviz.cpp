/****************************************************************************
** Meta object code from reading C++ file 'cviz.h'
**
** Created: Thu Dec 10 10:29:50 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "cviz.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cviz.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CViz[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x08,
      13,    5,    5,    5, 0x08,
      20,    5,    5,    5, 0x08,
      34,    5,    5,    5, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CViz[] = {
    "CViz\0\0open()\0save()\0drawCubants()\0"
    "saveVRML()\0"
};

const QMetaObject CViz::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_CViz,
      qt_meta_data_CViz, 0 }
};

const QMetaObject *CViz::metaObject() const
{
    return &staticMetaObject;
}

void *CViz::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CViz))
        return static_cast<void*>(const_cast< CViz*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int CViz::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: open(); break;
        case 1: save(); break;
        case 2: drawCubants(); break;
        case 3: saveVRML(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
