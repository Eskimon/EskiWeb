#include "mainwindow.h"

MonTabWidget::MonTabWidget(QWidget *parent) : QTabWidget(parent)
{

}

bool MonTabWidget::event(QEvent *event)
{
    if(event->type()==QEvent::MouseButtonDblClick)
    {
	Interface * essai = (Interface *) this->window();
	if(essai == NULL)
	    QMessageBox::critical(this,"Erreur","bug");
	else
	    essai->ajouttab();

	event->accept();
	return true;
    }
    else
    {
	event->ignore();
	return false;
    }
}

Interface::Interface(QWidget * parent, QString url) : QMainWindow(parent)
{
    this->setObjectName("Navigateur");

    favoris = new Favoris(this);
    historique = new Historique(this);

    if (!QDir(qApp->applicationDirPath() + "/cache/").exists())
    {
	    // Si le dossier de cache n'existe pas, on le crée
	    QDir(qApp->applicationDirPath()).mkdir("cache");
    }

    // on crée un emplacement pour enregistrer les données de cache
    QWebSettings::setIconDatabasePath(qApp->applicationDirPath() + "/cache/");
    //on crée le gestionnaire de cache...
    network_cache = new QNetworkDiskCache(this);
    network_cache->setCacheDirectory(qApp->applicationDirPath() + "/cache/");
    //on crée la requete permettant l'accès au cache...
    requete = new QNetworkRequest(QUrl(opt_accueil));
    requete->setAttribute(QNetworkRequest::CacheLoadControlAttribute,QNetworkRequest::PreferNetwork);
    requete->setAttribute(QNetworkRequest::CacheSaveControlAttribute,true);

    options_lire();

    QWebSettings::globalSettings()->setAttribute(QWebSettings::JavaEnabled,opt_java);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled,opt_plugins);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::JavascriptEnabled,opt_javascript);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::AutoLoadImages,opt_images);

    creer_actions();
    creer_menu();
    creer_design();

    search_engine->setCurrentIndex(opt_search_engine);
    this->setGeometry(opt_geometry);
    if(opt_maximized)
	this->showMaximized();

    for(int i=0; i<opt_mem_url.count(); i++)
    {
	ajouttab(opt_mem_url.at(i));
	conteneur->setTabText(i,opt_mem_name.at(i));
    }

    if(!conteneur->count()) //si il y a aucun onglet de lancer
	ajouttab(url);
}

void Interface::creer_menu(void)
{
    //on crée les menus   -------------------------------------------------------------------------
    menu_fichier = menuBar()->addMenu("&Fichier");
    menu_affichage = menuBar()->addMenu("&Affichage");
    menu_navigation = menuBar()->addMenu("&Historique");
    menu_favoris = menuBar()->addMenu("&Favoris");
    menu_aide = menuBar()->addMenu("Aide");

    //menu "fichier"   ----------------------------------------------------------------------------
    menu_fichier->addAction(action_new_window);
    menu_fichier->addAction(action_new);
    menu_fichier->addAction(action_close);
    menu_fichier->addSeparator();
    menu_fichier->addAction(action_open);
    menu_fichier->addAction(action_save);
    menu_fichier->addAction(action_print);
    menu_fichier->addSeparator();
    menu_fichier->addAction(action_preference);
    menu_fichier->addSeparator();
    menu_fichier->addAction(action_quitter);

    //menu "affichage"   --------------------------------------------------------------------------
    submenu_toolbar = menu_affichage->addMenu("Barre d'outils");
    submenu_toolbar->addAction(action_navigation);
    submenu_toolbar->addAction(action_search);
    submenu_toolbar->addAction(action_proxy);
    submenu_toolbar->addAction(action_bookmark);
    menu_affichage->addSeparator();
    menu_affichage->addAction(action_zoomtext);
    menu_affichage->addAction(action_zoomin);
    menu_affichage->addAction(action_zoomout);
    menu_affichage->addAction(action_zoom0);
    menu_affichage->addSeparator();
    menu_affichage->addAction(action_fullscreen);
    menu_affichage->addSeparator();
    menu_affichage->addAction(action_source);

    //menu "navigation"   -------------------------------------------------------------------------
    menu_navigation->addAction(action_previous);
    menu_navigation->addAction(action_next);
    menu_navigation->addSeparator();
    //menu_navigation->addAction(action_go);
    //menu_navigation->addAction(action_stop);
    //menu_navigation->addSeparator();
    //menu_navigation->addAction(action_refresh);
    menu_navigation->addAction(action_home);
    menu_navigation->addSeparator();
    menu_navigation->addAction(action_history);

    //menu "favoris"   ----------------------------------------------------------------------------
    menu_favoris->addAction(action_addbookmark);
    menu_favoris->addAction(action_showbookmark);

    //menu "aide"   -------------------------------------------------------------------------------
    action_about = menu_aide->addAction("A propos de Eskiweb");
    action_about_qt = menu_aide->addAction("A propos de Qt");
}

