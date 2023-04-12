#include "applicationresult.h"
#include <QProcess>
#include <QDebug>

ApplicationResult::ApplicationResult(const QString& title, const QString& context, int imageIndex, QObject* parent) :
    SearchResult(title, context, parent),
    imageIndex_(imageIndex)
{

}

QString ApplicationResult::delegate() const
{
    return "application";
}

QString ApplicationResult::imagePath() const
{
    return u"image://application/%1"_qs.arg(imageIndex_);
}
