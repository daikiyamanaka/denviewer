/****************************************************************************
** Meta object code from reading C++ file 'ChangeColorWidget.hpp'
**
** Created: Tue May 29 13:46:51 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ChangeColorWidget.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ChangeColorWidget.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ChangeColorWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      29,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ChangeColorWidget[] = {
    "ChangeColorWidget\0\0updated()\0"
    "set_surface_color()\0"
};

const QMetaObject ChangeColorWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ChangeColorWidget,
      qt_meta_data_ChangeColorWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ChangeColorWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ChangeColorWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ChangeColorWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ChangeColorWidget))
        return static_cast<void*>(const_cast< ChangeColorWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ChangeColorWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updated(); break;
        case 1: set_surface_color(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ChangeColorWidget::updated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
