#ifndef SEARCHENGINEMODEL_H
#define SEARCHENGINEMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "searchengine.h"

class SearchEngineModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int rowCount READ rowCount NOTIFY rowCountChanged)
    Q_PROPERTY(int highlightIndex READ highlightIndex NOTIFY highlightIndexChanged)

public:
    explicit SearchEngineModel(SearchEngine& searchEngine, QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = ResultRole) const override;
    int highlightIndex() const;

public slots:
    void queryChanged(const QString& query);
    void incrementHighlight();
    void decrementHighlight();

signals:
    void rowCountChanged();
    void highlightIndexChanged();

private:
    QVector<int> resultIndices_;
    SearchEngine searchEngine_;
    int highlightIndex_;
    enum SearchResultRoles {
        ResultRole = Qt::UserRole+1,
        DelegateRole,
        FocusedRole
    };
};

#endif // SEARCHENGINEMODEL_H
