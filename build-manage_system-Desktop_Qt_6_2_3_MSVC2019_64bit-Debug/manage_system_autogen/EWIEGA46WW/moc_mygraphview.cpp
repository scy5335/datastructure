/****************************************************************************
** Meta object code from reading C++ file 'mygraphview.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../manage_system/mygraphview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mygraphview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_myGraphView_t {
    const uint offsetsAndSize[14];
    char stringdata0[65];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_myGraphView_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_myGraphView_t qt_meta_stringdata_myGraphView = {
    {
QT_MOC_LITERAL(0, 11), // "myGraphView"
QT_MOC_LITERAL(12, 16), // "mouseLeftClicked"
QT_MOC_LITERAL(29, 0), // ""
QT_MOC_LITERAL(30, 8), // "position"
QT_MOC_LITERAL(39, 13), // "mouseReleased"
QT_MOC_LITERAL(53, 8), // "selected"
QT_MOC_LITERAL(62, 2) // "id"

    },
    "myGraphView\0mouseLeftClicked\0\0position\0"
    "mouseReleased\0selected\0id"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_myGraphView[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   32,    2, 0x06,    1 /* Public */,
       4,    0,   35,    2, 0x06,    3 /* Public */,
       5,    1,   36,    2, 0x06,    4 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QPointF,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,

       0        // eod
};

void myGraphView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<myGraphView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->mouseLeftClicked((*reinterpret_cast< QPointF(*)>(_a[1]))); break;
        case 1: _t->mouseReleased(); break;
        case 2: _t->selected((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (myGraphView::*)(QPointF );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myGraphView::mouseLeftClicked)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (myGraphView::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myGraphView::mouseReleased)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (myGraphView::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myGraphView::selected)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject myGraphView::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsView::staticMetaObject>(),
    qt_meta_stringdata_myGraphView.offsetsAndSize,
    qt_meta_data_myGraphView,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_myGraphView_t
, QtPrivate::TypeAndForceComplete<myGraphView, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QPointF, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>



>,
    nullptr
} };


const QMetaObject *myGraphView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *myGraphView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_myGraphView.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsView::qt_metacast(_clname);
}

int myGraphView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void myGraphView::mouseLeftClicked(QPointF _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void myGraphView::mouseReleased()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void myGraphView::selected(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
struct qt_meta_stringdata_myGraphVectex_t {
    const uint offsetsAndSize[8];
    char stringdata0[27];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_myGraphVectex_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_myGraphVectex_t qt_meta_stringdata_myGraphVectex = {
    {
QT_MOC_LITERAL(0, 13), // "myGraphVectex"
QT_MOC_LITERAL(14, 8), // "selected"
QT_MOC_LITERAL(23, 0), // ""
QT_MOC_LITERAL(24, 2) // "id"

    },
    "myGraphVectex\0selected\0\0id"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_myGraphVectex[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   20,    2, 0x06,    1 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void myGraphVectex::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<myGraphVectex *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->selected((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (myGraphVectex::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myGraphVectex::selected)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject myGraphVectex::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_myGraphVectex.offsetsAndSize,
    qt_meta_data_myGraphVectex,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_myGraphVectex_t
, QtPrivate::TypeAndForceComplete<myGraphVectex, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>



>,
    nullptr
} };


const QMetaObject *myGraphVectex::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *myGraphVectex::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_myGraphVectex.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QGraphicsEllipseItem"))
        return static_cast< QGraphicsEllipseItem*>(this);
    return QObject::qt_metacast(_clname);
}

int myGraphVectex::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void myGraphVectex::selected(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_myGraphEdge_t {
    const uint offsetsAndSize[2];
    char stringdata0[12];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_myGraphEdge_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_myGraphEdge_t qt_meta_stringdata_myGraphEdge = {
    {
QT_MOC_LITERAL(0, 11) // "myGraphEdge"

    },
    "myGraphEdge"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_myGraphEdge[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void myGraphEdge::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject myGraphEdge::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_myGraphEdge.offsetsAndSize,
    qt_meta_data_myGraphEdge,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_myGraphEdge_t
, QtPrivate::TypeAndForceComplete<myGraphEdge, std::true_type>



>,
    nullptr
} };


const QMetaObject *myGraphEdge::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *myGraphEdge::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_myGraphEdge.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QGraphicsLineItem"))
        return static_cast< QGraphicsLineItem*>(this);
    return QObject::qt_metacast(_clname);
}

int myGraphEdge::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
