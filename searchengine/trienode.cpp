#include "trienode.h"

TrieNode::TrieNode()
{

}

TrieNode* TrieNode::addChild(const QChar letter)
{
    TrieNode* newNode = new TrieNode;
    children_.insert(letter, newNode);
    return newNode;
}

TrieNode* TrieNode::getChild(const QChar letter)
{
    auto it = children_.find(letter);
    if(it == children_.end()) {
        return nullptr;
    }
    return it.value();
}

QVector<TokenNode*> TrieNode::tokens() const
{
    return tokens_;
}

void TrieNode::addToken(TokenNode* token)
{
    tokens_.append(token);
}
