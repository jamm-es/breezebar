#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include <QQmlApplicationEngine>
#include "searchresult.h"
#include "searchindex.h"
#include "searchmodule.h"

class SearchEngine
{
public:
    SearchEngine(std::initializer_list<SearchModule*> modules, QQmlApplicationEngine& qmlEngine);
    ~SearchEngine();

    SearchResult* resultAt(int index) const; // index must be valid
    QVector<int> search(const QString& query) const;

private:
    QVector<SearchModule*> modules_;
    SearchIndex index_;
};

#endif // SEARCHENGINE_H
