/****************************************************************************
** Meta object code from reading C++ file 'material_manage_page.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../manage_system/material_manage_page.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'material_manage_page.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_material_manage_page_t {
    const uint offsetsAndSize[14];
    char stringdata0[94];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_material_manage_page_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_material_manage_page_t qt_meta_stringdata_material_manage_page = {
    {
QT_MOC_LITERAL(0, 20), // "material_manage_page"
QT_MOC_LITERAL(21, 16), // "add_new_material"
QT_MOC_LITERAL(38, 0), // ""
QT_MOC_LITERAL(39, 11), // "description"
QT_MOC_LITERAL(51, 9), // "file_path"
QT_MOC_LITERAL(61, 16), // "get_all_material"
QT_MOC_LITERAL(78, 15) // "delete_material"

    },
    "material_manage_page\0add_new_material\0"
    "\0description\0file_path\0get_all_material\0"
    "delete_material"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_material_manage_page[] = {

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
       1,    2,   32,    2, 0x06,    1 /* Public */,
       5,    0,   37,    2, 0x06,    4 /* Public */,
       6,    1,   38,    2, 0x06,    5 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

void material_manage_page::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<material_manage_page *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->add_new_material((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->get_all_material(); break;
        case 2: _t->delete_material((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (material_manage_page::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&material_manage_page::add_new_material)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (material_manage_page::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&material_manage_page::get_all_material)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (material_manage_page::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&material_manage_page::delete_material)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject material_manage_page::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_material_manage_page.offsetsAndSize,
    qt_meta_data_material_manage_page,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_material_manage_page_t
, QtPrivate::TypeAndForceComplete<material_manage_page, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>



>,
    nullptr
} };


const QMetaObject *material_manage_page::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *material_manage_page::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_material_manage_page.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int material_manage_page::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void material_manage_page::add_new_material(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void material_manage_page::get_all_material()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void material_manage_page::delete_material(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
