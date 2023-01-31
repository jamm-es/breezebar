#include "searchmodule.h"

SearchModule::SearchModule() :
    moduleID_(nextModuleID++)
{

}

void SearchModule::initializeImageProvider(QQmlApplicationEngine& engine)
{
    // by default, does nothing - children module should reimplement to register an image provider
}

SearchModule::~SearchModule()
{

}

int SearchModule::nextModuleID = 0;
