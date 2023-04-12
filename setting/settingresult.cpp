#include "settingresult.h"

SettingResult::SettingResult(QObject *parent) :
    SearchResult{parent}
{

}

SettingResult::SettingResult(const QString& title, const QString& context, const QString& uri, const QString& iconName, QObject* parent) :
    SearchResult(title, context, parent),
    uri_(uri),
    iconName_(iconName)
{

}

QString SettingResult::delegate() const
{
    return "setting";
}

QString SettingResult::imagePath() const
{
    return u"image://setting/%1"_qs.arg(iconName_);
}

