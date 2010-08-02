#ifndef ZHTMLLISTMODEL_H
#define ZHTMLLISTMODEL_H

#define ZHTML_LIST_DEFAULT_MATCH_RX             "(?:<a[^>]*href)=[\"']([^\"']*)[\"']"
#define ZHTML_LIST_DEFAULT_EXCLD_RX             "^([\?&].*|/|\\.\\./?|\\./?)$"

#include <QtCore>
#include <QtNetwork>

class ZHTMLListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    ZHTMLListModel(QObject *parent=0);
    ZHTMLListModel(QUrl base, QObject *parent=0);
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section,Qt::Orientation orientation,int role) const;

signals:
    void downloadStarted();
    void downloadProgress(qreal);
    void downloadFinished();
    void authenticationRequired();
    void authenticationError();

public slots:
    void setBaseUrl(QUrl base);
    void setMatchExpression(QRegExp rx);
    void setMatchExpression(QString rx);
    void setExcludeExpression(QRegExp rx);
    void setExcludeExpression(QString rx);
    void fetchBase();
    void authenticate(QString username, QString password);

private slots:
    void _finished(QNetworkReply *r);
    void _authenticationRequired(QNetworkReply *r, QAuthenticator *auth);
    void _downloadProgress(qint64 in, qint64 total);

private:
    void init();
    void _processReplyData(QString data);

private:
    QStringList _data;
    QHash<QString,QString> _labels;
    QHash<QString,QString> _cache; // turbo-retarded caching for morons
    QUrl _base;
    QRegExp _matchRx;
    QRegExp _excludeRx;
    QNetworkAccessManager _net;
};

#endif // ZHTMLLISTMODEL_H
