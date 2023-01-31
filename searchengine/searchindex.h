#ifndef SEARCHINDEX_H
#define SEARCHINDEX_H

#include <QString>
#include <QVector>
#include "searchresult.h"
#include "searchnode.h"

class SearchIndex
{
public:
    SearchIndex();
    ~SearchIndex();

    void addResult(const QString& searchTerm, SearchResult* result);
    void addSingleResult(const QString& singleSearchTerm, SearchResult* result, int index=-1);
    QVector<int> search(const QString& query) const;
    SearchResult* resultAt(int index) const;

    static QString sanitizeQuery(const QString& query);

private:
    SearchNode* indexRoot_;
    QVector<SearchResult*> results_;
    static const int maxResults_;
};

#endif // SEARCHINDEX_H
