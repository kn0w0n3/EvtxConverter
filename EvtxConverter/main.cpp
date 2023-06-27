#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QQmlContext>

#include "maincontroller.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    MainController mainController;
    engine.rootContext()->setContextProperty("mainController", &mainController);

    const QUrl url(u"qrc:/EvtxConverter/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);
    app.setWindowIcon(QIcon("C:/EvtxConverter/images/appiconx.png"));
    return app.exec();
}
