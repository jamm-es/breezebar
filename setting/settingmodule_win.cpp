#include "settingmodule.h"
#include <QFile>
#include <QTextStream>

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
        QStringList lineParts = line.split(',');

        qDebug() << lineParts[0] << lineParts[1] << lineParts[2];

        line = csvStream.readLine();
    }
}
