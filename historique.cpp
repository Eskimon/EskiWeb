#include "historique.h"

Historique::Historique(QWidget *parent) : QWidget(parent)
{
    db_histo = QSqlDatabase::addDatabase("QSQLITE","db_histo");
    db_histo.setHostName("localhost");

    if(!QFile::exists(qApp->applicationDirPath() + "/historique.sqlite")) //si jamais la base n'existe pas, on la crée
	creer();
    db_histo.setDatabaseName(qApp->applicationDirPath() + "/historique.sqlite");
    //db_histo.setUserName("");
    //db_histo.setPassword("");

    if(!db_histo.open())
	QMessageBox::critical(this,"","connection echoué " + db_histo.lastError().text());

    //qDebug() << db_histo.tables();
}

Historique::~Historique(void)
{
    db_histo.close();
}

void Historique::creer(void)
{
    db_histo.setDatabaseName(qApp->applicationDirPath() + "/historique.sqlite");
    if(!db_histo.open())
    {
	QMessageBox::critical(this,"","connection à l'historique echoué " + db_histo.lastError().text());
	return;
    }

    QSqlQuery requete(db_histo);
    //création de la table "histo"
    if(!requete.exec("Create Table histo (id integer, nom text, favicon blob, url text, date blob, primary key(id));"))
	QMessageBox::information(this,"Erreur","Erreur lors de l'accès à la base de donnée" + requete.lastError().text());
}

void Historique::add(QWebHistoryItem item)
{
    QSqlQuery requete(db_histo);
    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);
    QPixmap pix;
    QIcon icone(":/icones/empty");

    if(!item.icon().isNull())
    {
	icone = item.icon();
	qDebug() << "icone";
    }
    else
	qDebug() << "pas icone";

    icone = icone.pixmap(16,16);
    pix.save(&buffer,"png");

    //on test voir si ce lien n'a pas déja été consulté aujourd'hui...
    requete.prepare("Select url from histo where url=:adresse and date=:date;");
    requete.bindValue(":adresse",item.url(), QSql::In);
    requete.bindValue(":date",QDate::currentDate().toString(Qt::ISODate),QSql::In);
    if(!requete.exec())
    {
	QMessageBox::information(this,"Erreur","Problème lors de la recherche d'antécédent dans l'historique !" + requete.lastError().text());
	return;
    }

    requete.first();
    if(requete.isValid()) //si on a un résultat, lien consulté, on sort...
	return;

    //sinon on ajoute...
    requete.prepare("Insert Into histo (nom,favicon,url,date) Values (:nom,:favicon,:url,:date);");
    requete.bindValue(":nom",item.title(),QSql::In);
    requete.bindValue(":favicon",buffer.data(),QSql::In | QSql::Binary);
    requete.bindValue(":url",item.url(),QSql::In);
    requete.bindValue(":date",QDate::currentDate().toString(Qt::ISODate),QSql::In);

    if(!requete.exec())
	QMessageBox::information(this,"Erreur","Problème lors de l'enregistrement de la page dans l'historique !" + requete.lastError().text());
}

void Historique::afficher(void)
{
    QSqlQuery requete(db_histo);

    QDialog fenetre(this,Qt::Window);
    fenetre.setModal(false);
    QGridLayout layout;

    QStandardItemModel modele(0, 3); //nom, date, url... 3 colonnes

    modele.setHeaderData(0,Qt::Horizontal,"Page");
    modele.setHeaderData(1,Qt::Horizontal,"Date (a-m-j)");
    modele.setHeaderData(2,Qt::Horizontal,"Url");

    QStandardItem aujourdhui(QIcon(":/icones/calendrier"),"Aujourd'hui");
    QStandardItem hier(QIcon(":/icones/calendrier"),"Hier");
    QStandardItem semaine(QIcon(":/icones/calendrier"),"7 jours");
    QStandardItem ancien(QIcon(":/icones/calendrier"),"Plus ancien");

    modele.appendRow(&aujourdhui);
    modele.appendRow(&hier);
    modele.appendRow(&semaine);
    modele.appendRow(&ancien);

    requete.prepare("Select nom, url, date, favicon from histo where 1");
    if(!requete.exec())  //si la requète à bugué...
    {
	QMessageBox::critical(this,"Erreur","Problème lors de la récupération de l'historique : "+requete.lastError().text());
	return;
    }

    int pos_nom = requete.record().indexOf("nom");
    int pos_url = requete.record().indexOf("url");
    int pos_date = requete.record().indexOf("date");
    int favicon = requete.record().indexOf("favicon");

    QString date;

    QStandardItem *tempnom = NULL;
    QStandardItem *tempdate = NULL;
    QStandardItem *tempurl = NULL;
    QPixmap * icone = NULL; //pointeur sur un pixmap
    QList<QStandardItem *> listchamp;

    QDate time;

    while(requete.next())
    {
	icone = new QPixmap;

	icone->loadFromData(requete.value(favicon).toByteArray(),"png");

	tempnom = new QStandardItem(QIcon(*icone),requete.value(pos_nom).toString());
	tempdate = new QStandardItem(requete.value(pos_date).toString());
	tempurl = new QStandardItem(requete.value(pos_url).toString());

	listchamp << tempnom << tempdate << tempurl;

	date = requete.value(pos_date).toString(); //on recupere la date encore pour placer dans la bonne période
	time.setYMD(date.mid(0,4).toInt(),date.mid(5,2).toInt(),date.mid(8,2).toInt());

	if(time == QDate::currentDate()) //c'est aujourd'hui
	    aujourdhui.appendRow(listchamp);
	else if(time.addDays(1) == QDate::currentDate())    //c'est hier
	    hier.appendRow(listchamp);
	else if(time.addDays(7) > QDate::currentDate())    //c'est ya une semaine
	    semaine.appendRow(listchamp);
	else   //c'est plus vieux que ca...
	    ancien.appendRow(listchamp);

	listchamp.clear();
    }

    QTreeView vue;
    vue.setModel(&modele);
    vue.setColumnWidth(0,200); //on preset la largeur de la colonne "nom"

    layout.addWidget(&vue,0,0);

    fenetre.setLayout(&layout);

    fenetre.resize(640,480);
    fenetre.exec();

    delete tempurl;
    delete tempnom;
    delete tempdate;
    delete icone; //destruction du pixmap... (c'est moche mais ca marche...)
}
