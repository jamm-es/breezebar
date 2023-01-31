#include "applicationmodule.h"

ApplicationModule::ApplicationModule()
{

}

QString ApplicationModule::name()
{
    return "Application";
}

void ApplicationModule::initializeImageProvider(QQmlApplicationEngine& engine)
{
    engine.addImageProvider("application", &imageProvider_);
}
