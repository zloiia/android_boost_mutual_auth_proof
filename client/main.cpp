#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "nativesslclient.h"
#include <QQmlContext>
#include <QQmlEngine>


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    //NativeClient client;

    QQmlApplicationEngine engine;
    qmlRegisterType<NativeClient>("testclient", 1, 0, "Socket");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    return app.exec();
}