void Interface::creer_actions(void)
{
    //actions "fichier"   -------------------------------------------------------------------------
    action_new_window = new QAction("Nouvel &fenêtre",this);
    action_new = new QAction("&Nouvel onglet",this);
    action_quitter = new QAction("&Quitter",this);
    action_close = new QAction("&Fermer onglet",this);
    action_print = new QAction("&Imprimer...",this);
    action_open = new QAction("&Ouvrir...",this);
    action_save = new QAction("&Sauver sous...",this);
    action_preference = new QAction("&Préférences...",this);

    connect(action_quitter,SIGNAL(triggered()),qApp,SLOT(quit()));
    connect(action_new,SIGNAL(triggered()),this,SLOT(ajouttab()));
    connect(action_new_window,SIGNAL(triggered()),this,SLOT(nouvelle_fenetre()));
    connect(action_close,SIGNAL(triggered()),this,SLOT(fermertab()));
    connect(action_print,SIGNAL(triggered()),this,SLOT(imprimer()));
    connect(action_open,SIGNAL(triggered()),this,SLOT(ouvrir()));
    connect(action_save,SIGNAL(triggered()),this,SLOT(sauver()));
    connect(action_preference,SIGNAL(triggered()),this,SLOT(preference()));

    action_new_window->setShortcut(QKeySequence(QKeySequence::New));
    action_quitter->setShortcut(QKeySequence(QKeySequence::Quit));
    action_new->setShortcut(QKeySequence(QKeySequence::AddTab));
    action_close->setShortcut(QKeySequence(QKeySequence::Close));
    action_print->setShortcut(QKeySequence(QKeySequence::Print));
    action_open->setShortcut(QKeySequence(QKeySequence::Open));
    action_save->setShortcut(QKeySequence(QKeySequence::Save));

    //actions "navigation"   ----------------------------------------------------------------------

    action_previous = new QAction("Page &précédente",this);
    action_next = new QAction("Page &suivante",this);
    action_go = new QAction("&Go !",this);
    action_stop = new QAction("&Stop !",this);
    action_refresh = new QAction("&Recharger",this);
    action_home = new QAction("Page d'&Accueil",this);
    action_history = new QAction("&Historique...",this);

    connect(action_previous,SIGNAL(triggered()),this,SLOT(precedent()));
    connect(action_next,SIGNAL(triggered()),this,SLOT(suivant()));
    connect(action_stop,SIGNAL(triggered()),this,SLOT(arreter()));
    connect(action_home,SIGNAL(triggered()),this,SLOT(accueil()));
    connect(action_refresh,SIGNAL(triggered()),this,SLOT(recharger()));
    connect(action_go,SIGNAL(triggered()),this,SLOT(aller()));
    connect(action_history,SIGNAL(triggered()),historique,SLOT(afficher()));

    action_previous->setShortcut(QKeySequence("Alt+left"));
    action_next->setShortcut(QKeySequence("Alt+right"));
    action_home->setShortcut(QKeySequence("Alt+home"));
    action_refresh->setShortcut(QKeySequence(QKeySequence::Refresh));
    action_history->setShortcut(QKeySequence("Ctrl+h"));

    action_previous->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/themes/"+ opt_theme + "/previous.png"));
    action_next->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/themes/"+ opt_theme + "/next.png"));
    action_go->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/themes/"+ opt_theme + "/go.png"));
    action_stop->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/themes/"+ opt_theme + "/stop.png"));
    action_refresh->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/themes/"+ opt_theme + "/refresh.png"));
    action_home->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/themes/"+ opt_theme + "/home.png"));

    //actions "affichage"   -----------------------------------------------------------------------
    action_fullscreen = new QAction("&Plein Ecran",this);
    action_zoomin = new QAction("Zoom a&vant",this);
    action_zoomout = new QAction("Zoom a&rrière",this);
    action_zoom0 = new QAction("Zoom &normal",this);
    action_zoomtext = new QAction("Zoom sur &texte",this);
    action_source = new QAction("Afficher source",this);
    action_search = new QAction("&Rechercher",this);
    action_navigation = new QAction("&Navigation",this);
    action_proxy = new QAction("&Proxy",this);
    action_bookmark = new QAction("&Favoris",this);

    action_fullscreen->setCheckable(true);
    action_zoomtext->setCheckable(true);
    action_search->setCheckable(true);
    action_navigation->setCheckable(true);
    action_navigation->setChecked(true);
    action_proxy->setCheckable(true);
    action_bookmark->setCheckable(true);
    action_bookmark->setChecked(true);

    connect(action_fullscreen,SIGNAL(toggled(bool)),this,SLOT(pleinecran(bool)));
    connect(action_zoomin,SIGNAL(triggered()),this,SLOT(zoomin()));
    connect(action_zoomout,SIGNAL(triggered()),this,SLOT(zoomout()));
    connect(action_zoom0,SIGNAL(triggered()),this,SLOT(zoomorigine()));
    connect(action_zoomtext,SIGNAL(toggled(bool)),this,SLOT(zoomtexte(bool)));
    connect(action_source,SIGNAL(triggered()),this,SLOT(afficher_source()));
    connect(action_search,SIGNAL(toggled(bool)),this,SLOT(showrechercher(bool)));
    connect(action_navigation,SIGNAL(toggled(bool)),this,SLOT(shownavigation(bool)));
    connect(action_proxy,SIGNAL(toggled(bool)),this,SLOT(showproxy(bool)));
    connect(action_bookmark,SIGNAL(toggled(bool)),this,SLOT(showfavoris(bool)));

    action_fullscreen->setShortcut(QKeySequence("F11"));
    action_zoomin->setShortcut(QKeySequence(QKeySequence::ZoomIn));
    action_zoomout->setShortcut(QKeySequence(QKeySequence::ZoomOut));
    action_zoom0->setShortcut(QKeySequence("Ctrl+0"));
    action_source->setShortcut(QKeySequence("Ctrl+U"));
    action_search->setShortcut(QKeySequence(QKeySequence::Find));

    //actions "favoris"   -------------------------------------------------------------------------
    action_addbookmark = new QAction("Mettre en favoris...",this);
    action_showbookmark =new QAction("Orgniser les favoris...",this);

    connect(action_addbookmark,SIGNAL(triggered()),this,SLOT(ajoutfavoris()));
    connect(action_showbookmark,SIGNAL(triggered()),favoris,SLOT(afficher()));

    //actions "help"   ----------------------------------------------------------------------------
    action_about = new QAction("A propos de EskiNet...",this);
    action_about_qt = new QAction("A propos de Qt...",this);

    connect(action_about_qt,SIGNAL(triggered()),qApp,SLOT(aboutQt()));
}

