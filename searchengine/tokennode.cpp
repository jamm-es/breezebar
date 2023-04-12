#include "tokennode.h"

TokenNode::TokenNode()
{

}

TokenNode* TokenNode::addChild(const QString& token)
{
    TokenNode* newNode = new TokenNode;
    children_.insert(token, newNode);
    return newNode;
}

TokenNode* TokenNode::getChild(const QString& token)
{
    auto it = children_.find(token);
    if(it == children_.end()) {
        return nullptr;
    }
    return it.value();
}

QVector<SearchResult*> TokenNode::results() const
{
    return results_;
}

void TokenNode::addResult(SearchResult* result)
{
    results_.append(result);
}
