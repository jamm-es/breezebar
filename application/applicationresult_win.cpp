#include "applicationresult.h"
#include <windows.h>
#include <QDir>

void ApplicationResult::run() const
{
    QString home = QDir::homePath();
    ShellExecuteW(NULL, NULL, context_.toStdWString().c_str(), NULL, home.toStdWString().c_str(), SW_SHOWNORMAL);
}

void ApplicationResult::runPrivileged() const
{
    QString home = QDir::homePath();
    ShellExecuteW(NULL, L"runas", context_.toStdWString().c_str(), NULL, home.toStdWString().c_str(), SW_SHOWNORMAL);
}