void Interface::creer_design(void)
{
    setWindowTitle("EskiWeb");
    //setWindowIcon(QIcon(QCoreApplication::applicationDirPath() + "/icones_prog/EskiNet_Logo.ico"));
    setWindowIcon(QIcon(":/icones/logo"));
    //conteneur = new QTabWidget(this);
    conteneur = new MonTabWidget(this);
    btn_addtab = new QPushButton(QIcon(QCoreApplication::applicationDirPath() + "/themes/" + opt_theme + "/add.png"),"",this);
    btn_addtab->setMaximumSize(32,32);
    btn_addtab->setFlat(false); //a voir lequel est plus propre...
    conteneur->setCornerWidget(btn_addtab, Qt::TopLeftCorner);
    connect(btn_addtab,SIGNAL(clicked()),this,SLOT(ajouttab()));
    connect(conteneur,SIGNAL(tabCloseRequested(int)),this,SLOT(fermertab(int)));
    connect(conteneur,SIGNAL(currentChanged(int)),this,SLOT(changementtab()));
    conteneur->setMovable(true);
    setCentralWidget(conteneur);

    creer_barre_navigation();
    creer_barre_recherche();
    creer_barre_proxy();
    creer_barre_favoris();
}

void Interface::creer_barre_navigation(void) //Création de la barre de navigation
{
    barre_navig = new QToolBar("Navigation",this);
    addToolBar(Qt::TopToolBarArea,barre_navig);
    barre_navig->setFloatable(false);
    barre_navig->setMovable(false);
    barre_navig->addAction(action_previous);
    histo = new QComboBox(this);
    histo_pos = new int;
    histo->setMaximumWidth(20);
    histo->setMaxVisibleItems(MAX_ITEM);
    histo->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    barre_navig->addAction(action_next);
    barre_navig->addWidget(histo);
    barre_navig->addAction(action_stop);
    barre_navig->addAction(action_refresh);
    barre_navig->addAction(action_home);
    adresse = new QLineEdit(this);
    barre_navig->addWidget(adresse);
    barre_navig->addAction(action_go);
    search_engine = new QComboBox(this);
    search_engine->addItem(QIcon(QCoreApplication::applicationDirPath() + "/ico_search/google.png"),"Google");
    search_engine->addItem(QIcon(QCoreApplication::applicationDirPath() + "/ico_search/google.png"),"J'ai...chance");
    search_engine->addItem(QIcon(QCoreApplication::applicationDirPath() + "/ico_search/wiki.png"),"Wikipedia");
    search_engine->addItem(QIcon(QCoreApplication::applicationDirPath() + "/ico_search/bing.ico"),"Bing");
    search_engine->addItem(QIcon(QCoreApplication::applicationDirPath() + "/ico_search/yahoo.jpg"),"Yahoo !");
    barre_navig->addWidget(search_engine);

    connect(histo,SIGNAL(activated(int)),this,SLOT(select_histo(int)));
    connect(adresse,SIGNAL(returnPressed()),action_go,SLOT(trigger()));
}

