#ifndef PREFERENCE_H
#define PREFERENCE_H

#include <QtGui>
#include "mainwindow.h"

class Preference : public QDialog
{
    Q_OBJECT
    public:
	Preference(QWidget *parent = 0, int panneau = 0);

    signals:

    public slots:
	void enregistrement(void);
	void theme_change(QListWidgetItem * index);
	void ouvrirproxy(void);
	void ajoutproxy(void);
	void supprproxy(void);
	void selectproxy(int pos);

    private:
	QString opt_theme;
	bool opt_mem;
	QString opt_accueil;
	bool opt_javascript;
	bool opt_java;
	bool opt_images;
	bool opt_plugins;

	QGridLayout *global;
	QTabWidget *boite;
	QWebView *fake; //QWebView inutile mais sinon impossibilité de rajouter cela dans un tab...
	QPushButton *btn_save;
	QPushButton *btn_cancel;

	QVBoxLayout *lay_general;
	QWidget *widg_general;

	QGroupBox *theme;
	QVBoxLayout *lay_theme;
	QLabel *lbl_theme;
	QListWidget *list_theme;
	QLabel *lbl_legende;

	QGroupBox *demarrage;
	QVBoxLayout *lay_demarrage;
	QRadioButton *radio_memoire;
	QRadioButton *radio_pasmemoire;
	QLabel *lbl_accueil;
	QLineEdit *champ_accueil;

	QVBoxLayout *lay_content;
	QWidget *widg_content;

	QGroupBox *contenu;
	QVBoxLayout *lay_contenu;
	QCheckBox *check_javascript;
	QCheckBox *check_java;
	QCheckBox *check_images;
	QCheckBox *check_plugins;

	QVBoxLayout *lay_proxy;
	QWidget *widg_proxy;

	QGroupBox *proxy;
	QGridLayout *lay_proxy_box;
	QComboBox *combo_proxy;
	QLabel *lbl_nom;
	QLineEdit *nom_proxy;
	QLabel *lbl_type;
	QComboBox *type_proxy;
	QLabel *lbl_ip;
	QLineEdit *champ_ip;
	QLabel *lbl_port;
	QLineEdit *champ_port;
	QLabel *lbl_pseudo;
	QLineEdit *champ_pseudo;
	QLabel *lbl_pass;
	QLineEdit *champ_pass;
	QPushButton *btn_sauver;
	QPushButton *btn_suppr;

	void lister_theme(void);
	void lire_options(void);
	bool tester_icones(QString path);
};

#endif // PREFERENCE_H
