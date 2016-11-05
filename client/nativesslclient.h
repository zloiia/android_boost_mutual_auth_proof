#ifndef NATIVECLIENT_H
#define NATIVECLIENT_H

#include <QObject>
#include <QSslSocket>
#include <QSslError>


class NativeClient : public QObject
{
    Q_OBJECT
public:
    explicit NativeClient(QObject *parent = 0);
    Q_INVOKABLE void fire(const QString &host, const int port);

signals:
    void successAnswerSignal(const QString &serverAnswer);
    void networkErrorSignal();
    void sslErrorSignal();

protected:
    void initSocket();

private slots:
    void onSSLError(QList<QSslError> err);
    void onHandshaked();
    void onNetworkError(QAbstractSocket::SocketError err);
    void onReadyRead();

private:
    QSslSocket _socket;

};

#endif // NATIVECLIENT_H
