/****************************************************************************
** Meta object code from reading C++ file 'ChangeViewAngle.h'
**
** Created: Tue May 29 13:46:51 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ChangeViewAngle.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ChangeViewAngle.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ChangeViewAngle[] = {

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
      17,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      27,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ChangeViewAngle[] = {
    "ChangeViewAngle\0\0updated()\0"
    "viewAngleIsUpdated()\0"
};

const QMetaObject ChangeViewAngle::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ChangeViewAngle,
      qt_meta_data_ChangeViewAngle, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ChangeViewAngle::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ChangeViewAngle::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ChangeViewAngle::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ChangeViewAngle))
        return static_cast<void*>(const_cast< ChangeViewAngle*>(this));
    return QWidget::qt_metacast(_clname);
}

int ChangeViewAngle::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updated(); break;
        case 1: viewAngleIsUpdated(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ChangeViewAngle::updated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
