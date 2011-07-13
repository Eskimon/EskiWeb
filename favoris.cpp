#include "favoris.h"

Favoris::Favoris(QWidget *parent) : QWidget(parent)
{
    db_fav = QSqlDatabase::addDatabase("QSQLITE","db_fav");
    db_fav.setHostName("localhost");

    if(!QFile::exists(qApp->applicationDirPath() + "/favoris.sqlite")) //si jamais la base n'existe pas, on la crée
	creer();
    db_fav.setDatabaseName(qApp->applicationDirPath() + "/favoris.sqlite");
    //db_fav.setUserName("");
    //db_fav.setPassword("");

    if(!db_fav.open())
	QMessageBox::critical(this,"","connection echoué " + db_fav.lastError().text());

    //qDebug() << db_fav.tables();
}

Favoris::~Favoris(void)
{
    db_fav.close();
}

bool Favoris::add(TFavoris * fav)
{
    QSqlQuery requete(db_fav);

    QDialog fenetre(this);
    QComboBox liste_dossiers;
    QLineEdit champ_nom(fav->nom);
    QDialogButtonBox btn(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal);
    QFormLayout layout;
    QStringList dossiers;

    liste_dossiers.setEditable(true);

    layout.addRow("nom du favoris :",&champ_nom);
    layout.addRow("Dossier :",&liste_dossiers);
    layout.addRow(&btn);
    fenetre.setLayout(&layout);

    connect(&btn,SIGNAL(accepted()),&fenetre,SLOT(accept()));
    connect(&btn,SIGNAL(rejected()),&fenetre,SLOT(close()));

    //on remplit la liste des dossiers
    if(requete.exec("Select nom_dossier from dossiers"))
    {
	while(requete.next())
	    dossiers << requete.value(0).toString();
    }
    else
	QMessageBox::critical(this,"Erreur","Problème survenu lors de la lecture des dossiers : " + requete.lastError().text());

    liste_dossiers.addItems(dossiers);

    if(fenetre.exec()) //si on click sur Save
    {
	QByteArray bytes;
	QBuffer buffer(&bytes);
	buffer.open(QIODevice::WriteOnly);
	QPixmap pix = fav->favicon.pixmap(16,16);
	pix.save(&buffer,"png");

	requete.prepare("INSERT INTO adresses (url,nom_favoris,dossier,favicon) VALUES (:url,:nom,:dossier,:favicon);");
	requete.bindValue(":url",fav->url,QSql::In);
	requete.bindValue(":nom",champ_nom.text(),QSql::In);
	requete.bindValue(":dossier",liste_dossiers.currentText(),QSql::In);
	requete.bindValue(":favicon",buffer.data(),QSql::In | QSql::Binary);

	buffer.close();

	if(dossiers.contains(liste_dossiers.currentText())) //si le dossier existe déjà
	{
	    if(!requete.exec())
	    {
		QMessageBox::critical(this,"Erreur","Problème survenu lors de l'enregistrement' : " + requete.lastError().text());
		return false;
	    }
	}
	else //sinon on doit l'ajouter dans la base de données...
	{
	    //if(!requete.exec("INSERT INTO adresses (url,nom_favoris,dossier,favicon) VALUES ('"+fav->url+"','"+champ_nom.text()+"','"+liste_dossiers.currentText()+"','"+QVariant(fav->favicon).toByteArray()+"');"))
	    if(!requete.exec())
	    {
		QMessageBox::critical(this,"Erreur","Problème survenu lors de l'enregistrement (adresse) : " + requete.lastError().text());
		return false;
	    }
	    if(!requete.exec("INSERT INTO dossiers (nom_dossier,parent) VALUES ('"+liste_dossiers.currentText()+"','favoris');"))
	    {
		QMessageBox::critical(this,"Erreur","Problème survenu lors de l'enregistrement (dossier) : " + requete.lastError().text());
		return false;
	    }
	}

    }
    else
	return false; //si l'enregistrement à merdé...

    fav->nom = champ_nom.text(); //nom sous lequel le lien à été enregitsré
    fav->path = liste_dossiers.currentText(); //nom du dossier dans lequel l'ajout à été fait...
    return true; //si l'enregistrement s'est bien passé
}

void Favoris::get_barre(QList<TFavoris> * fav)
{
    QSqlQuery requete(db_fav);

    if(requete.exec("Select * from adresses where dossier='barre de favoris';"))
    {
	int nom = requete.record().indexOf("nom_favoris");
	int url = requete.record().indexOf("url");
	int path = requete.record().indexOf("dossier");
	int favicon = requete.record().indexOf("favicon");

	TFavoris temp;
	QPixmap * pix = NULL; //pointeur sur un pixmap

	while(requete.next())
	{
	    pix = new QPixmap; //on le crée et le détruit à chaque passage... c'est moche mais ca marche :s
	    //qDebug() << nom << url << path << favicon;
	    temp.url = requete.value(url).toString();
	    temp.nom = requete.value(nom).toString();
	    temp.path = requete.value(path).toString();
	    pix->loadFromData(requete.value(favicon).toByteArray(),"png");
	    temp.favicon = QIcon(*pix);
	    fav->append(temp);
	}
	delete pix; //destruction du pixmap... (c'est moche mais ca marche...)
    }
    else
    {
	QMessageBox::critical(this,"Erreur","Problème de lecture des données :" + requete.lastError().text());
    }
}

void Favoris::creer(void)
{
    db_fav.setDatabaseName(qApp->applicationDirPath() + "/favoris.sqlite");
    if(!db_fav.open())
    {
	QMessageBox::critical(this,"","connection aux favoris echoué " + db_fav.lastError().text());
	return;
    }

    QSqlQuery requete(db_fav);
    //création de la table "dossiers"
    if(!requete.exec("Create Table dossiers (nom_dossier text, parent text, primary key(nom_dossier,parent));"))
	QMessageBox::information(this,"Erreur","Erreur lors de l'accès à la base de donnée" + requete.lastError().text());

    //création de la table "adresses"
    if(!requete.exec("Create Table adresses (id integer, url text, nom_favoris text, dossier text, favicon blob, primary key(id), foreign key(dossier) references dossiers(nom_dossier));"))
	QMessageBox::information(this,"Erreur","Erreur lors de l'accès à la base de donnée" + requete.lastError().text());

    //ajout du dossier racine "favoris"
    if(!requete.exec("Insert Into dossiers (nom_dossier) values ('favoris');"))
	QMessageBox::information(this,"Erreur","Erreur lors de l'accès à la base de donnée" + requete.lastError().text());

    //ajout du dossier "barre de favoris"
    if(!requete.exec("Insert Into dossiers (nom_dossier,parent) values ('barre de favoris','favoris');"))
	QMessageBox::information(this,"Erreur","Erreur lors de l'accès à la base de donnée" + requete.lastError().text());
}

void Favoris::afficher(void)
{
    QSqlQuery requete(db_fav);

    QDialog fenetre(this,Qt::Window);
    QGridLayout layout;
    QTreeWidget arbre;

    layout.addWidget(&arbre,0,0);

    fenetre.setLayout(&layout);

    fenetre.exec();
}
