#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>

#include "dchat_client_app.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    drift::ChatClientApp chat_app("tcp://127.0.0.1:5566");
//    drift::ChatClientApp chat_app("ipc:///tmp/dchat_service");

    engine.rootContext()->setContextProperty("chat_app", &chat_app);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