void Interface::creer_barre_recherche(void) //Création de la barre de recherche
{
    barre_search = new QToolBar("Recherche",this);
    addToolBar(Qt::BottomToolBarArea,barre_search);
    barre_search->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    barre_search->setFloatable(false);
    action_close_search = new QAction(QIcon(QCoreApplication::applicationDirPath() + "/themes/"+ opt_theme + "/search_close.png"),"",this);
    action_prev_search = new QAction(QIcon(QCoreApplication::applicationDirPath() + "/themes/"+ opt_theme + "/search_previous.png"),"précédent",this);
    action_next_search = new QAction(QIcon(QCoreApplication::applicationDirPath() + "/themes/"+ opt_theme + "/search_next.png"),"suivant",this);
    action_highlight = new QAction(QIcon(QCoreApplication::applicationDirPath() + "/themes/"+ opt_theme + "/search_highlight.png"),"Surligner occurences",this);
    action_close_search->setToolTip("Fermer");
    action_prev_search->setToolTip(action_prev_search->text());
    action_next_search->setToolTip(action_next_search->text());
    action_highlight->setToolTip(action_highlight->text());
    action_highlight->setCheckable(true);
    lbl_search = new QLabel("Recherche : ",this);
    line_search = new QLineEdit(this);
    //line_search->setAutoFillBackground(true);
    btn_casse = new QCheckBox("Respecter la casse",this);
    //space = new QSpacerItem(1,1,QSizePolicy::Expanding);
    search_options = new QWebPage::FindFlags;
    line_search->setMaximumWidth(200);
    barre_search->addAction(action_close_search);
    barre_search->addSeparator();
    barre_search->addWidget(lbl_search);
    barre_search->addWidget(line_search);
    barre_search->addAction(action_prev_search);
    barre_search->addAction(action_next_search);
    barre_search->addAction(action_highlight);
    barre_search->addWidget(btn_casse);
    barre_search->close();

    connect(action_close_search,SIGNAL(triggered()),this,SLOT(showrechercher()));
    connect(line_search,SIGNAL(returnPressed()),this,SLOT(rechercher()));
    connect(line_search,SIGNAL(textChanged(QString)),this,SLOT(rechercher()));
    connect(action_next_search,SIGNAL(triggered()),this,SLOT(rechercher()));
    connect(action_prev_search,SIGNAL(triggered()),this,SLOT(rechercher_rev()));
    connect(action_highlight,SIGNAL(toggled(bool)),this,SLOT(surligner(bool)));
}

void Interface::creer_barre_proxy(void) //Création de la barre des proxys
{
    barre_proxy = new QToolBar("Proxys",this);
    addToolBar(Qt::BottomToolBarArea,barre_proxy);
    combo_proxy = new QComboBox(this);
    lbl_ip = new QLabel(" ip/adresse : ",this);
    champ_ip = new QLabel(this);
    lbl_port = new QLabel(" port : ",this);
    champ_port = new QLabel(this);
    lbl_type = new QLabel(" type : ",this);
    champ_type = new QLabel(this);
    lbl_pseudo = new QLabel("    id : ",this);
    champ_pseudo = new QLabel(this);
    btn_activer = new QPushButton("Activer !",this);
    btn_editer = new QPushButton("Editer...",this);
    action_close_proxy = new QAction(QIcon(QCoreApplication::applicationDirPath() + "/themes/"+ opt_theme + "/search_close.png"),"Fermer",this);

    champ_ip->setFont(QFont("Courier",-1,QFont::Bold));
    champ_port->setFont(QFont("Courier",-1,QFont::Bold));
    champ_pseudo->setFont(QFont("Courier",-1,QFont::Bold));
    champ_type->setFont(QFont("Courier",-1,QFont::Bold));
    champ_ip->setMinimumWidth(200);
    champ_port->setMinimumWidth(60);
    champ_pseudo->setMinimumWidth(150);
    champ_type->setMinimumWidth(150);
    champ_ip->setMaximumWidth(200);
    champ_port->setMaximumWidth(60);
    champ_pseudo->setMaximumWidth(150);
    champ_type->setMaximumWidth(100);
    btn_activer->setCheckable(true);

    barre_proxy->addAction(action_close_proxy);
    barre_proxy->addSeparator();
    barre_proxy->addWidget(combo_proxy);
    barre_proxy->addWidget(lbl_ip);
    barre_proxy->addWidget(champ_ip);
    barre_proxy->addWidget(lbl_port);
    barre_proxy->addWidget(champ_port);
    barre_proxy->addWidget(lbl_type);
    barre_proxy->addWidget(champ_type);
    barre_proxy->addWidget(lbl_pseudo);
    barre_proxy->addWidget(champ_pseudo);
    barre_proxy->addWidget(btn_activer);
    barre_proxy->addWidget(btn_editer);

    connect(btn_activer,SIGNAL(toggled(bool)),this,SLOT(activerproxy(bool)));
    connect(btn_editer,SIGNAL(clicked()),this,SLOT(editerproxy()));
    connect(action_close_proxy,SIGNAL(triggered()),this,SLOT(showproxy()));
    connect(combo_proxy,SIGNAL(currentIndexChanged(int)),this,SLOT(selectproxy(int)));

    inventaire_proxy();

    barre_proxy->close();
}

