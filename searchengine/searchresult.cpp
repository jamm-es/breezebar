#include "searchresult.h"

SearchResult::SearchResult(QObject *parent)
    : QObject{parent}
{

}

SearchResult::SearchResult(QString title, QString context, QObject* parent) :
    QObject(parent),
    title_(title),
    context_(context)
{

}

QString SearchResult::title() const
{
    return title_;
}

QString SearchResult::context() const
{
    return context_;
}
