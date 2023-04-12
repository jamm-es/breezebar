#ifndef TOKENNODE_H
#define TOKENNODE_H

#include <QVector>
#include <QString>
#include <QHash>
#include "searchresult.h"

class TokenNode
{
public:
    TokenNode();
    TokenNode* addChild(const QString& token); // returns pointer to new node
    TokenNode* getChild(const QString& token);
    QVector<SearchResult*> results() const;
    void addResult(SearchResult* result);

private:
    QHash<QString, TokenNode*> children_;
    QVector<SearchResult*> results_;
};

#endif // TOKENNODE_H