void Interface::creer_barre_favoris(void) //Création de la barre de favoris
{
    QList<TFavoris> list;
    barre_favoris = new QToolBar("Favoris",this);
    addToolBar(Qt::TopToolBarArea,barre_favoris);
    barre_favoris->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    barre_favoris->setMaximumHeight(30);

    favoris->get_barre(&list);

    QSignalMapper * signalMapper =  new QSignalMapper(this);
    for(int i=0; i<list.count();i++)
    {
	//QAction *button =  QAction(list.at(i).nom,barre_favoris);
	QAction *button = new QAction(list.at(i).favicon,list.at(i).nom,this);
	button->setToolTip(list.at(i).nom + "\n" + list.at(i).url);
	connect(button, SIGNAL(triggered()),signalMapper,SLOT(map()));
	signalMapper->setMapping(button, list.at(i).url);
	barre_favoris->addAction(button);
    }
    connect(signalMapper,SIGNAL(mapped(QString)),this,SLOT(aller(QString)));

}

void Interface::ajouttab(QString url)
{
    if(url.isEmpty())
	url = opt_accueil;

    QWidget *fenetre;
    fenetre = new QWidget(this);
    QVBoxLayout *layout;
    layout = new QVBoxLayout(this);
    QWebView *onglet;
    onglet=new QWebView(this);
    QProgressBar *progression;
    progression = new QProgressBar(this);

    requete->setUrl(url);

    onglet->page()->networkAccessManager()->setCache(network_cache);

    onglet->page()->networkAccessManager()->setCookieJar(new MyCookieJar(this));

    //onglet->load(QUrl(url));
    onglet->load(*requete);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(onglet,1);
    layout->addWidget(progression);
    progression->setFixedHeight(15);
    fenetre->setLayout(layout);

    conteneur->setCurrentIndex(conteneur->addTab(fenetre,"Nouvel Page"));
    if(conteneur->count()>1)
	conteneur->setTabsClosable(true);

    connect(onglet->page(),SIGNAL(printRequested(QWebFrame*)),this,SLOT(imprimer())); //en cas de clic sur bouton imprimer dans une page
    connect(onglet,SIGNAL(titleChanged(QString)),this,SLOT(changertitre(QString)));
    connect(onglet,SIGNAL(iconChanged()),this,SLOT(changericone()));
    connect(onglet,SIGNAL(urlChanged(QUrl)),this,SLOT(changerurl(QUrl)));
    connect(onglet,SIGNAL(loadProgress(int)),progression,SLOT(setValue(int)));
    connect(onglet,SIGNAL(loadFinished(bool)),this,SLOT(showprogression(bool)));
    connect(onglet,SIGNAL(loadStarted()),this,SLOT(showprogression()));
}

void Interface::fermertab(int index)
{
    if(conteneur->count()==1)
	return;
    if(index==-1)
	index=conteneur->currentIndex();
    delete conteneur->widget(index)->findChild<QWidget *>(); //on vire de la mémoire...
    conteneur->removeTab(index); // et on vire de l'affichage
    changertitre(pagecourante()->title());
    changerurl(pagecourante()->url());
    if(conteneur->count()==1)
	conteneur->setTabsClosable(false);
}

void Interface::accueil(void)
{
    requete->setUrl(QUrl(opt_accueil));
    pagecourante()->load(*requete);
}

void Interface::aller(QString url)
{
    if(!url.isEmpty()) //si on accède à partir d'une autre source (favoris...) que le bouton go!
    {
	requete->setUrl(QUrl(url));
    }
    else //sinon on a cliké sur le bouton go !
    {
	//si l'adresse n'est pas du type connu http ou https, on fait une recherche rapide
	if(adresse->text().left(7) != "http://" && adresse->text().left(8) != "https://")
	{
	    switch(search_engine->currentIndex())
	    {
		case (0): //google
		    adresse->setText("http://www.google.com/search?q=" + adresse->text());
		    break;
		case (1): //j'ai de la chance
		    adresse->setText("http://www.google.com/search?q=" + adresse->text() + "&btnI=745");
		    break;
		case (2): //wikipedia
		    adresse->setText("http://fr.wikipedia.org/wiki/" + adresse->text());
		    break;
		case (3): //bing
		    adresse->setText("http://www.bing.com/search?q=" + adresse->text());
		    break;
		case (4): //yahoo
		    adresse->setText("http://fr.search.yahoo.com/search?p=" + adresse->text());
		    break;
	    }
	}
	requete->setUrl(QUrl(adresse->text()));
    }
    //pagecourante()->load(QUrl(adresse->text()));
    pagecourante()->load(*requete);
}

