#include "searchindex.h"
#include <QStack>

SearchIndex::SearchIndex() :
    indexRoot_(new SearchNode)
{

}

SearchIndex::~SearchIndex()
{
    for(SearchResult* result : results_) {
        delete result;
    }
    QStack<SearchNode*> toDeallocate;
    toDeallocate.push(indexRoot_);
    while(!toDeallocate.isEmpty()) {
        SearchNode* curr = toDeallocate.pop();
        QHashIterator<QChar, SearchNode*> it(curr->children());
        while(it.hasNext()) {
            it.next();
            toDeallocate.push(it.value());
        }
        delete curr;
    }
}

// splits searchTerm into smaller tokens and starts from each word
// ie, "foo bar" results in indexes for "foo bar" and "bar"
void SearchIndex::addResult(const QString& searchTerm, SearchResult* result)
{
    // add result
    int index = results_.size();
    results_.append(result);

    // build single search terms by adding tokens to the front, starting from backmost letter
    QString sanitizedSearchTerm = sanitizeQuery(searchTerm);
    QStringList tokens = sanitizedSearchTerm.split(' ');
    QString current;
    for(int i = tokens.size()-1; i >= 0; --i) {
        current = tokens.at(i) + ' ' + current;
        addSingleResult(current, result, index);
    }
}

// singleSearchTerm is assumed to already be sanitized
// index=-1 means result needs to be appended
void SearchIndex::addSingleResult(const QString& singleSearchTerm, SearchResult* result, int index)
{
    // add result to results_ if index is not properly set
    if(index == -1) {
        index = results_.size();
        results_.append(result);
    }

    // traverse index tree and add result to node
    TrieNode* currNode = trieRoot_;
    TrieNode* prevNode = nullptr;
    for(const QChar letter : singleSearchTerm) {
        prevNode = currNode;
        currNode = currNode->getChild(letter);

        // if the letter isn't a child yet, add it
        if(currNode == nullptr) {
            currNode = prevNode->addChild(letter);
        }
    }
    currNode->addResultIndex(index);
}

QVector<int> SearchIndex::search(const QString& query) const
{
    QString sanitizedQuery = sanitizeQuery(query);

    SearchNode* curr = indexRoot_;
    QVector<int> results;

    // special case - empty query means no results
    if(query.size() == 0) {
        return results;
    }

    for(const QChar letter : query.toLower()) {
        curr = curr->childAt(letter);

        // return empty results if we can't find anything in the tree along this part of the query
        if(curr == nullptr) {
            return results;
        }
    }
    QStack<SearchNode*> toTraverse;
    toTraverse.push(curr);
    while(!toTraverse.isEmpty()) {
        SearchNode* current = toTraverse.pop();
        results.append(current->resultIndices());
        if(results.size() >= maxResults_) {
            results.resize(maxResults_);
            results.squeeze();
            return results;
        }
        QHashIterator<QChar, SearchNode*> it(current->children());
        while(it.hasNext()) {
            it.next();
            toTraverse.push(it.value());
        }
    }
    return results;
}

SearchResult* SearchIndex::resultAt(int index) const
{
    return results_.at(index);
}

QString SearchIndex::sanitizeQuery(const QString& query)
{
    QString output = query.toLower();
    for(int i = 0; i < output.size(); ++i) {
        if(!output.at(i).isLetterOrNumber()) {
            output[i] = QChar(' ');
        }
    }
    return output.simplified();
}

const int SearchIndex::maxResults_ = 10;
