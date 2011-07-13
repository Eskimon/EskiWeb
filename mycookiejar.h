#ifndef MYCOOKIEJAR_H
#define MYCOOKIEJAR_H

#include <QNetworkCookieJar>
#include <QtGui>


class MyCookieJar : public QNetworkCookieJar
{
    Q_OBJECT
    public:
	MyCookieJar(QObject *parent=0);
	~MyCookieJar();
	QList<QNetworkCookie> cookiesForUrl ( const QUrl & url ) const;
	bool setCookiesFromUrl ( const QList<QNetworkCookie> & cookieList, const QUrl & url );

    signals:

    public slots:

};

#endif // MYCOOKIEJAR_H
