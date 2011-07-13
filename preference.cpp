#include "preference.h"

Preference::Preference(QWidget *parent, int panneau) : QDialog(parent)
{
    lire_options(); //on commence par lire les options

    global = new QGridLayout(this);
    boite = new QTabWidget(this);
    fake = new QWebView(this);
    fake->setVisible(false);
    btn_save = new QPushButton("Sauvergarder !",this);
    btn_cancel = new QPushButton("Annuler",this);
    connect(btn_save,SIGNAL(clicked()),this,SLOT(enregistrement()));
    connect(btn_cancel,SIGNAL(clicked()),this,SLOT(close()));

//création du premier onglet, onglet "général"
    {
	widg_general = new QWidget(this);
	lay_general = new QVBoxLayout(this);

	theme = new QGroupBox("Gestion des themes",this);
	lay_theme = new QVBoxLayout(this);
	lbl_theme = new QLabel("Choix du theme :",this);
	list_theme = new QListWidget(this);
	lbl_legende = new QLabel(this);
	lbl_legende->setText("<table><tr><td><font color='blue'>Bleu:</font></td><td><font color='blue'>Theme en cours</font></td></tr><tr><td><font color='green'>Vert:</font></td><td><font color='green'>Theme complet</font></td></tr><tr><td><font color='red'>Rouge:</font></td><td><font color='red'>Theme incomplet (icones manquantes)</font></td></tr></table>");
	lbl_legende->setFrameShape(QFrame::Box);
	lay_theme->addWidget(lbl_theme);
	lay_theme->addWidget(list_theme);
	lay_theme->addWidget(lbl_legende);
	theme->setLayout(lay_theme);
	lister_theme();
	connect(list_theme,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(theme_change(QListWidgetItem*)));

	demarrage = new QGroupBox("Démarrage",this);
	lay_demarrage = new QVBoxLayout(this);
	radio_pasmemoire = new QRadioButton("Charger la page d'accueil",this);
	radio_memoire = new QRadioButton("Charger les onglets fermés précédemments",this);
	lbl_accueil = new QLabel("Page d'accueil :",this);
	champ_accueil = new QLineEdit("http://www.google.fr/",this);
	lay_demarrage->addWidget(radio_memoire);
	lay_demarrage->addWidget(radio_pasmemoire);
	lay_demarrage->addWidget(lbl_accueil);
	lay_demarrage->addWidget(champ_accueil);
	demarrage->setLayout(lay_demarrage);
	radio_memoire->setChecked(opt_mem);
	radio_pasmemoire->setChecked(!opt_mem);
	champ_accueil->setText(opt_accueil);

	lay_general->addWidget(demarrage);
	lay_general->addWidget(theme);
	widg_general->setLayout(lay_general);
    }
//création du deuxième onglet, onglet "contenu"
    {
	widg_content = new QWidget(this);
	lay_content = new QVBoxLayout(this);
	contenu = new QGroupBox("Gestion des contenus",this);
	lay_contenu = new QVBoxLayout(this);
	check_javascript = new QCheckBox("Autoriser le JavaScript",this);
	check_java = new QCheckBox("Autoriser le Java",this);
	check_images = new QCheckBox("Autoriser l'affichage des images (supprimer pour navigation plus rapide)",this);
	check_plugins = new QCheckBox("Autoriser l'execution des plug-ins (Flash...)",this);
	lay_contenu->addWidget(check_javascript);
	lay_contenu->addWidget(check_java);
	lay_contenu->addWidget(check_images);
	lay_contenu->addWidget(check_plugins);
	contenu->setLayout(lay_contenu);
	check_javascript->setChecked(opt_javascript);
	check_java->setChecked(opt_java);
	check_images->setChecked(opt_images);
	check_plugins->setChecked(opt_plugins);
	lay_content->addWidget(contenu);
	lay_content->addStretch();
	widg_content->setLayout(lay_content);
    }
//création du troisième onglet, onglet "proxy"
    {
	widg_proxy = new QWidget(this);
	lay_proxy = new QVBoxLayout(this);
	proxy = new QGroupBox("Gestion des Proxys",this);
	lay_proxy_box = new QGridLayout(this);
	combo_proxy = new QComboBox(this);
	lbl_nom = new QLabel(" Nom symbolique :",this);
	nom_proxy = new QLineEdit(this);
	lbl_type = new QLabel(" Type de proxy :",this);
	type_proxy = new QComboBox(this);
	lbl_ip = new QLabel(" ip/adresse :",this);
	champ_ip = new QLineEdit(this);
	lbl_port = new QLabel(" port :",this);
	champ_port = new QLineEdit(this);
	lbl_pseudo = new QLabel("    id :",this);
	champ_pseudo = new QLineEdit(this);
	lbl_pass = new QLabel(" mdp :",this);
	champ_pass = new QLineEdit(this);
	btn_sauver = new QPushButton("Sauver",this);
	btn_suppr = new QPushButton("Supprimer",this);

	champ_port->setMaxLength(5);
	champ_pass->setEchoMode(QLineEdit::Password);
	type_proxy->addItem("SOCKS 5");
	type_proxy->addItem("HTTP");
	type_proxy->addItem("Caching HTTP");
	type_proxy->addItem("Caching FTP");

	lay_proxy_box->addWidget(combo_proxy,0,0);
	//lay_proxy_box->setRowStretch(1,10); //pour faire un peu d'espace...
	lay_proxy_box->addWidget(lbl_nom,2,0);
	lay_proxy_box->addWidget(nom_proxy,3,0);
	lay_proxy_box->addWidget(lbl_type,2,1);
	lay_proxy_box->addWidget(type_proxy,3,1);
	lay_proxy_box->addWidget(lbl_ip,4,0);
	lay_proxy_box->addWidget(champ_ip,5,0);
	lay_proxy_box->addWidget(lbl_port,4,1);
	lay_proxy_box->addWidget(champ_port,5,1);
	lay_proxy_box->addWidget(lbl_pseudo,6,0);
	lay_proxy_box->addWidget(champ_pseudo,7,0);
	lay_proxy_box->addWidget(lbl_pass,6,1);
	lay_proxy_box->addWidget(champ_pass,7,1);
	lay_proxy_box->addWidget(btn_suppr,8,0);
	lay_proxy_box->addWidget(btn_sauver,8,1);

	proxy->setLayout(lay_proxy_box);
	lay_proxy->addWidget(proxy);
	lay_proxy->addStretch();
	widg_proxy->setLayout(lay_proxy);
	champ_port->setInputMask("99999");

	ouvrirproxy();

	connect(btn_sauver,SIGNAL(clicked()),this,SLOT(ajoutproxy()));
	connect(btn_suppr,SIGNAL(clicked()),this,SLOT(supprproxy()));
	connect(combo_proxy,SIGNAL(currentIndexChanged(int)),this,SLOT(selectproxy(int)));
    }

    boite->addTab(widg_general,"General");
    boite->addTab(widg_content,"Contenus");
    boite->addTab(widg_proxy,"Proxy");

    boite->setCurrentIndex(panneau);
    global->addWidget(boite,0,0,1,2);
    global->addWidget(btn_cancel,1,0);
    global->addWidget(btn_save,1,1);
    this->setLayout(global);
}

