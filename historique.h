#ifndef HISTORIQUE_H
#define HISTORIQUE_H

#include <QtGui>
#include <QtSql>
#include <QtWebKit>

class Historique : public QWidget
{
    Q_OBJECT

    public slots:
	void afficher(void);

    public:
	Historique(QWidget *parent = 0);
	~Historique(void);
	void add(QWebHistoryItem item);

    signals:

    private:
	QSqlDatabase db_histo;
	void creer(void);
};

#endif // HISTORIQUE_H