void Interface::changertitre(QString titre)
{
    if(titre.isEmpty())
        titre = "(sans titre)";
    setWindowTitle(titre + "  -  EskiNet");
    conteneur->setTabToolTip(conteneur->currentIndex(),titre);
    if(titre.length()>12) //on met des "..." si le titre dépasse 12 caractères...
        titre = titre.left(12) + "...";
    conteneur->setTabText(conteneur->currentIndex(),titre.leftJustified(15)); //on a toujours la même largeur
    actu_history();
}

void Interface::changerurl(QUrl url)
{
    adresse->setText(url.toString());
    adresse->setCursorPosition(0);
    action_highlight->setChecked(false); //on surligne plus
}

void Interface::changericone(void)
{
    //appel pour le changement de l'icone, un second appel est fait pour être sur que la favicon est chargé
    //(en cas du bug du "premier chargement...)
    QIcon monicone = QWebSettings::iconForUrl(pagecourante()->url());
    if(!monicone.isNull())
	conteneur->setTabIcon(conteneur->currentIndex(),monicone);
    else //au cas ou l'icone est nulle, on met celle du programme...
	conteneur->setTabIcon(conteneur->currentIndex(),QIcon(":/icones/empty"));
}

void Interface::changementtab(void)
{
    changertitre(pagecourante()->title());
    changerurl(pagecourante()->url());
}

void Interface::showprogression(bool etat)
{
    conteneur->currentWidget()->findChild<QProgressBar *>()->setHidden(etat);
    if(etat)
    {
	actu_history(pagecourante()->title());
	//QWebSettings::iconForUrl(QUrl(pageWeb->url()));
	QIcon monicone = QWebSettings::iconForUrl(pagecourante()->url());
	if(!monicone.isNull())
	    conteneur->setTabIcon(conteneur->currentIndex(),monicone);
	else
	    conteneur->setTabIcon(conteneur->currentIndex(),QIcon(":/icones/empty"));
	historique->add(pagecourante()->history()->currentItem());
    }
}

void Interface::showproxy(bool etat)
{
    if(etat)
    {
	barre_proxy->show();
	btn_activer->setFocus();
    }
    else
    {
	barre_proxy->hide();
	action_proxy->setChecked(false);
    }
}

void Interface::shownavigation(bool etat)
{
    if(etat)
    {
	barre_navig->show();
	adresse->setFocus();
    }
    else
    {
	barre_navig->hide();
	action_navigation->setChecked(false);
    }
}

void Interface::showrechercher(bool etat)
{
    if(etat)
    {
	barre_search->show();
	line_search->setFocus();
	line_search->selectAll();;
    }
    else
    {
	barre_search->hide();
	action_search->setChecked(false);
    }
}

void Interface::rechercher(void)
{
    barre_search->setVisible(true);
    line_search->setFocus();

    *search_options = QWebPage::FindWrapsAroundDocument;

    if(action_highlight->isChecked())
	*search_options |= QWebPage::HighlightAllOccurrences;
    if(btn_casse->isChecked())
	*search_options |= QWebPage::FindCaseSensitively;

    if(!(line_search->text().isEmpty()))
    {
	if(!pagecourante()->findText(line_search->text(),*search_options))
	    line_search->setStyleSheet("QLineEdit { background: #FF6666}"); //pas de résultat trouvé
	else
	    line_search->setStyleSheet("QLineEdit { background: white}"); //au moins un résulat
    }
}

void Interface::rechercher_rev(void)
{
    line_search->setFocus();

    *search_options = QWebPage::FindWrapsAroundDocument;
    *search_options |= QWebPage::FindBackward;

    if(action_highlight->isChecked())
	*search_options |= QWebPage::HighlightAllOccurrences;
    if(btn_casse->isChecked())
	*search_options |= QWebPage::FindCaseSensitively;

    if(!(line_search->text().isEmpty()))
    {
	if(!pagecourante()->findText(line_search->text(),*search_options))
	    line_search->setStyleSheet("QLineEdit { background: #FF6666}"); //pas de résultat trouvé
	else
	    line_search->setStyleSheet("QLineEdit { background: white}"); //au moins un résulat
    }
}

void Interface::surligner(bool etat)
{
    *search_options = QWebPage::HighlightAllOccurrences;
    if(btn_casse->isChecked())
	*search_options |= QWebPage::FindCaseSensitively;
    if(!(line_search->text().isEmpty()))
    {
	if(etat)
	    pagecourante()->findText(line_search->text(),*search_options);
	else
	    pagecourante()->findText("",*search_options);
    }
    line_search->setFocus();
}

