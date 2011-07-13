#ifndef FAVORIS_H
#define FAVORIS_H

#include <QtGui>
#include <QtSql>

struct TFavoris
{
    QString nom;
    QString url;
    QIcon favicon;
    QString path;
};

//-------------------------------------------------------------------------------------------------

class Favoris : public QWidget
{
    Q_OBJECT

    public slots:
	void afficher(void);

    public:
	Favoris(QWidget *parent = 0);
	~Favoris(void);
	bool add(TFavoris * fav);
	void get_barre(QList<TFavoris> * fav);

    signals:

    private:
	QSqlDatabase db_fav;
	void creer(void);
};

#endif // FAVORIS_H
