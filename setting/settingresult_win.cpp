#include "settingresult.h"
#include <windows.h>

void SettingResult::open() const
{
    ShellExecuteW(NULL, NULL, uri_.toStdWString().c_str(), NULL, NULL, SW_SHOWNORMAL);
}