void Preference::lire_options(void)
{
    QSettings options("configuration.ini", QSettings::IniFormat);

    opt_theme = options.value("theme","Default").toString(); //on recupere le theme actuel
    opt_mem = options.value("Tabs/mem",false).toBool();
    opt_accueil = options.value("accueil","http://www.google.fr").toString();
    opt_javascript = options.value("javascript",true).toBool();
    opt_java = options.value("java",true).toBool();
    opt_images = options.value("images",true).toBool();
    opt_plugins = options.value("plugins",true).toBool();
}

void Preference::lister_theme(void)
{
    QDir chemin(QCoreApplication::applicationDirPath() + "/themes");
    QStringList list = chemin.entryList(QDir::AllDirs);
    list.removeFirst();
    list.removeFirst();
    list_theme->addItems(list);

    for(int i=0; i<list_theme->count(); i++)
    {
	if(!tester_icones(list_theme->item(i)->text())) //si une icone est manquante -> rouge
	    list_theme->item(i)->setForeground(Qt::red);
	else
	    list_theme->item(i)->setForeground(Qt::green);
	if(list_theme->item(i)->text() == opt_theme) //si le dossier correspond à celui du theme actuel -> bleu
	    list_theme->item(i)->setForeground(Qt::blue);
    }
}

bool Preference::tester_icones(QString path)
{
    QDir chemin(QCoreApplication::applicationDirPath() + "/themes/" + path);
    QStringList reference; //liste de référence des éléments nécessaires
    reference << "go.png" << "histo_pos.png" << "search_highlight.png" << "home.png" << "next.png" << "previous.png" << "refresh.png" << "search_close.png" << "search_next.png" << "search_previous.png" << "stop.png" << "add.png";
    reference.sort(); //on trie pour la comparaison
    QStringList list = chemin.entryList((QStringList() << "*.png"),QDir::Files);
    list.sort(); //on trie pour la comparaison
    //on test si la list à testé contient bien tous les éléments nécessaires
    for(int i=0; i<reference.count(); i++)
	if(!list.contains(reference.at(i)))
	    return false;
    return true;
}

