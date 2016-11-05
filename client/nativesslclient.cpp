#include "nativesslclient.h"
#include <QDebug>
#include <QSslCertificate>


NativeClient::NativeClient(QObject *parent) : QObject(parent)
{
    connect(&_socket, SIGNAL(encrypted()), this, SLOT(onHandshaked()));
    connect(&_socket, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(onSSLError(QList<QSslError>)));
    connect(&_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onNetworkError(QAbstractSocket::SocketError)));
    connect(&_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    initSocket();
}

void NativeClient::fire(const QString &host, const int port)
{
    _socket.connectToHostEncrypted(host, port);
}

void NativeClient::initSocket()
{
    QList<QSslCertificate> ca =QSslCertificate::fromPath(":/crt/certs/ca.crt");
    _socket.setCaCertificates(ca);

    _socket.setPeerVerifyMode(QSslSocket::VerifyPeer);
    _socket.setPrivateKey(":/crt/certs/client.key");
    _socket.setLocalCertificate(":/crt/certs/client.crt");
}

void NativeClient::onSSLError(QList<QSslError> err)
{
    qDebug() << "SSL" << err;
    _socket.close();
    emit sslErrorSignal();
}

void NativeClient::onHandshaked()
{
    qDebug() << "good";
    _socket.write("Test transfer data!!!");

}

void NativeClient::onNetworkError(QAbstractSocket::SocketError err)
{
    qDebug() << "Network error" << err;
    _socket.close();
}

void NativeClient::onReadyRead()
{
    QByteArray serverData =_socket.readAll();

    qDebug() << "Server say" << serverData;
    _socket.close();
    emit successAnswerSignal(QString(serverData));
}
