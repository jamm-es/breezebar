#include "applicationmodule.h"
#include <QStringList>
#include <QDir>
#include <QDirIterator>
#include <QImage>
#include <windows.h>
#include <commctrl.h>
#include "applicationresult.h"

void ApplicationModule::initializeIndex(SearchIndex& searchIndex)
{
    // generate list of start menu paths to search
    QStringList pathsToSearch = {
        R"(C:\ProgramData\Microsoft\Windows\Start Menu)", // system overall path
    };
    QDir homeStartMenu = QDir::home();
    homeStartMenu.cd(R"(AppData\Roaming\Microsoft\Windows\Start Menu)");
    pathsToSearch.append(homeStartMenu.absolutePath()); // add user specific path

    CoInitializeEx(NULL, COINIT_MULTITHREADED);

    int numLoaded = 0;

    // index shortcuts in each path
    for(const QString& pathToSearch : pathsToSearch) {
        // iterate through files recursively
        QDirIterator it(pathToSearch, QDir::NoDotAndDotDot | QDir::Files | QDir::System, QDirIterator::Subdirectories);
        while(it.hasNext()) {
            QFileInfo info = it.nextFileInfo();

            if(info.suffix() != "lnk" && info.suffix() != "url") {
                continue;
            }

            QString name = info.completeBaseName();
            QString path = QDir::toNativeSeparators(info.absoluteFilePath());

            // get icon
            SHFILEINFOW fileInfo = {0};
            HIMAGELIST systemImageList = (HIMAGELIST) SHGetFileInfoW(path.toStdWString().c_str(), 0, &fileInfo, sizeof(fileInfo), SHGFI_SYSICONINDEX | SHGFI_LARGEICON);
            HICON iconHandle = ImageList_GetIcon(systemImageList, fileInfo.iIcon, 0);
//            SHGetFileInfoW(path.toStdWString().c_str(), 0, &fileInfo, sizeof(fileInfo), SHGFI_ICONLOCATION);
//            HINSTANCE instance = GetModuleHandle(NULL);
//            HICON iconHandle = ExtractIconW(instance, fileInfo.szDisplayName, 0);

            QImage icon = QImage::fromHICON(iconHandle);
            DestroyIcon(iconHandle);
            int imageIndex = imageProvider_.addImage(icon);

            SearchResult* result = new ApplicationResult(name, path, imageIndex);
            searchIndex.addResult(info.completeBaseName().toLower(), result);

            ++numLoaded;
        }
    }

    qDebug() << "Application index loaded:" << numLoaded << "entries";

    CoUninitialize();
}

