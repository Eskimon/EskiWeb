#include "mycookiejar.h"

// Constructeur charge les cookies
MyCookieJar::MyCookieJar(QObject *parent) :QNetworkCookieJar(parent)
{
    QFile cookieFile(qApp->applicationDirPath() + "/cache/cookies.txt");
    if (cookieFile.exists() && cookieFile.open(QIODevice::ReadOnly) )
    {
	QList<QNetworkCookie> list;
	QByteArray line;
	while(!(line = cookieFile.readLine()).isNull())
	{
	    list.append(QNetworkCookie::parseCookies(line));
	}
	setAllCookies(list);
    }
}

// Destructeur, sauve les cookies
MyCookieJar::~MyCookieJar()
{
    QFile cookieFile(qApp->applicationDirPath() + "/cache/cookies.txt");
    if (cookieFile.open(QIODevice::WriteOnly) )
    {
	QTextStream out(&cookieFile);
	foreach(const QNetworkCookie & cookie, allCookies())
	{
	    if (!cookie.isSessionCookie())
		out << cookie.toRawForm() << endl;
	}
    }
}


QList<QNetworkCookie> MyCookieJar::cookiesForUrl ( const QUrl & url ) const
{
    //qDebug() << "Getting cookie for" << url;
    return QNetworkCookieJar::cookiesForUrl(url);
}

bool MyCookieJar::setCookiesFromUrl ( const QList<QNetworkCookie> & cookieList, const QUrl & url )
{
    //qDebug() << "Setting cookie for" << url;
    return QNetworkCookieJar::setCookiesFromUrl(cookieList, url);
}
