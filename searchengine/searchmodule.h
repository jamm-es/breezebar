#ifndef SEARCHMODULE_H
#define SEARCHMODULE_H

#include "searchindex.h"
#include <QQmlApplicationEngine>

class SearchModule
{
public:
    SearchModule();
    virtual ~SearchModule();

    virtual QString name() = 0;
    virtual void initializeIndex(SearchIndex& searchIndex) = 0;
    virtual void initializeImageProvider(QQmlApplicationEngine& engine);

protected:
    int moduleID_;

private:
    static int nextModuleID;
};

#endif // SEARCHMODULE_H
