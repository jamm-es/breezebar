#ifndef SEARCHRESULT_H
#define SEARCHRESULT_H

#include <QObject>

class SearchResult : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString delegate READ delegate CONSTANT)
    Q_PROPERTY(QString title READ title CONSTANT)
    Q_PROPERTY(QString context READ context CONSTANT)
    Q_PROPERTY(QString imagePath READ imagePath CONSTANT)

public:
    explicit SearchResult(QObject *parent = nullptr);
    SearchResult(QString title, QString context, QObject *parent = nullptr);

    virtual QString delegate() const = 0;
    QString title() const;
    QString context() const;
    virtual QString imagePath() const = 0;

protected:
    int moduleID_;
    QString title_;
    QString context_;
};

Q_DECLARE_METATYPE(SearchResult)

#endif // SEARCHRESULT_H