void Preference::enregistrement(void)
{
    QSettings options("configuration.ini", QSettings::IniFormat);
    Interface * navigateur = (Interface *) this->parentWidget()->window();

    options.setValue("theme",opt_theme); //on enregistre le theme selectionné
    options.setValue("Tabs/mem",radio_memoire->isChecked()); //on enregistre la sauvegarde ou non des onglets
    options.setValue("accueil",champ_accueil->text());
    options.setValue("javascript",check_javascript->isChecked());
    options.setValue("java",check_java->isChecked());
    options.setValue("images",check_images->isChecked());
    options.setValue("plugins",check_plugins->isChecked());

    QWebSettings::globalSettings()->setAttribute(QWebSettings::JavaEnabled,check_java->isChecked());
    QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled,check_plugins->isChecked());
    QWebSettings::globalSettings()->setAttribute(QWebSettings::JavascriptEnabled,check_javascript->isChecked());
    QWebSettings::globalSettings()->setAttribute(QWebSettings::AutoLoadImages,check_images->isChecked());

    navigateur->setOptionMemory(radio_memoire->isChecked());
    navigateur->setOptionAccueil(champ_accueil->text());
    this->close();
}

void Preference::theme_change(QListWidgetItem * index)
{
    QList<QListWidgetItem *> temp = list_theme->findItems(opt_theme,Qt::MatchCaseSensitive);
    if(!tester_icones(temp.at(0)->text())) //si une icone est manquante -> rouge
	temp.at(0)->setForeground(Qt::red);
    else
	temp.at(0)->setForeground(Qt::green);
    opt_theme = index->text();
    index->setForeground(Qt::blue); //on colorie en bleu le theme qui remplace l'ancien
    QMessageBox::information(this,"Changement theme","Attention, le changement de theme ne prendra effet qu'au prochain démarrage de l'application...");
}

void Preference::ouvrirproxy(void)
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

void Preference::ajoutproxy(void)
{
    if(combo_proxy->findText(nom_proxy->text()) != -1) //si le nom existe déjà
    {
	QMessageBox::critical(this,"Attention !","Ce nom est déjà utilisé");
	return;
    }

    if(nom_proxy->text().isEmpty() || champ_port->text().isEmpty())
    {
	QMessageBox::critical(this,"Attention","Le champ adresse ou port est vide !");
	return;
    }

    QSettings options("proxy.ini", QSettings::IniFormat);
    QStringList proxy;
    proxy << nom_proxy->text() << champ_ip->text() << champ_port->text() << type_proxy->currentText() << champ_pseudo->text() << champ_pass->text();
    options.setValue("ProxyList/"+proxy.at(0),proxy);
    combo_proxy->addItem(proxy.at(0),proxy);
    combo_proxy->setCurrentIndex(combo_proxy->findText(nom_proxy->text()));

    Interface * navigateur = (Interface *) this->parentWidget()->window(); //on modifie la liste déroulante du prog principale
    navigateur->setListeProxy(combo_proxy);
}

void Preference::supprproxy(void)
{
    if(combo_proxy->count()) //on s'assure qu'on essai pas de vider une liste vide
    {
	QSettings options("proxy.ini", QSettings::IniFormat); //on enregistre dans le fichier proxy
	nom_proxy->clear();
	champ_ip->clear();
	champ_port->clear();
	type_proxy->setCurrentIndex(0);
	champ_pseudo->clear();
	champ_pass->clear();
	combo_proxy->removeItem(combo_proxy->currentIndex());
	options.remove("ProxyList/"+combo_proxy->currentText());

	Interface * navigateur = (Interface *) this->parentWidget()->window(); //on modifie la liste déroulante du prog principale
	navigateur->setListeProxy(combo_proxy);
    }
}

void Preference::selectproxy(int pos)
{
    if(pos != -1)
    {
	QStringList content = combo_proxy->itemData(pos).toStringList();
	nom_proxy->setText(content.at(0));
	champ_ip->setText(content.at(1));
	champ_port->setText(content.at(2));
	type_proxy->setCurrentIndex(type_proxy->findText(content.at(3)));
	champ_pseudo->setText(content.at(4));
	champ_pass->setText(content.at(5));
    }
}
