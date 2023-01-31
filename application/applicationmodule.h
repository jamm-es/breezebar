#ifndef APPLICATIONMODULE_H
#define APPLICATIONMODULE_H

#include "searchmodule.h"
#include "applicationimageprovider.h"

class ApplicationModule : public SearchModule
{
public:
    ApplicationModule();

    virtual QString name() override;
    virtual void initializeIndex(SearchIndex& searchIndex) override;
    virtual void initializeImageProvider(QQmlApplicationEngine& engine) override;

private:
    ApplicationImageProvider imageProvider_;
};

#endif // APPLICATIONMODULE_H
