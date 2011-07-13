#ifndef HEADER_FENPRINCIPALE
#define HEADER_FENPRINCIPALE

#include <QtGui>
#include <QtWebKit>
//#include <QWebView>
//#include <QWebSettings>
//#include <QWebFrame>
//#include <QWebHistory>
//#include <QtNetwork>
#include <Qsci/qsciscintilla.h> // le header principal de QScintilla
#include <Qsci/qscilexerhtml.h> // coloriage en html
#include "preference.h"
#include "mycookiejar.h"
#include "favoris.h"
#include "historique.h"


#define MAX_ITEM 11
#define ZOOM 0.1

//class Favoris; // pour éviter les problèmes type: "error: ISO C++ forbids declaration of ‘Favoris’ with no type"

class MonTabWidget : public QTabWidget
{
    public:
	MonTabWidget(QWidget *parent = 0);

    private:

    protected:
	bool event(QEvent *event);

};

class Interface : public QMainWindow
{
    Q_OBJECT

    public:
	Interface(QWidget * parent = 0, QString url="");
	void setOptionMemory(bool opt) {opt_mem = opt;};
	void setOptionAccueil(QString url) {opt_accueil = url;};
	void setListeProxy(QComboBox * proxy);

    public slots:
        //---------------------------------------------------------------------------
        void precedent(void) {pagecourante()->back();};
        void suivant(void) {pagecourante()->forward();};
        void recharger(void) {pagecourante()->reload();};
        void arreter(void) {pagecourante()->stop();};
	void accueil(void);
	void aller(QString url="");
	void zoomin(void) {pagecourante()->setZoomFactor(pagecourante()->zoomFactor()+ZOOM);};
	void zoomout(void) {pagecourante()->setZoomFactor(pagecourante()->zoomFactor()-ZOOM);};
	void zoomorigine(void) {pagecourante()->setZoomFactor(1);};
	void zoomtexte(bool etat) {QWebSettings::globalSettings()->setAttribute(QWebSettings::ZoomTextOnly,etat);};
        //---------------------------------------------------------------------------
	void ajouttab(QString url="");
        void fermertab(int index=-1);
        void changertitre(QString titre);
	void changericone(void);
        void changerurl(QUrl url);
        void changementtab(void);
        void showprogression(bool etat=false);
	void shownavigation(bool etat=false);
	void showproxy(bool etat=false);
	void showrechercher(bool etat=false);
	void showfavoris(bool etat=false) {barre_favoris->setVisible(etat);};
        void rechercher(void);
	void rechercher_rev(void);
	void surligner(bool etat);
	void imprimer(void);
	void select_histo(int nb);
	void nouvelle_fenetre(void);
	void ouvrir(void);
	void pleinecran(bool etat);
	void sauver(void);
	void preference(void);
	void afficher_source(void);
	void activerproxy(bool etat);
	void inventaire_proxy(void);
	void selectproxy(int pos);
	void editerproxy(void);
	void ajoutfavoris(void);

    private:
        void creer_menu(void);
        QMenu *menu_fichier;
        QMenu *menu_navigation;
	QMenu *menu_affichage;
        QMenu *menu_aide;
	QMenu *submenu_toolbar;
	QMenu *menu_favoris;

        void creer_design(void);
	void creer_barre_navigation(void);
	void creer_barre_recherche(void);
	void creer_barre_proxy(void);
	void creer_barre_favoris(void);
	MonTabWidget *conteneur;
	QProgressBar *progression;
	QPushButton *btn_addtab;

	//barre de navigation
	QToolBar *barre_navig;
        QLineEdit *adresse;
	QComboBox *histo;
	int *histo_pos;
	QComboBox *search_engine;

	//barre de recherche
	QToolBar *barre_search;
	QLabel *lbl_search;
	QLineEdit *line_search;
	QCheckBox *btn_casse;
	QWebPage::FindFlags *search_options;
	QAction *action_close_search;
	QAction *action_prev_search;
	QAction *action_next_search;
	QAction *action_highlight;

	//barre de proxys
	QToolBar *barre_proxy;
	QAction *action_close_proxy;
	QComboBox *combo_proxy;
	QLabel *lbl_ip;
	QLabel *champ_ip;
	QLabel *lbl_port;
	QLabel *champ_port;
	QLabel *lbl_type;
	QLabel *champ_type;
	QLabel *lbl_pseudo;
	QLabel *champ_pseudo;
	QPushButton *btn_activer;
	QPushButton *btn_editer;

	//barre de favoris
	QToolBar *barre_favoris;

        void creer_actions(void);
        //actions "fichier"
        QAction *action_quitter;
        QAction *action_new;
        QAction *action_close;
	QAction *action_print;
	QAction *action_new_window;
	QAction *action_open;
	QAction *action_save;
	QAction *action_preference;

        //actions "navigation"
        QAction *action_previous;
        QAction *action_next;
        QAction *action_go;
        QAction *action_refresh;
        QAction *action_stop;
        QAction *action_home;
	QAction *action_history;

	//actions "affichage"
	QAction *action_search;
	QAction *action_navigation;
	QAction *action_proxy;
	QAction *action_bookmark;
	QAction *action_fullscreen;
	QAction *action_zoomin;
	QAction *action_zoomout;
	QAction *action_zoom0;
	QAction *action_zoomtext;
	QAction *action_source;

	//actions "favoris"
	QAction *action_addbookmark;
	QAction *action_showbookmark;

	//actions "help"
        QAction *action_about;
	QAction *action_about_qt;

	QWebView *pagecourante(void) {return conteneur->currentWidget()->findChild<QWebView *>();};
	void actu_history(QString texte="");

	//Gestion des options (attributs et méthodes)
	void options_lire(void);
	void options_ecrire(void);
	void liens_ecrire(void);
	QString opt_theme;
	QStringList opt_mem_url;
	QStringList opt_mem_name;
	int opt_search_engine;
	bool opt_maximized;
	QRect opt_geometry;
	bool opt_mem;
	QString opt_accueil;
	bool opt_javascript;
	bool opt_java;
	bool opt_images;
	bool opt_plugins;

	//trucs divers...
	QNetworkDiskCache *network_cache;
	QNetworkRequest *requete;
	Favoris *favoris;
	Historique *historique;

	//Ré-implémentation des méthodes...
	protected:
	    void closeEvent(QCloseEvent *event);
};


#endif
