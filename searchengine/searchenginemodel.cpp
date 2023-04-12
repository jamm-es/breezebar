#include "searchenginemodel.h"
#include <QDebug>
#include "applicationresult.h"

SearchEngineModel::SearchEngineModel(SearchEngine& searchEngine, QObject* parent) :
    QAbstractListModel(parent),
    searchEngine_(searchEngine),
    highlightIndex_(0)
{

}

QHash<int, QByteArray> SearchEngineModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ResultRole] = "result";
    roles[DelegateRole] = "delegate";
    roles[FocusedRole] = "focused";
    return roles;
}

int SearchEngineModel::rowCount(const QModelIndex &parent) const
{
    return resultIndices_.size();
}

QVariant SearchEngineModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() >= resultIndices_.size()) {
        return QVariant();
    }
    SearchResult* result = searchEngine_.resultAt(resultIndices_.at(index.row()));
    QString delegate = result->delegate();
    switch(role) {
        case ResultRole:
            if(delegate == "application") {
                return QVariant::fromValue<ApplicationResult*>(qobject_cast<ApplicationResult*>(result));
            }
            else {
                return QVariant::fromValue<SearchResult*>(result);
            }
        case FocusedRole:
            return index.row() == highlightIndex_;
        case DelegateRole:
            return index.row() == highlightIndex_ ? result->delegate() : "default";
        default:
            return QVariant();
    }
}

void SearchEngineModel::queryChanged(const QString& query)
{
    QVector<int> newResultIndices = searchEngine_.search(query);

    // check if we can get away with not updating anything, if search results don't chnage
    if(resultIndices_.size() == newResultIndices.size()) {
        bool isUpdateUnnecessary = true;
        for(int i = 0; i < resultIndices_.size(); ++i) {
            if(resultIndices_.at(i) != newResultIndices.at(i)) {
                isUpdateUnnecessary = false;
                break;
            }
        }
        if(isUpdateUnnecessary) return;
    }

    emit layoutAboutToBeChanged();

    highlightIndex_ = 0;
    resultIndices_ = searchEngine_.search(query);
    QModelIndexList newModelIndices(resultIndices_.size());
    for(int i = 0; i < resultIndices_.size(); ++i) {
        newModelIndices.replace(i, createIndex(resultIndices_.at(i), 0));
    }
    changePersistentIndexList(persistentIndexList(), newModelIndices);

    emit layoutChanged();
    emit rowCountChanged();
}

void SearchEngineModel::incrementHighlight()
{

    if(highlightIndex_ < resultIndices_.size()-1) {
//        ++highlightIndex_;
//        QModelIndex oldHighlightedIndex = createIndex(highlightIndex_-1, 0);
//        QModelIndex newHighlightedIndex = createIndex(highlightIndex_, 0);
//        QList<QPersistentModelIndex> changedIndices({oldHighlightedIndex, newHighlightedIndex});
//        emit layoutAboutToBeChanged(changedIndices);
//        emit dataChanged(oldHighlightedIndex, newHighlightedIndex, {FocusedRole, DelegateRole});
//        qDebug() << "HELLO2" << highlightIndex_;
//        emit highlightIndexChanged();
//        emit layoutChanged(changedIndices);
//        emit layoutAboutToBeChanged();
        ++highlightIndex_;
        emit dataChanged(createIndex(highlightIndex_-1, 0), createIndex(highlightIndex_, 0), {FocusedRole, DelegateRole});
        emit highlightIndexChanged();
//        emit layoutChanged();
    }

}

void SearchEngineModel::decrementHighlight()
{
    if(highlightIndex_ > 0) {
//        --highlightIndex_;
//        QModelIndex oldHighlightedIndex = createIndex(highlightIndex_+1, 0);
//        QModelIndex newHighlightedIndex = createIndex(highlightIndex_, 0);
//        QList<QPersistentModelIndex> changedIndices({oldHighlightedIndex, newHighlightedIndex});
//        emit layoutAboutToBeChanged(changedIndices);
//        emit dataChanged(newHighlightedIndex, oldHighlightedIndex, {FocusedRole, DelegateRole});
//        qDebug() << "HELLO?";
//        emit highlightIndexChanged();
//        emit layoutChanged(changedIndices);
//        emit layoutAboutToBeChanged();
        --highlightIndex_;
        emit dataChanged(createIndex(highlightIndex_, 0), createIndex(highlightIndex_+1, 0), {FocusedRole, DelegateRole});
        emit highlightIndexChanged();
//        emit layoutChanged();
    }
}

int SearchEngineModel::highlightIndex() const
{
    return highlightIndex_;
}
