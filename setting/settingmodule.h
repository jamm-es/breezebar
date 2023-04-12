#ifndef SETTINGMODULE_H
#define SETTINGMODULE_H

#include "searchmodule.h"
#include "settingimageprovider.h"

class SettingModule : public SearchModule
{
public:
    SettingModule();

    virtual QString name() override;
    virtual void initializeIndex(SearchIndex& searchIndex) override;
    virtual void initializeImageProvider(QQmlApplicationEngine& engine) override;

private:
    SettingImageProvider imageProvider_;
};

#endif // SETTINGMODULE_H