void Interface::imprimer(void)
{
    QPrinter *imprimante;
    imprimante = new QPrinter;

    QPrintDialog print(imprimante, this);

    if(print.exec() == QDialog::Accepted)
	pagecourante()->print(imprimante);
}

void Interface::actu_history(QString texte)
{
    histo->clear();
    QList<QWebHistoryItem> titre = pagecourante()->history()->backItems(MAX_ITEM);
    if(!titre.isEmpty())
    {
	//QMessageBox::information(this,"",QString::number(titre.count()));
	for(int i=0; i<titre.count(); i++)
	    histo->insertItem(0,titre.at(i).title());
    }
    if(!texte.isEmpty())
	histo->insertItem(0,texte);
    histo->setItemIcon(0,QIcon(QCoreApplication::applicationDirPath() + "/themes/" + opt_theme + "/histo_pos.png"));
    histo->setCurrentIndex(0);

    titre = pagecourante()->history()->forwardItems(MAX_ITEM);
    if(!titre.isEmpty())
    {
	//QMessageBox::information(this,"",QString::number(titre.count()));
	for(int i=0; i<titre.count(); i++)
	    histo->insertItem(0,titre.at(i).title());
	*histo_pos=titre.count();
    }
    else
	*histo_pos=0;
}

void Interface::select_histo(int nb)
{
    if(nb!=*histo_pos)
    {
	if(nb>*histo_pos)
	    for(int i=0; i<nb-*histo_pos; i++)
		pagecourante()->back();
	else
	    for(int i=0; i<*histo_pos-nb; i++)
		pagecourante()->forward();
    }
}

void Interface::nouvelle_fenetre(void)
{
    Interface *essai;
    essai = new Interface;
    essai->show();
}

void Interface::ouvrir(void)
{
    QString fichier_name(QFileDialog::getOpenFileName(this,"Ouvrir le fichier à traiter","/home","Images (*.png *.jpeg *.jpg *.gif *.ico *.bmp);;textes (*.txt *.text);;XML (*.xml);;HTML (*.html *.htm *.shtml *.xhtml"));
    if(!fichier_name.isEmpty())
	ajouttab(fichier_name);
}

void Interface::pleinecran(bool etat)
{
    if(etat)
	this->showFullScreen();
    else
	this->showNormal();
}

void Interface::sauver(void)
{
    QString file(QFileDialog::getSaveFileName(this,"Sauver sous...", "/home", "Fichiers HTML (*.html)"));
    if(file.isEmpty())
	return;
    QFile cible(file);
    if(cible.open(QIODevice::WriteOnly | QIODevice::Text))
    {
	QTextStream out(&cible);
	out << pagecourante()->page()->mainFrame()->toHtml();
    }
    else
	QMessageBox::critical(this,"Erreur","Erreur lors de l'écriture du fichier");
}

void Interface::options_ecrire(void)
{
    QSettings options("configuration.ini", QSettings::IniFormat);
    options.setValue("search_engine", search_engine->currentIndex());
    options.setValue("Geometry/geometry", this->geometry());
    options.setValue("Geometry/maximized", this->isMaximized());
}

void Interface::options_lire(void)
{
    QSettings options("configuration.ini", QSettings::IniFormat);
    opt_theme = options.value("theme","Default").toString();
    opt_search_engine = options.value("search_engine",0).toInt();
    opt_geometry = options.value("Geometry/geometry", QRect::QRect(0,0,800,600)).toRect();
    opt_maximized = options.value("Geometry/maximized",false).toBool();
    opt_mem = options.value("Tabs/mem",false).toBool();
    opt_accueil = options.value("accueil","http://www.google.fr").toString();
    opt_javascript = options.value("javascript",true).toBool();
    opt_java = options.value("java",true).toBool();
    opt_images = options.value("images",true).toBool();
    opt_plugins = options.value("plugins",true).toBool();
    if(opt_mem)
    {
	opt_mem_url.clear();
	opt_mem_name.clear();
	opt_mem_url = options.value("Tabs/Memoire/url","http://www.google.fr").toStringList();
	opt_mem_name = options.value("Tabs/Memoire/titre","(sans titre)").toStringList();
    }
    options.remove("Tabs/Memoire");
}

void Interface::liens_ecrire(void)
{
    QSettings options("configuration.ini", QSettings::IniFormat);
    opt_mem_url.clear();
    opt_mem_name.clear();

    options.setValue("Tabs/mem",true);
    //options.setValue("Tabs/Memoire/nb",conteneur->count());
    for(int i=0; i < conteneur->count(); i++)
    {
	conteneur->setCurrentIndex(i);
	opt_mem_url << pagecourante()->url().toString();
	opt_mem_name << pagecourante()->title();
    }
    options.setValue("Tabs/Memoire/url", opt_mem_url);
    options.setValue("Tabs/Memoire/titre", opt_mem_name);
}

