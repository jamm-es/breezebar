#include "searchnode.h"

SearchNode::SearchNode()
{

}

SearchNode::SearchNode(QChar letter) :
    letter_(letter)
{

}

QHash<QChar, SearchNode*> SearchNode::children() const
{
    return children_;
}

SearchNode* SearchNode::childAt(const QChar letter) const
{
    auto childIter = children_.find(letter);
    if(childIter == children_.end()) {
        return nullptr;
    }
    return childIter.value();
}

QVector<int> SearchNode::resultIndices() const
{
    return resultIndices_;
}

SearchNode* SearchNode::addChild(const QChar childChar)
{
    SearchNode* newNode = new SearchNode(childChar);
    children_.insert(childChar, newNode);
    return newNode;
}

void SearchNode::addResultIndex(int resultIndex)
{
    resultIndices_.append(resultIndex);
}
