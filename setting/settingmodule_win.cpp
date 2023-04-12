#include "settingmodule.h"
#include <QFile>
#include <QTextStream>
#include "settingresult.h"
#include "settingimageprovider.h"

void SettingModule::initializeIndex(SearchIndex& searchIndex) {

    QString filePath(":/breezebar/setting/settings_base.csv");

    // load settings from file
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file while initializing settings:" << filePath;
        return;
    }

    QTextStream csvStream(&file);
    QString line = csvStream.readLine();
    while(!line.isNull()) {
        // split into category, name, uri, icon name
        QStringList lineParts = line.split(',');

        QString searchTerm = lineParts.at(0) + ' ' + lineParts.at(1);
        SearchResult* result = new SettingResult(lineParts[1], lineParts[0], lineParts[2], lineParts[3]);

        searchIndex.addResult(searchTerm, result);

        line = csvStream.readLine();
    }
}

void SettingModule::initializeImageProvider(QQmlApplicationEngine& engine)
{
    engine.addImageProvider("setting", &imageProvider_);
}
