#ifndef SETTINGRESULT_H
#define SETTINGRESULT_H

#include <searchresult.h>

class SettingResult : public SearchResult
{
    Q_OBJECT
public:
    explicit SettingResult(QObject *parent = nullptr);
    SettingResult(const QString& title, const QString& context, const QString& uri, const QString& iconName, QObject *parent = nullptr);

    virtual QString delegate() const override;
    virtual QString imagePath() const override;
    Q_INVOKABLE void open() const;

private:
    QString uri_;
    QString iconName_;
};

Q_DECLARE_METATYPE(SettingResult)

#endif // SETTINGRESULT_H
