/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.hpp'
**
** Created: Tue May 29 13:46:48 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MainWindow.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      22,   11,   11,   11, 0x08,
      33,   11,   11,   11, 0x08,
      40,   11,   11,   11, 0x08,
      47,   11,   11,   11, 0x08,
      60,   11,   11,   11, 0x08,
      73,   11,   11,   11, 0x08,
      88,   11,   11,   11, 0x08,
     108,   11,   11,   11, 0x08,
     126,   11,   11,   11, 0x08,
     137,   11,   11,   11, 0x08,
     153,  149,   11,   11, 0x08,
     180,   11,   11,   11, 0x08,
     203,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0updated()\0new_file()\0"
    "open()\0save()\0openCamera()\0saveCamera()\0"
    "saveSnapshot()\0polygon_wireframe()\0"
    "polygon_surface()\0view_fit()\0view_init()\0"
    "x,y\0mouse_dragged(float,float)\0"
    "update_surface_color()\0"
    "update_perspective_angle()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updated(); break;
        case 1: new_file(); break;
        case 2: open(); break;
        case 3: save(); break;
        case 4: openCamera(); break;
        case 5: saveCamera(); break;
        case 6: saveSnapshot(); break;
        case 7: polygon_wireframe(); break;
        case 8: polygon_surface(); break;
        case 9: view_fit(); break;
        case 10: view_init(); break;
        case 11: mouse_dragged((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 12: update_surface_color(); break;
        case 13: update_perspective_angle(); break;
        default: ;
        }
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::updated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
