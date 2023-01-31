#include <QQmlEngine>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QHotkey>
#include "searchengine.h"
#include "searchenginemodel.h"
#include "applicationmodule.h"
#include "settingmodule.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    SearchEngine searchEngine({
        new ApplicationModule,
        new SettingModule
    }, engine);

    const QUrl url(u"qrc:/breezebar/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    SearchEngineModel searchEngineModel(searchEngine);
    QQmlContext* context = engine.rootContext();
    context->setContextProperty("searchEngineModel_", &searchEngineModel);

    // setup hotkey to show bar
    QHotkey hotkey(QKeySequence("Ctrl+Alt+Space"), true, &app);
    context->setContextProperty("hotkey_", &hotkey);

    engine.load(url);

    return app.exec();
}
