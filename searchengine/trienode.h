#ifndef TRIENODE_H
#define TRIENODE_H

#include <QHash>
#include <QChar>
#include <QVector>
#include "tokennode.h"

class TrieNode
{
public:
    TrieNode();
    TrieNode* addChild(const QChar letter); // returns pointer to new child
    TrieNode* getChild(const QChar letter);
    QVector<TokenNode*> tokens() const;
    void addToken(TokenNode* token);

private:
    QHash<QChar, TrieNode*> children_;
    QVector<TokenNode*> tokens_;
};

#endif // TRIENODE_H
