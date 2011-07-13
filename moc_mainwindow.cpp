/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Sun Jul 11 21:50:25 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Interface[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      45,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      23,   10,   10,   10, 0x0a,
      33,   10,   10,   10, 0x0a,
      45,   10,   10,   10, 0x0a,
      55,   10,   10,   10, 0x0a,
      69,   65,   10,   10, 0x0a,
      84,   10,   10,   10, 0x2a,
      92,   10,   10,   10, 0x0a,
     101,   10,   10,   10, 0x0a,
     111,   10,   10,   10, 0x0a,
     130,  125,   10,   10, 0x0a,
     146,   65,   10,   10, 0x0a,
     164,   10,   10,   10, 0x2a,
     181,  175,   10,   10, 0x0a,
     196,   10,   10,   10, 0x2a,
     214,  208,   10,   10, 0x0a,
     236,   10,   10,   10, 0x0a,
     251,   65,   10,   10, 0x0a,
     268,   10,   10,   10, 0x0a,
     284,  125,   10,   10, 0x0a,
     306,   10,   10,   10, 0x2a,
     324,  125,   10,   10, 0x0a,
     345,   10,   10,   10, 0x2a,
     362,  125,   10,   10, 0x0a,
     378,   10,   10,   10, 0x2a,
     390,  125,   10,   10, 0x0a,
     411,   10,   10,   10, 0x2a,
     428,  125,   10,   10, 0x0a,
     446,   10,   10,   10, 0x2a,
     460,   10,   10,   10, 0x0a,
     473,   10,   10,   10, 0x0a,
     490,  125,   10,   10, 0x0a,
     506,   10,   10,   10, 0x0a,
     520,  517,   10,   10, 0x0a,
     538,   10,   10,   10, 0x0a,
     557,   10,   10,   10, 0x0a,
     566,  125,   10,   10, 0x0a,
     583,   10,   10,   10, 0x0a,
     592,   10,   10,   10, 0x0a,
     605,   10,   10,   10, 0x0a,
     623,  125,   10,   10, 0x0a,
     642,   10,   10,   10, 0x0a,
     665,  661,   10,   10, 0x0a,
     682,   10,   10,   10, 0x0a,
     696,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Interface[] = {
    "Interface\0\0precedent()\0suivant()\0"
    "recharger()\0arreter()\0accueil()\0url\0"
    "aller(QString)\0aller()\0zoomin()\0"
    "zoomout()\0zoomorigine()\0etat\0"
    "zoomtexte(bool)\0ajouttab(QString)\0"
    "ajouttab()\0index\0fermertab(int)\0"
    "fermertab()\0titre\0changertitre(QString)\0"
    "changericone()\0changerurl(QUrl)\0"
    "changementtab()\0showprogression(bool)\0"
    "showprogression()\0shownavigation(bool)\0"
    "shownavigation()\0showproxy(bool)\0"
    "showproxy()\0showrechercher(bool)\0"
    "showrechercher()\0showfavoris(bool)\0"
    "showfavoris()\0rechercher()\0rechercher_rev()\0"
    "surligner(bool)\0imprimer()\0nb\0"
    "select_histo(int)\0nouvelle_fenetre()\0"
    "ouvrir()\0pleinecran(bool)\0sauver()\0"
    "preference()\0afficher_source()\0"
    "activerproxy(bool)\0inventaire_proxy()\0"
    "pos\0selectproxy(int)\0editerproxy()\0"
    "ajoutfavoris()\0"
};

const QMetaObject Interface::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Interface,
      qt_meta_data_Interface, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Interface::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Interface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Interface::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Interface))
        return static_cast<void*>(const_cast< Interface*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Interface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: precedent(); break;
        case 1: suivant(); break;
        case 2: recharger(); break;
        case 3: arreter(); break;
        case 4: accueil(); break;
        case 5: aller((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: aller(); break;
        case 7: zoomin(); break;
        case 8: zoomout(); break;
        case 9: zoomorigine(); break;
        case 10: zoomtexte((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: ajouttab((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: ajouttab(); break;
        case 13: fermertab((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: fermertab(); break;
        case 15: changertitre((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 16: changericone(); break;
        case 17: changerurl((*reinterpret_cast< QUrl(*)>(_a[1]))); break;
        case 18: changementtab(); break;
        case 19: showprogression((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 20: showprogression(); break;
        case 21: shownavigation((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 22: shownavigation(); break;
        case 23: showproxy((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 24: showproxy(); break;
        case 25: showrechercher((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 26: showrechercher(); break;
        case 27: showfavoris((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 28: showfavoris(); break;
        case 29: rechercher(); break;
        case 30: rechercher_rev(); break;
        case 31: surligner((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 32: imprimer(); break;
        case 33: select_histo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 34: nouvelle_fenetre(); break;
        case 35: ouvrir(); break;
        case 36: pleinecran((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 37: sauver(); break;
        case 38: preference(); break;
        case 39: afficher_source(); break;
        case 40: activerproxy((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 41: inventaire_proxy(); break;
        case 42: selectproxy((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 43: editerproxy(); break;
        case 44: ajoutfavoris(); break;
        default: ;
        }
        _id -= 45;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
