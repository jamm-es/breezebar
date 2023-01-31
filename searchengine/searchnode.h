#ifndef SEARCHNODE_H
#define SEARCHNODE_H

#include <QChar>
#include <QHash>
#include <QVector>

class SearchNode
{
public:
    SearchNode(); // construct the root node
    SearchNode(QChar letter); // construct a child node
    QHash<QChar, SearchNode*> children() const;
    SearchNode* childAt(const QChar letter) const; // returns nullptr if not found
    QVector<int> resultIndices() const;
    SearchNode* addChild(const QChar childChar); // returns the new child node
    void addResultIndex(int resultIndex);

private:
    QChar letter_;
    QHash<QChar, SearchNode*> children_;
    QVector<int> resultIndices_; // corresponds to indices of results_ in searchEngine
};

#endif // SEARCHNODE_H
