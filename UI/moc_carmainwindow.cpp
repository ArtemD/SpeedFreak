/****************************************************************************
** Meta object code from reading C++ file 'carmainwindow.h'
**
** Created: Fri Feb 26 11:59:39 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "carmainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'carmainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CarMainWindow[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x08,
      50,   44,   14,   14, 0x08,
      88,   83,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CarMainWindow[] = {
    "CarMainWindow\0\0on_autoStartButton_clicked()\0"
    "index\0on_listView_clicked(QModelIndex)\0"
    "unit\0updateUnitCompoBox(QString)\0"
};

const QMetaObject CarMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_CarMainWindow,
      qt_meta_data_CarMainWindow, 0 }
};

const QMetaObject *CarMainWindow::metaObject() const
{
    return &staticMetaObject;
}

void *CarMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CarMainWindow))
        return static_cast<void*>(const_cast< CarMainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int CarMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_autoStartButton_clicked(); break;
        case 1: on_listView_clicked((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 2: updateUnitCompoBox((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
