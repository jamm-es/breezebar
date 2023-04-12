#include "searchengine.h"
#include <QStack>
#include <QDebug>

SearchEngine::SearchEngine(std::initializer_list<SearchModule*> modules, QQmlApplicationEngine& qmlEngine) :
    modules_(modules)
{
    for(auto& module : modules_) {
        module->initializeIndex(index_);
        module->initializeImageProvider(qmlEngine);
    }
}

SearchEngine::~SearchEngine()
{
    for(const SearchModule* module : modules_) {
        delete module;
    }
}

SearchResult* SearchEngine::resultAt(int index) const
{
    return index_.resultAt(index);
}

QVector<int> SearchEngine::search(const QString& query) const
{
    return index_.search(query);
}