void Interface::closeEvent(QCloseEvent *event)
{
/*
    int reponse = QMessageBox::No;

    if(!opt_mem)
	reponse = QMessageBox::question(this, "Rappel", "Voulez-vous que le programme se souviennent des onglets en cours ?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

    if(reponse == QMessageBox::Cancel)
    {
	event->ignore();
	return;
    }
    if(reponse == QMessageBox::Yes || opt_mem)
	liens_ecrire();
*/
    if(opt_mem)
	liens_ecrire();
    options_ecrire();
    event->accept();
}

void Interface::preference(void)
{
    Preference *options;
    options = new Preference(this);
    options->exec();
}

void Interface::afficher_source(void)
{
    QString code = pagecourante()->page()->currentFrame()->toHtml();
    QsciScintilla *qscintilla = new QsciScintilla(this); // création de la zone de texte
    QsciLexerHTML *lexerHTML = new QsciLexerHTML(this);

    qscintilla->setUtf8(true);
    qscintilla->setLexer(lexerHTML);
    qscintilla->setText(code);
    qscintilla->showMaximized();
}

void Interface::activerproxy(bool etat)
{
    QNetworkProxy proxy;
    QStringList content = combo_proxy->itemData(combo_proxy->currentIndex()).toStringList();
    if(content.at(1)=="" || content.at(2)=="")
    {
	QMessageBox::critical(this,"Erreur","Erreur un des champs est vide");
	return;
    }
    if(etat) //si le proxy doit être activé
    {
	if(content.at(3) == "HTTP")
	    proxy.setType(QNetworkProxy::HttpProxy);
	else if(content.at(3) == "Caching HTTP")
	    proxy.setType(QNetworkProxy::HttpCachingProxy);
	else if(content.at(3) == "Caching FTP")
	    proxy.setType(QNetworkProxy::FtpCachingProxy);
	else
	    proxy.setType(QNetworkProxy::Socks5Proxy);

	proxy.setHostName(content.at(1)); //"Host" du proxy
	proxy.setPort(content.at(2).toInt()); //Port du proxy
	proxy.setUser(content.at(4)); //Pseudo (facultatif)
	proxy.setPassword(content.at(5)); //mot de passe (Facultatif)
    }
    else //si le proxy est désactivé
    {
	proxy.setType(QNetworkProxy::NoProxy);
    }
    QNetworkProxy::setApplicationProxy(proxy);
    //pagecourante()->page()->networkAccessManager()->setProxy(proxy);
}

void Interface::editerproxy(void)
{
    Preference * reglage;
    reglage = new Preference(this,2);
    reglage->exec();
}

void Interface::inventaire_proxy(void)
{
    QSettings options("proxy.ini", QSettings::IniFormat);

    QStringList chaine;
    QStringList cles;

    combo_proxy->clear();
    cles = options.allKeys();
    if(!cles.isEmpty())
    {
	for(int i=0; i<cles.count(); i++)
	{
	    chaine = options.value(cles.at(i),"").toStringList();
	    combo_proxy->addItem(chaine.at(0),chaine);
	}
	selectproxy(0);
    }
}

void Interface::selectproxy(int pos)
{
    if(pos != -1)
    {
	QStringList content = combo_proxy->itemData(pos).toStringList();
	champ_ip->setText(content.at(1));
	champ_port->setText(content.at(2));
	champ_type->setText(content.at(3));
	champ_pseudo->setText(content.at(4));
	//champ_pass->setText(content.at(5));
    }
}

void Interface::setListeProxy(QComboBox *proxy)
{
    combo_proxy->clear();
    for(int i=0; i<proxy->count(); i++)
    {
	champ_ip->clear();
	champ_port->clear();
	champ_type->clear();
	champ_pseudo->clear();
	combo_proxy->addItem(proxy->itemText(i),proxy->itemData(i));
	selectproxy(combo_proxy->count());
    }
}

void Interface::ajoutfavoris(void)
{
    TFavoris fav;

    fav.nom = pagecourante()->title();
    fav.url = pagecourante()->url().toString();
    fav.path = "";
    fav.favicon = QWebSettings::iconForUrl(pagecourante()->url());

    if(favoris->add(&fav)) //si l'enregistrement se passe bien
    {
	if(fav.path == "barre de favoris")
	{
	    QSignalMapper * signalMapper = new QSignalMapper(this);

	    //QAction *button = new QAction(fav.nom,barre_favoris);
	    QAction *button = new QAction(fav.favicon,fav.nom,this);
	    connect(button, SIGNAL(triggered()),signalMapper,SLOT(map()));
	    signalMapper->setMapping(button, fav.url);
	    barre_favoris->addAction(button);

	    connect(signalMapper,SIGNAL(mapped(QString)),this,SLOT(aller(QString)));
	}
    }
}
